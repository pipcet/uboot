/* SPDX-License-Identifier: GPL-2.0+ */
/*
 *  Copyright (C) 2018 Flowbird
 *  Martin Fuzzey  <martin.fuzzey@flowbird.group>
 */

#ifndef __DA9063_PMIC_H_
#define __DA9063_PMIC_H_

/* Register definitions below taken from the kernel */

/* Page selection I2C or SPI always in the beginning of any page. */
/* Page 0 : I2C access 0x000 - 0x0FF	SPI access 0x000 - 0x07F */
/* Page 1 :				SPI access 0x080 - 0x0FF */
/* Page 2 : I2C access 0x100 - 0x1FF	SPI access 0x100 - 0x17F */
/* Page 3 :				SPI access 0x180 - 0x1FF */
#define	DA9063_REG_PAGE_CON		0x00

/* System Control and Event Registers */
#define	DA9063_REG_STATUS_A		0x01
#define	DA9063_REG_STATUS_B		0x02
#define	DA9063_REG_STATUS_C		0x03
#define	DA9063_REG_STATUS_D		0x04
#define	DA9063_REG_FAULT_LOG		0x05
#define	DA9063_REG_EVENT_A		0x06
#define	DA9063_REG_EVENT_B		0x07
#define	DA9063_REG_EVENT_C		0x08
#define	DA9063_REG_EVENT_D		0x09
#define	DA9063_REG_IRQ_MASK_A		0x0A
#define	DA9063_REG_IRQ_MASK_B		0x0B
#define	DA9063_REG_IRQ_MASK_C		0x0C
#define	DA9063_REG_IRQ_MASK_D		0x0D
#define	DA9063_REG_CONTROL_A		0x0E
#define	DA9063_REG_CONTROL_B		0x0F
#define	DA9063_REG_CONTROL_C		0x10
#define	DA9063_REG_CONTROL_D		0x11
#define	DA9063_REG_CONTROL_E		0x12
#define	DA9063_REG_CONTROL_F		0x13
#define	DA9063_REG_PD_DIS		0x14

/* GPIO Control Registers */
#define	DA9063_REG_GPIO_0_1		0x15
#define	DA9063_REG_GPIO_2_3		0x16
#define	DA9063_REG_GPIO_4_5		0x17
#define	DA9063_REG_GPIO_6_7		0x18
#define	DA9063_REG_GPIO_8_9		0x19
#define	DA9063_REG_GPIO_10_11		0x1A
#define	DA9063_REG_GPIO_12_13		0x1B
#define	DA9063_REG_GPIO_14_15		0x1C
#define	DA9063_REG_GPIO_MODE0_7		0x1D
#define	DA9063_REG_GPIO_MODE8_15	0x1E
#define	DA9063_REG_SWITCH_CONT		0x1F

/* Regulator Control Registers */
#define	DA9063_REG_BCORE2_CONT		0x20
#define	DA9063_REG_BCORE1_CONT		0x21
#define	DA9063_REG_BPRO_CONT		0x22
#define	DA9063_REG_BMEM_CONT		0x23
#define	DA9063_REG_BIO_CONT		0x24
#define	DA9063_REG_BPERI_CONT		0x25
#define	DA9063_REG_LDO1_CONT		0x26
#define	DA9063_REG_LDO2_CONT		0x27
#define	DA9063_REG_LDO3_CONT		0x28
#define	DA9063_REG_LDO4_CONT		0x29
#define	DA9063_REG_LDO5_CONT		0x2A
#define	DA9063_REG_LDO6_CONT		0x2B
#define	DA9063_REG_LDO7_CONT		0x2C
#define	DA9063_REG_LDO8_CONT		0x2D
#define	DA9063_REG_LDO9_CONT		0x2E
#define	DA9063_REG_LDO10_CONT		0x2F
#define	DA9063_REG_LDO11_CONT		0x30
#define	DA9063_REG_SUPPLIES		0x31
#define	DA9063_REG_DVC_1		0x32
#define	DA9063_REG_DVC_2		0x33

/* GP-ADC Control Registers */
#define	DA9063_REG_ADC_MAN		0x34
#define	DA9063_REG_ADC_CONT		0x35
#define	DA9063_REG_VSYS_MON		0x36
#define	DA9063_REG_ADC_RES_L		0x37
#define	DA9063_REG_ADC_RES_H		0x38
#define	DA9063_REG_VSYS_RES		0x39
#define	DA9063_REG_ADCIN1_RES		0x3A
#define	DA9063_REG_ADCIN2_RES		0x3B
#define	DA9063_REG_ADCIN3_RES		0x3C
#define	DA9063_REG_MON_A8_RES		0x3D
#define	DA9063_REG_MON_A9_RES		0x3E
#define	DA9063_REG_MON_A10_RES		0x3F

/* RTC Calendar and Alarm Registers */
#define	DA9063_REG_COUNT_S		0x40
#define	DA9063_REG_COUNT_MI		0x41
#define	DA9063_REG_COUNT_H		0x42
#define	DA9063_REG_COUNT_D		0x43
#define	DA9063_REG_COUNT_MO		0x44
#define	DA9063_REG_COUNT_Y		0x45

#define	DA9063_AD_REG_ALARM_MI		0x46
#define	DA9063_AD_REG_ALARM_H		0x47
#define	DA9063_AD_REG_ALARM_D		0x48
#define	DA9063_AD_REG_ALARM_MO		0x49
#define	DA9063_AD_REG_ALARM_Y		0x4A
#define	DA9063_AD_REG_SECOND_A		0x4B
#define	DA9063_AD_REG_SECOND_B		0x4C
#define	DA9063_AD_REG_SECOND_C		0x4D
#define	DA9063_AD_REG_SECOND_D		0x4E

#define	DA9063_BB_REG_ALARM_S		0x46
#define	DA9063_BB_REG_ALARM_MI		0x47
#define	DA9063_BB_REG_ALARM_H		0x48
#define	DA9063_BB_REG_ALARM_D		0x49
#define	DA9063_BB_REG_ALARM_MO		0x4A
#define	DA9063_BB_REG_ALARM_Y		0x4B
#define	DA9063_BB_REG_SECOND_A		0x4C
#define	DA9063_BB_REG_SECOND_B		0x4D
#define	DA9063_BB_REG_SECOND_C		0x4E
#define	DA9063_BB_REG_SECOND_D		0x4F

#define DA9063_REG_HOLE_1 {0x50, 0x7F}

/* Sequencer Control Registers */
#define	DA9063_REG_SEQ			0x81
#define	DA9063_REG_SEQ_TIMER		0x82
#define	DA9063_REG_ID_2_1		0x83
#define	DA9063_REG_ID_4_3		0x84
#define	DA9063_REG_ID_6_5		0x85
#define	DA9063_REG_ID_8_7		0x86
#define	DA9063_REG_ID_10_9		0x87
#define	DA9063_REG_ID_12_11		0x88
#define	DA9063_REG_ID_14_13		0x89
#define	DA9063_REG_ID_16_15		0x8A
#define	DA9063_REG_ID_18_17		0x8B
#define	DA9063_REG_ID_20_19		0x8C
#define	DA9063_REG_ID_22_21		0x8D
#define	DA9063_REG_ID_24_23		0x8E
#define	DA9063_REG_ID_26_25		0x8F
#define	DA9063_REG_ID_28_27		0x90
#define	DA9063_REG_ID_30_29		0x91
#define	DA9063_REG_ID_32_31		0x92
#define	DA9063_REG_SEQ_A		0x95
#define	DA9063_REG_SEQ_B		0x96
#define	DA9063_REG_WAIT			0x97
#define	DA9063_REG_EN_32K		0x98
#define	DA9063_REG_RESET		0x99

/* Regulator Setting Registers */
#define	DA9063_REG_BUCK_ILIM_A		0x9A
#define	DA9063_REG_BUCK_ILIM_B		0x9B
#define	DA9063_REG_BUCK_ILIM_C		0x9C
#define	DA9063_REG_BCORE2_CFG		0x9D
#define	DA9063_REG_BCORE1_CFG		0x9E
#define	DA9063_REG_BPRO_CFG		0x9F
#define	DA9063_REG_BIO_CFG		0xA0
#define	DA9063_REG_BMEM_CFG		0xA1
#define	DA9063_REG_BPERI_CFG		0xA2
#define	DA9063_REG_VBCORE2_A		0xA3
#define	DA9063_REG_VBCORE1_A		0xA4
#define	DA9063_REG_VBPRO_A		0xA5
#define	DA9063_REG_VBMEM_A		0xA6
#define	DA9063_REG_VBIO_A		0xA7
#define	DA9063_REG_VBPERI_A		0xA8
#define	DA9063_REG_VLDO1_A		0xA9
#define	DA9063_REG_VLDO2_A		0xAA
#define	DA9063_REG_VLDO3_A		0xAB
#define	DA9063_REG_VLDO4_A		0xAC
#define	DA9063_REG_VLDO5_A		0xAD
#define	DA9063_REG_VLDO6_A		0xAE
#define	DA9063_REG_VLDO7_A		0xAF
#define	DA9063_REG_VLDO8_A		0xB0
#define	DA9063_REG_VLDO9_A		0xB1
#define	DA9063_REG_VLDO10_A		0xB2
#define	DA9063_REG_VLDO11_A		0xB3
#define	DA9063_REG_VBCORE2_B		0xB4
#define	DA9063_REG_VBCORE1_B		0xB5
#define	DA9063_REG_VBPRO_B		0xB6
#define	DA9063_REG_VBMEM_B		0xB7
#define	DA9063_REG_VBIO_B		0xB8
#define	DA9063_REG_VBPERI_B		0xB9
#define	DA9063_REG_VLDO1_B		0xBA
#define	DA9063_REG_VLDO2_B		0xBB
#define	DA9063_REG_VLDO3_B		0xBC
#define	DA9063_REG_VLDO4_B		0xBD
#define	DA9063_REG_VLDO5_B		0xBE
#define	DA9063_REG_VLDO6_B		0xBF
#define	DA9063_REG_VLDO7_B		0xC0
#define	DA9063_REG_VLDO8_B		0xC1
#define	DA9063_REG_VLDO9_B		0xC2
#define	DA9063_REG_VLDO10_B		0xC3
#define	DA9063_REG_VLDO11_B		0xC4

/* Backup Battery Charger Control Register */
#define	DA9063_REG_BBAT_CONT		0xC5

/* GPIO PWM (LED) */
#define	DA9063_REG_GPO11_LED		0xC6
#define	DA9063_REG_GPO14_LED		0xC7
#define	DA9063_REG_GPO15_LED		0xC8

/* GP-ADC Threshold Registers */
#define	DA9063_REG_ADC_CFG		0xC9
#define	DA9063_REG_AUTO1_HIGH		0xCA
#define	DA9063_REG_AUTO1_LOW		0xCB
#define	DA9063_REG_AUTO2_HIGH		0xCC
#define	DA9063_REG_AUTO2_LOW		0xCD
#define	DA9063_REG_AUTO3_HIGH		0xCE
#define	DA9063_REG_AUTO3_LOW		0xCF

#define DA9063_REG_HOLE_2 {0xD0, 0xFF}

/* DA9063 Configuration registers */
/* OTP */
#define	DA9063_REG_OTP_COUNT		0x101
#define	DA9063_REG_OTP_ADDR		0x102
#define	DA9063_REG_OTP_DATA		0x103

/* Customer Trim and Configuration */
#define	DA9063_REG_T_OFFSET		0x104
#define	DA9063_REG_INTERFACE		0x105
#define	DA9063_REG_CONFIG_A		0x106
#define	DA9063_REG_CONFIG_B		0x107
#define	DA9063_REG_CONFIG_C		0x108
#define	DA9063_REG_CONFIG_D		0x109
#define	DA9063_REG_CONFIG_E		0x10A
#define	DA9063_REG_CONFIG_F		0x10B
#define	DA9063_REG_CONFIG_G		0x10C
#define	DA9063_REG_CONFIG_H		0x10D
#define	DA9063_REG_CONFIG_I		0x10E
#define	DA9063_REG_CONFIG_J		0x10F
#define	DA9063_REG_CONFIG_K		0x110
#define	DA9063_REG_CONFIG_L		0x111

#define	DA9063_AD_REG_MON_REG_1		0x112
#define	DA9063_AD_REG_MON_REG_2		0x113
#define	DA9063_AD_REG_MON_REG_3		0x114
#define	DA9063_AD_REG_MON_REG_4		0x115
#define	DA9063_AD_REG_MON_REG_5		0x116
#define	DA9063_AD_REG_MON_REG_6		0x117
#define	DA9063_AD_REG_TRIM_CLDR		0x118

#define	DA9063_AD_REG_GP_ID_0		0x119
#define	DA9063_AD_REG_GP_ID_1		0x11A
#define	DA9063_AD_REG_GP_ID_2		0x11B
#define	DA9063_AD_REG_GP_ID_3		0x11C
#define	DA9063_AD_REG_GP_ID_4		0x11D
#define	DA9063_AD_REG_GP_ID_5		0x11E
#define	DA9063_AD_REG_GP_ID_6		0x11F
#define	DA9063_AD_REG_GP_ID_7		0x120
#define	DA9063_AD_REG_GP_ID_8		0x121
#define	DA9063_AD_REG_GP_ID_9		0x122
#define	DA9063_AD_REG_GP_ID_10		0x123
#define	DA9063_AD_REG_GP_ID_11		0x124
#define	DA9063_AD_REG_GP_ID_12		0x125
#define	DA9063_AD_REG_GP_ID_13		0x126
#define	DA9063_AD_REG_GP_ID_14		0x127
#define	DA9063_AD_REG_GP_ID_15		0x128
#define	DA9063_AD_REG_GP_ID_16		0x129
#define	DA9063_AD_REG_GP_ID_17		0x12A
#define	DA9063_AD_REG_GP_ID_18		0x12B
#define	DA9063_AD_REG_GP_ID_19		0x12C

#define	DA9063_BB_REG_CONFIG_M		0x112
#define	DA9063_BB_REG_CONFIG_N		0x113

#define	DA9063_BB_REG_MON_REG_1		0x114
#define	DA9063_BB_REG_MON_REG_2		0x115
#define	DA9063_BB_REG_MON_REG_3		0x116
#define	DA9063_BB_REG_MON_REG_4		0x117
#define	DA9063_BB_REG_MON_REG_5		0x11E
#define	DA9063_BB_REG_MON_REG_6		0x11F
#define	DA9063_BB_REG_TRIM_CLDR		0x120
/* General Purpose Registers */
#define	DA9063_BB_REG_GP_ID_0		0x121
#define	DA9063_BB_REG_GP_ID_1		0x122
#define	DA9063_BB_REG_GP_ID_2		0x123
#define	DA9063_BB_REG_GP_ID_3		0x124
#define	DA9063_BB_REG_GP_ID_4		0x125
#define	DA9063_BB_REG_GP_ID_5		0x126
#define	DA9063_BB_REG_GP_ID_6		0x127
#define	DA9063_BB_REG_GP_ID_7		0x128
#define	DA9063_BB_REG_GP_ID_8		0x129
#define	DA9063_BB_REG_GP_ID_9		0x12A
#define	DA9063_BB_REG_GP_ID_10		0x12B
#define	DA9063_BB_REG_GP_ID_11		0x12C
#define	DA9063_BB_REG_GP_ID_12		0x12D
#define	DA9063_BB_REG_GP_ID_13		0x12E
#define	DA9063_BB_REG_GP_ID_14		0x12F
#define	DA9063_BB_REG_GP_ID_15		0x130
#define	DA9063_BB_REG_GP_ID_16		0x131
#define	DA9063_BB_REG_GP_ID_17		0x132
#define	DA9063_BB_REG_GP_ID_18		0x133
#define	DA9063_BB_REG_GP_ID_19		0x134

/* 0x135 - 0x13f are readable, but not documented */
#define DA9063_REG_HOLE_3 {0x140, 0x17F}

/* Chip ID and variant */
#define	DA9063_REG_CHIP_ID		0x181
#define	DA9063_REG_CHIP_VARIANT		0x182
#define DA9063_REG_CUSTOMER_ID		0x183
#define DA9063_REG_CONFIG_ID		0x184

#define DA9063_NUM_OF_REGS		(DA9063_REG_CONFIG_ID + 1)

/* Drivers name */
#define DA9063_LDO_DRIVER	"da9063_ldo"
#define DA9063_BUCK_DRIVER	"da9063_buck"

/* Regulator modes */
enum {
	DA9063_LDOMODE_SLEEP,
	DA9063_LDOMODE_NORMAL
};

enum {
	DA9063_BUCKMODE_SLEEP,
	DA9063_BUCKMODE_SYNC,
	DA9063_BUCKMODE_AUTO,
};

#endif