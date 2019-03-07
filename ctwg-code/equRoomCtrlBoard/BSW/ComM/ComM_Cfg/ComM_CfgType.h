/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : ComM_CfgType.h
* 功能描述  : 通讯管理模块配置类型定义头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COMM_CFGTYPE_H_
#define  _COMM_CFGTYPE_H_

#include "ComM_Cfg.h"
/**********************************
            静态配置数据类型定义
 **********************************/
typedef  struct
{
	uint8   LowValue;      /*区间下限*/
	uint8   HightValue;    /*区间上限*/
	uint8   StepValue;     /*对应步长*/
}ComM_StepCfgType;

/*冗余组中单个控制器平衡算法相关配置数据类型*/
typedef  struct
{
    uint8   DevId;         /*设备Id号*/
    boolean Direct;        /*=FALSE;平衡值往下减;=TRUE:平衡值往上加*/
    uint8   NumOfSteps;    /*设备对应区间个数*/
    const  ComM_StepCfgType *pDevStepCfg;
    uint32  FaultTimeOut;  /*通讯故障超时时间*/  
}ComM_DevCfgType;

/*单个冗余组平衡算法相关配置数据类型*/
typedef  struct
{
    uint8   GroupId;         			/*冗余组ID号*/
    uint8   ValueOfBalance;  			/*平衡天平初值*/
    uint8   BalanceLowLimit; 			/*平衡天平下限值*/
    uint8   BalanceHiLimit;				/*平衡天平上限值*/
	uint8   TrustBusAtPowerOn;			/*开机默认信任总线*/
	uint8   NumOfControllerCfg;         /*冗余组中包含的控制器数量*/
    const   ComM_DevCfgType   *pControllerCfg;	/*冗余组包含控制器配置起始地址*/
}ComM_GroupCfgType;

/*模块支持的冗余组配置数据类型*/
typedef struct
{
   uint8 NumOfDevice;     		/*模块支持的控制器数量*/
   const ComM_DevCfgType   *pDevCfg;
   uint8 NumOfComMGroup;  		/*模块支持的冗余组数量*/
   const ComM_GroupCfgType *pGroupCfg;
}ComM_CfgType;

#endif

