/********************************************************************************//*！
*\file
*\brief      pio驱动程序头文件

*\version    1.0.0
*\date       2016\1\18
*\author     zdj
*
*pio驱动程序头文件
*
\verbatim
------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
                 
                 +------(NEW | MODify |ADD |DELete)------+
                 |
version          |    date(yyyy/mm/dd)  name        brief

---------------------+----------------+---------------------------------------------
 1.0.0         NEW       2016/1/18     zdj         create
------------------------------------------------------------------------------------
\endverbatim
************************************************************************************/

#ifndef _DRV_PIO_H_
#define _DRV_PIO_H_

/**
*\defgroup   pio 驱动程序头文件
*\{
*/
/*==================================================================================
*---------宏定义
===================================================================================*/
#if 1
/**\brief  pio a端口 */ 
#define DRV_PIO_PA0  0x49
#define DRV_PIO_PA1  0x4a
#define DRV_PIO_PA2  0x4b
#define DRV_PIO_PA3  0x4c
#define DRV_PIO_PA4  0x4d
#define DRV_PIO_PA5  0x4e
#define DRV_PIO_PA6  0x4f
#define DRV_PIO_PA7  0x50

/**\brief  pio b端口 */ 
#define DRV_PIO_PB0  0x20
#define DRV_PIO_PB1  0x21
#define DRV_PIO_PB2  0x22
#define DRV_PIO_PB3  0x23
#define DRV_PIO_PB4  0x24
#define DRV_PIO_PB5  0x25
#define DRV_PIO_PB6  0x26
#define DRV_PIO_PB7  0x27

/**\brief  pio c端口 */ 
#define DRV_PIO_PC0  0x1c
#define DRV_PIO_PC1  0x1d
#define DRV_PIO_PC2  0x1e
#define DRV_PIO_PC3  0x1f
#define DRV_PIO_PC4  0x28
#define DRV_PIO_PC5  0x29
#define DRV_PIO_PC6  0x2a
#define DRV_PIO_PC7  0x2b

/**\brief  pio d端口 */ 
#define DRV_PIO_PD0  0x41
#define DRV_PIO_PD1  0x42
#define DRV_PIO_PD2  0x43
#define DRV_PIO_PD3  0x44
#define DRV_PIO_PD4  0x53
#define DRV_PIO_PD5  0x54
#define DRV_PIO_PD6  0x55
#define DRV_PIO_PD7  0x56

/**\brief  pio e端口 */ 
#define DRV_PIO_PE2  0x46
#define DRV_PIO_PE3  0x45
#define DRV_PIO_PE4  0x33
#define DRV_PIO_PE5  0x32
#define DRV_PIO_PE6  0x31
#define DRV_PIO_PE7  0x30

/**\brief  pio h端口 */ 
#define DRV_PIO_PH0  0x40
#define DRV_PIO_PH1  0x3f
#define DRV_PIO_PH2  0x3e
#define DRV_PIO_PH3  0x3d
#define DRV_PIO_PH4  0x2f
#define DRV_PIO_PH5  0x2e
#define DRV_PIO_PH6  0x2d
#define DRV_PIO_PH7  0x2c

/**\brief  pio j端口 */ 
#define DRV_PIO_PJ0  0x18
#define DRV_PIO_PJ1  0x17
#define DRV_PIO_PJ2  0x5
#define DRV_PIO_PJ4  0x83
#define DRV_PIO_PJ5  0x82
#define DRV_PIO_PJ6  0x81
#define DRV_PIO_PJ7  0x80

/**\brief  pio k端口 */ 
#define DRV_PIO_PK0  0xa
#define DRV_PIO_PK1  0x9
#define DRV_PIO_PK2  0x8
#define DRV_PIO_PK3  0x7
#define DRV_PIO_PK4  0x16
#define DRV_PIO_PK5  0x15
#define DRV_PIO_PK6  0x6
#define DRV_PIO_PK7  0x8c

/**\brief  pio m端口 */ 
#define DRV_PIO_PM0  0x89
#define DRV_PIO_PM1  0x88
#define DRV_PIO_PM2  0x87
#define DRV_PIO_PM3  0x86
#define DRV_PIO_PM4  0x85
#define DRV_PIO_PM5  0x84
#define DRV_PIO_PM6  0x76
#define DRV_PIO_PM7  0x75

/**\brief  pio p端口 */ 
#define DRV_PIO_PP0  0x4
#define DRV_PIO_PP1  0x3
#define DRV_PIO_PP2  0x2
#define DRV_PIO_PP3  0x1
#define DRV_PIO_PP4  0x90
#define DRV_PIO_PP5  0x8f
#define DRV_PIO_PP6  0x8e
#define DRV_PIO_PP7  0x8d

/**\brief  pio s端口 */ 
#define DRV_PIO_PS0  0x77
#define DRV_PIO_PS1  0x78
#define DRV_PIO_PS2  0x79
#define DRV_PIO_PS3  0x7a
#define DRV_PIO_PS4  0x7b
#define DRV_PIO_PS5  0x7c
#define DRV_PIO_PS6  0x7d
#define DRV_PIO_PS7  0x7e

/**\brief  pio t端口 */ 
#define DRV_PIO_PT0  0xb
#define DRV_PIO_PT1  0xc
#define DRV_PIO_PT2  0xd
#define DRV_PIO_PT3  0xe
#define DRV_PIO_PT4  0x11
#define DRV_PIO_PT5  0x12
#define DRV_PIO_PT6  0x13
#define DRV_PIO_PT7  0x14

/**\brief  pio ad端口 */ 
#define DRV_PIO_PAD0   0x59
#define DRV_PIO_PAD1   0x5b
#define DRV_PIO_PAD2   0x5d
#define DRV_PIO_PAD3   0x5f
#define DRV_PIO_PAD4   0x61
#define DRV_PIO_PAD5   0x63
#define DRV_PIO_PAD6   0x65
#define DRV_PIO_PAD7   0x67
#define DRV_PIO_PAD8   0x5a
#define DRV_PIO_PAD9   0x5c
#define DRV_PIO_PAD10  0x5e
#define DRV_PIO_PAD11  0x60
#define DRV_PIO_PAD12  0x62
#define DRV_PIO_PAD13  0x64
#define DRV_PIO_PAD14  0x66
#define DRV_PIO_PAD15  0x68
#define DRV_PIO_PAD16  0x69
#define DRV_PIO_PAD17  0x6a
#define DRV_PIO_PAD18  0x6f
#define DRV_PIO_PAD19  0x70
#define DRV_PIO_PAD20  0x71
#define DRV_PIO_PAD21  0x72
#define DRV_PIO_PAD22  0x73
#define DRV_PIO_PAD23  0x74
#endif
/*==================================================================================
*---------函数声明
===================================================================================*/
unsigned char drv_pio_init(void);
unsigned char drv_pioa_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piob_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pioc_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piod_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pioe_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pioh_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pioj_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piok_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piom_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piop_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pios_tris(unsigned char pin,unsigned char tris);
unsigned char drv_piot_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pad_tris(unsigned char pin,unsigned char tris);
unsigned char drv_pioa_read(unsigned char pin,unsigned char *data);
unsigned char drv_piob_read(unsigned char pin,unsigned char *data);
unsigned char drv_pioc_read(unsigned char pin,unsigned char *data);
unsigned char drv_piod_read(unsigned char pin,unsigned char *data);
unsigned char drv_pioe_read(unsigned char pin,unsigned char *data);
unsigned char drv_pioh_read(unsigned char pin,unsigned char *data);
unsigned char drv_pioj_read(unsigned char pin,unsigned char *data);
unsigned char drv_piok_read(unsigned char pin,unsigned char *data);
unsigned char drv_piom_read(unsigned char pin,unsigned char *data);
unsigned char drv_piop_read(unsigned char pin,unsigned char *data);
unsigned char drv_pios_read(unsigned char pin,unsigned char *data);
unsigned char drv_piot_read(unsigned char pin,unsigned char *data);
unsigned char drv_pad_read(unsigned char pin,unsigned char *data);
unsigned char drv_pioa_write(unsigned char pin,unsigned char data);
unsigned char drv_piob_write(unsigned char pin,unsigned char data);
unsigned char drv_pioc_write(unsigned char pin,unsigned char data);
unsigned char drv_piod_write(unsigned char pin,unsigned char data);
unsigned char drv_pioe_write(unsigned char pin,unsigned char data);
unsigned char drv_pioh_write(unsigned char pin,unsigned char data);
unsigned char drv_pioj_write(unsigned char pin,unsigned char data);
unsigned char drv_piok_write(unsigned char pin,unsigned char data);
unsigned char drv_piom_write(unsigned char pin,unsigned char data);
unsigned char drv_piop_write(unsigned char pin,unsigned char data);
unsigned char drv_pios_write(unsigned char pin,unsigned char data);
unsigned char drv_piot_write(unsigned char pin,unsigned char data);
unsigned char drv_pad_write(unsigned char pin,unsigned char data);

#endif