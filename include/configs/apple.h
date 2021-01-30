#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#define CONFIG_SYS_LOAD_ADDR	0x880000000
#define CONFIG_SYS_MALLOC_LEN	SZ_64M

#define CONFIG_LNX_KRNL_IMG_TEXT_OFFSET_BASE	CONFIG_SYS_TEXT_BASE

/* Environment */
#define ENV_DEVICE_SETTINGS \
	"stdin=serial\0" \
	"stdout=serial,vidconsole\0" \
	"stderr=serial,vidconsole\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	ENV_DEVICE_SETTINGS

#endif
