/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Port.h
* 功能描述      : Port模块头文件(.h)定义
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名             版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/ 
#ifndef _PORT_H_
#define _PORT_H_

/**************************** 引用部分 *************************************/
#include "Port_Cfg.h"
#include "Port_CfgType.h"
#include "Port_Define.h"

/****************************宏定义部分*************************************/
/*错误定义*/
#define PORT_E_PARAM_PIN					(0x0au) /*PIN脚输入参数错误*/
#define PORT_E_DIRECTION_UNCHANGEABLE		(0x0bu) /*引脚方向为不可改变*/
#define PORT_E_PARAM_CONFIG					(0x0cu) /*模块配置参数错误*/
#define PORT_E_PARAM_INVALID			    (0x0du) /*输入参数无效*/
#define PORT_E_MODE_UNCHANGEABLE			(0x0eu) /*引脚模式为不可改变*/
#define PORT_E_UNINIT						(0x0fu) /*模块未初始化*/
#define PORT_E_DIRECTION_IN					(0x10u) /*引脚方向=输入*/
#define PORT_E_DIRECTION_OUT				(0x11u) /*引脚方向=输出*/

/* API Service ID's*/
#define PORT_INIT_ID						(0x00u)
#define PORT_SET_PIN_MODE_ID 			    (0x01u)
#define PORT_SET_PIN_DIRECTION_ID			(0x02u)
#define PORT_WRITE_PIN_VALUE_ID				(0x03u)
#define PORT_READ_PIN_VALUE_ID				(0x04u)



/**************************** 全局变量声明部分 *************************************/
extern const Port_ConfigType  Port_Config;


/**************************** 全局函数声明部分 *************************************/
/************************************************************
* 函数名称: Port_Init
* 函数描述: Port模块初始化.
* 输入参数: (*ConfigPtr):模块静态配置参数;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
extern	void   Port_Init(const Port_ConfigType *ConfigPtr);

/************************************************************
* 函数名称: Port_SetPinMode
* 函数描述: 设置指定引脚的工作模式.
* 输入参数: PinId:引脚ID号;
			Mode :引脚待修改工作模式;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
extern	void   Port_SetPinMode(Port_PinType PinId, Port_PinModeType Mode);

/************************************************************
* 函数名称: Port_SetPinDirection
* 函数描述: 设置指定引脚的输入/输出方向.
* 输入参数: PinId:引脚ID号;
			Mode :引脚待修改方向;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
extern	void Port_SetPinDirection(Port_PinType PinId,boolean PinDirection);

/************************************************************
* 函数名称: Port_WritePinValue
* 函数描述: 设置指定引脚的值(高/低电平)
* 输入参数: PinId：Pin脚Id号。
 *          PinLevelValue: Pin脚待设置值.
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
 * 		如果PinId方向=In, 则直接返回,不进行值更新;			
 * 		如果PinId方向=Out,则进行对应的值更新;
*************************************************************/
extern	void Port_WritePinValue(Port_PinType PinId,boolean PinLevelValue);

/************************************************************
* 函数名称: Port_ReadPinValue
* 函数描述: 读取指定引脚的值(高/低电平)
* 输入参数: PinId：Pin脚Id号。
* 输出参数: *pPinLevelValue: 读取到的Pin脚电平值
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
extern	void Port_ReadPinValue(Port_PinType PinId,boolean *pPinLevelValue);

#endif /*_PORT_H_*/

