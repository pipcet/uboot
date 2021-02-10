// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Mark Kettenis <kettenis@openbsd.org>
 */

#include <common.h>

#include <asm/armv8/mmu.h>
#include <asm/global_data.h>

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
	/* This is a lie, but it works for now. */
	gd->ram_size = 4ULL * SZ_1G;
	return 0;
}

void reset_cpu(ulong ignored)
{
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
