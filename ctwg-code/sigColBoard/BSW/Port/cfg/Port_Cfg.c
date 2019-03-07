/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Port_Cfg.c
* 功能描述      : Port模块配置头文件(.h)定义
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名             版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/

/**************************** 引用部分 *********************************/
#include "Port_Cfg.h"
#include "Port_CfgType.h"
#include "Port_Define.h"
#include "drv_pio.h"  /*add by chenms 2017-10-27*/
/**************************** 定义部分 *********************************/
/************************************
          2OO3LCU主控板引脚定义
************************************/
const Port_PinConfigurationType Port_PinConfig[14]=
{    
    /*DC12V、24V电源故障状态引脚*/
	{PORT_PIN_PC5  ,PORT_C,  DRV_PIO_PC5,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*DC12V故障检测*/
	{PORT_PIN_PC4  ,PORT_C,  DRV_PIO_PC4,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*DC24V故障检测*/

    /*看门狗喂狗线*/
	{PORT_PIN_PH0  ,PORT_H,  DRV_PIO_PH0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_LOW },/*WDI*/

	/*RUN LED*/
	{PORT_PIN_PA4  ,PORT_A,  DRV_PIO_PA4,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH },/*对应板子LED5*/
	/*CAN1 LED*/
	{PORT_PIN_PA3,  PORT_A,  DRV_PIO_PA3,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH},/*对应板子LED6*/
	/*CAN2 LED*/
	{PORT_PIN_PA2,  PORT_A,  DRV_PIO_PA2,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH},/*对应板子LED7*/
	
	/*预留*/
	{PORT_PIN_PA1  ,PORT_A,  DRV_PIO_PA1,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_HIGH },/*对应板子LED8*/
	{PORT_PIN_PA0  ,PORT_A,  DRV_PIO_PA0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_HIGH },/*对应板子LED9*/

	/*车辆入/出检测 4个引脚*/
	{PORT_PIN_PD2  ,PORT_D,  DRV_PIO_PD2,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*入库检测1*/
	{PORT_PIN_PD3  ,PORT_D,  DRV_PIO_PD3,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*入库检测2*/
	
	{PORT_PIN_PD0  ,PORT_D,  DRV_PIO_PD0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*出库检测1*/
	{PORT_PIN_PD1  ,PORT_D,  DRV_PIO_PD1,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*出库检测2*/

	/*散热风扇控制 2个引脚*/
	{PORT_PIN_PB5  ,PORT_B,  DRV_PIO_PB5,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_LOW },/*散热风扇1*/
	{PORT_PIN_PB6  ,PORT_B,  DRV_PIO_PB6,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_LOW },/*散热风扇2*/   
};  

const Port_ConfigType  Port_Config=
{
    14u,
    &Port_PinConfig[0]
};



