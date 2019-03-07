/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com.c
* 功能描述  : 通讯模块源文件(.c)定义
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "Com.h"
#include "ComM.h"
#include "CanIf.h"
#include "Osal.h"
#include "drv_sci.h"

/*****************************************
            运行时数据结构类型定义
 ****************************************/
typedef enum
{
	TIMER_OFF = 0u,
	TIMER_ON  = 1u
}Com_TimerStatusType;

typedef struct
{
	uint32  CurTicks;
	uint32  ExpireTicks;
	Com_TimerStatusType  TimerStatus;
}Com_TimerCtrlType;

/*单个报文运行时数据类型*/
typedef struct
{
	uint32  IpduId;		/*报文配置ID*/
	boolean IsEnable;	/*=0:禁止报文接收或发送;=1:使能报文接收或发送*/
	Com_TimerCtrlType  TimerCtrl;
	uint8 	TrigerCnt;	/*触发次数  addeb by sunj 2019-1-10 13:55*/
}Com_IpduCtrlType;

/*单个协议运行时数据结构*/
typedef struct
{
	uint8  ProtocolId;	/*协议Id号*/
    Com_IpduCtrlType  IpduCtrl[COM_MAX_IPDUNUM];
}Com_ProtocolCtrlType;

/*模块状态运行时数据结构*/
typedef  enum
{
	COM_UNINIT = 0u,
	COM_INIT   = 1u
}Com_MkStatusType;

typedef struct
{
	Com_ProtocolCtrlType ProtocolCtrl[COM_MAX_PROTOCOLNUM];	
	Com_MkStatusType  	 Com_MkStatus;
}Com_MkCtrlType;

/*****************************************
            运行时数据结构定义
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Com_MkCtrlType  Com_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            静态函数声明
 ****************************************/
#if  1
STATIC  Std_ReturnType Com_SearchProtocolInConfig(uint8 ProtocolId,uint8 *pProtocolCfg);
STATIC  Std_ReturnType Com_SearchReceiveIpduInConfig(uint8 ProtocolId,uint32 IpduId, uint8 *pIpduCfg);
STATIC  Std_ReturnType Com_SearchTransmitIpduInConfig(uint8 ProtocolId,uint32 IpduId, uint8 *pIpduCfg);
STATIC  Std_ReturnType Com_JudgeTrigerCondition(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex);
STATIC  void  Com_TxMainFunction(void);
STATIC  void  Com_SendMessageByTriger(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex);
STATIC  void  Com_SendMessageByPeriod(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex);
STATIC  void  Com_SendMessageByMixed(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex);
STATIC  void  Com_ChangeRxPduId(uint32 PduId,uint32 *pPduId);
#endif

/************************************************************
* 函数名称:Com_Init
* 函数描述:Com模块初始化
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
void  Com_Init(void)
{
	uint8 ProtocolIndex = 0u;
	uint8 IpduIndex = 0u;

	/*****************************/
	if(COM_MAX_PROTOCOLNUM < Com_Cfg.NumOfProtocol)
	{
		/*静态配置参数错误*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_INIT_ID,
						COM_E_CONFIGPARAM_INVALID);					
#endif
		return;
	}
	
	/*****************************/
	for(ProtocolIndex=0u;ProtocolIndex<(Com_Cfg.NumOfProtocol);ProtocolIndex++)
	{
		if((Com_Cfg.pProtocoCfg[ProtocolIndex].NumOfIPdu)> COM_MAX_IPDUNUM)	
		{
		  /*模块支持的协议(s)中,若实际配置的(接收+发送)报文数量>COM_MAX_IPDUNUM,
		    则参数COM_MAX_IPDUNUM配置错误,需要进行修改!*/
		#if(STD_ON == COM_DEV_ERROR_DETECT)
			Det_ReportError(MODULE_ID_COM,
							Com_Cfg.pProtocoCfg[ProtocolIndex].protocolId,  
							COM_INIT_ID,
							COM_E_CONFIGPARAM_INVALID);					
		#endif
			return;
		}
	}
	/*****************************/
	OSAL_ENTER_CRITICAL();
    for(ProtocolIndex=0u;ProtocolIndex<(Com_Cfg.NumOfProtocol);ProtocolIndex++)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolIndex].ProtocolId 
							= Com_Cfg.pProtocoCfg[ProtocolIndex].protocolId; /*协议ID号*/
		
		for(IpduIndex=0u;IpduIndex<(Com_Cfg.pProtocoCfg[ProtocolIndex].NumOfIPdu);IpduIndex++)
		{
			/*报文ID号*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].IpduId   
							= Com_Cfg.pProtocoCfg[ProtocolIndex].pIPduCfg[IpduIndex].IPduId; 

			/*默认禁止报文收/发*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].IsEnable = FALSE; 

			/*默认报文触发次数为0 added by sunj 2019-1-10 13:57*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].TrigerCnt = 0;

			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].TimerCtrl.TimerStatus = TIMER_OFF;
		}
	}
	Com_MkCtrl.Com_MkStatus = COM_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:Com_RxIndication
* 函数描述:通知Com模块接收的指定协议ID号的报文
* 输入参数:ProtocolId:接收报文对应协议ID号;
           PduInfo:接收报文;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
Std_ReturnType  Com_RxIndication(uint8 ProtocolId,const PduInfoType PduInfo)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	uint32 NewPduId = 0ul;
	Std_ReturnType ret = E_NOT_OK;
	function *pCallBackFunction = NULL_PTR;
	
	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_RXINDICATION_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*接收报文对应协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_RXINDICATION_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
    
	/**********************/
	/*将接收到的报文Id,根据具体的应用场景进行转换*/
	Com_ChangeRxPduId(PduInfo.PduId,&NewPduId);
	
	ret = Com_SearchReceiveIpduInConfig(ProtocolId,NewPduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*接收报文Id,模块不支持(未配置或方向为"发送")*/
		return(E_NOT_OK);
	}
	
	/**********************/
	if(FALSE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		/*当前禁止接收该报文*/
		return(E_NOT_OK);
	}

	/**********************/
	pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
	if(NULL_PTR != pCallBackFunction)
	{
	   /*解析接收到的报文*/
	   ret = (*pCallBackFunction)(&PduInfo);
	}
	return(ret);
}
/************************************************************
* 函数名称:Com_EnablePacketRx
* 函数描述:使能Com模块,接收指定协议中的指定报文.
* 输入参数:ProtocolId:协议ID号
           PduId     :报文ID号
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
Std_ReturnType  Com_EnablePacketRx(uint8 ProtocolId,uint32 PduId)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_RX_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
 	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_ENABLEPACKET_RX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
   
	ret = Com_SearchReceiveIpduInConfig(ProtocolId,PduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入报文Id,模块不支持("未配置"或配置为"发送")*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_RX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}

	/**********************/
	OSAL_ENTER_CRITICAL();
	if(FALSE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable = TRUE;
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* 函数名称:Com_DisablePacketRx
* 函数描述:禁止Com模块,接收指定协议中的指定报文.
* 输入参数:ProtocolId:协议ID号
           PduId     :报文ID号
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
Std_ReturnType  Com_DisablePacketRx(uint8 ProtocolId,uint32 PduId)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_DISABLEPACKET_RX_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
 	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_DISABLEPACKET_RX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
   
	ret = Com_SearchReceiveIpduInConfig(ProtocolId,PduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入报文Id,模块不支持("未配置"或配置为"发送")*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_DISABLEPACKET_RX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
	OSAL_ENTER_CRITICAL();
	if(TRUE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable = FALSE;
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);	
}

/************************************************************
* 函数名称:Com_EnablePacketTx
* 函数描述:使能Com模块,发送指定协议中的指定报文
* 输入参数:ProtocolId:协议ID号
           PduId     :报文ID号
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
Std_ReturnType  Com_EnablePacketTx(uint8 ProtocolId,uint32 PduId)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_TX_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
 	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_ENABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
   
	ret = Com_SearchTransmitIpduInConfig(ProtocolId,PduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入报文Id,模块不支持("未配置"或配置为"接收")*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}

	/**********************/
	OSAL_ENTER_CRITICAL();
	if(FALSE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		/*当前状态为"禁止发送"，使能发送*/
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable = TRUE;
		/********************/
		if(   (COM_PERIOD == Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].TxMode)
			||(COM_MIXED  == Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].TxMode))
		{
			/*发送模式=COM_PERIOD或COM_MIXED*/
			Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks
			                           	= OSALTimeGet();
			
			Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.ExpireTicks
										= Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].PeriodTimes;

			Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.TimerStatus
										= TIMER_ON;
		}
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* 函数名称:Com_DisablePacketTx
* 函数描述:禁止Com模块发送指定协议中的指定报文
* 输入参数:ProtocolId:协议ID号
           PduId     :报文ID号
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
Std_ReturnType  Com_DisablePacketTx(uint8 ProtocolId,uint32 PduId)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_DISABLEPACKET_TX_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	/**********************/
 	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_DISABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
   
	ret = Com_SearchTransmitIpduInConfig(ProtocolId,PduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入报文Id,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_DISABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
	OSAL_ENTER_CRITICAL();
	if(TRUE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable = FALSE;
		/*关闭定时器*/
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.TimerStatus = TIMER_OFF;
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* 函数名称:Com_MainFunction
* 函数描述:Com模块后台主循环函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :该函数被周期任务调用
*************************************************************/
void  Com_MainFunction(void)
{
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_MAINFUNCTION_ID,
						COM_E_UNINIT);					
#endif
		return;
	}
	/**********************/
	Com_TxMainFunction();
}

/************************************************************
* 函数名称:Com_RxIndicationHook
* 函数描述:通知Com模块,对应控制器接收到报文;
* 输入参数:DevCfgId:接收到报文的控制器在CanIf模块中的配置索引;
           			= 0u:Can0控制器;
           			= 1u:Can1控制器;
           (*pPduInfo):接收到报文内容;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :下层CanIf模块调用(Rx ISR)
*************************************************************/
Std_ReturnType  Com_RxIndicationHook(uint8 DevCfgId,const PduInfoType *pPduInfo)
{
	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
		/*模块未初始化*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_RXINDICATIONHOOK_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
	if(NULL_PTR == pPduInfo)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_RXINDICATIONHOOK_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
	/*TODO*/
	return(E_OK);
}

/************************************************************
						静态函数定义
 ************************************************************/
#if 1
/************************************************************
* 函数名称:	Com_SearchProtocolInConfig
* 函数描述:	在模块静态配置结构中，查找是否ProtocolId配置；
* 输入参数:	ProtocolId:协议ID号
* 输出参数:	(*pProtocolCfg):协议配置索引号;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  :	E_OK:在模块静态配置中,查找成功;
           	E_NOT_OK:在模块静态配置中,查找失败;
* 备注	  :
*************************************************************/
STATIC  Std_ReturnType Com_SearchProtocolInConfig(uint8 ProtocolId,uint8 *pProtocolCfg)
{
	uint8 ProtocolIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/**********************/
    for(ProtocolIndex=0u;ProtocolIndex<(Com_Cfg.NumOfProtocol);ProtocolIndex++)
	{
		if(ProtocolId == Com_Cfg.pProtocoCfg[ProtocolIndex].protocolId)
		{
			(*pProtocolCfg) = ProtocolIndex;
			break;
		}
	}
	if(ProtocolIndex == (Com_Cfg.NumOfProtocol))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}
	return(ret);
}


/************************************************************
* 函数名称:	Com_SearchReceiveIpduInConfig
* 函数描述:	在指定协议的报文配置结构中，查找IpduId是否配置且为接收；
* 输入参数:	ProtocolId:协议Id号;
			IpduId    :报文Id号;
* 输出参数: (*pIpduCfg):协议中报文配置索引号;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  :	E_OK:在模块静态配置中,查找成功;
           	E_NOT_OK:在模块静态配置中,查找失败;
* 备注	  :
*************************************************************/
STATIC  Std_ReturnType Com_SearchReceiveIpduInConfig(uint8 ProtocolId,uint32 IpduId, uint8 *pIpduCfg)
{
	uint8 IpduIndex    = 0u;
	uint8 ProtocolCfgIndex= 0u;
	uint8 IpduCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;
	const Com_SingleProtocoCfgType *pProtocoCfg = NULL_PTR;
	
	/**********************/
	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*ProtocolId未配置*/
		return(E_NOT_OK);
	}
	
	/**********************/
	pProtocoCfg = &(Com_Cfg.pProtocoCfg[ProtocolCfgIndex]);
	for(IpduIndex=0u;IpduIndex<(pProtocoCfg->NumOfIPdu);IpduIndex++)
	{
		if(   (IpduId == pProtocoCfg->pIPduCfg[IpduIndex].IPduId)
			&&(COM_RECEIVE == pProtocoCfg->pIPduCfg[IpduIndex].Direction) )
		{
		    /*指定报文配置且方向=COM_RECEIVE*/
			(*pIpduCfg) = IpduIndex;
			break;
		}
	}
	if(IpduIndex == (pProtocoCfg->NumOfIPdu))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}
	return(ret);
}

/************************************************************
* 函数名称:	Com_SearchTransmitIpduInConfig
* 函数描述:	在指定协议的报文配置结构中，查找IpduId是否配置且为发送；
* 输入参数:	ProtocolId:协议Id号;
			IpduId    :报文Id号;
* 输出参数:	(*pIpduCfg):协议中报文配置索引号;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  :	E_OK:在模块静态配置中,查找成功;
           	E_NOT_OK:在模块静态配置中,查找失败;
* 备注	  :
*************************************************************/
STATIC  Std_ReturnType Com_SearchTransmitIpduInConfig(uint8 ProtocolId,uint32 IpduId, uint8 *pIpduCfg)
{
	uint8 IpduIndex    = 0u;
	uint8 ProtocolCfgIndex= 0u;
	uint8 IpduCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;
	const Com_SingleProtocoCfgType *pProtocoCfg = NULL_PTR;
	
	/**********************/
	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*ProtocolId未配置*/
		return(E_NOT_OK);
	}
	
	/**********************/
	pProtocoCfg = &(Com_Cfg.pProtocoCfg[ProtocolCfgIndex]);
	for(IpduIndex=0u;IpduIndex<(pProtocoCfg->NumOfIPdu);IpduIndex++)
	{
		if(   (IpduId == pProtocoCfg->pIPduCfg[IpduIndex].IPduId)
			&&(COM_TRANSMIT == pProtocoCfg->pIPduCfg[IpduIndex].Direction))
		{
		    /*指定报文配置且方向=COM_TRANSMIT*/
			(*pIpduCfg) = IpduIndex;
			break;
		}
	}
	if(IpduIndex == (pProtocoCfg->NumOfIPdu))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
	}
	return(ret);
}

/************************************************************
* 函数名称:	Com_TxMainFunction
* 函数描述:	模块发送,后台主循环
* 输入参数:	无
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
STATIC  void  Com_TxMainFunction(void)
{
	uint8  ProtocolIndex = 0u;
	uint8  PduIdIndex = 0u;
  	const  Com_IPduCfgType *pIPduCfg = NULL_PTR;
	
	/**********************/
	for(ProtocolIndex=0u;ProtocolIndex<(Com_Cfg.NumOfProtocol);ProtocolIndex++)
	{   
		for(PduIdIndex=0u;PduIdIndex<(Com_Cfg.pProtocoCfg[ProtocolIndex].NumOfIPdu);PduIdIndex++)
		{
		    pIPduCfg = &(Com_Cfg.pProtocoCfg[ProtocolIndex].pIPduCfg[PduIdIndex]);
			if(   (COM_TRANSMIT == pIPduCfg->Direction)
				&&(TRUE == Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[PduIdIndex].IsEnable))
			{   
				/*协议报文配置为"COM_TRANSMIT",且使能发送*/
				switch(pIPduCfg->TxMode)
				{
					case COM_TRIGER:	/*触发发送*/
						 Com_SendMessageByTriger(ProtocolIndex,PduIdIndex);
						 break;
						 
					case COM_PERIOD:	/*周期发送*/
						 Com_SendMessageByPeriod(ProtocolIndex,PduIdIndex);
						 break;
						 
					case COM_MIXED:     /*周期+触发发送*/
						 Com_SendMessageByMixed(ProtocolIndex,PduIdIndex);
						 break;
						 
					default:
						 break;
				}
			}
		}
	}
}

/************************************************************
* 函数名称:	Com_SendMessageByTriger
* 函数描述:	触发类发送消息
* 输入参数:	ProtocolCfgIndex:协议配置索引号;
            PduIdCfgIndex   :协议中报文具体配置索引号;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
STATIC void  Com_SendMessageByTriger(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex)
{
	PduInfoType PduInfo;
	Std_ReturnType  ret = E_NOT_OK;
	function *pCallBackFunction = NULL_PTR;

	/************************/
	ret = Com_JudgeTrigerCondition(ProtocolCfgIndex,PduIdCfgIndex);
	if(E_OK == ret)
	{
		/*触发条件满足,立即发送*/
		pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
			(void)(*pCallBackFunction)(&PduInfo);
		}
	}
}

/************************************************************
* 函数名称:	Com_SendMessageByPeriod
* 函数描述:	周期发送消息
* 输入参数:	ProtocolCfgIndex:协议配置索引号;
            PduIdCfgIndex   :协议中报文具体配置索引号;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
STATIC void  Com_SendMessageByPeriod(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex)
{
    uint32  oldticks = 0ul;
	uint32  elapseticks = 0ul;
	PduInfoType PduInfo;
	function *pCallBackFunction = NULL_PTR;

	/************************/
	OSAL_ENTER_CRITICAL();
	oldticks = Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks;
	OSAL_EXIT_CRITICAL();
	elapseticks = (uint32)(OSALTimeGet() - oldticks);
	if(elapseticks >= Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.ExpireTicks)
	{
		/* 周期超时,立即发送 */
		OSAL_ENTER_CRITICAL();
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks = OSALTimeGet();	
		OSAL_EXIT_CRITICAL();
		pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
		    (void)(*pCallBackFunction)(&PduInfo); /*准备数据,并发送*/
		}
	}
}

/************************************************************
* 函数名称:	Com_SendMessageByPeriod
* 函数描述:	触发+周期发送消息
* 输入参数:	ProtocolCfgIndex:协议配置索引号;
            PduIdCfgIndex   :协议中报文具体配置索引号;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
STATIC void  Com_SendMessageByMixed(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex)
{
    uint32  oldticks = 0ul;
	uint32  elapseticks = 0ul;
	PduInfoType PduInfo;
	Std_ReturnType  ret = E_NOT_OK;
	function *pCallBackFunction = NULL_PTR;

	/***********************/
	ret = Com_JudgeTrigerCondition(ProtocolCfgIndex,PduIdCfgIndex);	
	if(E_OK == ret)
	{
		/*满足触发条件,则立即发送*/
		pCallBackFunction =  Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
			(void)(*pCallBackFunction)(&PduInfo);
		}
		/* 刷新周期时间,作为下次周期发送的时间基点 */
		OSAL_ENTER_CRITICAL();
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks = OSALTimeGet();
		OSAL_EXIT_CRITICAL();
	}
	else
	{
		/***********************/
		OSAL_ENTER_CRITICAL();
		oldticks = Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks;
		OSAL_EXIT_CRITICAL();
		elapseticks = (uint32)(OSALTimeGet() - oldticks);
		if(elapseticks >= (Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.ExpireTicks))
		{
		   	/*刷新周期时间,立即发送*/
			OSAL_ENTER_CRITICAL();
		   	Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks =  OSALTimeGet();
			OSAL_EXIT_CRITICAL();
			pCallBackFunction =  Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
			if(NULL_PTR != pCallBackFunction)
			{
				(void)(*pCallBackFunction)(&PduInfo);
			}
		}
	}
}



/************************************************************
                  需要配置人员进行完善的函数
 ************************************************************/
/************************************************************
* 函数名称: Com_JudgeTrigerCondition
* 函数描述: 计算指定协议指定报文的发送触发条件是否满足;
* 输入参数:	ProtocolCfgIndex:协议配置索引号;
            PduIdCfgIndex   :协议中报文具体配置索引号;
* 输出参数: 无
* 输入/输出参数:无
* 返回值  : E_OK: 触发条件满足;
            E_NOT_OK: 触发条件不满足;
* 可重入性: 
* 备注    : 
*************************************************************/
STATIC Std_ReturnType Com_JudgeTrigerCondition(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex)
{
   /*根据具体的应用场景进行条件判断*/
   /* Todo */
	if(Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TrigerCnt>0)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TrigerCnt--;
		return(E_OK);
	}
	
	return(E_NOT_OK);
}

/************************************************************
* 函数名称:	Com_ChangeRxPduId
* 函数描述:	将实际接收到的PduId,根据具体的应用场景进行转换;
* 输入参数:	PduId:实际接收到的报文Id号;
* 输出参数:	(*pPduId):根据应用场景转换后的报文Id;
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  : 运达特色:一个ID包括:帧类型、源地址、目标地址、心跳等之类的信息
            故ID是时刻变化的,要将静态配置ID与动态变化ID对应起来，需要经过该
            函数将动态变化部分屏蔽掉，只关注不变部分;
*************************************************************/
STATIC  void  Com_ChangeRxPduId(uint32 PduId,uint32 *pPduId)
{
	/*根据具体的应用场景,将接收到的报文Id进行转换*/
	/* Todo */
	(*pPduId) = PduId & 0xFF000000; /*保留最高字节*/
}


/***************************************************************************//*!
 * \brief   将1~2bit的状态填充在目标字节内
 *			当numOfbit为1时,state为true时，相应bit为1B， state为false时，相应bit为0B
 *			当numOfbit为2时,state为true时，相应bit为10B，state为false时，相应bit为01B
 *
 * \param *dest         目标字节地址
 * \param numOfbit      状态占用的bit数量
 * \param bitOffset     位偏移，当numOfbit为1时，取值范围为7~0；当numOfbit为2时，取值范围为7~1；
 * \param state         状态
 *
 * \return				返回-1为失败，返回0为成功
 *
 * \author              sunj 2019/01/02 10:00
 *
 *****************************************************************************/
int8 Com_bit2Byte(uint8 *dest,uint8 numOfbit,uint8 bitOffset,boolean state) 
{
	if(numOfbit==1)
	{
		if((bitOffset<0)||(bitOffset>7))
			return -1;

		if(state==FALSE) 
		{
			*dest &= (~(0x80>>(7-bitOffset)));
		}
		else if(state==TRUE) 
		{ 
			*dest |= 0x80>>(7-bitOffset);
		}
		else
		{
			return -1;
		}
	}
	else if(numOfbit==2)
	{
		if((bitOffset<1)||(bitOffset>7))
			return -1;

		if(state==FALSE) 
		{
			*dest &= (~(0x80>>(7-bitOffset)));
			*dest |= (0x40>>(7-bitOffset));
		}
		else if(state==TRUE) 
		{ 
		    *dest |= (0x80>>(7-bitOffset));
    		*dest &= (~(0x40>>(7-bitOffset)));	
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

Std_ReturnType  Com_SetTrigerCnt(uint8 ProtocolId,uint32 PduId,uint8 cnt)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_TX_ID,
						COM_E_UNINIT);					
#endif
		return(E_NOT_OK);
	}
	
	/**********************/
 	ret = Com_SearchProtocolInConfig(ProtocolId,&ProtocolCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入协议ID号,模块不支持(未配置)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_ENABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
   
	ret = Com_SearchTransmitIpduInConfig(ProtocolId,PduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*输入报文Id,模块不支持("未配置"或配置为"接收")*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						0u,
						COM_ENABLEPACKET_TX_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}

	/**********************/
	OSAL_ENTER_CRITICAL();
 	Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TrigerCnt = 5;
	OSAL_EXIT_CRITICAL();
	return(E_OK);    
}

#endif
