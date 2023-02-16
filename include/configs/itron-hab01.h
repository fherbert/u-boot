/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef __CONFIG_ITRON_HAB01_H
#define __CONFIG_ITRON_HAB01_H


/* RAM */
#define CONFIG_SYS_SDRAM_BASE		0x80000000
#define CONFIG_SYS_INIT_SP_OFFSET	0x800000

/* SPL */
#define CONFIG_SYS_UBOOT_START		CONFIG_TEXT_BASE

/* Dummy value */
#define CONFIG_SYS_UBOOT_BASE		0

/* Serial SPL */
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_SERIAL)
#define CONFIG_SYS_NS16550_MEM32
#define CONFIG_SYS_NS16550_CLK		40000000
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#define CONFIG_SYS_NS16550_COM1		0xb0000c00

#endif

/* UART */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, \
					  230400, 460800, 921600 }

/* Environment settings */
#define CONFIG_EXTRA_ENV_SETTINGS \
    "bootmenu_default=0\0" \
    "bootmenu_0=Run from flash=bootm 0xbc050000 \0" \
    "bootmenu_1=Flash u-boot from tftp=askenv serverip TFTP Server IP: && askenv ipaddr IP Address: && askenv file_name File name: && ledblink start && tftpboot 0x82000000 ${file_name} && run writeflash\0" \
    "bootmenu_2=Flash u-boot from USB=setenv bootfile itronhab01.ldr && ledblink start && usb start && load usb 0 && run writeflash\0" \
    "bootmenu_3=Flash OS from USB=setenv bootfile itronhab01.img && setenv flashoffset 0x50000 && ledblink start && usb start && load usb 0 && run writeflash\0" \
    "writeflash=sf probe && sf update ${fileaddr} ${flashoffset} 0x${filesize} && ledblink stop && reset\0" \
    "tf=setenv serverip 10.0.0.5 && setenv ipaddr 10.0.0.76 && ledblink start && tftpboot 0x82000000 itronhab01.ldr && run writeflash\0" \
    "flashoffset=0\0" \
    "preboot=if button reset; then " \
      "led itron:orange:wifi on;" \
      "sleep 5;" \
      "led itron:orange:wifi off;" \
      "sleep 15;" \
      "if button reset; then " \
        "led itron:orange:wifi on && setenv bootmenu_default 2;" \
      "else " \
        "setenv bootmenu_default 3;" \
      "fi;" \
    "fi;\0" \

#endif /* __CONFIG_ITRON_HAB01_H */
