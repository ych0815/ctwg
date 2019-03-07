/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Port_CfgType.c
* 功能描述      : Port模块配置数据类型头文件(.h)定义
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名             版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/
#ifndef  _PORT_CFGTYPE_H_
#define  _PORT_CFGTYPE_H_

/**************************** 引用部分 *************************************/
#include "Port_Cfg.h"

/**************************** 定义部分 *************************************/
/* 引脚类型 */
typedef uint8 Port_PinType;  

/* 引脚功能模式 */
typedef enum
{
	PORT_PIN_MODE_ADC = 1u,
	PORT_PIN_MODE_CAN = 2u,
	PORT_PIN_MODE_DIO = 3u,
	PORT_PIN_MODE_DIO_GPT = 4u,
	PORT_PIN_MODE_DIO_WDG = 5u,
	PORT_PIN_MODE_FLEXRAY = 6u,
	PORT_PIN_MODE_ICU = 7u,
	PORT_PIN_MODE_LIN = 8u,
	PORT_PIN_MODE_MEM = 9u,
	PORT_PIN_MODE_PWM = 10u,
	PORT_PIN_MODE_SPI = 11u,
	PORT_PIN_MODE_SCI = 12u
}Port_PinModeType;

/* 定义引脚电平 */
typedef enum
{
    PORT_PIN_LEVEL_LOW  = 0u,
    PORT_PIN_LEVEL_HIGH = 1u
} Port_PinLevelValueType;

/* 定义引脚方向*/
typedef enum   
{
    PORT_PIN_IN  = 0u,
    PORT_PIN_OUT = 1u
} Port_PinDirectionType;

/* 单支引脚配置结构体 */
typedef struct
{   
    Port_PinType		PortPinId;		/* 引脚ID(应用可见) */	
	uint8               PortType;		/* 端口类型(A/B/C....)*/
	Port_PinType        PortDrvPinId;   /* 引脚驱动模块中ID*//*add by chenms 2017-10-27*/
    Port_PinModeType	PortPinMode;  	/* 引脚工作模式 */	
	boolean 	PortPinModeChangeable;  /* 引脚工作模式能否动态改变*/
    boolean 	PortPinDirection;  		/* 引脚方向(输入/输出) */  	
    boolean		PortPinDirectionChangeable;	/* 引脚方向能否动态改变 */		 
    boolean		PortPinLevelValue;			/* 引脚默认电平 */
}Port_PinConfigurationType;

/* 模块配置结构体 */
typedef struct
{
    uint8 PortNumberOfPortPins;
    const Port_PinConfigurationType *Port_PinConfiguration;
}Port_ConfigType;

#endif

