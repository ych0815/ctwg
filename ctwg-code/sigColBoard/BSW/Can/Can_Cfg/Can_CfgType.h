/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Can_CfgType.h
* 功能描述  : 9s12xep100-Can驱动配置类型定义头文件(Can_CfgType.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            			 New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CAN_CFGTYPE_H_
#define  _CAN_CFGTYPE_H_

/**************************************
              	头文件
 *************************************/
#include "Can_Cfg.h"

/**************************************
		接收滤波类型定义
 *************************************/
typedef struct
{
	uint32  FilterMaskId;   /*滤波掩码Id*/
	uint32  FilterAcceptId; /*滤波接收Id*/
}Can_FilterCfgType;

/**************************************
		控制器配置类型定义
 *************************************/
/*CAN控制器支持的波特率*/
typedef enum
{
	CAN_BPS_100K  = 0u,		/*BPS=100K*/
	CAN_BPS_125K  = 1u,		/*BPS=125K*/
	CAN_BPS_250K  = 2u,		/*BPS=250K*/
	CAN_BPS_500K  = 3u,		/*BPS=500K*/
	CAN_BPS_1000K = 4u 		/*BPS=1000K*/
}Can_ControllerBpsType;

/*CAN控制器中断配置类型*/
typedef void (*pIntFunction)(void);
typedef struct
{
	uint8  	IntPriority; 				 /*中断优先级*/
	pIntFunction InterruptCallback; 	 /*中断回调函数*/
}Can_ControllerIntType;

typedef struct
{
	uint8  ControllerId;  				 /*片内控制器ID号*/
	Can_ControllerBpsType BaudRate;		 /*控制器波特率*/
	const  Can_ControllerIntType *pInterruptCfg;/*控制器中断相关配置*/
	uint8   NumOfControllerFilter;		 /*控制器滤波配置数量*/
	const  Can_FilterCfgType 	 *pControllerFilterCfg;/*指向控制器滤波配置*/
}Can_ControllerCfgType;

/************************************
		控制器包含邮箱配置类型
 ************************************/
typedef enum
{
	CANID_STANDARD = 0u, /*标准帧*/
	CANID_EXTENDED = 1u  /*扩展帧*/
}Can_IdType;

typedef enum 
{
	CANID_RECEIVE  = 0u, /*接收*/	
	CANID_TRANSMIT = 1u	 /*发送*/
}Can_ObjectType;

typedef struct
{
	uint32  CanId;		  /*Can Id值:该项配置值对发送无影响*/
	uint8   CanObjectId;  /*硬件邮箱ID号(0~[控制器支持最大值-1)],该项配置值对发送无影响*/
	Can_IdType 	CanIdType;/*CanId类型(标准/扩展)*/
	Can_ObjectType  	  CanObjectTrans;   /*传输方向*/
	const  Can_FilterCfgType     *pFilterMaskRef; 	/*接收滤波配置,该项配置值对发送无影响*/
	const  Can_ControllerCfgType *pCanControlRef; 	/*该邮箱关联的CAN控制器*/
}Can_HardwareObjectCfgType;

/************************************
		模块静态配置类型
 ************************************/
typedef  struct
{
	uint8  NumOfController; 			/*模块支持的控制器个数*/
	const  Can_ControllerCfgType     *pControllerCfg;
	uint8  NumOfHardwareObject;     	/*模块支持的邮箱个数*/ 
	const  Can_HardwareObjectCfgType *pHardwareObjectCfg;
}Can_CfgType;

#endif

