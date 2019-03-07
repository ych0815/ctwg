/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Can_Cfg.c
* 功能描述  : 9s12xep100-Can驱动配置源文件(Can_Cfg.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New

说明:
1)目前版本的模块逻辑:仅支持2个32位的Filter: bitX=1:忽略;bitX=0:比较;
  扩展帧:配置Bit28~bit0有效;
  标准帧:配置Bit10~bit0有效;
2)目前版本只支持配置单个发送硬件缓存,控制器所有的发送报文均通过该发送硬件缓存发送;
3)目前版本若控制器没有配置接收邮箱,则默认控制器接收扩展帧;
          若控制器没有配置发送邮箱,则默认控制器发送扩展帧;
**------------------------------------------------------------------------------------------------*/
#include "Can_Cfg.h"
#include "Can_CfgType.h"

/*****************************************
(received id与FilterAcceptId,若通过FilterMaskId定义的滤波规则
(bitX=0:对应位比较;bitX=1:对应位忽略),则接收 )
 *****************************************/
const Can_FilterCfgType  Can_FilterIdCfg[2] = 
{
	{
		0xFFFFFFFF,  /*FilterMaskId  (不比较)*/
		0x400   	 /*FilterAcceptId		 */
	},
	{
		0xFFFFFFFF,	 /*FilterMaskId  (不比较)*/
		0x08000000	 /*FilterAcceptId        */
	}		
};

const Can_ControllerCfgType Can_ControllerCfg[2] = 
{
	{
		CAN_CONTROLLER_0,	/*ControllerId*/
		CAN_BPS_100K,	 	/*BaudRate*/
		NULL_PTR,         	/*pInterruptCfg*/
		2u,					/*NumOfControllerFilter*/		
		&Can_FilterIdCfg[0] /*pControllerFilterCfg*/
	},
	{
		CAN_CONTROLLER_1,
		CAN_BPS_100K,
		NULL_PTR,
		2u,
		&Can_FilterIdCfg[0]
	}
};

const Can_HardwareObjectCfgType  Can_HardwareObjectCfg[4] = 
{
	{
		0x00ul,					/*CanId*/
		0,						/*CanObjectId*/
		CANID_EXTENDED, 		/*CanIdType*/
		CANID_RECEIVE,			/*CanObjectTrans*/
		NULL_PTR,				/*pFilterMaskRef*/
		&Can_ControllerCfg[0] 	/*pCanControlRef*/
	},
	{
		0x1000,				 	/*该项配置值对发送无影响*/
		3,					 	/*该项配置值对发送无影响*/	
		CANID_EXTENDED,	
		CANID_TRANSMIT,	
		NULL_PTR,			 	/*该项配置值对发送无影响*/
		&Can_ControllerCfg[0]
	},
	/**********************/
	{
		0x00ul,					/*CanId*/
		0,						/*CanObjectId*/
		CANID_EXTENDED, 		/*CanIdType*/
		CANID_RECEIVE,			/*CanObjectTrans*/
		NULL_PTR,				/*pFilterMaskRef*/
		&Can_ControllerCfg[1] 	/*pCanControlRef*/
	},
	{
		0x1000,				 	/*该项配置值对发送无影响*/
		3,					 	/*该项配置值对发送无影响*/		
		CANID_EXTENDED,	
		CANID_TRANSMIT,	
		NULL_PTR,			 	/*该项配置值对发送无影响*/
		&Can_ControllerCfg[1]
	}
};

const  Can_CfgType  Can_Cfg= 
{
	2u,							/*NumOfController*/
	&Can_ControllerCfg[0],		/*pControllerCfg*/
	4u,							/*NumOfMailBox*/
	&Can_HardwareObjectCfg[0]  	/*pHardwareObjectCfg*/
};

