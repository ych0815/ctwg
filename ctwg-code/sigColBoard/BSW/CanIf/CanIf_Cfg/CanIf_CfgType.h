/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : CanIf_CfgType.h
* 功能描述  : CanIf模块配置类型定义头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CANIF_CFGTYPE_H_
#define  _CANIF_CFGTYPE_H_

/**************************************
              	头文件
 **************************************/
#include "CanIf_Cfg.h"

/**************************************
             	静态配置数据类型定义
 **************************************/
/*单个控制器配置数据类型*/
typedef struct
{
	uint8  ControllerId;	/*ECU级(片内+外扩)控制器ID号*/
	uint8  ProtocolId;     	/*控制器支持的协议Id号*/
}CanIf_ControllerCfgType;

/*控制器冗余组配置类型*/
typedef struct
{
	uint8  GroupId;		   /*冗余组ID号*/
	const  CanIf_ControllerCfgType  *pController1;  /*冗余组包括控制器1*/  
	const  CanIf_ControllerCfgType  *pController2;  /*冗余组包括控制器2*/  
}CanIf_ControllerGroupCfgType;

typedef struct
{
	uint8  NumOfController;	/*模块配置的控制器数量*/
	const  CanIf_ControllerCfgType *pControllerCfg;
	uint8  NumOfGroup;		/*模块配置的冗余组数量*/
	const  CanIf_ControllerGroupCfgType *pGroupCfg;
}CanIf_CfgType;

#endif

