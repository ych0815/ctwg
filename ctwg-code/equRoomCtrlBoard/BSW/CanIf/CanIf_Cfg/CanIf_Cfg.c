/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : CanIf_Cfg.c
* 功能描述  : CanIf模块配置源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            			 New
**------------------------------------------------------------------------------------------------*/
#include "CanIf_Cfg.h"
#include "CanIf_CfgType.h"

const  CanIf_ControllerCfgType CanIf_ControllerCfg[2]= 
{
	{CAN_CONTROLLER_0, 0u}, /*ControllerId,ProtocolId*/
	{CAN_CONTROLLER_1, 0u}
};

/*该冗余组配置必须与ComM模块内配置一致(GroupId、ControllerId)*/
const  CanIf_ControllerGroupCfgType	CanIf_ControllerGroupCfg[1] = 
{
	{
		0u,						 /*GroupId*/ 			
	 	&CanIf_ControllerCfg[0], /*pController1*/
	 	&CanIf_ControllerCfg[1]  /*pController2*/
	} 
};

const  CanIf_CfgType  CanIf_Cfg = 
{
	2u,						 /*模块配置的控制器数量*/
	&CanIf_ControllerCfg[0],
	1u,						 /*模块配置的冗余组数量*/
	&CanIf_ControllerGroupCfg[0]
};





