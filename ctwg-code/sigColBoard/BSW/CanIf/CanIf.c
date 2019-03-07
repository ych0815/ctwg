/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : CanIf.c
* ��������  : Can�������ӿڲ�ʵ��Դ�ļ�(CanIf.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
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
            ����ʱ���ݽṹ���Ͷ���
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
	boolean  IsTransmitting; 			/*=FALSE:������δ����;=TRUE:����CAN��������ǰ���ڷ���*/
}CanIf_ControllerDataType;

/**************************/
typedef  enum
{
	CANIF_UNINIT = 0u,		/*ģ��δ��ʼ��*/
	CANIF_INIT   = 1u,
}CanIf_MkStatusType;

typedef  struct
{
	CanIf_ControllerDataType ControllerData[CANIF_CONTROLLER_NUM];
	CanIf_TimerCtrlType      ControllerIsrTxTimer[CANIF_CONTROLLER_NUM]; /*�������жϷ��͸�������ʱ���ݽṹ(2018-5-22,pm 19:01)*/
    CanIf_MkStatusType	     MkStatus;
}CanIf_MkCtrlType;

/*****************************************
            ����ʱ���ݽṹ����
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile CanIf_MkCtrlType  CanIf_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            ��̬��������
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
* ��������: CanIf_Init
* ��������: CanIfģ���ʼ��.
* �������: ��
* �������: ��
* ����/�������:��
* ��������: ��������
* ����ֵ  : �� 
* ��ע	  :
*************************************************************/
void  CanIf_Init(void)
{
	uint8 ControllerIndex = 0u;
	uint8 ControllerId = 0u;
	uint8 GroupIndex = 0u;
	
	/***************************
	        ���ò�����Ч�Լ��
	 ***************************/
	if(CANIF_CONTROLLER_NUM != CanIf_Cfg.NumOfController)
	{
		/*ģ�����õĿ�����������һ��*/
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
			/*��ͬ���ڵ�����������ID����ͬ*/
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
			/*��ͬ���ڵ�������������Ӧ��Э��ID�Ų�ͬ*/
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
* ��������: CanIf_RxIndication
* ��������: ֪ͨCanIfģ��,�豸��ΪDevId�Ŀ��������յ�����;
* �������: DevId  :CAN�������豸ID
		    PduInfo:���յ��ı�����Ϣ
* �������: ��
* ����/�������:��
* ��������:��������
* ����ֵ  : E_OK:�²�֪ͨ�ɹ�;
            E_NOT_OK:�²�֪ͨʧ��;
* ��ע	  :�²�Can����ģ������ж�(Rx ISR)����
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
		/*ģ��δ��ʼ��*/
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
		/*����ֵδ����,��Ч*/	
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
		/*���ջ����������������ձ���*/
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
* ��������:CanIf_Transmit
* ��������:֪ͨDevIdָ��Can����������һ֡����;
* �������:DevId  :������ID��;
           PduInfo:�����ͱ���;
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  : E_OK:���ͳɹ�;
            E_NOT_OK:����ʧ��;
* ��ע	  :�ϲ�Comģ�����
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
		/*ģ��δ��ʼ��*/
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
		/*����ֵδ����,��Ч*/	
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
		/*������״̬Ϊ"BusOff",��ֱ���˳�*/
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

	/*��������ͱ���*/
	OSAL_ENTER_CRITICAL();
	Tin = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin;
	Tout= CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut;
	OSAL_EXIT_CRITICAL();
	
	dis = (uint8)(Tin - Tout);
	if(dis >= CAN_TXBUFFSIZE)
	{
		/*���ͻ����������������ͱ���*/
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
	    /*��Ӧ����������,׼������*/
		OSAL_ENTER_CRITICAL();
		CanIf_MkCtrl.ControllerData[DevIdCfgIndex].IsTransmitting = TRUE;
		OSAL_EXIT_CRITICAL();

		/***********************************/
		/*added by chenms 2018-5-23,am 9:28*/
		CanIf_StartControllerIsrTxTimer(DevId); /*�����������жϷ��͸��ٶ�ʱ��*/
		/***********************************/
		
		Can_EnableTxInterrupt(DevId); /*ʹ�ܷ����жϣ������̲����ж�*/
		return(E_OK);
	}
}

/************************************************************
* ��������: CanIf_ResetTransmitQueue
* ��������: ֪ͨCanIfģ��,���DevIdָ���������ķ��Ͷ���;
* �������: DevId:������ID��
* �������: ��
* ����/�������:��
* ��������: ��������
* ����ֵ  : ��
* ��ע	  : �²�Can����ģ�����
*************************************************************/
void  CanIf_ResetTransmitQueue(uint8 DevId)
{
	uint8  TxIndex = 0u;
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret   = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/	
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
		/*����ֵδ����,��Ч*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_RESET_TRANSMITQUENE_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return;
	}
	/*************************
	  ��λDevId��Ӧ�ķ��Ͷ���
	**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.Tin = 0u;
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut= 0u;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������: CanIf_TransmitQueueIsEmpty
* ��������: ֪ͨCanIfģ��,DevIdָ���������ķ��Ͷ����Ѿ�Ϊ��;
* �������: DevId:�豸ID��
* �������: ��
* ����/�������:��
* ��������: ��������
* ����ֵ  : ��
* ��ע	  : �²�Can����ģ�鷢���жϺ���(Tx ISR)����
*************************************************************/
void  CanIf_TransmitQueueIsEmpty(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/	
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
		/*����ֵδ����,��Ч*/	
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
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].IsTransmitting = FALSE; /*����������ֹͣ*/
	OSAL_EXIT_CRITICAL();

	/***********************************/
	/*added by chenms 2018-5-23,am 9:28*/
	CanIf_StopControllerIsrTxTimer(DevId); /*�رտ������жϷ��͸��ٶ�ʱ��*/
	/***********************************/
		
	/*��ֹ�����ж�*/
	Can_DisableTxInterrupt(DevId);
    return;	
}

/************************************************************
* ��������:CanIf_GetNextPacket
* ��������:֪ͨCanIfģ��,��DevIdָ����Can���������Ͷ�����,
		   ��ȡһ֡�����ͱ���;
* �������:DevId:
		  (*pPduInfo):
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  : E_OK: ��ȡһ֡�����ͱ��ĳɹ�;
            E_NOT_OK: ��ȡһ֡�����ͱ���ʧ��;
* ��ע	  :�²�Can����ģ�鷢���ж�(Tx ISR)����
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
		/*ģ��δ��ʼ��*/	
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
		/*����ֵδ����,��Ч*/	
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
		/*����ֵ��Ч*/
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
		/*���ͻ����*/
		return(E_NOT_OK);
	}	
 	OSAL_ENTER_CRITICAL();
    (*pPduInfo) = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.PduInfo[Tout & (CAN_TXBUFFSIZE - 1u)];
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].TxData.TOut++;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
	
}

/************************************************************
* ��������:CanIf_Mainfunction
* ��������:CanIfģ���ṩ�ĺ�̨��ѭ��
* �������:��
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  : ��;
* ��ע	  :�ú�����Ҫ�����ڵ���
*************************************************************/
void CanIf_Mainfunction(void) 
{
	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/	
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
* ��������:CanIf_RxIndicationHook
* ��������:Can�����������ж�֪ͨ���Ӻ���
* �������:DevId  :�豸ID��;
           (*pPduInfo):���յ���CAN����
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��;
* ��ע	  :�²�Can����ģ������ж�(Rx ISR)����
*************************************************************/
Std_ReturnType CanIf_RxIndicationHook(uint8 DevId, const PduInfoType *pPduInfo)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
		/*����ֵδ����,��Ч*/	
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
		/*��ڲ�����Ч*/
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
* ��������:CanIf_TxConfirmHook
* ��������:Can��������������ж�֪ͨ���Ӻ���
* �������:DevId:�豸ID��;
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��;
* ��ע	  :�²�Can����ģ�鷢������ж�(Tx ISR)����
*************************************************************/
Std_ReturnType CanIf_TxConfirmHook(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	if(CANIF_UNINIT == CanIf_MkCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
		/*����ֵδ����,��Ч*/	
#if(STD_ON == CANIF_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CANIF,
						0u,
						CANIF_TXCONFIRMHOOK_ID,
						CANIF_E_PARAM_INVALID);
#endif
		return(E_NOT_OK);
	}
	
	/***********************************/
	/*��added by chenms 2018-5-23,am 9:28*/
	CanIf_FreshControllerIsrTxTimer(DevId); /*ˢ�¿������жϷ��͸��ٶ�ʱ��*/

	return(E_OK);	
}

/************************************************************
						��̬��������
 ************************************************************/
#if 1
/************************************************************
* ��������: CanIf_InitController
* ��������: ��ʼ��ָ����������CanIfģ���е�����ʱ���ݽṹ.
* �������: DevId:������ID��;
* �������: ��
* ����/�������:��
* ��������: ��������
* ����ֵ  : �� 
* ��ע	  :
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
		/*����ֵδ����,��Ч*/	
	   return;
	}
	
	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerData[ControllerIndex].IsTransmitting = FALSE;/*Ĭ�Ͽ������޷���*/
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
* ��������:	CanIf_SearchDeviceConfigIndex
* ��������:	��ģ�龲̬���ýṹ�У������Ƿ�DevId���ã�
* �������:	DevId: �豸ID��
* �������:	(*pDevCfgIndex):�豸��������;
* ����/�������:��
* ��������:	��������
* ����ֵ  :	E_OK:��ģ�龲̬������,����DevId�ɹ�;
           	E_NOT_OK:��ģ�龲̬������,����DevIdʧ��;
* ��ע	  :
*************************************************************/
STATIC Std_ReturnType CanIf_SearchDeviceConfigIndex(uint8 DevId,uint8 *pDevCfgIndex)
{
	uint8   Index = 0u;
	Std_ReturnType  ret = E_NOT_OK;

	for(Index=0u;Index<(CanIf_Cfg.NumOfController);Index++)
	{
	    if(DevId == CanIf_Cfg.pControllerCfg[Index].ControllerId)
    	{
    		/*����DevId,����̬����*/
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
* ��������:	CanIf_ReadRxPacket
* ��������:	��ȡ���յ��ı���
* �������:	DevId: �豸ID��
* �������:	(*pPduInfo):���ձ�������;
* ����/�������:��
* ��������:	��������
* ����ֵ  :	E_OK:��ȡָ���豸���ձ��ĳɹ�;
           	E_NOT_OK:��ȡָ���豸���ձ���ʧ��;
* ��ע	  :
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
		/*����DevId,δ����*/
		return(E_NOT_OK);
	}
	OSAL_ENTER_CRITICAL();
    Rin = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.Rin;
	Rout= CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.ROut;
	OSAL_EXIT_CRITICAL();	
	if(Rin == Rout)
	{
		/*���ջ����*/
		return(E_NOT_OK);
	}
	
	OSAL_ENTER_CRITICAL();
	(*pPduInfo) = CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.PduInfo[Rout & (CAN_RXBUFFSIZE - 1u)];
	CanIf_MkCtrl.ControllerData[DevIdCfgIndex].RxData.ROut++;
	OSAL_EXIT_CRITICAL();
	return(E_OK);
}

/************************************************************
* ��������: CanIf_InitControllerIsrTxTimer
* ��������: ��ʼ��ָ����������CanIfģ���е�����ʱ���ݽṹ.
* �������: DevId:������ID��;
* �������: ��
* ����/�������:��
* ��������: ��������
* ����ֵ  : �� 
* ��ע	  : added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void  CanIf_InitControllerIsrTxTimer(uint8 DevId)
{
	uint8 DevIdCfgIndex = 0u;
	Std_ReturnType  ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
    if(E_NOT_OK == ret)
	{
		/*����ֵδ����,��Ч*/	
	   return;
	}
	
	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].ExpireTicks = CANIF_CONTROLLER_ISRTXTICKS;
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_OFF; /*Ĭ�϶�ʱ���ر�*/
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:CanIf_StartControllerIsrTxTimer
* ��������:����ָ�����������жϷ��Ͷ�ʱ��;
* �������:DevId:
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��
* ��ע	  :added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void CanIf_StartControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*����ֵδ����,��Ч*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	/*������Ӧ���������жϷ���׷�ٶ�ʱ��*/
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].CurTicks    = OSALTimeGet();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].ExpireTicks = CANIF_CONTROLLER_ISRTXTICKS;
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_ON;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:CanIf_FreshControllerIsrTxTimer
* ��������:ˢ��ָ�����������жϷ��Ͷ�ʱ��;
* �������:DevId:
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��
* ��ע	  :added by chenms,2018-5-22 pm 19:05
*************************************************************/
STATIC void CanIf_FreshControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*����ֵδ����,��Ч*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	if(TIMER_ON == CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus)
	{	
		/*ˢ�¶�Ӧ���������жϷ���׷�ٶ�ʱ��*/
		CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].CurTicks = OSALTimeGet();
	}
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:CanIf_StopControllerIsrTxTimer
* ��������:ָֹͣ�����������жϷ��Ͷ�ʱ��;
* �������:DevId:
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��
* ��ע	  :
*************************************************************/
STATIC void CanIf_StopControllerIsrTxTimer(uint8 DevId)
{
	uint8  DevIdCfgIndex = 0u;
	Std_ReturnType ret = E_NOT_OK;

	/**************************/
	ret = CanIf_SearchDeviceConfigIndex(DevId,&DevIdCfgIndex);
	if(E_NOT_OK == ret)
	{ 
		/*����ֵδ����,��Ч*/	
		return;
	}

	/**************************/
	OSAL_ENTER_CRITICAL();
	CanIf_MkCtrl.ControllerIsrTxTimer[DevIdCfgIndex].TimerStatus = TIMER_OFF;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:CanIf_RxMainfunction
* ��������:CanIfģ���ṩ��̨��ѭ��(���մ���)
* �������:��
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  : ��;
* ��ע	  :�ú�����Ҫ�����ڵ���
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

			/*��ȡ�����������������Ϣ*/
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
			    /*�����������ڿ�����1���ҿ�����1��ȡ���ݳɹ�*/
				Com_RxIndication(CanIf_Cfg.pGroupCfg[GroupIndex].pController1->ProtocolId,
								 PduInfo1);
			}
			else if(  (TrustControllerId == CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ControllerId) 
					&&(E_OK == ret2))
			{
			    /*�����������ڿ�����2���ҿ�����2��ȡ���ݳɹ�*/
				Com_RxIndication(CanIf_Cfg.pGroupCfg[GroupIndex].pController2->ProtocolId,
								 PduInfo2);
			}
			else if((E_NOT_OK == ret1) && (E_NOT_OK == ret2))
			{
				 /*�������ڿ�������ȡ���ݾ����ɹ�*/
				 GroupEmptyCount++;
			}
			else
			{
				/*Nothing to do 
				 (1)���ο�����1������������2�н��ձ���
				 (2)���ο�����2������������1�н��ձ���*/
			}
		}
		/**************************/
		if(GroupEmptyCount == (CanIf_Cfg.NumOfGroup))
		{
			/*CanIfģ��֧�ֵĿ������飬����Ч���ձ���*/
			break;
		}
	}
	/*****************************************/
}
/************************************************************
* ��������:CanIf_TxMainfunction
* ��������:CanIfģ���ṩ��̨��ѭ��(���ʹ���);
* �������:��
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��
* ��ע	  :
*************************************************************/
STATIC void CanIf_TxMainfunction(void)
{
    /*******************************
     �Կ������жϷ���׷�ٶ�ʱ�����д���
	 *******************************/
	 CanIf_TxMainfunctionForIsrTxTimer();
}
/************************************************************
* ��������:CanIf_TxMainfunctionForIsrTxTimer
* ��������:CanIfģ���ṩ�Ŀ������жϷ���׷�ٶ�ʱ�����д���;
* �������:��
* �������:��
* ����/�������:��
* ��������:��������
* ����ֵ  :��
* ��ע	  :
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
			/*����ֵδ����,��Ч*/	
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
				/*�������жϷ��͸��ٳ�ʱ*/
				/*��֪ͨCanIfģ��,�����Ӧ�ķ��Ͷ���*/
				CanIf_ResetTransmitQueue(DevId);

				/*��-���������--���ڷ��ͱ�ʶ*/
				/*��-�رտ������жϷ��͸��ٶ�ʱ��*/
				/*��-��ֹ�����ж�*/
				CanIf_TransmitQueueIsEmpty(DevId);

				/*��-��ֹ����ָ��������Ӳ��Buffer�е�Pending����*/
				Can_RequestTransmitterMessageAbort(DevId);
			}
		}
	}
}

#endif



