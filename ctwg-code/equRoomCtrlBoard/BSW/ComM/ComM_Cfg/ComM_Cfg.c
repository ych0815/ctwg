/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : ComM_Cfg.c
* 功能描述  : 通讯管理模块配置源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "ComM_Cfg.h"
#include "ComM_CfgType.h"

const  ComM_StepCfgType   ComM_StepAddCfg[3] = 
{
  {0,   10,   10},   /*区间下限,区间上限,对应步长*/
  {11,  30,   2 },
  {31,  100,  1 }
};

const  ComM_StepCfgType   ComM_StepSubCfg[3] = 
{
  {0,   70,    1},   /*区间下限,区间上限,对应步长*/
  {71,  90,    2},
  {91,  100,  10}
};

const  ComM_DevCfgType    ComM_DevCfg[2] = 
{
  {CAN_CONTROLLER_0, TRUE,  3, &ComM_StepAddCfg[0], 2000ul},
  {CAN_CONTROLLER_1, FALSE, 3, &ComM_StepSubCfg[0], 2000ul}
};

/*该冗余组配置必须与CanIf模块内配置一致(GroupId、ControllerId)*/
const  ComM_GroupCfgType ComM_GroupCfg[1] = 
{
	{
		0u,  				/*冗余组ID号*/
		50u, 				/*平衡天平初值*/
		1u,					/*平衡天平下限值*/
		99,     			/*平衡天平上限值*/ 
		CAN_CONTROLLER_0,	/*冗余组开机默认信任总线*/
		2u,					/*冗余组中包含的控制器数量*/				
		&ComM_DevCfg[0]    	/*冗余组包含控制器配置起始地址*/
	}
};

const ComM_CfgType   ComM_Cfg = 
{
	2u,						/*模块支持的控制器数量*/
	&ComM_DevCfg[0],
	1u,						/*模块支持的冗余组数量*/
	&ComM_GroupCfg[0]
};










