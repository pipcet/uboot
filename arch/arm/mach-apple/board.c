// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Mark Kettenis <kettenis@openbsd.org>
 */

#include <common.h>
#include <efi_loader.h>

#include <asm/armv8/mmu.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <asm/system.h>

DECLARE_GLOBAL_DATA_PTR;

static struct mm_region apple_mem_map[] = {
	{
		/* I/O */
		.virt = 0x200000000,
		.phys = 0x200000000,
		.size = 8UL * SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* I/O */
		.virt = 0x500000000,
		.phys = 0x500000000,
		.size = 2UL * SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* I/O */
		.virt = 0x680000000,
		.phys = 0x680000000,
		.size = SZ_512M,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* PCIE */
		.virt = 0x6a0000000,
		.phys = 0x6a0000000,
		.size = SZ_512M,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRE) |
			 PTE_BLOCK_INNER_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* PCIE */
		.virt = 0x6c0000000,
		.phys = 0x6c0000000,
		.size = SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRE) |
			 PTE_BLOCK_INNER_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* RAM */
		.virt = 0x800000000,
		.phys = 0x800000000,
		.size = 8UL * SZ_1G,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		/* Empty entry for framebuffer */
		0,
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = apple_mem_map;

int board_init(void)
{
	return 0;
}

int dram_init(void)
{
	int index, node, ret;
	fdt_addr_t base;
	fdt_size_t size;

	ret = fdtdec_setup_mem_size_base();
	if (ret)
		return ret;

	/* Update RAM mapping. */
	index = ARRAY_SIZE(apple_mem_map) - 3;
	apple_mem_map[index].virt = gd->ram_base;
	apple_mem_map[index].phys = gd->ram_base;
	apple_mem_map[index].size = gd->ram_size;

	node = fdt_path_offset(gd->fdt_blob, "/chosen/framebuffer");
	if (node < 0)
		return 0;

	base = fdtdec_get_addr_size(gd->fdt_blob, node, "reg", &size);
	if (base == FDT_ADDR_T_NONE)
		return 0;

	/* Add framebuffer mapping. */
	index = ARRAY_SIZE(apple_mem_map) - 2;
	apple_mem_map[index].virt = base;
	apple_mem_map[index].phys = base;
	apple_mem_map[index].size = size;
	apple_mem_map[index].attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL_NC) |
		PTE_BLOCK_INNER_SHARE | PTE_BLOCK_PXN | PTE_BLOCK_UXN;

	return 0;
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

#define APPLE_WDT_BASE		0x23d2b0000ULL

#define APPLE_WDT_SYS_CTL_ENABLE	BIT(2)

typedef struct apple_wdt {
	u32	reserved0[3];
	u32	chip_ctl;
	u32	sys_tmr;
	u32	sys_cmp;
	u32	reserved1;
	u32	sys_ctl;
} apple_wdt_t;

void reset_cpu(ulong ignored)
{
	apple_wdt_t *wdt = (apple_wdt_t *)APPLE_WDT_BASE;

	writel(0, &wdt->sys_cmp);
	writel(APPLE_WDT_SYS_CTL_ENABLE, &wdt->sys_ctl);

	while(1)
		wfi();
}

extern long fw_dtb_pointer;

void *board_fdt_blob_setup(void)
{
	return (void *)fw_dtb_pointer;
}

ulong board_get_usable_ram_top(ulong total_size)
{
	/*
	 * Top part of RAM is used by firmware for things like the
	 * framebuffer.  This gives us plenty of room to play with.
	 */
	return 0x980000000;
}

unsigned long get_uart_clk(int dev_index)
{
	return 24000000;
}

__weak phys_addr_t apple_mbox_phys_start;
__weak phys_size_t apple_mbox_size;

int ft_board_setup(void *blob, struct bd_info *bd)
{
	if (apple_mbox_size > 0) {
		/* Reserve memory stolen by the mailboxes. */
		efi_add_memory_map(apple_mbox_phys_start, apple_mbox_size,
				   EFI_RESERVED_MEMORY_TYPE);
	}

	return 0;
}
