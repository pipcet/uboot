// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Mark Kettenis <kettenis@openbsd.org>
 */

#include <common.h>
#include <asm/io.h>
#include <clk-uclass.h>
#include <dm.h>

#define CLK_ENABLE	(0xf << 0)
#define CLK_LOCKED	(0xf << 4)
#define CLK_RUN		(1 << 28)

struct apple_clk_priv {
	struct clk_bulk parents;
	void *base;
};

static int apple_clk_enable(struct clk *clk)
{
	struct apple_clk_priv *priv = dev_get_priv(clk->dev);

	clk_enable_bulk(&priv->parents);

	writel(readl(priv->base) | CLK_ENABLE, priv->base);
	while ((readl(priv->base) & CLK_LOCKED) != CLK_LOCKED)
		;

	writel(readl(priv->base) | CLK_RUN, priv->base);
	return 0;
}

static struct clk_ops apple_clk_ops = {
	.enable = apple_clk_enable,
};

static const struct udevice_id apple_clk_ids[] = {
	{ .compatible = "apple,pmgr-clk-gate" },
	{ /* sentinel */ }
};

static int apple_clk_probe(struct udevice *dev)
{
	struct apple_clk_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	clk_get_bulk(dev, &priv->parents);

	return 0;
}

U_BOOT_DRIVER(clk_apple) = {
	.name = "clk_apple",
	.id = UCLASS_CLK,
	.of_match = apple_clk_ids,
	.ops = &apple_clk_ops,
	.probe = apple_clk_probe,
	.priv_auto = sizeof(struct apple_clk_priv),
};
