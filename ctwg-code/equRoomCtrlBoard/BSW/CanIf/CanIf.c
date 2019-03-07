/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : CanIf.c
* 功能描述  : Can控制器接口层实现源文件(CanIf.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
**------------------------------------------------------------------------------------------------*/
#include "CanIf.h"
#include "ComM.h"
#include "Can.h"
#include "Com.h"
#include "Osal.h"
#include "drv_sci.h"

/****************************************
            运行时数据结构类型定义
 ****************************************/
typedef  enum
{
	TIMER_OFF = 0u,
	TIMER_ON  = 1u
}CanIf_TimerStatusType;

typedef struct
{
	uint32  CurTicks;
	uint32  ExpireTicks;
	CanIf_TimerStatusType TimerStatus;
}CanIf_TimerCtrlType;

/*************************/
typedef  struct
{
	uint8	Rin;
   	uint8	ROut;
   	PduInfoType	PduInfo[CAN_RXBUFFSIZE];
}CanIf_ControllerRxDataType;

typedef  struct
{
   	uint8	Tin;
   	uint8	TOut;
   	PduInfoType	PduInfo[CAN_TXBUFFSIZE];
}CanIf_ControllerTxDataType;

typedef  struct
{
	CanIf_ControllerRxDataType	RxData;
	CanIf_ControllerTxDataType	TxData;
	boolean  IsTransmitting; 			/*=FALSE:控制器未发送;=TRUE:表明CAN控制器当前正在发送*/
}CanIf_ControllerDataType;

/**************************/
typedef  enum
{
	CANIF_UNINIT = 0u,		/*模块未初始化*/
	CANIF_INIT   = 1u,
}CanIf_MkStatusType;

typedef  struct
{
	CanIf_ControllerDataType ControllerData[CANIF_CONTROLLER_NUM];
	CanIf_TimerCtrlType      ControllerIsrTxTimer[CANIF_CONTROLLER_NUM]; /*控制器中断发送跟踪运行时数据结构(2018-5-22,pm 19:01)*/
    CanIf_MkStatusType	     MkStatus;
}CanIf_MkCtrlType;

/*****************************************
            运行时数据结构定义
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile CanIf_MkCtrlType  CanIf_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            静态函数声明
 ****************************************/
#if  1
STATIC void  CanIf_InitController(uint8 DevId);
STATIC Std_ReturnType  CanIf_SearchDeviceConfigIndex(uint8 DevId,uint8 *pDevCfgIndex);
STATIC Std_ReturnType  CanIf_ReadRxPacket(uint8 DevId,PduInfoType *pPduInfo);
STATIC void  CanIf_InitControllerIsrTxTimer(uint8 DevId);
STATIC void  CanIf_StartControllerIsrTxTimer(uint8 DevId);
STATIC void  CanIf_FreshControllerIsrTxTimer(uint8 DevId);
STATIC void  CanIf_StopControllerIsrTxTimer(uint8 DevId);
STATIC void  CanIf_RxMainfunction(void); 
STATIC void  CanIf_TxMainfunction(void);
STATIC void  CanIf_TxMainfunctionForIsrTxTimer(void);
#endif
/************************************************************
* 函数名称: CanIf_Init
* 函数描述: CanIf模块初始化.
* 输入参数: 无
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入
* 返回值  : 无 
* 备注	  :
*************************************************************/
void  CanIf_Init(void)
{
	uint8 ControllerIndex = 0u;
	uint8 ControllerId = 0u;
	uint8 GroupIndex = 0u;
	
	/***************************
	        配置参数有效性检查
	 ***************************/
	if(CANIF_CONTROLLER_NUM != CanIf_Cfg.NumOfController)
	{
		/*模块配置的控制器数量不一致*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_INIT_ID,
						CANIF_E_CONFIGPARAM_INVALID);
#endif
		return;
	}

	for(GroupIndex=0u;GroupIndex<(CanIf_Cfg.NumOfGroup);GroupIndex++)
	{
		if(	(CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ControllerId)
			== (CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ControllerId))
		{
			/*相同组内的两个控制器ID号相同*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
			Det_ReportError(MODULE_ID_CANIF,
							CanIf_Cfg.pGroupCfg[GroupIndex].GroupId,
							CANIF_INIT_ID,
							CANIF_E_CONFIGPARAM_INVALID);		
#endif
			return;			
		}
		/**************************/
		if(	(CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ProtocolId)
			!= (CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ProtocolId))
		{
			/*相同组内的两个控制器对应的协议ID号不同*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
			Det_ReportError(MODULE_ID_CANIF,
							CanIf_Cfg.pGroupCfg[GroupIndex].GroupId,
							CANIF_INIT_ID,
							CANIF_E_CONFIGPARAM_INVALID);	
#endif
			return;			
		}	
	}
	
	/**************************/
	for(ControllerIndex=0u;ControllerIndex<(CanIf_Cfg.NumOfController);ControllerIndex++)
	{
	    ControllerId = CanIf_Cfg.pControllerCfg[ControllerIndex].ControllerId;
		CanIf_InitController(ControllerId);

		/***********************************/
		/*added by chenms 2018-5-23 9:28*/
		CanIf_InitControllerIsrTxTimer(ControllerId);
		/***********************************/
	}
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.MkStatus = CANIF_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称: CanIf_RxIndication
* 函数描述: 通知CanIf模块,设备号为DevId的控制器接收到报文;
* 输入参数: DevId  :CAN控制器设备ID
		    PduInfo:接收到的报文信息
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  : E_OK:下层通知成功;
            E_NOT_OK:下层通知失败;
* 备注	  :下层Can驱动模块接收中断(Rx ISR)调用
*************************************************************/
Std_ReturnType CanIf_RxIndication(uint8 DevId, const PduInfoType PduInfo)
{
	uint8  dis = 0u;
	uint8  Rin = 0u;
	uint8  Rout= 0u;
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RXINDICATION_ID,
						CANIF_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RXINDICATION_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
	OSAL_ENTER_CRITICAL();
	Rin  = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.Rin;
	Rout = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.ROut;
	OSAL_EXIT_CRITICAL();
	
	dis = (uint8)(Rin - Rout);
    if(dis >= CAN_RXBUFFSIZE)
	{
		/*接收缓存已满，放弃接收报文*/
#if 0
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						DevId,
						CANIF_TRANSMIT_ID,
						CANIF_E_RECEIVEBUFF_FULL);		
#endif
#endif
		return(E_NOT_OK);
	}
	OSAL_ENTER_CRITICAL();
    CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.PduInfo[Rin & (CAN_RXBUFFSIZE - 1u)] = PduInfo;
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.Rin++;
	OSAL_EXIT_CRITICAL();
	return(E_OK);	
}

/************************************************************
* 函数名称:CanIf_Transmit
* 函数描述:通知DevId指定Can控制器发送一帧报文;
* 输入参数:DevId  :控制器ID号;
           PduInfo:待发送报文;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  : E_OK:发送成功;
            E_NOT_OK:发送失败;
* 备注	  :上层Com模块调用
*************************************************************/
Std_ReturnType CanIf_Transmit(uint8 DevId,const PduInfoType PduInfo)
{
    uint8  Tin = 0u;
	uint8  Tout= 0u;
	uint8  dis = 0u;
	uint8  DevIdCfgIndex = 0u;
	uint8  ControllerStatus = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TRANSMIT_ID,
						CANIF_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}

	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TRANSMIT_ID,
						CANIF_E_PARAM_INVALID);		
#endif
		return(E_NOT_OK);
	}
	/**************************/
    ret = ComM_GetControllerStatus(DevId,&ControllerStatus);
    if((E_NOT_OK == ret) || (0u != ControllerStatus))
	{
		/*控制器状态为"BusOff",则直接退出*/
#if 0
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						DevId,
						CANIF_TRANSMIT_ID,
						CANIF_E_CONTROLLER_BUSOFF);		
#endif
#endif
		return(E_NOT_OK);
	}

	/*缓存待发送报文*/
	OSAL_ENTER_CRITICAL();
	Tin = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin;
	Tout= CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut;
	OSAL_EXIT_CRITICAL();
	
	dis = (uint8)(Tin - Tout);
	if(dis >= CAN_TXBUFFSIZE)
	{
		/*发送缓存已满，放弃发送报文*/
#if 0
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						DevId,
						CANIF_TRANSMIT_ID,
						CANIF_E_TRANSBUFF_FULL);		
#endif
#endif
		return(E_NOT_OK);
	}
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.PduInfo[Tin & (CAN_TXBUFFSIZE - 1u)] = PduInfo;
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin++;
	OSAL_EXIT_CRITICAL();
	/**************************/
	if(FALSE == CanIf_MkCtrl.ControllerData[DevIdCfgIndex].IsTransmitting)
	{
	    /*对应控制器空闲,准备发送*/
		OSAL_ENTER_CRITICAL();
		CanIf_MkCtrl.ControllerData[DevIdCfgIndex].IsTransmitting = TRUE;
		OSAL_EXIT_CRITICAL();

		/***********************************/
		/*added by chenms 2018-5-23,am 9:28*/
		CanIf_StartControllerIsrTxTimer(DevId); /*启动控制器中断发送跟踪定时器*/
		/***********************************/
		
		Can_EnableTxInterrupt(DevId); /*使能发送中断，则立刻产生中断*/
		return(E_OK);
	}
}

/************************************************************
* 函数名称: CanIf_ResetTransmitQueue
* 函数描述: 通知CanIf模块,清除DevId指定控制器的发送队列;
* 输入参数: DevId:控制器ID号
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入
* 返回值  : 无
* 备注	  : 下层Can驱动模块调用
*************************************************************/
void  CanIf_ResetTransmitQueue(uint8 DevId)
{
	uint8  TxIndex = 0u;
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret   = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RESET_TRANSMITQUENE_ID,
						CANIF_E_UNINIT);				
#endif
		return;
	}
	
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RESET_TRANSMITQUENE_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return;
	}
	/*************************
	  复位DevId对应的发送队列
	**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin = 0u;
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut= 0u;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称: CanIf_TransmitQueueIsEmpty
* 函数描述: 通知CanIf模块,DevId指定控制器的发送队列已经为空;
* 输入参数: DevId:设备ID号
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入
* 返回值  : 无
* 备注	  : 下层Can驱动模块发送中断函数(Tx ISR)调用
*************************************************************/
void  CanIf_TransmitQueueIsEmpty(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TRANSMITQUENE_ISEMPTY_ID,
						CANIF_E_UNINIT);		
#endif
		return;
	}

	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TRANSMITQUENE_ISEMPTY_ID,
						CANIF_E_PARAM_INVALID);	
#endif
		return;
	}
	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].IsTransmitting = FALSE; /*控制器发送停止*/
	OSAL_EXIT_CRITICAL();

	/***********************************/
	/*added by chenms 2018-5-23,am 9:28*/
	CanIf_StopControllerIsrTxTimer(DevId); /*关闭控制器中断发送跟踪定时器*/
	/***********************************/
		
	/*禁止发送中断*/
	Can_DisableTxInterrupt(DevId);
    return;	
}

/************************************************************
* 函数名称:CanIf_GetNextPacket
* 函数描述:通知CanIf模块,从DevId指定的Can控制器发送队列中,
		   获取一帧待发送报文;
* 输入参数:DevId:
		  (*pPduInfo):
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  : E_OK: 获取一帧待发送报文成功;
            E_NOT_OK: 获取一帧待发送报文失败;
* 备注	  :下层Can驱动模块发送中断(Tx ISR)调用
*************************************************************/
Std_ReturnType CanIf_GetNextPacket(uint8 DevId,PduInfoType *pPduInfo)
{
	uint8  Tin = 0u;
	uint8  Tout= 0u;
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_GETNEXTPACKET_ID,
						CANIF_E_UNINIT);			
#endif
		return(E_NOT_OK);
	}

	/*****/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_GETNEXTPACKET_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return(E_NOT_OK);
	}

	/*****/
	if(NULL_PTR == pPduInfo)
	{ 
		/*参数值无效*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_GETNEXTPACKET_ID,
						CANIF_E_PARAM_INVALID);		
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
 	OSAL_ENTER_CRITICAL();
    Tin = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin;
	Tout= CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut;
	OSAL_EXIT_CRITICAL();
	
	if(Tin == Tout)
	{
		/*发送缓存空*/
		return(E_NOT_OK);
	}	
 	OSAL_ENTER_CRITICAL();
    (*pPduInfo) = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.PduInfo[Tout & (CAN_TXBUFFSIZE - 1u)];
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut++;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
	
}

/************************************************************
* 函数名称:CanIf_Mainfunction
* 函数描述:CanIf模块提供的后台主循环
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  : 无;
* 备注	  :该函数需要被周期调用
*************************************************************/
void CanIf_Mainfunction(void) 
{
	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_MAINFUNCTION_ID,
						CANIF_E_UNINIT);		
#endif
		return;
	}
	
	/**************************/
	CanIf_RxMainfunction();
	CanIf_TxMainfunction();
}
/************************************************************
* 函数名称:CanIf_RxIndicationHook
* 函数描述:Can控制器接收中断通知钩子函数
* 输入参数:DevId  :设备ID号;
           (*pPduInfo):接收到的CAN报文
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无;
* 备注	  :下层Can驱动模块接收中断(Rx ISR)调用
*************************************************************/
Std_ReturnType CanIf_RxIndicationHook(uint8 DevId, const PduInfoType *pPduInfo)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RXINDICATIONHOOK_ID,
						CANIF_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RXINDICATIONHOOK_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
	if(NULL_PTR == pPduInfo)
	{
		/*入口参数无效*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RXINDICATIONHOOK_ID,
						CANIF_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
	Com_RxIndicationHook(DevIdCfgIndex,pPduInfo);
	return(E_OK);	
}

/************************************************************
* 函数名称:CanIf_TxConfirmHook
* 函数描述:Can控制器发送完成中断通知钩子函数
* 输入参数:DevId:设备ID号;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无;
* 备注	  :下层Can驱动模块发送完成中断(Tx ISR)调用
*************************************************************/
Std_ReturnType CanIf_TxConfirmHook(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TXCONFIRMHOOK_ID,
						CANIF_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TXCONFIRMHOOK_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return(E_NOT_OK);
	}
	
	/***********************************/
	/*①added by chenms 2018-5-23,am 9:28*/
	CanIf_FreshControllerIsrTxTimer(DevId); /*刷新控制器中断发送跟踪定时器*/

	return(E_OK);	
}

/************************************************************
						静态函数定义
 ************************************************************/
#if 1
/************************************************************
* 函数名称: CanIf_InitController
* 函数描述: 初始化指定控制器在CanIf模块中的运行时数据结构.
* 输入参数: DevId:控制器ID号;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入
* 返回值  : 无 
* 备注	  :
*************************************************************/
STATIC void  CanIf_InitController(uint8 DevId)
{
	uint8 ControllerIndex = 0u;
	uint8 TxIndex = 0u;
	uint8 RxIndex = 0u;
	Std_ReturnType  ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&ControllerIndex);
    if(E_NOT_OK == ret)
	{
		/*参数值未配置,无效*/	
	   return;
	}
	
	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[ControllerIndex].IsTransmitting = FALSE;/*默认控制器无发送*/
	CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.Tin = 0u;
	CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.TOut= 0u;
	for(TxIndex=0u;TxIndex<CAN_TXBUFFSIZE;TxIndex++)
	{
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduId = 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduLength = 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[0]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[1]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[2]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[3]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[4]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[5]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[6]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].TxData.PduInfo[TxIndex].PduData[7]= 0u;
	}
	/****************/
	CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.Rin = 0u;
	CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.ROut= 0u;	
	for(RxIndex=0u;RxIndex<CAN_RXBUFFSIZE;RxIndex++)
	{
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduId = 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduLength = 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[0]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[1]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[2]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[3]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[4]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[5]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[6]= 0u;
		CanIf_MkCtrl.ControllerData[ControllerIndex].RxData.PduInfo[RxIndex].PduData[7]= 0u;
	}
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:	CanIf_SearchDeviceConfigIndex
* 函数描述:	在模块静态配置结构中，查找是否DevId配置；
* 输入参数:	DevId: 设备ID号
* 输出参数:	(*pDevCfgIndex):设备配置索引;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  :	E_OK:在模块静态配置中,查找DevId成功;
           	E_NOT_OK:在模块静态配置中,查找DevId失败;
* 备注	  :
*************************************************************/
STATIC Std_ReturnType CanIf_SearchDeviceConfigIndex(uint8 DevId,uint8 *pDevCfgIndex)
{
	uint8   Index = 0u;
	Std_ReturnType  ret = E_NOT_OK;

	for(Index=0u;Index<(CanIf_Cfg.NumOfController);Index++)
	{
	    if(DevId == CanIf_Cfg.pControllerCfg[Index].ControllerId)
    	{
    		/*参数DevId,被静态配置*/
			(*pDevCfgIndex) = Index;
			break;
    	}
	}
	if(Index == (CanIf_Cfg.NumOfController))
	{
	    ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}
	return ret;
}

/************************************************************
* 函数名称:	CanIf_ReadRxPacket
* 函数描述:	读取接收到的报文
* 输入参数:	DevId: 设备ID号
* 输出参数:	(*pPduInfo):接收报文内容;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  :	E_OK:读取指定设备接收报文成功;
           	E_NOT_OK:读取指定设备接收报文失败;
* 备注	  :
*************************************************************/
STATIC  Std_ReturnType  CanIf_ReadRxPacket(uint8 DevId,PduInfoType *pPduInfo)
{
	uint8  Rin = 0u;
	uint8  Rout= 0u;
	uint8  DevIdCfgIndex = 0u;
    Std_ReturnType  ret = E_NOT_OK;
	
    /**********************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
    if(E_NOT_OK == ret)
	{
		/*参数DevId,未配置*/
		return(E_NOT_OK);
	}
	OSAL_ENTER_CRITICAL();
    Rin = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.Rin;
	Rout= CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.ROut;
	OSAL_EXIT_CRITICAL();	
	if(Rin == Rout)
	{
		/*接收缓存空*/
		return(E_NOT_OK);
	}
	
	OSAL_ENTER_CRITICAL();
	(*pPduInfo) = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.PduInfo[Rout & (CAN_RXBUFFSIZE - 1u)];
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.ROut++;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* 函数名称: CanIf_InitControllerIsrTxTimer
* 函数描述: 初始化指定控制器在CanIf模块中的运行时数据结构.
* 输入参数: DevId:控制器ID号;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入
* 返回值  : 无 
* 备注	  : added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void  CanIf_InitControllerIsrTxTimer(uint8 DevId)
{
	uint8 DevIdCfgIndex = 0u;
	Std_ReturnType  ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
    if(E_NOT_OK == ret)
	{
		/*参数值未配置,无效*/	
	   return;
	}
	
	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].ExpireTicks = CANIF_CONTROLLER_ISRTXTICKS;
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_OFF; /*默认定时器关闭*/
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:CanIf_StartControllerIsrTxTimer
* 函数描述:启动指定控制器的中断发送定时器;
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无
* 备注	  :added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void CanIf_StartControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	/*启动对应控制器的中断发送追踪定时器*/
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].CurTicks    = OSALTimeGet();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].ExpireTicks = CANIF_CONTROLLER_ISRTXTICKS;
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_ON;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:CanIf_FreshControllerIsrTxTimer
* 函数描述:刷新指定控制器的中断发送定时器;
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无
* 备注	  :added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void CanIf_FreshControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	if(TIMER_ON == CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus)
	{	
		/*刷新对应控制器的中断发送追踪定时器*/
		CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].CurTicks = OSALTimeGet();
	}
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:CanIf_StopControllerIsrTxTimer
* 函数描述:停止指定控制器的中断发送定时器;
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无
* 备注	  :
*************************************************************/
STATIC void CanIf_StopControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*参数值未配置,无效*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_OFF;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:CanIf_RxMainfunction
* 函数描述:CanIf模块提供后台主循环(接收处理)
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  : 无;
* 备注	  :该函数需要被周期调用
*************************************************************/
uint8  TrustControllerId_Old = 0xFFu;  
STATIC void CanIf_RxMainfunction(void) 
{

    uint8  GroupIndex = 0u;
	uint8  GroupEmptyCount = 0u;
	uint8  TrustControllerId = 0u;
	PduInfoType PduInfo1;
	PduInfoType	PduInfo2;
	Std_ReturnType  ret1 = E_NOT_OK;
	Std_ReturnType  ret2 = E_NOT_OK;
	
	/**************************/
	while(1)
	{
		GroupEmptyCount = 0u;
		for(GroupIndex=0u;GroupIndex<(CanIf_Cfg.NumOfGroup);GroupIndex++)
		{
			ret1 = CanIf_ReadRxPacket((CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ControllerId),&PduInfo1);
			ret2 = CanIf_ReadRxPacket((CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ControllerId),&PduInfo2);

			/*获取冗余组控制器信任信息*/
			ComM_GetTrustInfo(CanIf_Cfg.pGroupCfg[GroupIndex].GroupId,&TrustControllerId);
/****************************/
#if 0
if(TrustControllerId != TrustControllerId_Old)
{
	TrustControllerId_Old = TrustControllerId;
	Drv_Sci_Write((const uint8 *)"\r\n\r\n Trust bus Id=0x",0,0);
	Drv_Sci_WriteCharAscii(TrustControllerId);
}
#endif
/****************************/
			if(	(TrustControllerId == CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ControllerId)
				&&(E_OK == ret1))
			{
			    /*信任冗余组内控制器1，且控制器1读取数据成功*/
				Com_RxIndication(CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ProtocolId,
								 PduInfo1);
			}
			else if(  (TrustControllerId == CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ControllerId) 
					&&(E_OK == ret2))
			{
			    /*信任冗余组内控制器2，且控制器2读取数据成功*/
				Com_RxIndication(CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ProtocolId,
								 PduInfo2);
			}
			else if((E_NOT_OK == ret1) && (E_NOT_OK == ret2))
			{
				 /*冗余组内控制器读取数据均不成功*/
				 GroupEmptyCount++;
			}
			else
			{
				/*Nothing to do 
				 (1)信任控制器1，但仅控制器2有接收报文
				 (2)信任控制器2，但仅控制器1有接收报文*/
			}
		}
		/**************************/
		if(GroupEmptyCount == (CanIf_Cfg.NumOfGroup))
		{
			/*CanIf模块支持的控制器组，无有效接收报文*/
			break;
		}
	}
	/*****************************************/
}
/************************************************************
* 函数名称:CanIf_TxMainfunction
* 函数描述:CanIf模块提供后台主循环(发送处理);
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无
* 备注	  :
*************************************************************/
STATIC void CanIf_TxMainfunction(void)
{
    /*******************************
     对控制器中断发送追踪定时器进行处理
	 *******************************/
	 CanIf_TxMainfunctionForIsrTxTimer();
}
/************************************************************
* 函数名称:CanIf_TxMainfunctionForIsrTxTimer
* 函数描述:CanIf模块提供的控制器中断发送追踪定时器进行处理;
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无
* 备注	  :
*************************************************************/
STATIC void CanIf_TxMainfunctionForIsrTxTimer(void)
{
	uint8	Index = 0u;
	uint8	DevId = 0u;
	uint8  	DevIdCfgIndex = 0u;
	uint32  CurTicks = 0ul;
	uint32  OldTicks = 0ul;
	uint32  ElapseTicks = 0ul;	
	Std_ReturnType  ret = E_NOT_OK;

	/******************************/
	for(Index=0u;Index<(CanIf_Cfg.NumOfController);Index++)
	{
		DevId = CanIf_Cfg.pControllerCfg[Index].ControllerId;
		/*****************************/
		ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
		if(E_NOT_OK == ret)
		{
			/*参数值未配置,无效*/	
		   	continue;
		}
		/*****************************/
		if(TIMER_ON == CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus)
		{
			OSAL_ENTER_CRITICAL();
			OldTicks = CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].CurTicks;
			OSAL_EXIT_CRITICAL();
			
			CurTicks = OSALTimeGet();
			ElapseTicks = (uint32)(CurTicks - OldTicks);
			if(ElapseTicks >= CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].ExpireTicks)
			{
				/*控制器中断发送跟踪超时*/
				/*①通知CanIf模块,清除对应的发送队列*/
				CanIf_ResetTransmitQueue(DevId);

				/*②-清除控制器--正在发送标识*/
				/*③-关闭控制器中断发送跟踪定时器*/
				/*④-禁止发送中断*/
				CanIf_TransmitQueueIsEmpty(DevId);

				/*⑤-终止发送指定控制器硬件Buffer中的Pending报文*/
				Can_RequestTransmitterMessageAbort(DevId);
			}
		}
	}
}

#endif



