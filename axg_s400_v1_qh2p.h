/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/configs/axg_s400_v1_qh2p.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __AXG_S400_V1_H__
#define __AXG_S400_V1_H__

#include <asm/arch/cpu.h>

#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE	990
#define CONFIG_VDDEE_INIT_VOLTAGE	1050		// voltage for power up
#define CONFIG_VDDEE_SLEEP_VOLTAGE	 810		// voltage for suspend

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

/* SMP Definitions */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* config saradc*/
#define CONFIG_CMD_SARADC 1

//#define CONFIG_AML_PRODUCT_MODE 1 //
#ifdef CONFIG_AML_PRODUCT_MODE
#define CONFIG_SILENT_CONSOLE
#define CONFIG_NO_FASTBOOT_FLASHING
#define CONFIG_USB_TOOL_ENTRY   "echo product mode"
#define CONFIG_KNL_LOG_LEVEL    "loglevel=1"
#else
#define CONFIG_USB_TOOL_ENTRY   "update 1500"
#define CONFIG_KNL_LOG_LEVEL    "loglevel=7"
#define CONFIG_CMD_BOOTI        1
#define CONFIG_CMD_MEMORY       1
#define CONFIG_CMD_JTAG	        1
#define CONFIG_CMD_AUTOSCRIPT   1
#define CONFIG_USB_STORAGE      1
#endif

/* command watchdog */
#define CONFIG_CMD_WATCHDOG 1

/*config irblaster*/
#define CONFIG_CMD_IRBLASTER 1

/*config a/b system*/
#define CONFIG_AB_SYSTEM 1

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
#define CONFIG_BOOTLOADER_CONTROL_BLOCK

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

#define CONFIG_BT_WAKEUP
//#define CONFIG_WIFI_WAKEUP

//Enable ir remote wake up for bl30
#define CONFIG_IR_REMOTE_POWER_UP_KEY_CNT 5
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0xef10fe01 //amlogic tv ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define CONFIG_ADC_POWER_KEY_CHAN   0  /*channel range: 0-7*/
#define CONFIG_ADC_POWER_KEY_VAL    0  /*sample value range: 0-1023*/

/*smc*/
#define CONFIG_ARM_SMCCC       1

/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=1\0"\
        "jtag=disable\0"\
        "loadaddr=1080000\0"\
        "panel_type=lcd_3\0" \
        "lcd_ctrl=0x00000000\0" \
        "lcd_debug=0x00000000\0" \
        "outputmode=panel\0" \
        "hdmimode=1080p60hz\0" \
        "cvbsmode=576cvbs\0" \
        "display_width=480\0" \
        "display_height=480\0" \
        "display_bpp=24\0" \
        "display_color_index=24\0" \
        "display_layer=osd0\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
        "dtb_mem_addr=0x1000000\0" \
        "fb_addr=0x3d800000\0" \
        "fb_width=480\0" \
        "fb_height=480\0" \
        "fdt_high=0x20000000\0"\
        "try_auto_burn=update 700 750;\0"\
        "EnableSelinux=enforcing\0" \
        "boot_part=boot_b\0"\
        "boot_failcnt=0\0"\
        "silent_boot=0\0"\
        "skip_console=0\0" \
        "initargs="\
            "rootfstype=ramfs init=/init " CONFIG_KNL_LOG_LEVEL " console=ttyS0,115200 no_console_suspend earlycon=aml_uart,0xff803000 ramoops.pstore_en=1 ramoops.record_size=0x8000 ramoops.console_size=0x4000 "\
            "\0"\
        "storeargs="\
            "get_bootloaderversion;" \
            "setenv bootargs ${initargs} androidboot.selinux=${EnableSelinux} androidboot.firstboot=${firstboot} jtag=${jtag}; "\
            "setenv bootargs ${bootargs} androidboot.bootloader=${bootloader_version};"\
            "setenv bootargs ${bootargs} androidboot.slot_suffix=${active_slot};"\
            "run set_boot_flag;"\
            "\0"\
        "set_boot_flag="\
            "if test ${boot_part} = boot_a; then "\
                "setenv boot_failcnt 1;"\
            "else"\
                " setenv boot_failcnt 2;"\
            "fi;"\
            "\0"\
        "boot_failed="\
            "if itest ${boot_failcnt} == 1; then "\
                "setenv boot_failcnt 2; setenv boot_part boot_b; set_active_slot b;"\
            "else if itest ${boot_failcnt} == 2; then "\
                "setenv boot_failcnt 1; setenv boot_part boot_a; set_active_slot a;"\
            "fi;"\
            "fi;"\
            "\0"\
        "factory_detect="\
            "if keyman read deviceid ${loadaddr} str; then "\
                "echo HAVE SN Code ...; "\
            "else "\
                "echo Switch to boot_b system, because of NOT found SN Code ...; "\
                "setenv boot_failcnt 2; set_active_slot b;"\
            "fi;"\
            "\0"\
        "storeboot="\
            "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "run boot_failed; "\
            "run storeargs;"\
            "reset;"\
            "\0"\
        "bcb_cmd="\
            "get_valid_slot;"\
            "\0"\


#define CONFIG_PREBOOT  \
            "run bcb_cmd;"\
            "run storeargs;"\
            "if test ${reboot_mode} = cold_boot; then run try_auto_burn; fi;"
#define CONFIG_BOOTCOMMAND "run storeboot"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK					1200 //MHz. Range: 600-1800, should be multiple of 24

/* ddr */
#define CONFIG_DDR_SIZE					0 //MB //0 means ddr size auto-detect

/* IMPORTANT
 *    DDR clk <= 400MHz, please enable CONFIG_DDR_PLL_BYPASS blow
 *    DDR clk > 400MHz, please disable CONFIG_DDR_PLL_BYPASS blow
 */
#define CONFIG_DDR_CLK					912  //MHz, Range: 200-1200, should be multiple of 24
#define CONFIG_DDR4_CLK					792  //MHz, this is for same board with DDR4 chip

#define CONFIG_NR_DRAM_BANKS			1
/* DDR type setting
 *    CONFIG_DDR_TYPE_LPDDR3   : LPDDR3
 *    CONFIG_DDR_TYPE_DDR3     : DDR3
 *    CONFIG_DDR_TYPE_DDR4     : DDR4
 *    CONFIG_DDR_TYPE_AUTO     : DDR3/DDR4 auto detect */
#define CONFIG_DDR_TYPE					CONFIG_DDR_TYPE_AUTO
/* DDR channel setting, please refer hardware design.
 *    CONFIG_DDR0_16BIT        : DDR0 16bit mode
 *    CONFIG_DDR0_16BIT_2      : DDR0 16bit mode, 2ranks
 *    CONFIG_DDR_CHL_AUTO      : auto detect RANK0 / RANK0+1 */
#define CONFIG_DDR_CHANNEL_SET			CONFIG_DDR0_16BIT
/* ddr functions */
#define CONFIG_DDR_FULL_TEST			0 //0:disable, 1:enable. ddr full test
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_LOW_POWER			1 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR4_TIMING_TEST			0 //0:disable, 1:enable. ddr4 timing test function
#define CONFIG_DDR_PLL_BYPASS			0 //0:disable, 1:enable. ddr pll bypass function
#define CONFIG_DDR_FUNC_PRINT_WINDOW	0 //0:disable, 1:enable. print ddr training window

/* storage: emmc/nand/sd */
#define	CONFIG_STORE_COMPATIBLE 1
/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */
/* support for mtd */
#define CONFIG_AML_MTD 1
/* support for nftl */
//#define CONFIG_AML_NAND	1

#if defined(CONFIG_AML_NAND) && defined(CONFIG_AML_MTD)
#error CONFIG_AML_NAND/CONFIG_AML_MTD can not support at the sametime;
#endif

#ifdef CONFIG_AML_MTD

/* bootloader is construct by bl2 and fip
 * when DISCRETE_BOOTLOADER is enabled, bl2 & fip
 * will not be stored continuously, and nand layout
 * would be bl2|rsv|fip|normal, but not
 * bl2|fip|rsv|normal anymore
 */
#define CONFIG_DISCRETE_BOOTLOADER

#ifdef  CONFIG_DISCRETE_BOOTLOADER
#define CONFIG_TPL_SIZE_PER_COPY          0x200000
#define CONFIG_TPL_COPY_NUM               4
#define CONFIG_TPL_PART_NAME              "tpl"
/* for bl2, restricted by romboot */
#define CONFIG_BL2_COPY_NUM               8
#endif /* CONFIG_DISCRETE_BOOTLOADER */

#define CONFIG_CMD_NAND 1
#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
#define CONFIG_AML_MTDPART	1
/* mtd parts by env default way.*/
/*
#define MTDIDS_NAME_STR		"aml_nand.0"
#define MTDIDS_DEFAULT		"nand1=" MTDIDS_NAME_STR
#define MTDPARTS_DEFAULT	"mtdparts=" MTDIDS_NAME_STR ":" \
					"3M@8192K(logo),"	\
					"10M(recovery),"	\
					"8M(kernel),"	\
					"40M(rootfs),"	\
					"-(data)"
*/
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_CMD_NAND_TORTURE 1
#define CONFIG_CMD_MTDPARTS   1
#define CONFIG_MTD_PARTITIONS 1
#define CONFIG_SYS_MAX_NAND_DEVICE  2
#define CONFIG_SYS_NAND_BASE_LIST   {0}
#endif
/* endof CONFIG_AML_MTD */
#define		CONFIG_AML_SD_EMMC 1
#ifdef		CONFIG_AML_SD_EMMC
	#define 	CONFIG_GENERIC_MMC 1
	#define 	CONFIG_CMD_MMC 1
    #define     CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000
#endif
/* storage macro checks */
#if defined(CONFIG_AML_MTD) && defined(CONFIG_AML_NAND)
#error mtd/nftl are mutually-exclusive, only 1 nand driver can be enabled.
#endif

#define 	CONFIG_ENV_OVERWRITE
#define 	CONFIG_CMD_SAVEENV

/* fixme, need fix*/

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

#define		CONFIG_PARTITIONS 1
#define 	CONFIG_SYS_NO_FLASH  1
//#define     CONFIG_AML_GPT


/* vpu */
#define CONFIG_AML_VPU 1
#define CONFIG_VPU_CLK_LEVEL_DFT 3

/* DISPLAY & HDMITX */
//#define CONFIG_AML_HDMITX20 1
//#define CONFIG_AML_CANVAS 1
#define CONFIG_AML_VOUT 1
#define CONFIG_AML_OSD 1
#define CONFIG_AML_MINUI 1
#define CONFIG_OSD_SCALE_ENABLE 0
#define CONFIG_CMD_BMP 1

#if defined(CONFIG_AML_VOUT)
//#define CONFIG_AML_CVBS 1
#endif

#define CONFIG_AML_LCD    1
/*#define CONFIG_AML_LCD_TV 1*/
#define CONFIG_AML_LCD_TABLET 1
#define CONFIG_AML_LCD_EXTERN 1
#define CONFIG_AML_LCD_EXTERN_MIPI_TV070WSM 1
#define CONFIG_AML_LCD_EXTERN_MIPI_ST7701 1
#define CONFIG_AML_LCD_EXTERN_MIPI_P070ACB 1
#define CONFIG_AML_BL_EXTERN  1
#define CONFIG_AML_BL_EXTERN_MIPI_IT070ME05 1

#define CONFIG_AML_WIFI_EN_INIT
#define CONFIG_AML_GPIO_WIFI_EN_1  PIN_GPIOX_7
#define CONFIG_AML_GPIO_WIFI_EN_2  PIN_GPIOX_16
#define CONFIG_AML_GPIO_WIFI_EN_1_NAME	"GPIOX_7"
#define CONFIG_AML_GPIO_WIFI_EN_2_NAME	"GPIOX_16"

#define CONFIG_AML_PCIE
#define CONFIG_AML_PCIEA_GPIO_RESET  PIN_GPIOX_19
#define CONFIG_AML_PCIEB_GPIO_RESET  PIN_GPIOZ_10
#define CONFIG_AML_PCIEA_GPIO_RESET_NAME	"GPIOX_19"
#define CONFIG_AML_PCIEB_GPIO_RESET_NAME	"GPIOZ_10"

#define CONFIG_PCI 1
#define CONFIG_CMD_PCI 1
#define CONFIG_CMD_PCI_ENUM 1
#define CONFIG_PCIE_AMLOGIC 1
#define CONFIG_PCI_SCAN_SHOW 1

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
#define CONFIG_CMD_USB 1
#if defined(CONFIG_CMD_USB)
	#define CONFIG_GXL_XHCI_BASE            0xff500000
	#define CONFIG_GXL_USB_PHY2_BASE        0xffe09000
	#define CONFIG_GXL_USB_PHY3_BASE        0xffe09080
	#define CONFIG_USB_XHCI		1
	#define CONFIG_USB_XHCI_AMLOGIC_GXL 1
#endif //#if defined(CONFIG_CMD_USB)

#define CONFIG_TXLX_USB        1

//UBOOT fastboot config
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#ifdef CONFIG_AML_MTD
#define CONFIG_FASTBOOT_FLASH_NAND_DEV 1
#endif
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1
#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0xA000000
#define CONFIG_DEVICE_PRODUCT	"axg_s400"

//UBOOT Factory usb/sdcard burning config
#define CONFIG_AML_V2_FACTORY_BURN              1       //support factory usb burning
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1       //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1       //There isn't power-key for factory sdcard burning
//#define CONFIG_SD_BURNING_SUPPORT_UI            1       //Displaying upgrading progress bar when sdcard/udisk burning
#define CONFIG_AML_LOCAL_BURN_BUFF_NOT_ALIGN    1

#define CONFIG_AML_SECURITY_KEY                 1
#define CONFIG_UNIFY_KEY_MANAGE                 1

/* net */
#define CONFIG_CMD_NET   1
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        arm_gxbb
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          10.18.9.97          /* Our ip address */
	#define CONFIG_GATEWAYIP       10.18.9.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        10.18.9.113         /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/* other devices */
/* I2C DM driver*/
//#define CONFIG_DM_I2C
#if defined(CONFIG_DM_I2C)
#define CONFIG_SYS_I2C_MESON		1
#else
#define CONFIG_SYS_I2C_AML			1
#define CONFIG_SYS_I2C_SPEED		400000
#define CONFIG_I2C_MULTI_BUS 		1
#endif

#define CONFIG_EFUSE 1
/* #define CONFIG_SYS_I2C_AML_IS31F123XX 1 */

/* commands */
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_I2C 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_MISC 1

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
#define CONFIG_BOOTDELAY	1
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC     1
#define CONFIG_CMD_ITEST    1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_SYS_MEM_TOP_HIDE 0
#define CONFIG_MULTI_DTB	1

/* debug mode defines */
//#define CONFIG_DEBUG_MODE			1
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG		636
#define CONFIG_CPU_CLK_DEBUG		600
#endif

//2017.04.26
//data compress for BL30,BL32,BL33
//compress ratio is about 50%, BL31 will take the decompress
//profit :
//          size : u-boot.bin 1.2MB -> 780KB
//          boot time : 140ms decrease
//default: enable the data compress feature
//to disable the data compress please just define followings
//#define CONFIG_AML_BL30_COMPRESS_DISABLE 1
//#define CONFIG_AML_BL32_COMPRESS_DISABLE 1
//#define CONFIG_AML_BL33_COMPRESS_DISABLE 1


//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//for GXBB SRAM size limitation just disable NAND
//as the socket board default has no NAND
//#undef CONFIG_AML_NAND

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   1

//unify build for generate encrypted kernel image
//SRC : "board/amlogic/axg_s400_v1/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG       1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif
#define ETHERNET_INTERNAL_PHY
#define CONFIG_AML_KASLR_SEED

#endif

