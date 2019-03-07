/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Com.c
* ��������  : ͨѶģ��Դ�ļ�(.c)����
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "Com.h"
#include "ComM.h"
#include "CanIf.h"
#include "Osal.h"
#include "drv_sci.h"

/*****************************************
            ����ʱ���ݽṹ���Ͷ���
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

/*������������ʱ��������*/
typedef struct
{
	uint32  IpduId;		/*��������ID*/
	boolean IsEnable;	/*=0:��ֹ���Ľ��ջ���;=1:ʹ�ܱ��Ľ��ջ���*/
	Com_TimerCtrlType  TimerCtrl;
	uint8 	TrigerCnt;	/*��������  addeb by sunj 2019-1-10 13:55*/
}Com_IpduCtrlType;

/*����Э������ʱ���ݽṹ*/
typedef struct
{
	uint8  ProtocolId;	/*Э��Id��*/
    Com_IpduCtrlType  IpduCtrl[COM_MAX_IPDUNUM];
}Com_ProtocolCtrlType;

/*ģ��״̬����ʱ���ݽṹ*/
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
            ����ʱ���ݽṹ����
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Com_MkCtrlType  Com_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            ��̬��������
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
* ��������:Com_Init
* ��������:Comģ���ʼ��
* �������:��
* �������:��
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  :
*************************************************************/
void  Com_Init(void)
{
	uint8 ProtocolIndex = 0u;
	uint8 IpduIndex = 0u;

	/*****************************/
	if(COM_MAX_PROTOCOLNUM < Com_Cfg.NumOfProtocol)
	{
		/*��̬���ò�������*/
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
		  /*ģ��֧�ֵ�Э��(s)��,��ʵ�����õ�(����+����)��������>COM_MAX_IPDUNUM,
		    �����COM_MAX_IPDUNUM���ô���,��Ҫ�����޸�!*/
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
							= Com_Cfg.pProtocoCfg[ProtocolIndex].protocolId; /*Э��ID��*/
		
		for(IpduIndex=0u;IpduIndex<(Com_Cfg.pProtocoCfg[ProtocolIndex].NumOfIPdu);IpduIndex++)
		{
			/*����ID��*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].IpduId   
							= Com_Cfg.pProtocoCfg[ProtocolIndex].pIPduCfg[IpduIndex].IPduId; 

			/*Ĭ�Ͻ�ֹ������/��*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].IsEnable = FALSE; 

			/*Ĭ�ϱ��Ĵ�������Ϊ0 added by sunj 2019-1-10 13:57*/
			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].TrigerCnt = 0;

			Com_MkCtrl.ProtocolCtrl[ProtocolIndex].IpduCtrl[IpduIndex].TimerCtrl.TimerStatus = TIMER_OFF;
		}
	}
	Com_MkCtrl.Com_MkStatus = COM_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:Com_RxIndication
* ��������:֪ͨComģ����յ�ָ��Э��ID�ŵı���
* �������:ProtocolId:���ձ��Ķ�ӦЭ��ID��;
           PduInfo:���ձ���;
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
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
		/*���ձ��Ķ�ӦЭ��ID��,ģ�鲻֧��(δ����)*/
#if(STD_ON == COM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COM,
						ProtocolId,
						COM_RXINDICATION_ID,
						COM_E_PARAM_INVALID);					
#endif
		return(E_NOT_OK);
	}
    
	/**********************/
	/*�����յ��ı���Id,���ݾ����Ӧ�ó�������ת��*/
	Com_ChangeRxPduId(PduInfo.PduId,&NewPduId);
	
	ret = Com_SearchReceiveIpduInConfig(ProtocolId,NewPduId,&PduIdCfgIndex);
	if(E_NOT_OK == ret)
	{
		/*���ձ���Id,ģ�鲻֧��(δ���û���Ϊ"����")*/
		return(E_NOT_OK);
	}
	
	/**********************/
	if(FALSE == Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable)
	{
		/*��ǰ��ֹ���ոñ���*/
		return(E_NOT_OK);
	}

	/**********************/
	pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
	if(NULL_PTR != pCallBackFunction)
	{
	   /*�������յ��ı���*/
	   ret = (*pCallBackFunction)(&PduInfo);
	}
	return(ret);
}
/************************************************************
* ��������:Com_EnablePacketRx
* ��������:ʹ��Comģ��,����ָ��Э���е�ָ������.
* �������:ProtocolId:Э��ID��
           PduId     :����ID��
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :
*************************************************************/
Std_ReturnType  Com_EnablePacketRx(uint8 ProtocolId,uint32 PduId)
{
	uint8  ProtocolCfgIndex = 0u;
	uint8  PduIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
		/*����Э��ID��,ģ�鲻֧��(δ����)*/
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
		/*���뱨��Id,ģ�鲻֧��("δ����"������Ϊ"����")*/
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
* ��������:Com_DisablePacketRx
* ��������:��ֹComģ��,����ָ��Э���е�ָ������.
* �������:ProtocolId:Э��ID��
           PduId     :����ID��
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :
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
		/*����Э��ID��,ģ�鲻֧��(δ����)*/
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
		/*���뱨��Id,ģ�鲻֧��("δ����"������Ϊ"����")*/
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
* ��������:Com_EnablePacketTx
* ��������:ʹ��Comģ��,����ָ��Э���е�ָ������
* �������:ProtocolId:Э��ID��
           PduId     :����ID��
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :
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
		/*����Э��ID��,ģ�鲻֧��(δ����)*/
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
		/*���뱨��Id,ģ�鲻֧��("δ����"������Ϊ"����")*/
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
		/*��ǰ״̬Ϊ"��ֹ����"��ʹ�ܷ���*/
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].IsEnable = TRUE;
		/********************/
		if(   (COM_PERIOD == Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].TxMode)
			||(COM_MIXED  == Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].TxMode))
		{
			/*����ģʽ=COM_PERIOD��COM_MIXED*/
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
* ��������:Com_DisablePacketTx
* ��������:��ֹComģ�鷢��ָ��Э���е�ָ������
* �������:ProtocolId:Э��ID��
           PduId     :����ID��
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :
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
		/*����Э��ID��,ģ�鲻֧��(δ����)*/
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
		/*���뱨��Id,ģ�鲻֧��(δ����)*/
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
		/*�رն�ʱ��*/
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.TimerStatus = TIMER_OFF;
	}
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* ��������:Com_MainFunction
* ��������:Comģ���̨��ѭ������
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ����ֵ  :
* ��ע	  :�ú����������������
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
* ��������:Com_RxIndicationHook
* ��������:֪ͨComģ��,��Ӧ���������յ�����;
* �������:DevCfgId:���յ����ĵĿ�������CanIfģ���е���������;
           			= 0u:Can0������;
           			= 1u:Can1������;
           (*pPduInfo):���յ���������;
* �������:��
* ����/�������:��
* ��������:������
* ����ֵ  :E_OK:�����ɹ�;
           E_NOT_OK:����ʧ��;
* ��ע	  :�²�CanIfģ�����(Rx ISR)
*************************************************************/
Std_ReturnType  Com_RxIndicationHook(uint8 DevCfgId,const PduInfoType *pPduInfo)
{
	/**********************/
	if(COM_UNINIT == Com_MkCtrl.Com_MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
						��̬��������
 ************************************************************/
#if 1
/************************************************************
* ��������:	Com_SearchProtocolInConfig
* ��������:	��ģ�龲̬���ýṹ�У������Ƿ�ProtocolId���ã�
* �������:	ProtocolId:Э��ID��
* �������:	(*pProtocolCfg):Э������������;
* ����/�������:��
* ��������:	��������
* ����ֵ  :	E_OK:��ģ�龲̬������,���ҳɹ�;
           	E_NOT_OK:��ģ�龲̬������,����ʧ��;
* ��ע	  :
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
* ��������:	Com_SearchReceiveIpduInConfig
* ��������:	��ָ��Э��ı������ýṹ�У�����IpduId�Ƿ�������Ϊ���գ�
* �������:	ProtocolId:Э��Id��;
			IpduId    :����Id��;
* �������: (*pIpduCfg):Э���б�������������;
* ����/�������:��
* ��������:	��������
* ����ֵ  :	E_OK:��ģ�龲̬������,���ҳɹ�;
           	E_NOT_OK:��ģ�龲̬������,����ʧ��;
* ��ע	  :
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
		/*ProtocolIdδ����*/
		return(E_NOT_OK);
	}
	
	/**********************/
	pProtocoCfg = &(Com_Cfg.pProtocoCfg[ProtocolCfgIndex]);
	for(IpduIndex=0u;IpduIndex<(pProtocoCfg->NumOfIPdu);IpduIndex++)
	{
		if(   (IpduId == pProtocoCfg->pIPduCfg[IpduIndex].IPduId)
			&&(COM_RECEIVE == pProtocoCfg->pIPduCfg[IpduIndex].Direction) )
		{
		    /*ָ�����������ҷ���=COM_RECEIVE*/
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
* ��������:	Com_SearchTransmitIpduInConfig
* ��������:	��ָ��Э��ı������ýṹ�У�����IpduId�Ƿ�������Ϊ���ͣ�
* �������:	ProtocolId:Э��Id��;
			IpduId    :����Id��;
* �������:	(*pIpduCfg):Э���б�������������;
* ����/�������:��
* ��������:	��������
* ����ֵ  :	E_OK:��ģ�龲̬������,���ҳɹ�;
           	E_NOT_OK:��ģ�龲̬������,����ʧ��;
* ��ע	  :
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
		/*ProtocolIdδ����*/
		return(E_NOT_OK);
	}
	
	/**********************/
	pProtocoCfg = &(Com_Cfg.pProtocoCfg[ProtocolCfgIndex]);
	for(IpduIndex=0u;IpduIndex<(pProtocoCfg->NumOfIPdu);IpduIndex++)
	{
		if(   (IpduId == pProtocoCfg->pIPduCfg[IpduIndex].IPduId)
			&&(COM_TRANSMIT == pProtocoCfg->pIPduCfg[IpduIndex].Direction))
		{
		    /*ָ�����������ҷ���=COM_TRANSMIT*/
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
* ��������:	Com_TxMainFunction
* ��������:	ģ�鷢��,��̨��ѭ��
* �������:	��
* �������: ��
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  :
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
				/*Э�鱨������Ϊ"COM_TRANSMIT",��ʹ�ܷ���*/
				switch(pIPduCfg->TxMode)
				{
					case COM_TRIGER:	/*��������*/
						 Com_SendMessageByTriger(ProtocolIndex,PduIdIndex);
						 break;
						 
					case COM_PERIOD:	/*���ڷ���*/
						 Com_SendMessageByPeriod(ProtocolIndex,PduIdIndex);
						 break;
						 
					case COM_MIXED:     /*����+��������*/
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
* ��������:	Com_SendMessageByTriger
* ��������:	�����෢����Ϣ
* �������:	ProtocolCfgIndex:Э������������;
            PduIdCfgIndex   :Э���б��ľ�������������;
* �������: ��
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  :
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
		/*������������,��������*/
		pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
			(void)(*pCallBackFunction)(&PduInfo);
		}
	}
}

/************************************************************
* ��������:	Com_SendMessageByPeriod
* ��������:	���ڷ�����Ϣ
* �������:	ProtocolCfgIndex:Э������������;
            PduIdCfgIndex   :Э���б��ľ�������������;
* �������: ��
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  :
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
		/* ���ڳ�ʱ,�������� */
		OSAL_ENTER_CRITICAL();
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TimerCtrl.CurTicks = OSALTimeGet();	
		OSAL_EXIT_CRITICAL();
		pCallBackFunction = Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
		    (void)(*pCallBackFunction)(&PduInfo); /*׼������,������*/
		}
	}
}

/************************************************************
* ��������:	Com_SendMessageByPeriod
* ��������:	����+���ڷ�����Ϣ
* �������:	ProtocolCfgIndex:Э������������;
            PduIdCfgIndex   :Э���б��ľ�������������;
* �������: ��
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  :
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
		/*���㴥������,����������*/
		pCallBackFunction =  Com_Cfg.pProtocoCfg[ProtocolCfgIndex].pIPduCfg[PduIdCfgIndex].pFunctionName;
		if(NULL_PTR != pCallBackFunction)
		{
			(void)(*pCallBackFunction)(&PduInfo);
		}
		/* ˢ������ʱ��,��Ϊ�´����ڷ��͵�ʱ����� */
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
		   	/*ˢ������ʱ��,��������*/
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
                  ��Ҫ������Ա�������Ƶĺ���
 ************************************************************/
/************************************************************
* ��������: Com_JudgeTrigerCondition
* ��������: ����ָ��Э��ָ�����ĵķ��ʹ��������Ƿ�����;
* �������:	ProtocolCfgIndex:Э������������;
            PduIdCfgIndex   :Э���б��ľ�������������;
* �������: ��
* ����/�������:��
* ����ֵ  : E_OK: ������������;
            E_NOT_OK: ��������������;
* ��������: 
* ��ע    : 
*************************************************************/
STATIC Std_ReturnType Com_JudgeTrigerCondition(uint8 ProtocolCfgIndex,uint8 PduIdCfgIndex)
{
   /*���ݾ����Ӧ�ó������������ж�*/
   /* Todo */
	if(Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TrigerCnt>0)
	{
		Com_MkCtrl.ProtocolCtrl[ProtocolCfgIndex].IpduCtrl[PduIdCfgIndex].TrigerCnt--;
		return(E_OK);
	}
	
	return(E_NOT_OK);
}

/************************************************************
* ��������:	Com_ChangeRxPduId
* ��������:	��ʵ�ʽ��յ���PduId,���ݾ����Ӧ�ó�������ת��;
* �������:	PduId:ʵ�ʽ��յ��ı���Id��;
* �������:	(*pPduId):����Ӧ�ó���ת����ı���Id;
* ����/�������:��
* ��������:	��������
* ����ֵ  : ��
* ��ע	  : �˴���ɫ:һ��ID����:֡���͡�Դ��ַ��Ŀ���ַ��������֮�����Ϣ
            ��ID��ʱ�̱仯��,Ҫ����̬����ID�붯̬�仯ID��Ӧ��������Ҫ������
            ��������̬�仯�������ε���ֻ��ע���䲿��;
*************************************************************/
STATIC  void  Com_ChangeRxPduId(uint32 PduId,uint32 *pPduId)
{
	/*���ݾ����Ӧ�ó���,�����յ��ı���Id����ת��*/
	/* Todo */
	(*pPduId) = PduId & 0xFF000000; /*��������ֽ�*/
}


/***************************************************************************//*!
 * \brief   ��1~2bit��״̬�����Ŀ���ֽ���
 *			��numOfbitΪ1ʱ,stateΪtrueʱ����ӦbitΪ1B�� stateΪfalseʱ����ӦbitΪ0B
 *			��numOfbitΪ2ʱ,stateΪtrueʱ����ӦbitΪ10B��stateΪfalseʱ����ӦbitΪ01B
 *
 * \param *dest         Ŀ���ֽڵ�ַ
 * \param numOfbit      ״̬ռ�õ�bit����
 * \param bitOffset     λƫ�ƣ���numOfbitΪ1ʱ��ȡֵ��ΧΪ7~0����numOfbitΪ2ʱ��ȡֵ��ΧΪ7~1��
 * \param state         ״̬
 *
 * \return				����-1Ϊʧ�ܣ�����0Ϊ�ɹ�
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
		/*����Э��ID��,ģ�鲻֧��(δ����)*/
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
		/*���뱨��Id,ģ�鲻֧��("δ����"������Ϊ"����")*/
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
