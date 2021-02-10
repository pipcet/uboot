// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Mark Kettenis <kettenis@openbsd.org>
 */

#include <common.h>
#include <dm.h>
#include <mailbox-uclass.h>
#include <asm/io.h>
#include <linux/delay.h>

#define REG_CPU_CTRL	0x0044
#define REG_A2I_STAT	0x8110
#define  REG_A2I_STAT_EMPTY	BIT(17)
#define  REG_A2I_STAT_FULL	BIT(16)
#define REG_I2A_STAT	0x8114
#define  REG_I2A_STAT_EMPTY	BIT(17)
#define  REG_I2A_STAT_FULL	BIT(16)
#define REG_A2I_MSG0	0x8800
#define REG_A2I_MSG1	0x8808
#define REG_I2A_MSG0	0x8830
#define REG_I2A_MSG1	0x8838

struct apple_mbox_priv {
	void *base;
};

static void apple_mbox_wait(struct apple_mbox_priv *priv)
{
	while (readl(priv->base + REG_A2I_STAT) & REG_A2I_STAT_FULL)
		udelay(1);

	while (readl(priv->base + REG_I2A_STAT) & REG_I2A_STAT_EMPTY)
		udelay(1);
}

static int apple_mbox_send(struct mbox_chan *chan, const void *data)
{
	struct apple_mbox_priv *priv = dev_get_priv(chan->dev);
	const u64 *msg = data;

	writeq(msg[0], priv->base + REG_A2I_MSG0);
	writeq((msg[1] & ~0xffULL) | chan->id, priv->base + REG_A2I_MSG1);
	while (readl(priv->base + REG_A2I_STAT) & REG_A2I_STAT_FULL)
		udelay(1);

	return 0;
}

static int apple_mbox_recv(struct mbox_chan *chan, void *data)
{
	struct apple_mbox_priv *priv = dev_get_priv(chan->dev);
	u64 *msg = data;

retry:
	while (readl(priv->base + REG_I2A_STAT) & REG_I2A_STAT_EMPTY)
		udelay(1);

	msg[0] = readq(priv->base + REG_I2A_MSG0);
	msg[1] = readq(priv->base + REG_I2A_MSG1);

	if ((msg[1] & 0xffULL) != chan->id)
		goto retry;

	return 0;
}

struct mbox_ops apple_mbox_ops = {
	.send = apple_mbox_send,
	.recv = apple_mbox_recv,
};

static int apple_mbox_probe(struct udevice *dev)
{
	struct apple_mbox_priv *priv = dev_get_priv(dev);
	u64 msg[2];
	int endpoint;
	int endpoints[256];
	int nendpoints = 0;
	int msgtype;
	u64 subtype;
	int i;

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	/* EP0_IDLE */
	writeq(0x0060000000000220, priv->base + REG_A2I_MSG0);
	writeq(0x0000000000000000, priv->base + REG_A2I_MSG1);

	/* EP0_WAIT_HELLO */
	apple_mbox_wait(priv);
	msg[0] = readq(priv->base + REG_I2A_MSG0);
	msg[1] = readq(priv->base + REG_I2A_MSG1);

	endpoint = msg[1] & 0xff;
	msgtype = (msg[0] >> 52) & 0xff;
	if (endpoint != 0) {
		printf("%s: unexpected endpoint %d\n", __func__, endpoint);
		return -EINVAL;
	}
	if (msgtype != 1) {
		printf("%s: unexpected message type %d\n", __func__, msgtype);
		return -EINVAL;
	}

	/* EP0_SEND_HELLO */
	subtype = msg[0] & 0xffffffff;
	writeq(0x0020000100000000 | subtype , priv->base + REG_A2I_MSG0);
	writeq(0x0000000000000000, priv->base + REG_A2I_MSG1);

wait_epmap:
	/* EP0_WAIT_EPMAP */
	apple_mbox_wait(priv);
	msg[0] = readq(priv->base + REG_I2A_MSG0);
	msg[1] = readq(priv->base + REG_I2A_MSG1);

	endpoint = msg[1] & 0xff;
	msgtype = (msg[0] >> 52) & 0xff;
	if (endpoint != 0) {
		printf("%s: unexpected endpoint %d\n", __func__, endpoint);
		return -EINVAL;
	}
	if (msgtype != 8) {
		printf("%s: unexpected message type %d\n", __func__, msgtype);
		return -EINVAL;
	}

	for (i = 0; i < 32; i++) {
		if (msg[0] & (1U << i)) {
			endpoint = i + 32 * ((msg[0] >> 32) & 7);
			endpoints[nendpoints++] = endpoint;
		}
	}

	/* EP0_SEND_EPACK */
	subtype = (msg[0] >> 32) & 0x80007;
	writeq(0x0080000000000000 | (subtype << 32) | !(subtype & 7), priv->base + REG_A2I_MSG0);
	writeq(0x0000000000000000, priv->base + REG_A2I_MSG1);

	if ((subtype & 0x80000) == 0)
		goto wait_epmap;

	for (i = 0; i < nendpoints; i++) {
		while (readl(priv->base + REG_A2I_STAT) & REG_A2I_STAT_FULL)
			udelay(1);

		/* EP0_SEND_EPSTART */
		subtype = endpoints[i];
		writeq(0x0050000000000002 | (subtype << 32), priv->base + REG_A2I_MSG0);
		writeq(0x0000000000000000, priv->base + REG_A2I_MSG1);
	}

	/* EP0_WAIT_PWROK (discard) */
	apple_mbox_wait(priv);
	msg[0] = readq(priv->base + REG_I2A_MSG0);
	msg[1] = readq(priv->base + REG_I2A_MSG1);

	/* EP0_WAIT_PWROK */
	apple_mbox_wait(priv);
	msg[0] = readq(priv->base + REG_I2A_MSG0);
	msg[1] = readq(priv->base + REG_I2A_MSG1);

	endpoint = msg[1] & 0xff;
	msgtype = (msg[0] >> 52) & 0xff;
	if (endpoint != 0) {
		printf("%s: unexpected endpoint %d\n", __func__, endpoint);
		return -EINVAL;
	}
	if (msgtype != 7) {
		printf("%s: unexpected message type %d\n", __func__, msgtype);
		return -EINVAL;
	}

	/* EP0_SEND_PWRACK */
	subtype = msg[0] & 0xffffffff;
	writeq(0x00b0000000000000 | subtype , priv->base + REG_A2I_MSG0);
	writeq(0x0000000000000000, priv->base + REG_A2I_MSG1);

	return 0;
}

static const struct udevice_id apple_mbox_of_match[] = {
	{ .compatible = "apple,iop-mailbox-m1" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(apple_mbox) = {
	.name = "apple-mbox",
	.id = UCLASS_MAILBOX,
	.of_match = apple_mbox_of_match,
	.probe = apple_mbox_probe,
	.priv_auto = sizeof(struct apple_mbox_priv),
	.ops = &apple_mbox_ops,
};
