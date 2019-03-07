/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : ComM.c
* ��������  : CANͨѶ����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
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
            ����ʱ���ݽṹ���Ͷ���
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

/*����������״̬*/
typedef  enum 
{
   COMM_CONTROLER_OK     = 0u,     	/*����������*/
   COMM_CONTROLER_BUSOFF = 1u   	/*���������߹ر�*/
}ComM_ControlerStatusType;

/*������ͨѶ״̬*/
typedef  enum
{
   COMM_COMMUNICAITON_OK = 0u,   	/*������ͨ������*/
   COMM_COMMUNICAITON_ERR= 1u  		/*������ͨ�Ź���*/
}ComM_ControllerSubStatusType;

/*��������������ʱ���ݽṹ*/
typedef  struct
{
   uint8  ControllerId;  		   	/*������ID��*/	
   ComM_TimerCtrlType   TimerCtrl; 	/*������ͨѶ����/�쳣���ٶ�ʱ��*/
   ComM_ControlerStatusType	ControllerStatus;		/*������״̬(����/���߹ر�)*/
   ComM_ControllerSubStatusType ControllerSubStatus;/*��������״̬(ͨ��״̬:����/�쳣)*/
}ComM_ControllerCtrlType;

/*��������������ʱ���ݽṹ*/
typedef struct
{
   uint8  GroupId;	  				/*������ID��*/
   uint8  CurBalanceValue;  		/*������������ƽֵ*/
   uint8  CurTrustBus; 				/*�����鵱ǰ����������Ϣ*/
   ComM_ControllerCtrlType ControllerCtrl[2]; /*���������2·��������Ϣ*/
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
            ����ʱ���ݽṹ����
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile ComM_RunCtrlType  ComM_RunCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            ��̬��������
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
* ��������:ComM_Init
* ��������:ComMģ���ʼ��
* �������:��
* �������:��
* ����/�������:��
* ����ֵ  :
* ��������:��������
* ��ע	  :
*************************************************************/
void ComM_Init(void)
{
	uint8  GroupIndex = 0u;

	/****************************
			���ò������
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
* ��������:ComM_RxIndication
* ��������:֪ͨComMģ��,�豸��=DevId��CAN���������յ�����
* �������:DevId:������ID��;
* �������:��
* ����/�������:��
* ����ֵ  :E_OK:�²�֪ͨ�ɹ�
		   E_NOT_OK:ģ��δ��ʼ������ڲ�������;
* ��������:������
* ��ע	  :�²�Can����ģ������ж�(Rx ISR)����
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
		/*ģ��δ��ʼ��*/
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
		/*DevId��Ч*/
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
      ������ƽֵ1:��ѯ��ǰ��ƽֵ��Ӧ����
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
        /*��ǰƽ����ƽֵ��������û���ҵ���Ӧ��Χ*/
	  	return(E_NOT_OK);
	}
	
	/************************************
      ������ƽֵ2:����������ƽֵ
    *************************************/
    OSAL_ENTER_CRITICAL();
   	if(TRUE == pControllCfg->Direct)
	{
		/* "+" ���� */
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue += StepValue;
	}
	else
	{
		/* "-" ����*/
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
      �ÿ���������״̬OK + ������CANͨѶOK
    *************************************/
    OSAL_ENTER_CRITICAL();
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerStatus    
								= COMM_CONTROLER_OK; 
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus 
								= COMM_COMMUNICAITON_OK;
	
	if((ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.ExpireTicks)> 0u)
	{
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.CurTicks   
								= OSALTimeGet();/*ˢ��ͨѶ��ʱʱ��*/
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.ExpireTicks
								= pControllCfg->FaultTimeOut;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus
								= TIMER_ON;	   	/*������ʱTimer*/

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
* ��������:ComM_BusOffIndication
* ��������:֪ͨComMģ��,�豸��=DevId��CAN����������BusOff.
* �������:DevId:
* �������:��
* ����/�������:��
* ����ֵ  :E_OK:�²�֪ͨ�ɹ�
		   E_NOT_OK:ģ��δ��ʼ������ڲ�������;
* ��������:������
* ��ע	  :
*************************************************************/
Std_ReturnType ComM_BusOffIndication(uint8 DevId)
{
	uint8  GroupOffset = 0u;
	uint8  ControllOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
		/*DevId��Ч*/
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
							= COMM_CONTROLER_BUSOFF;	/*�ÿ�����״̬"BusOff"*/
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].ControllerSubStatus      
							= COMM_COMMUNICAITON_ERR;  	/*�ÿ�����ͨѶ״̬"Communication Error"*/
	
	ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[ControllOffset].TimerCtrl.TimerStatus 
	                        = TIMER_OFF;				/*�رն�ʱ��*/
	OSAL_EXIT_CRITICAL();
	
	/*ֹͣCAN������*/
	//Can_EnterStopMode(DevId);

	/*********************************/
	/*Modified by chenms 2018-6-6,pm16:07*/
	/*��֪ͨCanIfģ��,�����Ӧ�ķ��Ͷ���*/
	CanIf_ResetTransmitQueue(DevId);

	/*��-���������--���ڷ��ͱ�ʶ*/
	/*��-�رտ������жϷ��͸��ٶ�ʱ��*/
	/*��-��ֹ�����ж�*/
    CanIf_TransmitQueueIsEmpty(DevId);
	
	/*��-��ֹ����ָ��������Ӳ��Buffer�е�Pending����*/
	Can_RequestTransmitterMessageAbort(DevId);
	return(E_OK);	
}

/************************************************************
* ��������:ComM_GetTrustInfo
* ��������:��ȡ���=GroupId������������Ϣ.
* �������:GroupId:˫CAN������ID��;
* �������:(*pTrustInfo):����������������Ϣ,����Ϊָ���������ο�����ID��;
* ����/�������:
* ����ֵ  :E_OK:�ɹ���ȡ����������������Ϣ
		   E_NOT_OK:ģ��δ��ʼ������ڲ�������;
* ��������:
* ��ע	  :
*************************************************************/
Std_ReturnType ComM_GetTrustInfo(uint8 GroupId,uint8 *pTrustInfo)
{
	uint8  GroupOffset = 0u;
	Std_ReturnType ret = E_NOT_OK;
	
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/
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
		/*GroupId��Ч*/
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
* ��������:ComM_GetControllerStatus
* ��������:��ȡ�豸��=DevId��CAN������״̬��Ϣ.
* �������: DevId:Can������ID��;
* �������:(*pControllerStatus):Can������״̬��Ϣ; 
           = 0:COMM_CONTROLLER_OK ������״̬OK; 
           = 1:COMM_CONTROLLER_BUSOFF  ������״̬busOff;
* ����/�������:
* ����ֵ  :E_OK:�ɹ���ȡ������״̬��Ϣ;
		   E_NOT_OK:ģ��δ��ʼ������ڲ�������;
* ��������:
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
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
		/*DevId��Ч*/
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
* ��������:ComM_GetControllerCommStatus
* ��������:��ȡ�豸��=DevId��������ͨѶ״̬��Ϣ.
* �������: DevId:Can������ID��;
* �������:(*pCommStatus):Can������ͨѶ״̬; 
    		= 0u:COMM_COMMUNICAITON_OK   ������ͨ������
    		= 1u:COMM_COMMUNICAITON_ERR  ������ͨ�Ź���
* ����/�������:
* ����ֵ  :E_OK:�ɹ���ȡ������״̬��Ϣ;
		   E_NOT_OK:ģ��δ��ʼ������ڲ�������;
* ��������:
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
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
		/*DevId��Ч*/
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
* ��������: ComM_MainFunction
* ��������: ComMģ���̨��ѭ��.
* �������: DevId:Can������ID��;
* �������:(*pControllerStatus):Can������״̬��Ϣ;
* ����/�������:
* ����ֵ  : ��
* ��������:
* ��ע	  :�ú�����Ҫ�����ڵ���
*************************************************************/
void ComM_MainFunction(void)
{
	/**************************/
	if(COMM_UNINIT == ComM_RunCtrl.MkStatus)
	{
		/*ģ��δ��ʼ��*/
#if(STD_ON == COMM_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_COMM,
						0u,
						COMM_MAINFUNCTION_ID,
						COMM_E_UNINIT);					
#endif
		return;
	}

	/**************************/
	/*�����������������ͨѶ��ʱ*/
	ComM_MainFunctionForCalcCommunicationFault();

	/*��������������е�����������Ϣ*/
	ComM_MainFunctionForCalcTrustInfo();
}

#if 1
/************************************************************
* ��������:ComM_InitGroup
* ��������:ComMģ���ʼ��ָ��������;
* �������:GroupId:������ID��
* �������:��
* ����/�������:��
* ����ֵ  :
* ��������:������
* ��ע	  :
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
		/*GroupId��Ч*/
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
	      �������ڿ�����0
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
	      �������ڿ�����1
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
* ��������:ComM_SearchDeviceInConfig
* ��������:����DevId�ھ�̬�����е��������±�+�������ڵĿ������±�.
* �������: DevId:Can������ID��;
* �������:(*pGroupCfg):����DevId���ڵ������������±�;
		   (*pControllCfg):����DevId���ڵ���������������Ŀ������±�;
* ����/�������:
* ����ֵ  :E_OK:�ھ�̬������,���ҳɹ�;
           E_NOT_OK:�ھ�̬������,����ʧ��;
* ��������:
* ��ע	  :
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
* ��������:ComM_SearchGroupInConfig
* ��������:����GroupId�ھ�̬�����е��������±�.
* �������: GroupId:������ID��;
* �������:(*pGroupCfg):GroupId���ڵ������������±�;
* ����/�������:
* ����ֵ  :E_OK:�ھ�̬������,���ҳɹ�;
           E_NOT_OK:�ھ�̬������,����ʧ��;
* ��������:
* ��ע	  :
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
* ��������:ComM_MainFunctionForCalcCommunicationFault
* ��������:ģ���̨ѭ����������������Ƿ�ͨѶ����
* �������:��
* �������:��
* ����/�������:
* ����ֵ  :��
* ��������:
* ��ע	  :�ú����ڱ�ComM_MainFunction()����;
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
					/*���ճ�ʱ,�ÿ�������������ͨѶ����*/
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
* ��������:ComM_MainFunctionForCalcCommunicationFault
* ��������:ģ���̨ѭ������������������������
* �������:��
* �������:��
* ����/�������:
* ����ֵ  :��
* ��������:
* ��ע	  :�ú����ڱ�ComM_MainFunction()����;
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
			/*��������·CAN��������OK*/
			ComM_CalcTrustBusForBothOK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
        /***************/
		else if(  (COMM_CONTROLER_OK == Controller0_Status)
			    &&(COMM_CONTROLER_BUSOFF == Controller1_Status))
		{
			/*����������ĵ�0·������OK,��1·������BusOff*/
			ComM_CalcTrustBusInController0OK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
        /***************/
		else if(  (COMM_CONTROLER_BUSOFF == Controller0_Status)
			    &&(COMM_CONTROLER_OK == Controller1_Status))
		{
			/*����������ĵ�0·������BusOff,��1·������OK*/
			ComM_CalcTrustBusInController1OK(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
		else
		{
			/*�������������·CAN������������*/
			ComM_CalcTrustBusInAllFault(ComM_RunCtrl.GroupCtrl[GroupOffset].GroupId);
		}
	}
}

/************************************************************
* ��������:ComM_CalcTrustBusForBothOK
* ��������:��ָ����������,��·CAN��������OK�������,��������������������.
* �������:GroupId:������ID��;
* �������:��
* ����/�������:
* ����ֵ  :��
* ��������:
* ��ע	  :
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
		/*GroupIdδ��������*/
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
	     ��������·CAN������ͨѶ��������
	      �������ƽֵ��������ʶ��
	    *******************************/
	    if(TRUE == ComM_Cfg.pGroupCfg[GroupOffset].pControllerCfg[0].Direct)
		{
		   /* ������������ĵ�һ��������:��ƽֵ"+"���� */
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
			/*���β�����ʽΪ����"+"������*/
			OSAL_ENTER_CRITICAL();
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = ControllerIdForAddStep;
			OSAL_EXIT_CRITICAL();
		}
		else if(BalanceValue < 40u)
		{
			/*���β�����ʽΪ����"-"������*/
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
		/*�������ڵ�1·ͨѶ����,��2·ͨѶ�쳣,���ε�1·*/
		if( ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
				ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId )
		{
			/*�����������л�Ϊ���ε�1·*/
			/* Nothing to do */ 
		}
		else
		{
			OSAL_ENTER_CRITICAL();
			/*�л�Ϊ���ε�1·*/
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus = 
							ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;

			/*��ǰ������ƽֵ�ָ�Ϊ���γ�ֵ*/
			ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue = 
							ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance;
			OSAL_EXIT_CRITICAL();
		}
	}
	else if(   (COMM_COMMUNICAITON_ERR == Controller0_ComStatus)
		     &&(COMM_COMMUNICAITON_OK  == Controller1_ComStatus))
	{
		/*�������ڵ�1·ͨѶ�쳣,��2·ͨѶ����,���ε�2·*/
		if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
			ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId )
		{
			/* ��ǰ�Ѿ����ε�2· */
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
		/*�������ڵ�1·,��2·��ͨѶ�쳣,����֮ǰ������Ϣ*/
		//OSAL_ENTER_CRITICAL();
		//ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus 
		//			= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
		//OSAL_EXIT_CRITICAL();
	}
}

/************************************************************
* ��������:ComM_CalcTrustBusInController0OK
* ��������:��ָ����������,��0·������OK,��1·���������ϵ������,��������������������.
* �������:GroupNum:������ID��;
* �������:��
* ����/�������:
* ����ֵ  :��
* ��������:
* ��ע	  :
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
		/*GroupIdδ��������*/
		return;
	}

	/*********************************
     ��ѯ�������ڵ�1·�������Ƿ��Իָ�
     *********************************/
	Controller1_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
    Can_GetControllerStatus(Controller1_Id, &Controller1_Status);

	OSAL_ENTER_CRITICAL();
	if((0u == Controller1_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus))
	{
		/*�������ڵ�1·������
		  ���Իָ�(TxOK or TxWRN or TxERR) */
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus 
		              = COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus       
					  = COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*�������ڵ�1·������δ�Իָ�(Bus-Off)���1·�������Ѿ��ָ��ҽ��յ�����֪ͨ*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	/******************************
	   �л�����Ϊ�������ڿ�����0
	 ******************************/
	if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
		       ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId)
	{
		/*�������Ѿ����ε�0·������,�����*/
		;
	}
	else
	{
	    /*�����鵱ǰ���ε�1·���������л���������*/
		OSAL_ENTER_CRITICAL();
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus     
					= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;

		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue 
					= ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance; /*��ƽֵ�ָ�Ϊ��ֵ*/
		OSAL_EXIT_CRITICAL();
	}
}

/************************************************************
* ��������:ComM_CalcTrustBusInController1OK
* ��������:��ָ����������,��0·����������,��1·������OK�������,��������������������.
* �������:GroupId:������ID��;
* �������:��
* ����/�������:
* ��������:
* ��ע	  :
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
		/*GroupIdδ��������*/
		return;
	}

	/*********************************
     ��ѯ�������ڵ�0·�������Ƿ��Իָ�
     *********************************/
	Controller0_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
	Can_GetControllerStatus(Controller0_Id, &Controller0_Status);

	OSAL_ENTER_CRITICAL();
	if((0u == Controller0_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus))
	{
		/*�������ڵ�0·������
		  ���Իָ�(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus 
							= COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus       
							= COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*�������ڵ�0·������δ�Իָ�(Bus-Off)���0·�������Ѿ��ָ��ҽ��յ�����֪ͨ*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	
	/******************************
	   �л�����Ϊ�������ڿ�����1
	 ******************************/
	if(ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus == 
		       ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId)
	{
		/*�������Ѿ����ε�1·������,�����*/
		;
	}
	else
	{
		/*�����鵱ǰ���ε�0·���������л���������*/
		OSAL_ENTER_CRITICAL();
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurTrustBus 
						= ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].CurBalanceValue 
						= ComM_Cfg.pGroupCfg[GroupOffset].ValueOfBalance; /*��ƽֵ�ָ�Ϊ��ֵ*/
		OSAL_EXIT_CRITICAL();
	}
}
/************************************************************
* ��������:ComM_CalcTrustBusInController1OK
* ��������:��ָ����������,��0·+��1·�����������.
* �������:GroupNum:������ID��;
* �������:��
* ����/�������:
* ����ֵ  :��
* ��������:
* ��ע	  :
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
		/*GroupIdδ��������*/
		return;
	}
	/*********************************
     ��ѯ�������ڵ�0·�������Ƿ��Իָ�
     *********************************/
	Controller0_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerId;
	Can_GetControllerStatus(Controller0_Id, &Controller0_Status);
	
	OSAL_ENTER_CRITICAL();
	if((0u == Controller0_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus))
	{
		/*�������ڵ�0·������
		  ���Իָ�(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerStatus 
							= COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[0].ControllerSubStatus       
							= COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*�������ڵ�0·������δ�Իָ�(Bus-Off)���0·�������Ѿ��ָ��ҽ��յ�����֪ͨ*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
	
	/*********************************
     ��ѯ�������ڵ�1·�������Ƿ��Իָ�
     *********************************/
	Controller1_Id = ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerId;
    Can_GetControllerStatus(Controller1_Id, &Controller1_Status);
    
	OSAL_ENTER_CRITICAL();
	if((0u == Controller1_Status)
		&&(COMM_CONTROLER_BUSOFF == ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus))
	{
		/*�������ڵ�1·������
		  ���Իָ�(TxOK or TxWRN or TxERR)*/
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerStatus 
		              = COMM_CONTROLER_OK;
		
		ComM_RunCtrl.GroupCtrl[GroupOffset].ControllerCtrl[1].ControllerSubStatus       
					  = COMM_COMMUNICAITON_ERR;	
	}
	else
	{
		/*�������ڵ�1·������δ�Իָ�(Bus-Off)���1·�������Ѿ��ָ��ҽ��յ�����֪ͨ*/
		/*Nothing to do*/
	}
	OSAL_EXIT_CRITICAL();
}

#endif

