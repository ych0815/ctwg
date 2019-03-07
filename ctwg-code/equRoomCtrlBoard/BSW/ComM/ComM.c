/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : ComM.c
* 功能描述  : CAN通讯管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "ComM.h"
#include "Can.h"
#include "CanIf.h"
#include "Osal.h"
#include "drv_sci.h"
#include "Gateway.h"

/***************************************
            运行时数据结构类型定义
****************************************/
typedef  enum
{
   TIMER_OFF = 0u,										
   TIMER_ON  = 1u										
}ComM_TimerStatusType;

typedef  struct
{
   uint32  CurTicks;										
   uint32  ExpireTicks;											
   ComM_TimerStatusType TimerStatus;									
}ComM_TimerCtrlType;														

/*控制器自身状态*/
typedef  enum 
{
   COMM_CONTROLER_OK     = 0u,     	/*控制器正常*/
   COMM_CONTROLER_BUSOFF = 1u   	/*控制器总线关闭*/
}ComM_ControlerStatusType;

/*控制器通讯状态*/
typedef  enum
{
   COMM_COMMUNICAITON_OK = 0u,   	/*控制器通信正常*/
   COMM_COMMUNICAITON_ERR= 1u  		/*控制器通信故障*/
}ComM_ControllerSubStatusType;

/*单个控制器运行时数据结构*/
typedef  struct
{
   uint8  ControllerId;  		   	/*控制器ID号*/	
   ComM_TimerCtrlType   TimerCtrl; 	/*控制器通讯正常/异常跟踪定时器*/
   ComM_ControlerStatusType	ControllerStatus;		/*控制器状态(正常/总线关闭)*/
   ComM_ControllerSubStatusType ControllerSubStatus;/*控制器子状态(通信状态:正常/异常)*/
}ComM_ControllerCtrlType;

/*单个冗余组运行时数据结构*/
typedef struct
{
   uint8  GroupId;	  				/*冗余组ID号*/
   uint8  CurBalanceValue;  		/*冗余组最新天平值*/
   uint8  CurTrustBus; 				/*冗余组当前信任总线信息*/
   ComM_ControllerCtrlType ControllerCtrl[2]; /*冗余组包含2路控制器信息*/
}ComM_GroupCtrlType;

typedef  enum
{
   COMM_UNINIT = 0u,
   COMM_INIT   = 1u   
}ComM_MkStatusType;

typedef  struct
{
   ComM_GroupCtrlType GroupCtrl[COMM_SUPPORT_GROUPNUM];
   ComM_MkStatusType  MkStatus;
}ComM_RunCtrlType;

/*****************************************
            运行时数据结构定义
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile ComM_RunCtrlType  ComM_RunCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            静态函数声明
 ****************************************/
#if  1
STATIC void ComM_InitGroup(uint8  GroupId);
STATIC Std_ReturnType  ComM_SearchDeviceInConfig(uint8 DevId,uint8 *pGroupCfg,uint8 *pControllCfg);
STATIC Std_ReturnType  ComM_SearchGroupInConfig(uint8 GroupId,uint8 *pGroupCfg);
STATIC void  ComM_MainFunctionForCalcCommunicationFault(void);
STATIC void  ComM_MainFunctionForCalcTrustInfo(void);
STATIC void  ComM_CalcTrustBusForBothOK(uint8  GroupNum);
STATIC void  ComM_CalcTrustBusInController0OK(uint8  GroupNum);
STATIC void  ComM_CalcTrustBusInController1OK(uint8  GroupNum);
STATIC void  ComM_CalcTrustBusInAllFault(uint8  GroupNum);
#endif

/************************************************************
* 函数名称:ComM_Init
* 函数描述:ComM模块初始化
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 返回值  :
* 可重入性:不可重入
* 备注	  :
*************************************************************/
void ComM_Init(void)
{
	uint8  GroupIndex = 0u;

	/****************************
			配置参数检查
	 ***************************/
	if(COMM_SUPPORT_GROUPNUM != ComM_Cfg.NumOfComMGroup)
	{
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_INIT_ID,
						COMM_E_CONFIGPARAM_INVALID);					
#endif
		return;
	}

	/****************************/
	for(GroupIndex=0u;GroupIndex<(ComM_Cfg.NumOfComMGroup);GroupIndex++)
	{
		ComM_InitGroup(ComM_Cfg.pGroupCfg[GroupIndex].GroupId);
	}	
	OSAL_ENTER_CRITICAL();
	ComM_RunCtrl.MkStatus = COMM_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:ComM_RxIndication
* 函数描述:通知ComM模块,设备号=DevId的CAN控制器接收到报文
* 输入参数:DevId:控制器ID号;
* 输出参数:无
* 输入/输出参数:无
* 返回值  :E_OK:下层通知成功
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:可重入
* 备注	  :下层Can驱动模块接收中断(Rx ISR)调用
*************************************************************/
Std_ReturnType ComM_RxIndication(uint8 DevId)
{
	uint8  GroupOffset = 0u;
	uint8  ControllOffset = 0u;
	uint8  StepIndex  = 0u;
	uint8  StepValue  = 0u;
	ComM_GroupCfgType *pGroupCfg = NULL_PTR;
	ComM_DevCfgType   *pControllCfg = NULL_PTR;
	Std_ReturnType ret = E_NOT_OK;
	uint8  CurBalanceValue = 0u;
	
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_RXINDICATION_ID,
						COMM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
    
	/**************************/
	ret = ComM_SearchDeviceInConfig( DevId,&GroupOffset,&ControllOffset);
	if(E_NOT_OK == ret)
	{
		/*DevId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_RXINDICATION_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}

	pGroupCfg    = &(ComM_Cfg.pGroupCfg[GroupOffset]);
	pControllCfg = &(ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[ControllOffset]); 
	/************************************
      计算天平值1:查询当前天平值对应步长
    *************************************/
	for(StepIndex=0u;StepIndex < (pControllCfg->NumOfSteps);StepIndex++)
	{
		OSAL_ENTER_CRITICAL();
		CurBalanceValue = ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue;
		OSAL_EXIT_CRITICAL();
		if(   (CurBalanceValue >= pControllCfg->pDevStepCfg[StepIndex].LowValue)
			&&(CurBalanceValue <= pControllCfg->pDevStepCfg[StepIndex].HightValue))
		{
			StepValue = pControllCfg->pDevStepCfg[StepIndex].StepValue;
			break;
		}
	}
	if((pControllCfg->NumOfSteps) == StepIndex)
	{
        /*当前平衡天平值在配置中没有找到对应范围*/
	  	return(E_NOT_OK);
	}
	
	/************************************
      计算天平值2:计算最新天平值
    *************************************/
    OSAL_ENTER_CRITICAL();
   	if(TRUE == pControllCfg->Direct)
	{
		/* "+" 步长 */
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue += StepValue;
	}
	else
	{
		/* "-" 步长*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue -= StepValue;
	}
	if((ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue)> (pGroupCfg->BalanceHiLimit))
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = pGroupCfg->BalanceHiLimit;
	}
    if((ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue)< (pGroupCfg->BalanceLowLimit))
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = pGroupCfg->BalanceLowLimit;
	}
    OSAL_EXIT_CRITICAL();
	
	/************************************
      置控制器自身状态OK + 控制器CAN通讯OK
    *************************************/
    OSAL_ENTER_CRITICAL();
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerStatus    
								= COMM_CONTROLER_OK; 
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus 
								= COMM_COMMUNICAITON_OK;
	
	if((ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.ExpireTicks)> 0u)
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.CurTicks   
								= OSALTimeGet();/*刷新通讯超时时间*/
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.ExpireTicks
								= pControllCfg->FaultTimeOut;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus
								= TIMER_ON;	   	/*重启定时Timer*/

		if(ControllOffset==0)
		{
			equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta = 1;
		}
		else if(ControllOffset==1)
		{
			equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta = 1;
		}				
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);	
}

/************************************************************
* 函数名称:ComM_BusOffIndication
* 函数描述:通知ComM模块,设备号=DevId的CAN控制器产生BusOff.
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 返回值  :E_OK:下层通知成功
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:可重入
* 备注	  :
*************************************************************/
Std_ReturnType ComM_BusOffIndication(uint8 DevId)
{
	uint8  GroupOffset = 0u;
	uint8  ControllOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_BUSOFFINDICATION_ID,
						COMM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	/**************************/
	ret = ComM_SearchDeviceInConfig(DevId,&GroupOffset,&ControllOffset);
	if(E_NOT_OK == ret)
	{
		/*DevId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_BUSOFFINDICATION_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}

	/**********************/
	OSAL_ENTER_CRITICAL();	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerStatus 
							= COMM_CONTROLER_BUSOFF;	/*置控制器状态"BusOff"*/
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus      
							= COMM_COMMUNICAITON_ERR;  	/*置控制器通讯状态"Communication Error"*/
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus 
	                        = TIMER_OFF;				/*关闭定时器*/
	OSAL_EXIT_CRITICAL();
	
	/*停止CAN控制器*/
	//Can_EnterStopMode(DevId);

	/*********************************/
	/*Modified by chenms 2018-6-6,pm16:07*/
	/*①通知CanIf模块,清除对应的发送队列*/
	CanIf_ResetTransmitQueue(DevId);

	/*②-清除控制器--正在发送标识*/
	/*③-关闭控制器中断发送跟踪定时器*/
	/*④-禁止发送中断*/
    CanIf_TransmitQueueIsEmpty(DevId);
	
	/*⑤-终止发送指定控制器硬件Buffer中的Pending报文*/
	Can_RequestTransmitterMessageAbort(DevId);
	return(E_OK);	
}

/************************************************************
* 函数名称:ComM_GetTrustInfo
* 函数描述:获取组号=GroupId的信任总线信息.
* 输入参数:GroupId:双CAN冗余组ID号;
* 输出参数:(*pTrustInfo):冗余组信任总线信息,内容为指定组内信任控制器ID号;
* 输入/输出参数:
* 返回值  :E_OK:成功读取冗余组信任总线信息
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
Std_ReturnType ComM_GetTrustInfo(uint8 GroupId,uint8 *pTrustInfo)
{
	uint8  GroupOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETTRUSTINFO_ID,
						COMM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	/**************************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)		
	{
		/*GroupId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETTRUSTINFO_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	/**************************/
	OSAL_ENTER_CRITICAL();
	(*pTrustInfo) = ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus;
	OSAL_EXIT_CRITICAL();
	return(E_OK);	
}

/************************************************************
* 函数名称:ComM_GetControllerStatus
* 函数描述:获取设备号=DevId的CAN控制器状态信息.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pControllerStatus):Can控制器状态信息; 
           = 0:COMM_CONTROLLER_OK 控制器状态OK; 
           = 1:COMM_CONTROLLER_BUSOFF  控制器状态busOff;
* 输入/输出参数:
* 返回值  :E_OK:成功读取控制器状态信息;
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
Std_ReturnType ComM_GetControllerStatus(uint8 DevId,uint8 *pControllerStatus)
{
	
	uint8  GroupOffset = 0u;
	uint8  ControllOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	(*pControllerStatus) = COMM_CONTROLER_BUSOFF;
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETCONTROLLERSTATUS_ID,
						COMM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	/**************************/
	ret = ComM_SearchDeviceInConfig(DevId,&GroupOffset,&ControllOffset);
	if(E_NOT_OK == ret)
	{
		/*DevId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETCONTROLLERSTATUS_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	/**************************/
	OSAL_ENTER_CRITICAL();
	(*pControllerStatus) = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerStatus;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}
/************************************************************
* 函数名称:ComM_GetControllerCommStatus
* 函数描述:获取设备号=DevId控制器的通讯状态信息.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pCommStatus):Can控制器通讯状态; 
    		= 0u:COMM_COMMUNICAITON_OK   控制器通信正常
    		= 1u:COMM_COMMUNICAITON_ERR  控制器通信故障
* 输入/输出参数:
* 返回值  :E_OK:成功读取控制器状态信息;
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
Std_ReturnType ComM_GetControllerCommStatus(uint8 DevId,uint8 *pCommStatus)
{
	
	uint8  GroupOffset = 0u;
	uint8  ControllOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	(*pCommStatus) = COMM_COMMUNICAITON_ERR;
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETCONTROLLERCOMMSTATUS_ID,
						COMM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	/**************************/
	ret = ComM_SearchDeviceInConfig(DevId,&GroupOffset,&ControllOffset);
	if(E_NOT_OK == ret)
	{
		/*DevId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_GETCONTROLLERCOMMSTATUS_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	/**************************/
	OSAL_ENTER_CRITICAL();
	(*pCommStatus) = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* 函数名称: ComM_MainFunction
* 函数描述: ComM模块后台主循环.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pControllerStatus):Can控制器状态信息;
* 输入/输出参数:
* 返回值  : 无
* 可重入性:
* 备注	  :该函数需要被周期调用
*************************************************************/
void ComM_MainFunction(void)
{
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_MAINFUNCTION_ID,
						COMM_E_UNINIT);					
#endif
		return;
	}

	/**************************/
	/*计算各个控制器接收通讯超时*/
	ComM_MainFunctionForCalcCommunicationFault();

	/*计算各个冗余组中的信任总线信息*/
	ComM_MainFunctionForCalcTrustInfo();
}

#if 1
/************************************************************
* 函数名称:ComM_InitGroup
* 函数描述:ComM模块初始化指定冗余组;
* 输入参数:GroupId:冗余组ID号
* 输出参数:无
* 输入/输出参数:无
* 返回值  :
* 可重入性:可重入
* 备注	  :
*************************************************************/
STATIC void ComM_InitGroup(uint8  GroupId)
{
	uint8  GroupOffset   = 0u;
	uint8  ControllOffset= 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/***************************************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)		
	{
		/*GroupId无效*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_INITGROUP_ID,
						COMM_E_PARAM_INVALID);					
#endif
		return;
	}

	/***************************************/
	OSAL_ENTER_CRITICAL();
	ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId 		= ComM_Cfg.pGroupCfg[GroupOffset].GroupId;
	ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance;
	ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus     = ComM_Cfg.pGroupCfg[GroupOffset].TrustBusAtPowerOn;
	/**************************
	      冗余组内控制器0
	 **************************/
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId 			= ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[0].DevId;
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus 		= COMM_CONTROLER_OK;	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus 	= COMM_COMMUNICAITON_OK;
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].TimerCtrl.TimerStatus = TIMER_OFF;
	if( ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[0].FaultTimeOut > 0u)
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].TimerCtrl.CurTicks 	= OSALTimeGet();
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].TimerCtrl.ExpireTicks = ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[0].FaultTimeOut; 
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].TimerCtrl.TimerStatus = TIMER_ON;
	}
	/**************************
	      冗余组内控制器1
	 **************************/
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId 			= ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[1].DevId;
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus 		= COMM_CONTROLER_OK;	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus 	= COMM_COMMUNICAITON_OK;
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].TimerCtrl.TimerStatus = TIMER_OFF;
	if(ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[1].FaultTimeOut > 0u)
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].TimerCtrl.CurTicks 	= OSALTimeGet();
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].TimerCtrl.ExpireTicks = ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[1].FaultTimeOut; 
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].TimerCtrl.TimerStatus = TIMER_ON;		
	}
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:ComM_SearchDeviceInConfig
* 函数描述:查找DevId在静态配置中的冗余组下标+冗余组内的控制器下标.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pGroupCfg):输入DevId所在的配置冗余组下标;
		   (*pControllCfg):输入DevId所在的配置冗余组包含的控制器下标;
* 输入/输出参数:
* 返回值  :E_OK:在静态配置中,查找成功;
           E_NOT_OK:在静态配置中,查找失败;
* 可重入性:
* 备注	  :
*************************************************************/
STATIC Std_ReturnType  ComM_SearchDeviceInConfig(uint8 DevId,uint8 *pGroupCfg,uint8 *pControllCfg)
{
	uint8  GroupOffset    = 0u;
	uint8  ControllOffset = 0u;

	/**********************************/
	for(GroupOffset=0u;GroupOffset<(ComM_Cfg.NumOfComMGroup);GroupOffset++)
	{
		for(ControllOffset=0u;ControllOffset<(ComM_Cfg.pGroupCfg[GroupOffset].NumOfControllerCfg);ControllOffset++)
		{
			if(DevId == ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[ControllOffset].DevId)
			{
				(*pGroupCfg)    = GroupOffset;
				(*pControllCfg) = ControllOffset;
				return(E_OK);
			}
		}
	}
	return(E_NOT_OK);
}

/************************************************************
* 函数名称:ComM_SearchGroupInConfig
* 函数描述:查找GroupId在静态配置中的冗余组下标.
* 输入参数: GroupId:冗余组ID号;
* 输出参数:(*pGroupCfg):GroupId所在的配置冗余组下标;
* 输入/输出参数:
* 返回值  :E_OK:在静态配置中,查找成功;
           E_NOT_OK:在静态配置中,查找失败;
* 可重入性:
* 备注	  :
*************************************************************/
STATIC Std_ReturnType  ComM_SearchGroupInConfig(uint8 GroupId,uint8 *pGroupCfg)
{
	uint8  GroupOffset = 0u;
	/**********************************/
	for(GroupOffset=0u;GroupOffset<(ComM_Cfg.NumOfComMGroup);GroupOffset++)
	{
		if(GroupId == ComM_Cfg.pGroupCfg[GroupOffset].GroupId)
		{
			(*pGroupCfg) = GroupOffset;
			return(E_OK);
		}
	}
	return(E_NOT_OK);
}
/************************************************************
* 函数名称:ComM_MainFunctionForCalcCommunicationFault
* 函数描述:模块后台循环计算各个控制器是否通讯故障
* 输入参数:无
* 输出参数:无
* 输入/输出参数:
* 返回值  :无
* 可重入性:
* 备注	  :该函数在被ComM_MainFunction()调用;
*************************************************************/
STATIC void  ComM_MainFunctionForCalcCommunicationFault(void)
{
	uint8  GroupOffset    = 0u;
	uint8  ControllOffset = 0u;
	uint32 CurTicks = 0ul;
	uint32 ExpireTicks = 0ul;
	uint32 ElapseTicks = 0ul;
	uint32 TraceTicks  = 0ul;
	
	for(GroupOffset=0u;GroupOffset<(ComM_Cfg.NumOfComMGroup);GroupOffset++)
	{
		for(ControllOffset=0u;ControllOffset<(ComM_Cfg.pGroupCfg[GroupOffset].NumOfControllerCfg);ControllOffset++)
		{
			if(TIMER_ON == (ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus))
			{
				OSAL_ENTER_CRITICAL();
				CurTicks    = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.CurTicks;
				ExpireTicks = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.ExpireTicks;
				OSAL_EXIT_CRITICAL();
				TraceTicks  = OSALTimeGet();
				ElapseTicks = (uint32)(TraceTicks - CurTicks);
				if( ElapseTicks >= ExpireTicks )
				{
/*******************************/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
Drv_Sci_Write((const uint8 *)"\r\n\r\n Receive timeout,GroupId=",0,0);
Drv_Sci_WriteCharAscii(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
Drv_Sci_Write((const uint8 *)",ControllId=",0,0);
Drv_Sci_WriteCharAscii(ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerId);
#endif
/*******************************/
					/*接收超时,置控制器正常，但通讯故障*/
					OSAL_ENTER_CRITICAL();
					ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerStatus 
											= COMM_CONTROLER_OK;
					
					ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus 
											= COMM_COMMUNICAITON_ERR;
					
					ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus 
											= TIMER_OFF;
					if(ControllOffset==0)
					{
						equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta = 2;
					}
					else if(ControllOffset==1)
					{
						equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta = 2;
					}

					OSAL_EXIT_CRITICAL();
				}
			}
		}
	}
}

/************************************************************
* 函数名称:ComM_MainFunctionForCalcCommunicationFault
* 函数描述:模块后台循环计算各组控制器的信任总线
* 输入参数:无
* 输出参数:无
* 输入/输出参数:
* 返回值  :无
* 可重入性:
* 备注	  :该函数在被ComM_MainFunction()调用;
*************************************************************/
STATIC void  ComM_MainFunctionForCalcTrustInfo(void)
{
	uint8  	GroupOffset = 0u;
	uint8	Controller0_Status = COMM_CONTROLER_OK;
	uint8	Controller1_Status = COMM_CONTROLER_OK;

	/*******************************************/
	for(GroupOffset=0u;GroupOffset<(ComM_Cfg.NumOfComMGroup);GroupOffset++)
	{
		OSAL_ENTER_CRITICAL();
		Controller0_Status = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus;
		Controller1_Status = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus;
		OSAL_EXIT_CRITICAL();	
		if(   (COMM_CONTROLER_OK == Controller0_Status)
			&&(COMM_CONTROLER_OK == Controller1_Status))
		{
			/*冗余组两路CAN控制器均OK*/
			ComM_CalcTrustBusForBothOK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
        /***************/
		else if(  (COMM_CONTROLER_OK == Controller0_Status)
			    &&(COMM_CONTROLER_BUSOFF == Controller1_Status))
		{
			/*冗余组包含的第0路控制器OK,第1路控制器BusOff*/
			ComM_CalcTrustBusInController0OK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
        /***************/
		else if(  (COMM_CONTROLER_BUSOFF == Controller0_Status)
			    &&(COMM_CONTROLER_OK == Controller1_Status))
		{
			/*冗余组包含的第0路控制器BusOff,第1路控制器OK*/
			ComM_CalcTrustBusInController1OK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
		else
		{
			/*冗余组包含的两路CAN控制器均故障*/
			ComM_CalcTrustBusInAllFault(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
	}
}

/************************************************************
* 函数名称:ComM_CalcTrustBusForBothOK
* 函数描述:在指定冗余组内,两路CAN控制器均OK的情况下,计算冗余组内信任总线.
* 输入参数:GroupId:冗余组ID号;
* 输出参数:无
* 输入/输出参数:
* 返回值  :无
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  ComM_CalcTrustBusForBothOK(uint8  GroupId)
{
	uint8  GroupOffset = 0u;
	uint8  BalanceValue  = 0u;
	uint8  ControllerIdForAddStep = 0u;
	uint8  ControllerIdForSubStep = 0u;
	ComM_ControllerSubStatusType Controller0_ComStatus;
	ComM_ControllerSubStatusType Controller1_ComStatus;
	Std_ReturnType  ret = E_NOT_OK;

	/***************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)
	{
		/*GroupId未进行配置*/
		return;
	}
	
	/***************/
	OSAL_ENTER_CRITICAL();
	Controller0_ComStatus = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus;
	Controller1_ComStatus = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus;
	OSAL_EXIT_CRITICAL();
	if(   (COMM_COMMUNICAITON_OK == Controller0_ComStatus)
		&&(COMM_COMMUNICAITON_OK == Controller1_ComStatus))
	{
	    /******************************
	     冗余组两路CAN控制器通讯均正常，
	      则根据天平值进行信任识别
	    *******************************/
	    if(TRUE == ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[0].Direct)
		{
		   /* 该冗余组包含的第一个控制器:天平值"+"步长 */
		   ControllerIdForAddStep = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
		   ControllerIdForSubStep = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
		}
		else
		{
		   ControllerIdForSubStep = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
		   ControllerIdForAddStep = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
		}
		/******************************/
		BalanceValue = ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue;
		if(BalanceValue > 60u)
		{
			/*信任操作方式为步长"+"的总线*/
			OSAL_ENTER_CRITICAL();
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = ControllerIdForAddStep;
			OSAL_EXIT_CRITICAL();
		}
		else if(BalanceValue < 40u)
		{
			/*信任操作方式为步长"-"的总线*/
			OSAL_ENTER_CRITICAL();
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = ControllerIdForSubStep;
			OSAL_EXIT_CRITICAL();
		}
		else
		{
			/* 40<=BalanceValue<=60*/
			/* Nothing to do */
		}
	}
	else if(   (COMM_COMMUNICAITON_OK == Controller0_ComStatus)
		     &&(COMM_COMMUNICAITON_ERR== Controller1_ComStatus))
	{
		/*冗余组内第1路通讯正常,第2路通讯异常,信任第1路*/
		if( ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
				ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId )
		{
			/*信任总线已切换为信任第1路*/
			/* Nothing to do */ 
		}
		else
		{
			OSAL_ENTER_CRITICAL();
			/*切换为信任第1路*/
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = 
							ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;

			/*当前信任天平值恢复为信任初值*/
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = 
							ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance;
			OSAL_EXIT_CRITICAL();
		}
	}
	else if(   (COMM_COMMUNICAITON_ERR == Controller0_ComStatus)
		     &&(COMM_COMMUNICAITON_OK  == Controller1_ComStatus))
	{
		/*冗余组内第1路通讯异常,第2路通讯正常,信任第2路*/
		if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
			ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId )
		{
			/* 当前已经信任第2路 */
			/* Nothing to do */
		}
		else
		{
			OSAL_ENTER_CRITICAL();
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = 
						ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;

			ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = 
						ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance;				
			OSAL_EXIT_CRITICAL();
		}
	}
	else
	{
		/*冗余组内第1路,第2路均通讯异常,保持之前信任信息*/
		//OSAL_ENTER_CRITICAL();
		//ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus 
		//			= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
		//OSAL_EXIT_CRITICAL();
	}
}

/************************************************************
* 函数名称:ComM_CalcTrustBusInController0OK
* 函数描述:在指定冗余组内,第0路控制器OK,第1路控制器故障的情况下,计算冗余组内信任总线.
* 输入参数:GroupNum:冗余组ID号;
* 输出参数:无
* 输入/输出参数:
* 返回值  :无
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  ComM_CalcTrustBusInController0OK(uint8  GroupId)
{
	uint8 	GroupOffset = 0u;
	uint8 	Controller1_Id = 0u;
	uint8   Controller1_Status = 0xFFu;
	Std_ReturnType  ret = E_NOT_OK;

	/***************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)
	{
		/*GroupId未进行配置*/
		return;
	}

	/*********************************
     查询冗余组内第1路控制器是否自恢复
     *********************************/
	Controller1_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
    Can_GetControllerStatus(Controller1_Id, &Controller1_Status);

	OSAL_ENTER_CRITICAL();
	if((0u == Controller1_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus))
	{
		/*冗余组内第1路控制器
		  已自恢复(TxOK or TxWRN or TxERR) */
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus 
		              = COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus       
					  = COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*冗余组内第1路控制器未自恢复(Bus-Off)或第1路控制器已经恢复且接收到报文通知*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	/******************************
	   切换信任为冗余组内控制器0
	 ******************************/
	if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
		       ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId)
	{
		/*冗余组已经信任第0路控制器,则忽略*/
		;
	}
	else
	{
	    /*冗余组当前信任第1路控制器，切换信任总线*/
		OSAL_ENTER_CRITICAL();
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus     
					= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;

		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue 
					= ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance; /*天平值恢复为初值*/
		OSAL_EXIT_CRITICAL();
	}
}

/************************************************************
* 函数名称:ComM_CalcTrustBusInController1OK
* 函数描述:在指定冗余组内,第0路控制器故障,第1路控制器OK的情况下,计算冗余组内信任总线.
* 输入参数:GroupId:冗余组ID号;
* 输出参数:无
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  ComM_CalcTrustBusInController1OK(uint8  GroupId)
{
	uint8   GroupOffset = 0u;
	uint8 	Controller0_Id = 0u;
	uint8   Controller0_Status = 0xFFu;
	Std_ReturnType  ret = E_NOT_OK;

	/***************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)
	{
		/*GroupId未进行配置*/
		return;
	}

	/*********************************
     查询冗余组内第0路控制器是否自恢复
     *********************************/
	Controller0_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
	Can_GetControllerStatus(Controller0_Id, &Controller0_Status);

	OSAL_ENTER_CRITICAL();
	if((0u == Controller0_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus))
	{
		/*冗余组内第0路控制器
		  已自恢复(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus 
							= COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus       
							= COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*冗余组内第0路控制器未自恢复(Bus-Off)或第0路控制器已经恢复且接收到报文通知*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	
	/******************************
	   切换信任为冗余组内控制器1
	 ******************************/
	if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
		       ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId)
	{
		/*冗余组已经信任第1路控制器,则忽略*/
		;
	}
	else
	{
		/*冗余组当前信任第0路控制器，切换信任总线*/
		OSAL_ENTER_CRITICAL();
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus 
						= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue 
						= ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance; /*天平值恢复为初值*/
		OSAL_EXIT_CRITICAL();
	}
}
/************************************************************
* 函数名称:ComM_CalcTrustBusInController1OK
* 函数描述:在指定冗余组内,第0路+第1路均故障情况下.
* 输入参数:GroupNum:冗余组ID号;
* 输出参数:无
* 输入/输出参数:
* 返回值  :无
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  ComM_CalcTrustBusInAllFault(uint8  GroupId)
{
	uint8 	GroupOffset = 0u;
	uint8 	Controller0_Id = 0u;
	uint8 	Controller1_Id = 0u;
	uint8   Controller0_Status = 0xFF;
	uint8   Controller1_Status = 0xFF;
	Std_ReturnType  ret = E_NOT_OK;
	
	/***************/
	ret = ComM_SearchGroupInConfig(GroupId,&GroupOffset);
	if(E_NOT_OK == ret)
	{
		/*GroupId未进行配置*/
		return;
	}
	/*********************************
     查询冗余组内第0路控制器是否自恢复
     *********************************/
	Controller0_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
	Can_GetControllerStatus(Controller0_Id, &Controller0_Status);
	
	OSAL_ENTER_CRITICAL();
	if((0u == Controller0_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus))
	{
		/*冗余组内第0路控制器
		  已自恢复(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus 
							= COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus       
							= COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*冗余组内第0路控制器未自恢复(Bus-Off)或第0路控制器已经恢复且接收到报文通知*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	
	/*********************************
     查询冗余组内第1路控制器是否自恢复
     *********************************/
	Controller1_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
    Can_GetControllerStatus(Controller1_Id, &Controller1_Status);
    
	OSAL_ENTER_CRITICAL();
	if((0u == Controller1_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus))
	{
		/*冗余组内第1路控制器
		  已自恢复(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus 
		              = COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus       
					  = COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*冗余组内第1路控制器未自恢复(Bus-Off)或第1路控制器已经恢复且接收到报文通知*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
}

#endif

