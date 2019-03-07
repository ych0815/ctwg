/********************************************************************************//*！
*\file
*\brief      pio驱动程序
*\version    1.0.0
*\date       2015\1\12
*\author     zdj
*
*pio驱动程序
*
\verbatim
------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
                 
                 +------(NEW | MODify |ADD |DELete)------+
                 |
version          |    date(yyyy/mm/dd)  name        brief

---------------------+----------------+---------------------------------------------
 1.0.0         NEW       2015/1/12     zdj         create
------------------------------------------------------------------------------------
\endverbatim
************************************************************************************/

#include "mc9s12xep100.h"
#include "drv_pio.h"
/**
*\defgroup   pio 驱动程序
*\{
*/

                 
/*==================================================================================
*---------函数定义
===================================================================================*/

/********************************************************************************//*！
*\brief      pio初始化函数
*
*pio驱动初始化
*
*\param  
*
*\return    errno   错误值
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pio_init(void) 
{
    return 0;
}


#if 1
/********************************************************************************//*！
*\brief      PIOA端口方向设置函数
*
*本函数用于设置PIOA端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       错误值
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pioa_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PA0: DDRA_DDRA0 = tris;break;
      case DRV_PIO_PA1: DDRA_DDRA1 = tris;break;
      case DRV_PIO_PA2: DDRA_DDRA2 = tris;break;
      case DRV_PIO_PA3: DDRA_DDRA3 = tris;break;
      case DRV_PIO_PA4: DDRA_DDRA4 = tris;break;
      case DRV_PIO_PA5: DDRA_DDRA5 = tris;break;
      case DRV_PIO_PA6: DDRA_DDRA6 = tris;break;
      case DRV_PIO_PA7: DDRA_DDRA7 = tris;break;
      default:return 1;
    }
    return 0;
}
 
 
/********************************************************************************//*！
*\brief      PIOB端口方向设置函数
*
*本函数用于设置PIOB端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piob_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PB0: DDRB_DDRB0 = tris;break;
      case DRV_PIO_PB1: DDRB_DDRB1 = tris;break;
      case DRV_PIO_PB2: DDRB_DDRB2 = tris;break;
      case DRV_PIO_PB3: DDRB_DDRB3 = tris;break;
      case DRV_PIO_PB4: DDRB_DDRB4 = tris;break;
      case DRV_PIO_PB5: DDRB_DDRB5 = tris;break;
      case DRV_PIO_PB6: DDRB_DDRB6 = tris;break;
      case DRV_PIO_PB7: DDRB_DDRB7 = tris;break;
      default:return 1;
    }
    return 0;
}
     
/********************************************************************************//*！
*\brief      PIOC端口方向设置函数
*
*本函数用于设置PIOC端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pioc_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PC0: DDRC_DDRC0 = tris;break;
      case DRV_PIO_PC1: DDRC_DDRC1 = tris;break;
      case DRV_PIO_PC2: DDRC_DDRC2 = tris;break;
      case DRV_PIO_PC3: DDRC_DDRC3 = tris;break;
      case DRV_PIO_PC4: DDRC_DDRC4 = tris;break;
      case DRV_PIO_PC5: DDRC_DDRC5 = tris;break;
      case DRV_PIO_PC6: DDRC_DDRC6 = tris;break;
      case DRV_PIO_PC7: DDRC_DDRC7 = tris;break;
      default:return 1;
    }
    return 0;
}
     
/********************************************************************************//*！
*\brief      PIOD端口方向设置函数
*
*本函数用于设置PIOD端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piod_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PD0: DDRD_DDRD0 = tris;break;
      case DRV_PIO_PD1: DDRD_DDRD1 = tris;break;
      case DRV_PIO_PD2: DDRD_DDRD2 = tris;break;
      case DRV_PIO_PD3: DDRD_DDRD3 = tris;break;
      case DRV_PIO_PD4: DDRD_DDRD4 = tris;break;
      case DRV_PIO_PD5: DDRD_DDRD5 = tris;break;
      case DRV_PIO_PD6: DDRD_DDRD6 = tris;break;
      case DRV_PIO_PD7: DDRD_DDRD7 = tris;break;
      default:return 1;
    }
    return 0;
}
     
     
/********************************************************************************//*！
*\brief      PIOE端口方向设置函数
*
*本函数用于设置PIOE端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pioe_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PE2: DDRE_DDRE2 = tris;break;
      case DRV_PIO_PE3: DDRE_DDRE3 = tris;break;
      case DRV_PIO_PE4: DDRE_DDRE4 = tris;break;
      case DRV_PIO_PE5: DDRE_DDRE5 = tris;break;
      case DRV_PIO_PE6: DDRE_DDRE6 = tris;break;
      case DRV_PIO_PE7: DDRE_DDRE7 = tris;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOH端口方向设置函数
*
*本函数用于设置PIOH端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pioh_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PH0: DDRH_DDRH0 = tris;break;
      case DRV_PIO_PH1: DDRH_DDRH1 = tris;break;
      case DRV_PIO_PH2: DDRH_DDRH2 = tris;break;
      case DRV_PIO_PH3: DDRH_DDRH3 = tris;break;
      case DRV_PIO_PH4: DDRH_DDRH4 = tris;break;
      case DRV_PIO_PH5: DDRH_DDRH5 = tris;break;
      case DRV_PIO_PH6: DDRH_DDRH6 = tris;break;
      case DRV_PIO_PH7: DDRH_DDRH7 = tris;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOJ端口方向设置函数
*
*本函数用于设置PIOJ端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pioj_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PJ0: DDRJ_DDRJ0 = tris;break;
      case DRV_PIO_PJ1: DDRJ_DDRJ1 = tris;break;
      case DRV_PIO_PJ2: DDRJ_DDRJ2 = tris;break;
      case DRV_PIO_PJ4: DDRJ_DDRJ4 = tris;break;
      case DRV_PIO_PJ5: DDRJ_DDRJ5 = tris;break;
      case DRV_PIO_PJ6: DDRJ_DDRJ6 = tris;break;
      case DRV_PIO_PJ7: DDRJ_DDRJ7 = tris;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOK端口方向设置函数
*
*本函数用于设置PIOK端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piok_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PK0: DDRK_DDRK0 = tris;break;
      case DRV_PIO_PK1: DDRK_DDRK1 = tris;break;
      case DRV_PIO_PK2: DDRK_DDRK2 = tris;break;
      case DRV_PIO_PK3: DDRK_DDRK3 = tris;break;
      case DRV_PIO_PK4: DDRK_DDRK4 = tris;break;
      case DRV_PIO_PK5: DDRK_DDRK5 = tris;break;
      case DRV_PIO_PK6: DDRK_DDRK6 = tris;break;
      case DRV_PIO_PK7: DDRK_DDRK7 = tris;break;
      default:return 1;
    }
    return 0;
}
   
/********************************************************************************//*！
*\brief      PIOM端口方向设置函数
*
*本函数用于设置PIOM端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piom_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PM0: DDRM_DDRM0 = tris;break;
      case DRV_PIO_PM1: DDRM_DDRM1 = tris;break;
      case DRV_PIO_PM2: DDRM_DDRM2 = tris;break;
      case DRV_PIO_PM3: DDRM_DDRM3 = tris;break;
      case DRV_PIO_PM4: DDRM_DDRM4 = tris;break;
      case DRV_PIO_PM5: DDRM_DDRM5 = tris;break;
      case DRV_PIO_PM6: DDRM_DDRM6 = tris;break;
      case DRV_PIO_PM7: DDRM_DDRM7 = tris;break;
      default:return 1;
    }
    return 0;
}
   
/********************************************************************************//*！
*\brief      PIOP端口方向设置函数
*
*本函数用于设置PIOP端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piop_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PP0: DDRP_DDRP0 = tris;break;
      case DRV_PIO_PP1: DDRP_DDRP1 = tris;break;
      case DRV_PIO_PP2: DDRP_DDRP2 = tris;break;
      case DRV_PIO_PP3: DDRP_DDRP3 = tris;break;
      case DRV_PIO_PP4: DDRP_DDRP4 = tris;break;
      case DRV_PIO_PP5: DDRP_DDRP5 = tris;break;
      case DRV_PIO_PP6: DDRP_DDRP6 = tris;break;
      case DRV_PIO_PP7: DDRP_DDRP7 = tris;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOS端口方向设置函数
*
*本函数用于设置PIOS端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pios_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PS0: DDRS_DDRS0 = tris;break;
      case DRV_PIO_PS1: DDRS_DDRS1 = tris;break;
      case DRV_PIO_PS2: DDRS_DDRS2 = tris;break;
      case DRV_PIO_PS3: DDRS_DDRS3 = tris;break;
      case DRV_PIO_PS4: DDRS_DDRS4 = tris;break;
      case DRV_PIO_PS5: DDRS_DDRS5 = tris;break;
      case DRV_PIO_PS6: DDRS_DDRS6 = tris;break;
      case DRV_PIO_PS7: DDRS_DDRS7 = tris;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOT端口方向设置函数
*
*本函数用于设置PIOT端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_piot_tris(unsigned char pin,unsigned char tris) 
{
    switch(pin) 
    {
      case DRV_PIO_PT0: DDRT_DDRT0 = tris;break;
      case DRV_PIO_PT1: DDRT_DDRT1 = tris;break;
      case DRV_PIO_PT2: DDRT_DDRT2 = tris;break;
      case DRV_PIO_PT3: DDRT_DDRT3 = tris;break;
      case DRV_PIO_PT4: DDRT_DDRT4 = tris;break;
      case DRV_PIO_PT5: DDRT_DDRT5 = tris;break;
      case DRV_PIO_PT6: DDRT_DDRT6 = tris;break;
      case DRV_PIO_PT7: DDRT_DDRT7 = tris;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOAD端口方向设置函数
*
*本函数用于设置PIOAD端口的方向
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pad_tris(unsigned char pin,unsigned char tris) 
{
	ATD0DIENH = 0xFF; /*置为PADx为IO口*/
	ATD0DIENL = 0xFF;
	ATD1DIENL = 0xFF;
    switch(pin) 
    {
      case DRV_PIO_PAD0: DDR1AD0_DDR1AD00 = tris;break;
      case DRV_PIO_PAD1: DDR1AD0_DDR1AD01 = tris;break;
      case DRV_PIO_PAD2: DDR1AD0_DDR1AD02 = tris;break;
      case DRV_PIO_PAD3: DDR1AD0_DDR1AD03 = tris;break;
      case DRV_PIO_PAD4: DDR1AD0_DDR1AD04 = tris;break;
      case DRV_PIO_PAD5: DDR1AD0_DDR1AD05 = tris;break;
      case DRV_PIO_PAD6: DDR1AD0_DDR1AD06 = tris;break;
      case DRV_PIO_PAD7: DDR1AD0_DDR1AD07 = tris;break;
      case DRV_PIO_PAD8: DDR0AD0_DDR0AD00 = tris;break;
      case DRV_PIO_PAD9: DDR0AD0_DDR0AD01 = tris;break;
      case DRV_PIO_PAD10: DDR0AD0_DDR0AD02 = tris;break;
      case DRV_PIO_PAD11: DDR0AD0_DDR0AD03 = tris;break;
      case DRV_PIO_PAD12: DDR0AD0_DDR0AD04 = tris;break;
      case DRV_PIO_PAD13: DDR0AD0_DDR0AD05 = tris;break;
      case DRV_PIO_PAD14: DDR0AD0_DDR0AD06 = tris;break;
      case DRV_PIO_PAD15: DDR0AD0_DDR0AD07 = tris;break;
      case DRV_PIO_PAD16: DDR1AD1_DDR1AD10 = tris;break;
      case DRV_PIO_PAD17: DDR1AD1_DDR1AD11 = tris;break;
      case DRV_PIO_PAD18: DDR1AD1_DDR1AD12 = tris;break;
      case DRV_PIO_PAD19: DDR1AD1_DDR1AD13 = tris;break;
      case DRV_PIO_PAD20: DDR1AD1_DDR1AD14 = tris;break;
      case DRV_PIO_PAD21: DDR1AD1_DDR1AD15 = tris;break;
      case DRV_PIO_PAD22: DDR1AD1_DDR1AD16 = tris;break;
      case DRV_PIO_PAD23: DDR1AD1_DDR1AD17 = tris;break;
      default:return 1;
    }
    return 0;
}
#endif

#if 1
/********************************************************************************//*！
*\brief      PIOA端口读函数
*
*本函数用于读取IO A端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pioa_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PA0: *data = PORTA_PA0;break;
      case DRV_PIO_PA1: *data = PORTA_PA1;break;
      case DRV_PIO_PA2: *data = PORTA_PA2;break;
      case DRV_PIO_PA3: *data = PORTA_PA3;break;
      case DRV_PIO_PA4: *data = PORTA_PA4;break;
      case DRV_PIO_PA5: *data = PORTA_PA5;break;
      case DRV_PIO_PA6: *data = PORTA_PA6;break;
      case DRV_PIO_PA7: *data = PORTA_PA7;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOB端口读函数
*
*本函数用于读取IO B端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piob_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PB0: *data = PORTB_PB0;break;
      case DRV_PIO_PB1: *data = PORTB_PB1;break;
      case DRV_PIO_PB2: *data = PORTB_PB2;break;
      case DRV_PIO_PB3: *data = PORTB_PB3;break;
      case DRV_PIO_PB4: *data = PORTB_PB4;break;
      case DRV_PIO_PB5: *data = PORTB_PB5;break;
      case DRV_PIO_PB6: *data = PORTB_PB6;break;
      case DRV_PIO_PB7: *data = PORTB_PB7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOC端口读函数
*
*本函数用于读取IO C端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pioc_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PC0: *data = PORTC_PC0;break;
      case DRV_PIO_PC1: *data = PORTC_PC1;break;
      case DRV_PIO_PC2: *data = PORTC_PC2;break;
      case DRV_PIO_PC3: *data = PORTC_PC3;break;
      case DRV_PIO_PC4: *data = PORTC_PC4;break;
      case DRV_PIO_PC5: *data = PORTC_PC5;break;
      case DRV_PIO_PC6: *data = PORTC_PC6;break;
      case DRV_PIO_PC7: *data = PORTC_PC7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOD端口读函数
*
*本函数用于读取IO D端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piod_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PD0: *data = PORTD_PD0;break;
      case DRV_PIO_PD1: *data = PORTD_PD1;break;
      case DRV_PIO_PD2: *data = PORTD_PD2;break;
      case DRV_PIO_PD3: *data = PORTD_PD3;break;
      case DRV_PIO_PD4: *data = PORTD_PD4;break;
      case DRV_PIO_PD5: *data = PORTD_PD5;break;
      case DRV_PIO_PD6: *data = PORTD_PD6;break;
      case DRV_PIO_PD7: *data = PORTD_PD7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOE端口读函数
*
*本函数用于读取IO E端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pioe_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      
      case DRV_PIO_PE2: *data = PORTE_PE2;break;
      case DRV_PIO_PE3: *data = PORTE_PE3;break;
      case DRV_PIO_PE4: *data = PORTE_PE4;break;
      case DRV_PIO_PE5: *data = PORTE_PE5;break;
      case DRV_PIO_PE6: *data = PORTE_PE6;break;
      case DRV_PIO_PE7: *data = PORTE_PE7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOH端口读函数
*
*本函数用于读取IO H端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pioh_read(unsigned char pin,unsigned char *data) 
{                 
    switch(pin) 
    {
      case DRV_PIO_PH0: *data = PTH_PTH0;break;
      case DRV_PIO_PH1: *data = PTH_PTH1;break;
      case DRV_PIO_PH2: *data = PTH_PTH2;break;
      case DRV_PIO_PH3: *data = PTH_PTH3;break;
      case DRV_PIO_PH4: *data = PTH_PTH4;break;
      case DRV_PIO_PH5: *data = PTH_PTH5;break;
      case DRV_PIO_PH6: *data = PTH_PTH6;break;
      case DRV_PIO_PH7: *data = PTH_PTH7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOJ端口读函数
*
*本函数用于读取IO J端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pioj_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PJ0: *data = PTJ_PTJ0;break;
      case DRV_PIO_PJ1: *data = PTJ_PTJ1;break;
      case DRV_PIO_PJ2: *data = PTJ_PTJ2;break;
      case DRV_PIO_PJ4: *data = PTJ_PTJ4;break;
      case DRV_PIO_PJ5: *data = PTJ_PTJ5;break;
      case DRV_PIO_PJ6: *data = PTJ_PTJ6;break;
      case DRV_PIO_PJ7: *data = PTJ_PTJ7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOK端口读函数
*
*本函数用于读取IO K端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piok_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PK0: *data = PORTK_PK0;break;
      case DRV_PIO_PK1: *data = PORTK_PK1;break;
      case DRV_PIO_PK2: *data = PORTK_PK2;break;
      case DRV_PIO_PK3: *data = PORTK_PK3;break;
      case DRV_PIO_PK4: *data = PORTK_PK4;break;
      case DRV_PIO_PK5: *data = PORTK_PK5;break;
      case DRV_PIO_PK6: *data = PORTK_PK6;break;
      case DRV_PIO_PK7: *data = PORTK_PK7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOM端口读函数
*
*本函数用于读取IO M端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piom_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PM0: *data = PTM_PTM0;break;
      case DRV_PIO_PM1: *data = PTM_PTM1;break;
      case DRV_PIO_PM2: *data = PTM_PTM2;break;
      case DRV_PIO_PM3: *data = PTM_PTM3;break;
      case DRV_PIO_PM4: *data = PTM_PTM4;break;
      case DRV_PIO_PM5: *data = PTM_PTM5;break;
      case DRV_PIO_PM6: *data = PTM_PTM6;break;
      case DRV_PIO_PM7: *data = PTM_PTM7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOP端口读函数
*
*本函数用于读取IO P端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piop_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PP0: *data = PTP_PTP0;break;
      case DRV_PIO_PP1: *data = PTP_PTP1;break;
      case DRV_PIO_PP2: *data = PTP_PTP2;break;
      case DRV_PIO_PP3: *data = PTP_PTP3;break;
      case DRV_PIO_PP4: *data = PTP_PTP4;break;
      case DRV_PIO_PP5: *data = PTP_PTP5;break;
      case DRV_PIO_PP6: *data = PTP_PTP6;break;
      case DRV_PIO_PP7: *data = PTP_PTP7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOS端口读函数
*
*本函数用于读取IO S端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_pios_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PS0: *data = PTS_PTS0;break;
      case DRV_PIO_PS1: *data = PTS_PTS1;break;
      case DRV_PIO_PS2: *data = PTS_PTS2;break;
      case DRV_PIO_PS3: *data = PTS_PTS3;break;
      case DRV_PIO_PS4: *data = PTS_PTS4;break;
      case DRV_PIO_PS5: *data = PTS_PTS5;break;
      case DRV_PIO_PS6: *data = PTS_PTS6;break;
      case DRV_PIO_PS7: *data = PTS_PTS7;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOT端口读函数
*
*本函数用于读取IO T端的数据
*
*\param     pin     引脚号
*           *data   读取端口数据
*\return    1       设置引脚错误
*\retval    0       正常读取
*
**********************************************************************************/
unsigned char drv_piot_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PT0: *data = PTT_PTT0;break;
      case DRV_PIO_PT1: *data = PTT_PTT1;break;
      case DRV_PIO_PT2: *data = PTT_PTT2;break;
      case DRV_PIO_PT3: *data = PTT_PTT3;break;
      case DRV_PIO_PT4: *data = PTT_PTT4;break;
      case DRV_PIO_PT5: *data = PTT_PTT5;break;
      case DRV_PIO_PT6: *data = PTT_PTT6;break;
      case DRV_PIO_PT7: *data = PTT_PTT7;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOAD端口方向读函数
*
*本函数用于读取PIOAD端口的数据
*
*\param     pin  引脚号
*           tris 方向（1：输出/0：输入） 
*\return    1       设置引脚错误
*\retval    0       初始化正常
*
**********************************************************************************/
unsigned char drv_pad_read(unsigned char pin,unsigned char *data) 
{
    switch(pin) 
    {
      case DRV_PIO_PAD0: *data = PT1AD0_PT1AD00;break;
      case DRV_PIO_PAD1: *data = PT1AD0_PT1AD01;break;
      case DRV_PIO_PAD2: *data = PT1AD0_PT1AD02;break;
      case DRV_PIO_PAD3: *data = PT1AD0_PT1AD03;break;
      case DRV_PIO_PAD4: *data = PT1AD0_PT1AD04;break;
      case DRV_PIO_PAD5: *data = PT1AD0_PT1AD05;break;
      case DRV_PIO_PAD6: *data = PT1AD0_PT1AD06;break;
      case DRV_PIO_PAD7: *data = PT1AD0_PT1AD07;break;
      case DRV_PIO_PAD8: *data = PT0AD0_PT0AD00;break;
      case DRV_PIO_PAD9: *data = PT0AD0_PT0AD01;break;
      case DRV_PIO_PAD10: *data = PT0AD0_PT0AD02;break;
      case DRV_PIO_PAD11: *data = PT0AD0_PT0AD03;break;
      case DRV_PIO_PAD12: *data = PT0AD0_PT0AD04;break;
      case DRV_PIO_PAD13: *data = PT0AD0_PT0AD05;break;
      case DRV_PIO_PAD14: *data = PT0AD0_PT0AD06;break;
      case DRV_PIO_PAD15: *data = PT0AD0_PT0AD07;break;
      case DRV_PIO_PAD16: *data = PT1AD1_PT1AD10;break;
      case DRV_PIO_PAD17: *data = PT1AD1_PT1AD11;break;
      case DRV_PIO_PAD18: *data = PT1AD1_PT1AD12;break;
      case DRV_PIO_PAD19: *data = PT1AD1_PT1AD13;break;
      case DRV_PIO_PAD20: *data = PT1AD1_PT1AD14;break;
      case DRV_PIO_PAD21: *data = PT1AD1_PT1AD15;break;
      case DRV_PIO_PAD22: *data = PT1AD1_PT1AD16;break;
      case DRV_PIO_PAD23: *data = PT1AD1_PT1AD17;break;
      default:return 1;
    }
    return 0;
}

#endif

#if 1
/********************************************************************************//*！
*\brief      PIOA端口写函数
*
*本函数用于向IO A端写入数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pioa_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PA0: PORTA_PA0 = data;break;
      case DRV_PIO_PA1: PORTA_PA1 = data;break;
      case DRV_PIO_PA2: PORTA_PA2 = data;break;
      case DRV_PIO_PA3: PORTA_PA3 = data;break;
      case DRV_PIO_PA4: PORTA_PA4 = data;break;
      case DRV_PIO_PA5: PORTA_PA5 = data;break;
      case DRV_PIO_PA6: PORTA_PA6 = data;break;
      case DRV_PIO_PA7: PORTA_PA7 = data;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PIOB端口写函数
*
*本函数用于向IO B端写入数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piob_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PB0: PORTB_PB0 = data;break;
      case DRV_PIO_PB1: PORTB_PB1 = data;break;
      case DRV_PIO_PB2: PORTB_PB2 = data;break;
      case DRV_PIO_PB3: PORTB_PB3 = data;break;
      case DRV_PIO_PB4: PORTB_PB4 = data;break;
      case DRV_PIO_PB5: PORTB_PB5 = data;break;
      case DRV_PIO_PB6: PORTB_PB6 = data;break;
      case DRV_PIO_PB7: PORTB_PB7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOC端口写函数
*
*本函数用于写入IO C端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pioc_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PC0: PORTC_PC0 = data;break;
      case DRV_PIO_PC1: PORTC_PC1 = data;break;
      case DRV_PIO_PC2: PORTC_PC2 = data;break;
      case DRV_PIO_PC3: PORTC_PC3 = data;break;
      case DRV_PIO_PC4: PORTC_PC4 = data;break;
      case DRV_PIO_PC5: PORTC_PC5 = data;break;
      case DRV_PIO_PC6: PORTC_PC6 = data;break;
      case DRV_PIO_PC7: PORTC_PC7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOD端口写入函数
*
*本函数用于写入IO D端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piod_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PD0: PORTD_PD0 = data;break;
      case DRV_PIO_PD1: PORTD_PD1 = data;break;
      case DRV_PIO_PD2: PORTD_PD2 = data;break;
      case DRV_PIO_PD3: PORTD_PD3 = data;break;
      case DRV_PIO_PD4: PORTD_PD4 = data;break;
      case DRV_PIO_PD5: PORTD_PD5 = data;break;
      case DRV_PIO_PD6: PORTD_PD6 = data;break;
      case DRV_PIO_PD7: PORTD_PD7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOE端口读函数
*
*本函数用于向IO E端写入数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pioe_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      
      case DRV_PIO_PE2: PORTE_PE2 = data;break;
      case DRV_PIO_PE3: PORTE_PE3 = data;break;
      case DRV_PIO_PE4: PORTE_PE4 = data;break;
      case DRV_PIO_PE5: PORTE_PE5 = data;break;
      case DRV_PIO_PE6: PORTE_PE6 = data;break;
      case DRV_PIO_PE7: PORTE_PE7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOH端口写函数
*
*本函数用于写入IO H端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pioh_write(unsigned char pin,unsigned char data) 
{                 
    switch(pin) 
    {
      case DRV_PIO_PH0: PTH_PTH0 = data;break;
      case DRV_PIO_PH1: PTH_PTH1 = data;break;
      case DRV_PIO_PH2: PTH_PTH2 = data;break;
      case DRV_PIO_PH3: PTH_PTH3 = data;break;
      case DRV_PIO_PH4: PTH_PTH4 = data;break;
      case DRV_PIO_PH5: PTH_PTH5 = data;break;
      case DRV_PIO_PH6: PTH_PTH6 = data;break;
      case DRV_PIO_PH7: PTH_PTH7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOJ端口写函数
*
*本函数用于写入IO J端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pioj_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PJ0: PTJ_PTJ0 = data;break;
      case DRV_PIO_PJ1: PTJ_PTJ1 = data;break;
      case DRV_PIO_PJ2: PTJ_PTJ2 = data;break;
      case DRV_PIO_PJ4: PTJ_PTJ4 = data;break;
      case DRV_PIO_PJ5: PTJ_PTJ5 = data;break;
      case DRV_PIO_PJ6: PTJ_PTJ6 = data;break;
      case DRV_PIO_PJ7: PTJ_PTJ7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOK端口写函数
*
*本函数用于写入IO K端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piok_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PK0: PORTK_PK0 = data;break;
      case DRV_PIO_PK1: PORTK_PK1 = data;break;
      case DRV_PIO_PK2: PORTK_PK2 = data;break;
      case DRV_PIO_PK3: PORTK_PK3 = data;break;
      case DRV_PIO_PK4: PORTK_PK4 = data;break;
      case DRV_PIO_PK5: PORTK_PK5 = data;break;
      case DRV_PIO_PK6: PORTK_PK6 = data;break;
      case DRV_PIO_PK7: PORTK_PK7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOM端口写函数
*
*本函数用于写入IO M端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piom_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PM0: PTM_PTM0 = data;break;
      case DRV_PIO_PM1: PTM_PTM1 = data;break;
      case DRV_PIO_PM2: PTM_PTM2 = data;break;
      case DRV_PIO_PM3: PTM_PTM3 = data;break;
      case DRV_PIO_PM4: PTM_PTM4 = data;break;
      case DRV_PIO_PM5: PTM_PTM5 = data;break;
      case DRV_PIO_PM6: PTM_PTM6 = data;break;
      case DRV_PIO_PM7: PTM_PTM7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOP端口写函数
*
*本函数用于写入IO P端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piop_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PP0: PTP_PTP0 = data;break;
      case DRV_PIO_PP1: PTP_PTP1 = data;break;
      case DRV_PIO_PP2: PTP_PTP2 = data;break;
      case DRV_PIO_PP3: PTP_PTP3 = data;break;
      case DRV_PIO_PP4: PTP_PTP4 = data;break;
      case DRV_PIO_PP5: PTP_PTP5 = data;break;
      case DRV_PIO_PP6: PTP_PTP6 = data;break;
      case DRV_PIO_PP7: PTP_PTP7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOS端口写函数
*
*本函数用于写入IO S端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_pios_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PS0: PTS_PTS0 = data;break;
      case DRV_PIO_PS1: PTS_PTS1 = data;break;
      case DRV_PIO_PS2: PTS_PTS2 = data;break;
      case DRV_PIO_PS3: PTS_PTS3 = data;break;
      case DRV_PIO_PS4: PTS_PTS4 = data;break;
      case DRV_PIO_PS5: PTS_PTS5 = data;break;
      case DRV_PIO_PS6: PTS_PTS6 = data;break;
      case DRV_PIO_PS7: PTS_PTS7 = data;break;
      default:return 1;
    }
    return 0;
}

/********************************************************************************//*！
*\brief      PIOT端口写函数
*
*本函数用于写入IO T端的数据
*
*\param     pin     引脚号
*           data    写入端口数据
*\return    1       设置引脚错误
*\retval    0       正常写入
*
**********************************************************************************/
unsigned char drv_piot_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PT0: PTT_PTT0 = data;break;
      case DRV_PIO_PT1: PTT_PTT1 = data;break;
      case DRV_PIO_PT2: PTT_PTT2 = data;break;
      case DRV_PIO_PT3: PTT_PTT3 = data;break;
      case DRV_PIO_PT4: PTT_PTT4 = data;break;
      case DRV_PIO_PT5: PTT_PTT5 = data;break;
      case DRV_PIO_PT6: PTT_PTT6 = data;break;
      case DRV_PIO_PT7: PTT_PTT7 = data;break;
      default:return 1;
    }
    return 0;
}


/********************************************************************************//*！
*\brief      PAD端口写函数
*
*本函数用于写入PAD端口的数据
*
*\param     pin     引脚号
*           data    写入数据 
*\return    1       设置引脚错误
*\retval    0       写入正常
*
**********************************************************************************/
unsigned char drv_pad_write(unsigned char pin,unsigned char data) 
{
    switch(pin) 
    {
      case DRV_PIO_PAD0: PT1AD0_PT1AD00 = data;break;
      case DRV_PIO_PAD1: PT1AD0_PT1AD01 = data;break;
      case DRV_PIO_PAD2: PT1AD0_PT1AD02 = data;break;
      case DRV_PIO_PAD3: PT1AD0_PT1AD03 = data;break;
      case DRV_PIO_PAD4: PT1AD0_PT1AD04 = data;break;
      case DRV_PIO_PAD5: PT1AD0_PT1AD05 = data;break;
      case DRV_PIO_PAD6: PT1AD0_PT1AD06 = data;break;
      case DRV_PIO_PAD7: PT1AD0_PT1AD07 = data;break;
      case DRV_PIO_PAD8: PT0AD0_PT0AD00 = data;break;
      case DRV_PIO_PAD9: PT0AD0_PT0AD01 = data;break;
      case DRV_PIO_PAD10: PT0AD0_PT0AD02 = data;break;
      case DRV_PIO_PAD11: PT0AD0_PT0AD03 = data;break;
      case DRV_PIO_PAD12: PT0AD0_PT0AD04 = data;break;
      case DRV_PIO_PAD13: PT0AD0_PT0AD05 = data;break;
      case DRV_PIO_PAD14: PT0AD0_PT0AD06 = data;break;
      case DRV_PIO_PAD15: PT0AD0_PT0AD07 = data;break;
      case DRV_PIO_PAD16: PT1AD1_PT1AD10 = data;break;
      case DRV_PIO_PAD17: PT1AD1_PT1AD11 = data;break;
      case DRV_PIO_PAD18: PT1AD1_PT1AD12 = data;break;
      case DRV_PIO_PAD19: PT1AD1_PT1AD13 = data;break;
      case DRV_PIO_PAD20: PT1AD1_PT1AD14 = data;break;
      case DRV_PIO_PAD21: PT1AD1_PT1AD15 = data;break;
      case DRV_PIO_PAD22: PT1AD1_PT1AD16 = data;break;
      case DRV_PIO_PAD23: PT1AD1_PT1AD17 = data;break;
      default:return 1;
    }
    return 0;
}
#endif
