/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Can.c
* ��������  : 9s12xep100-Can��Դ�ļ�(Can.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
* 1.0.1       2019/1/4        sunj                MODify
**------------------------------------------------------------------------------------------------*/
#include "Can.h"
#include "CanIf.h"
#include "ComM.h"
#include "drv_sci.h"

/****************************************
           ����ʱ���ݽṹ���Ͷ���
 ****************************************/
typedef  enum
{
	CAN_UNINIT = 0u,
	CAN_INIT   = 1u
}Can_MkStatusType;

typedef struct
{
	Can_MkStatusType  MkStatus;
}Can_MkCtrlType;
/*****************************************
            ����ʱ���ݽṹ����
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Can_MkCtrlType  Can_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            ��̬��������
 ****************************************/
#if 1
STATIC void Can_CalcBaseAddrByControllerId(uint8 DevId,uint32 *pBaseAddr);
STATIC void	Can_EnterInitMode(uint32 BaseAddr);
STATIC void	Can_ExitInitMode(uint32 BaseAddr);
STATIC void	Can_ConfigBaudRate(uint32 BaseAddr,Can_ControllerBpsType Bps);
STATIC void Can_ConfigFilter(uint32 BaseAddr,Can_IdType IdType,uint8 FilterNum,Can_FilterCfgType *pFilterCfg);
STATIC Std_ReturnType Can_SearchControllerFromRxObjectCfg(uint8  DevId,uint8 *pObjectIndex);
STATIC Std_ReturnType Can_SearchControllerFromTxObjectCfg(uint8  DevId,uint8 *pObjectIndex);
STATIC Std_ReturnType Can_SearchControllerFromControllerCfg(uint8  DevId,uint8 *pControllerIndex);
STATIC void  Can_Write(uint8  DevId,PduInfoType PduInfo);
STATIC void  Can_TansmitIsrProcess(uint8 DevId);
STATIC void  Can_ReceiveIsrProcess(uint8 DevId);
STATIC void  Can_ErrorIsrProcess(uint8 DevId);
STATIC void  Can_InitController(uint8 DevId);
#endif

/*********************************************
         ����IDת����S12�涨��ID��ʽ
 *********************************************/
/*��չ֡*/
#define CAN_R0_EID(x)		((uint8)(((x) >> 21) & 0xff))   		/*ID28~ID21*/ 
#define CAN_R1_EID(x)		((uint8)(((x) >> 15) & 0x07) | (uint8)(((x) >> 13) & 0xe0) | 0x18)/*ID17~ID15,ID20~ID18,SRR=1,IDE=1*/
#define CAN_R2_EID(x)		((uint8)(((x) >> 7) & 0xff)) 	   	/*ID14~ID07*/
#define CAN_R3_EID(x,y)		((uint8)  ((x) << 1) | (uint8)(y))	/*ID06~ID00,y=RTR*/
/*********************/
/*��׼֡*/
#define CAN_R0_SID(x)		((uint8)(((x) >> 3) & 0xff))							/*ID10~ID3*/
#define CAN_R1_SID(x,y)		((uint8)(((x) << 5) & 0xe0)) | (((uint8)(y)) << 4) 	/*ID2~ID0,y=RTR,IDE=0*/

/************************************************************
* ��������:Can_Init
* ��������:Can����ģ���ʼ��,�ú�����Ҫ��ģ�龲̬���õ����п�������ʼ��.
* �������:��
* �������:��
* ����/�������:��
* ��������: ��������
* ��ע	  :
*************************************************************/
void  Can_Init(void)
{
	uint8  ControllerIndex = 0u;
	uint8  ControllerId = 0u;
	
	/********************/
	for(ControllerIndex=0u;ControllerIndex<(Can_Cfg.NumOfController);ControllerIndex++)
	{
		ControllerId = Can_Cfg.pControllerCfg[ControllerIndex].ControllerId;
		Can_InitController(ControllerId);
	}
	OSAL_ENTER_CRITICAL();
	Can_MkCtrl.MkStatus = CAN_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* ��������:Can_EnableTxInterrupt
* ��������:ʹ��DevIdָ��Can�����������ж�;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
void  Can_EnableTxInterrupt(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENABLE_TXINTERRUPT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENABLE_TXINTERRUPT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTIER.Bits.TXEIE0 = 1u;
}


/************************************************************
* ��������:Can_DisableTxInterrupt
* ��������:��ֹDevIdָ��Can�����������ж�;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
void  Can_DisableTxInterrupt(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_DISABLE_TXINTERRUPT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_DISABLE_TXINTERRUPT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTIER.Bits.TXEIE0 = 0u;
}

/************************************************************
* ��������:Can_RequestTransmitterMessageAbort
* ��������:������ֹ����ָ��������Ӳ��Buffer�е�Pending����;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
void  Can_RequestTransmitterMessageAbort(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_REQUESTMESSAGEABORT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_REQUESTMESSAGEABORT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTARQ.Bits.ABTRQ0 = 1u;
}

/************************************************************
* ��������:Can_EnterStopMode
* ��������:ֹͣDevIdָ��Can����������;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
void  Can_EnterStopMode(uint8  DevId)
{
#if 0
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTERSTOP_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTERSTOP_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);

	/*�����ʼ��ģʽ,CAN������ֹͣ*/	
	Can_EnterInitMode(BaseAddr);
#endif
}
/************************************************************
* ��������:Can_GetControllerStatus
* ��������:��ȡDevIdָ��Can������״̬;
* �������:DevId:Can�������豸ID��;
* �������:(*pCanStatus): =0:CAN������û�н���BusOff;
                          =1:CAN����������BusOff;
* ����/�������:
* ��������:
* ��ע	  :(pCanReg->CANRFLG.MergedBits.grpTSTAT) 
			=0:TxOK; ���Ϳ���������;
			=1:TxWRN;���Ϳ���������;
			=2:TxERR;���Ϳ���������;
			=3:Bus-Off;���Ϳ��������߹ر�;
*************************************************************/
void  Can_GetControllerStatus(uint8  DevId,uint8 *pCanStatus)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType *pCanReg = NULL_PTR;

	(*pCanStatus) = 0xFFu; 
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	if(NULL_PTR == pCanStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;
    if(3u == (pCanReg->CANRFLG.MergedBits.grpTSTAT))
	{
		/*����������"BusOff"״̬*/
		(*pCanStatus) = 1u;
	}
	else
	{
		/*����������"TxOK","TxWRN" "TxERR"״̬*/
		(*pCanStatus) = 0u;
	}
}

/************************************************************
					��̬����ʵ��
 ***********************************************************/
#if	1
/************************************************************
* ��������:Can_CalcBaseAddrByControllerId
* ��������:���ݿ�����ID,����������Ĵ�������ַ;
* �������:DevId:CAN������ID;
* �������:(*pBaseAddr):�������Ĵ�������ַ��
* ����/�������:��
* ��������:������
* ��ע	  :
*************************************************************/
STATIC void Can_CalcBaseAddrByControllerId(uint8 DevId,uint32 *pBaseAddr)
{
	switch(DevId)
	{
		case CAN_CONTROLLER_0:
			 (*pBaseAddr) = 0x140u;
			 break;
			 
		case CAN_CONTROLLER_1:
			 (*pBaseAddr) = 0x180u;
			 break;
			 
		case CAN_CONTROLLER_2:
			 (*pBaseAddr) = 0x1C0u;
			 break;
			 
		case CAN_CONTROLLER_3:
			 (*pBaseAddr) = 0x200u;
			 break;
			 
		case CAN_CONTROLLER_4:
			 (*pBaseAddr) = 0x280u;
			 break;	
			 
		default:
#if 0
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		/*������Ч*/
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_CALCBASEADDRBYCONTROLLERID_ID,
						CAN_E_PARAM_INVALID);				
#endif
#endif
			break;
	}
}

/************************************************************
* ��������:Can_EnterInitMode
* ��������:Can�����������ʼ��ģʽ��
* �������:BaseAddr:�豸�Ĵ�������ַ;
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :
*************************************************************/
STATIC void  Can_EnterInitMode(uint32 BaseAddr)
{
	volatile uint16   WaitTimes = 0u;
	volatile Can_RegType *pCanReg = NULL_PTR;

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	/**********************************/
	/*��������ʼ��ģʽ*/
	pCanReg->CANCTL0.Bits.INITRQ = 1u;  
	for(WaitTimes=0u;WaitTimes<CAN_REQUEST_CONFIRM_TIMES;WaitTimes++)
	{
		if(1u == pCanReg->CANCTL1.Bits.INITAK)
		{
			/*ȷ�Ͽ����������ʼ��ģʽ*/
			break;
		}
	}
	if(CAN_REQUEST_CONFIRM_TIMES == WaitTimes)
	{
		/*�����������ʼ��ģʽ,ʧ��*/
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTER_INITMODE,
						CAN_E_ENTER_INITMODE_INVALID);			
#endif
	}	
}

/************************************************************
* ��������:Can_ExitInitMode
* ��������:Can�������˳���ʼ��ģʽ��
* �������:BaseAddr:�豸�Ĵ�������ַ;
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :
*************************************************************/
STATIC void  Can_ExitInitMode(uint32 BaseAddr)
{
	volatile uint16   WaitTimes = 0u;
	volatile Can_RegType *pCanReg = NULL_PTR;

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	/*�����˳���ʼ��ģʽ*/
	pCanReg->CANCTL0.Bits.INITRQ = 0u;  
	for(WaitTimes=0u;WaitTimes<CAN_REQUEST_CONFIRM_TIMES;WaitTimes++)
	{
		if(0u == pCanReg->CANCTL1.Bits.INITAK)
		{
			/*ȷ�Ͽ������˳���ʼ��ģʽ*/
			break;
		}
	}
	if(CAN_REQUEST_CONFIRM_TIMES == WaitTimes)
	{
		/*�������˳���ʼ��ģʽ,ʧ��*/
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_EXIT_INITMODE,
						CAN_E_EXIT_INITMODE_INVALID);			
#endif
	}	
}

/************************************************************
* ��������:Can_ConfigBaudRate
* ��������:����CAN������������
* �������:BaseAddr:�豸�Ĵ�������ַ;
           Bps:�����ò���������
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  : �ú����Ĳ����ʳ�ֵ����ģ��
            BusClock=50�׵�����½��еļ���.
            Bps = fBus/(Prescaler value *(1+TimeSegment1+TimeSegment2))
            
            OscClock=4M������½��еļ���  modify by sunj 2019/1/4 14:54
            Bps = fOsc/(Prescaler value *(1+TimeSegment1+TimeSegment2))
            ����100k 125k 250k 500K�����޸�,��ͨ������   1000kδ��ͨ
*************************************************************/
STATIC void  Can_ConfigBaudRate(uint32 BaseAddr,Can_ControllerBpsType Bps)
{
	volatile Can_RegType *pCanReg = NULL_PTR;

	/*********************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	switch(Bps)
	{
		case CAN_BPS_100K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 3u;//24  
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 5u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 2u;//12
			 break;

		case CAN_BPS_125K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 1u;//19
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 4u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 9u;//12
			 break;
			 
		case CAN_BPS_250K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u; //9
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 4u; //5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 9u;//12
			 break;
			 
		case CAN_BPS_500K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u;//4
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 1u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 4u;//12
			 break;
			 
		case CAN_BPS_1000K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u;//9
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 1u;//1
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 0u;//1
			 break;
			 
		default:
			 break;			 
	}    	
}

/************************************************************
* ��������:Can_ConfigFilter
* ��������:����CAN�������˲���
* �������:BaseAddr:�豸�Ĵ�������ַ;
           FilterNum:�豸�������˲�������;
           pFilterCfg:�豸�������˲��������׵�ַ;
* �������:��
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC void  Can_ConfigFilter(uint32 BaseAddr,Can_IdType IdType,uint8 FilterNum,Can_FilterCfgType *pFilterCfg)
{
    uint32  FilterMaskId = 0ul;
	uint32  FilterAcceptId = 0ul;
	volatile Can_RegType *pCanReg = NULL_PTR;
	
	/*********************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	switch(FilterNum)
	{
		case 2u:
			 /*CANIDAC,ѡ��2��32λ�˲���*/
			 pCanReg->CANIDAC.Bits.IDAM0 = 0u;
			 pCanReg->CANIDAC.Bits.IDAM1 = 0u;
             if(CANID_STANDARD == IdType)
         	 {	
         	 	/*==��׼֡==*/
				/*MaskId*/
				FilterMaskId = pFilterCfg[0].FilterMaskId;
				pCanReg->CANIDMR0.Byte = CAN_R0_SID(FilterMaskId); 
				pCanReg->CANIDMR1.Byte = CAN_R1_SID(FilterMaskId,0) & 0xE7;   /*Bit4=0,Bit3=0:��ʾ��Ҫ�Ƚ�(RTR && IDE)λ*/
				FilterMaskId = pFilterCfg[1].FilterMaskId;
				pCanReg->CANIDMR4.Byte = CAN_R0_SID(FilterMaskId);
				pCanReg->CANIDMR5.Byte = CAN_R1_SID(FilterMaskId,0) & 0xE7;   /*Bit4=0,Bit3=0:��ʾ��Ҫ�Ƚ�(RTR && IDE)λ*/ 

				/*AcceptId*/
				FilterAcceptId = pFilterCfg[0].FilterAcceptId;
				pCanReg->CANIDAR0.Byte = CAN_R0_SID(FilterAcceptId);
				pCanReg->CANIDAR1.Byte = CAN_R1_SID(FilterAcceptId,0); /*Bit4=0,Bit3=0:��ʾֻ����(��׼֡&&����֡)*/
				FilterAcceptId = pFilterCfg[1].FilterAcceptId;
				pCanReg->CANIDAR4.Byte = CAN_R0_SID(FilterAcceptId);
				pCanReg->CANIDAR5.Byte = CAN_R1_SID(FilterAcceptId,0); /*Bit4=0,Bit3=0:��ʾֻ����(��׼֡&&����֡)*/
         	 }
			 else
		 	 {
		 	 	/*==��չ֡==*/
				/*MaskId*/
				FilterMaskId = pFilterCfg[0].FilterMaskId;
				pCanReg->CANIDMR0.Byte = CAN_R0_EID(FilterMaskId);
				pCanReg->CANIDMR1.Byte = CAN_R1_EID(FilterMaskId) & 0xE7;/*SRR(Bit4)=0,IDE(Bit3)=0:��ʾ��Ҫ�Ƚ�SRR && IDEλ*/  
				pCanReg->CANIDMR2.Byte = CAN_R2_EID(FilterMaskId);
				pCanReg->CANIDMR3.Byte = CAN_R3_EID(FilterMaskId,0);     /*RTR(Bit0)=0:��ʾ��Ҫ�Ƚ�RTRλ*/
				FilterMaskId = pFilterCfg[1].FilterMaskId;
				pCanReg->CANIDMR4.Byte = CAN_R0_EID(FilterMaskId);
				pCanReg->CANIDMR5.Byte = CAN_R1_EID(FilterMaskId) & 0xE7;/*SRR(Bit4)=0,IDE(Bit3)=0:��ʾ��Ҫ�Ƚ�SRR && IDEλ*/ 
				pCanReg->CANIDMR6.Byte = CAN_R2_EID(FilterMaskId);
				pCanReg->CANIDMR7.Byte = CAN_R3_EID(FilterMaskId,0);     /*RTR(Bit0)=0:��ʾ��Ҫ�Ƚ�RTRλ*/

				/*AcceptId*/
				FilterAcceptId = pFilterCfg[0].FilterAcceptId;
				pCanReg->CANIDAR0.Byte = CAN_R0_EID(FilterAcceptId);
				pCanReg->CANIDAR1.Byte = CAN_R1_EID(FilterAcceptId); 	/*SRR(Bit4)=1,IDE(Bit3)=1:��ʾֻ������չ֡*/  
				pCanReg->CANIDAR2.Byte = CAN_R2_EID(FilterAcceptId);
				pCanReg->CANIDAR3.Byte = CAN_R3_EID(FilterAcceptId,0);  /*RTR(Bit0)=0:��ʾֻ��������֡*/
				FilterAcceptId = pFilterCfg[1].FilterAcceptId;
				pCanReg->CANIDAR4.Byte = CAN_R0_EID(FilterAcceptId);
				pCanReg->CANIDAR5.Byte = CAN_R1_EID(FilterAcceptId); 	/*SRR(Bit4)=1,IDE(Bit3)=1:��ʾֻ������չ֡*/   
				pCanReg->CANIDAR6.Byte = CAN_R2_EID(FilterAcceptId);
				pCanReg->CANIDAR7.Byte = CAN_R3_EID(FilterAcceptId,0);  /*RTR(Bit0)=0:��ʾֻ��������֡*/
		 	 }
			 break;
			 
		case 4u:
			 /*�ݲ�֧��4��16λ�˲�*/
			 break;
			 
		case 8u:
			 /*�ݲ�֧��8��8λ�˲�*/
			 break;
			 
		default:
			 break;
	}
}
/************************************************************
* ��������:Can_SearchControllerFromRxObjectCfg
* ��������:������ľ�̬�����в���DevId��Ӧ��������;
* �������:DevId:������ID��;
* �������:(*pObjectIndex):��̬����������;
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromRxObjectCfg(uint8  DevId,uint8 *pObjectIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;
		
	for(Index=0u;Index<(Can_Cfg.NumOfHardwareObject);Index++)
	{
		if(   (DevId == Can_Cfg.pHardwareObjectCfg[Index].pCanControlRef->ControllerId)
			&&(CANID_RECEIVE == Can_Cfg.pHardwareObjectCfg[Index].CanObjectTrans))
		{
			/*���ҵ������ÿ�����������*/
			(*pObjectIndex) = Index;
			break;
		}
	}
	if(Index < Can_Cfg.NumOfHardwareObject)
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

/************************************************************
* ��������:Can_SearchControllerFromRxObjectCfg
* ��������:������ľ�̬�����в���DevId��Ӧ��������;
* �������:DevId:������ID��;
* �������:(*pObjectIndex):��̬����������;
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromTxObjectCfg(uint8  DevId,uint8 *pObjectIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;
		
	for(Index=0u;Index<(Can_Cfg.NumOfHardwareObject);Index++)
	{
		if(   (DevId == Can_Cfg.pHardwareObjectCfg[Index].pCanControlRef->ControllerId)
			&&(CANID_TRANSMIT == Can_Cfg.pHardwareObjectCfg[Index].CanObjectTrans))
		{
			/*���ҵ������ÿ�����������*/
			(*pObjectIndex) = Index;
			break;
		}
	}
	if(Index < Can_Cfg.NumOfHardwareObject)
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

/************************************************************
* ��������:Can_SearchControllerIndex
* ��������:�ڿ�������̬�����в���DevId��Ӧ����������;
* �������:DevId:������ID��;
* �������:(*pObjectIndex):��̬���ÿ�����������;
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromControllerCfg(uint8  DevId,uint8 *pControllerIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;

	for(Index=0u;Index<(Can_Cfg.NumOfController);Index++)
	{
		if(DevId == Can_Cfg.pControllerCfg[Index].ControllerId)
		{
			/*���ҵ�ָ��������������*/
		   (*pControllerIndex) = Index;
		   break;
		}
	}
	if(Index < (Can_Cfg.NumOfController))
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

/************************************************************
* ��������:Can_Write
* ��������:ָ��DevId��Ӧ��Can����������,��PduInfo����д��CanӲ������;
* �������:DevId  :Can�������豸ID��;
		   PduInfo:
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC void  Can_Write(uint8  DevId,PduInfoType PduInfo)
{
    Std_ReturnType  ret = E_NOT_OK;
	uint8 HardTxObjectIndex = 0u;
	uint32 BaseAddr = 0ul;
	Can_IdType  IdCfgType;
	volatile Can_RegType  *pCanReg = NULL_PTR;
    uint8  TxBuffNum = 0u;

	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;

	/*ѡ���ͻ���*/
	pCanReg->CANTBSEL.MergedBits.grpTX = pCanReg->CANTFLG.MergedBits.grpTXE;
	TxBuffNum = pCanReg->CANTBSEL.MergedBits.grpTX;
	/******************************/
	ret = Can_SearchControllerFromTxObjectCfg(DevId,&HardTxObjectIndex);
	if(E_NOT_OK == ret)
	{
		/*�ÿ������޷�����������,Ĭ�Ϸ�����չ֡*/
		IdCfgType = CANID_EXTENDED;
	}
	else
	{
		IdCfgType = Can_Cfg.pHardwareObjectCfg[HardTxObjectIndex].CanIdType;
	}
	/* ID */
	if(CANID_EXTENDED == IdCfgType)
	{
		/*��չ֡*/
		pCanReg->CANTXIDR0.Byte = CAN_R0_EID(PduInfo.PduId);
		pCanReg->CANTXIDR1.Byte = CAN_R1_EID(PduInfo.PduId);
		pCanReg->CANTXIDR2.Byte = CAN_R2_EID(PduInfo.PduId);
		pCanReg->CANTXIDR3.Byte = CAN_R3_EID(PduInfo.PduId,0);
	}
	else
	{
		/*��׼֡*/
		pCanReg->CANTXIDR0.Byte = CAN_R0_SID(PduInfo.PduId);
		pCanReg->CANTXIDR1.Byte = CAN_R1_SID(PduInfo.PduId,0);
	}
	/* DLC */
	pCanReg->CANTXDLR.MergedBits.grpDLC = PduInfo.PduLength;

	/* DATA */
	pCanReg->CANTXDSR0.Byte = PduInfo.PduData[0];
	pCanReg->CANTXDSR1.Byte = PduInfo.PduData[1];
	pCanReg->CANTXDSR2.Byte = PduInfo.PduData[2];
	pCanReg->CANTXDSR3.Byte = PduInfo.PduData[3];
	pCanReg->CANTXDSR4.Byte = PduInfo.PduData[4];
	pCanReg->CANTXDSR5.Byte = PduInfo.PduData[5];
	pCanReg->CANTXDSR6.Byte = PduInfo.PduData[6];
	pCanReg->CANTXDSR7.Byte = PduInfo.PduData[7];	

	/* ���ѡ����buffer�Ŀձ�ʾ */
	pCanReg->CANTFLG.MergedBits.grpTXE = TxBuffNum;
}

/************************************************************
* ��������:Can0_TansmitIsrProcess
* ��������:Can�����������жϴ����ú���;
* �������:DevId:������ID��;
* �������:��
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC void  Can_TansmitIsrProcess(uint8 DevId)
{
	PduInfoType  PduInfo;
	Std_ReturnType ret = E_NOT_OK;

	/***********************/
	/*added by chenms 2018-5-23,am10:10*/
	CanIf_TxConfirmHook(DevId);
	
	/***********************/
	ret = CanIf_GetNextPacket(DevId,&PduInfo);
	if(E_NOT_OK == ret)
	{
		/*���ķ�����ɣ�֪ͨ�ϲ�ģ��ֹͣ����*/
		CanIf_TransmitQueueIsEmpty(DevId);
	}
	else
	{
		/*���ͱ���*/
		Can_Write(DevId,PduInfo);
	}
}

/************************************************************
* ��������:Can_ReceiveIsrProcess
* ��������:Can�����������жϴ����ú���;
* �������:
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC void Can_ReceiveIsrProcess(uint8 DevId)
{
    uint8  ID[4] = {0u};
	uint32 BaseAddr = 0ul;
	PduInfoType  PduInfo;
	volatile Can_RegType  *pCanReg = NULL_PTR;
    
	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;
	
	/***********/
	/*����CanId*/
	if(1u == pCanReg->CANRXIDR1.Bits.IDE)
	{
		/*��չ֡ID*/		
		ID[0] = pCanReg->CANRXIDR0.Byte; /*ID28~ID21*/	
		ID[1] = pCanReg->CANRXIDR1.Byte; /*ID20~ID15*/
		ID[2] = pCanReg->CANRXIDR2.Byte; /*ID14~ID7 */	
		ID[3] = pCanReg->CANRXIDR3.Byte; /*ID6~ID0  */
		PduInfo.PduId =   (((uint32) ID[0]) << 21u)\
			            | (((uint32)(ID[1] & 0xE0))<< 13u)\
			            | (((uint32)(ID[1] & 0x07))<< 15u)\
			            | (((uint32)ID[2]) << 7u)\
			            | (((uint32)(ID[3] & 0xFE))>> 1u);
	}
	else
	{
		/*��׼֡ID*/		
		ID[0] = pCanReg->CANRXIDR0.Byte; 	/*ID10~ID3*/		
		ID[1] = pCanReg->CANRXIDR1.Byte; 	/*ID2 ~ID0*/
		PduInfo.PduId =  (((uint32) ID[0]) << 3u)|(((uint32)(ID[1] & 0xE0))>>5u);
	}	
	/*Dlc*/
	PduInfo.PduLength = (pCanReg->CANRXDLR.Byte) & 0x0F;	

	/*Data0~Data7*/
	PduInfo.PduData[0]= pCanReg->CANRXDSR0.Byte;
	PduInfo.PduData[1]= pCanReg->CANRXDSR1.Byte;
	PduInfo.PduData[2]= pCanReg->CANRXDSR2.Byte;
	PduInfo.PduData[3]= pCanReg->CANRXDSR3.Byte;
	PduInfo.PduData[4]= pCanReg->CANRXDSR4.Byte;
	PduInfo.PduData[5]= pCanReg->CANRXDSR5.Byte;
	PduInfo.PduData[6]= pCanReg->CANRXDSR6.Byte;
	PduInfo.PduData[7]= pCanReg->CANRXDSR7.Byte;

	/*�����������жϱ�ʾ*/
	pCanReg->CANRFLG.Bits.RXF = 1u;

    /*֪ͨCanIfģ�鱣�汨��*/
	CanIf_RxIndication(DevId,PduInfo);  

	/*֪ͨComMģ����յ�����*/
	ComM_RxIndication(DevId);

    /*֪ͨCanIfģ����в��ֱ������⴦��*/
    /*added by chenms 2018-5-3*/
	CanIf_RxIndicationHook(DevId,&PduInfo);
}


/************************************************************
* ��������:Can_ErrorIsrProcess
* ��������:Can�����������жϴ����ú���;
* �������:
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
STATIC void Can_ErrorIsrProcess(uint8 DevId)
{
	uint32 BaseAddr = 0ul;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;

	if(1u == pCanReg->CANRFLG.Bits.OVRIF)
	{
		/*�������������ش����ж�*/
		pCanReg->CANRFLG.Bits.OVRIF = 1u; /*������ش���*/
	}
	if(1u == pCanReg->CANRFLG.Bits.CSCIF)
	{
		/*����������������˳�bufOff�ж�*/
		if(3u == pCanReg->CANRFLG.MergedBits.grpTSTAT)
		{
			/*����BusOff�����ж�*/
			ComM_BusOffIndication(DevId);
		}
		else
		{
			/*�˳�BusOff�ж�*/
			/*TOdo*/
		}
		pCanReg->CANRFLG.Bits.CSCIF = 1u; /*���״̬�ı��ʾ*/
	}
}

/************************************************************
* ��������:Can_InitController
* ��������:��ʼ��ָ��������
* �������:DevId:Can�������豸ID��;
* �������:��
* ����/�������:��
* ��������: ��������
* ��ע	  :
*************************************************************/
STATIC void  Can_InitController(uint8 DevId)
{
	uint8  HardRxObjectIndex = 0u;
	uint8  ControllerCfgIndex   = 0u;
	uint8  FilterNum = 0u;
	uint32 BaseAddr  = 0ul;
	Can_IdType  IdCfgType;
	Can_ControllerBpsType BaudRate = 0u;
	Can_FilterCfgType  *pFilterCfg = NULL_PTR;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	Std_ReturnType ret = E_NOT_OK;
	volatile uint16 WaitTimes = 0u;

	/****************************/  
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerCfgIndex);
	if(E_NOT_OK == ret)
	{
	    /*DevIdδ����*/
//#if(STD_ON == CAN_DEV_ERROR_DETECT)
//		Det_ReportError(MODULE_ID_CAN,
//						0u,
//						CAN_INITCONTROLLER_ID,
//						CAN_E_PARAM_INVALID);				
//#endif
		return;
	}
	/****************************/
	/*�������������ַ*/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;

    /****************************************
             ��ʼ��ģʽ��,����������
     ***************************************/
	/*�����ʼ��ģʽ*/
	Can_EnterInitMode(BaseAddr);

	/*ʹ��CAN������*/
	pCanReg->CANCTL1.Bits.CANE   = 1u; 
	
	/*ѡ����ʱ��OscClk----modify by sunj 2019/1/4 14:54*/
	pCanReg->CANCTL1.Bits.CLKSRC = 0u; 

	/*�˳�����ģʽ*/
	pCanReg->CANCTL1.Bits.LISTEN = 0u; 
			
	/*bus-Off�Զ��ָ�*/
	pCanReg->CANCTL1.Bits.BORM   = 0u;

	/*����������������*/
	BaudRate  = Can_Cfg.pControllerCfg[ControllerCfgIndex].BaudRate;
	Can_ConfigBaudRate(BaseAddr,BaudRate);

	/*����ָ����������Ӧ�Ľ���CANID����*/
	ret = Can_SearchControllerFromRxObjectCfg(DevId,&HardRxObjectIndex);
	if(E_NOT_OK == ret)
	{
		/*�ÿ������޽�����������,Ĭ���˲���չ֡*/
		IdCfgType = CANID_EXTENDED;
	}
	else
	{
		IdCfgType = Can_Cfg.pHardwareObjectCfg[HardRxObjectIndex].CanIdType;		
	}
	/*�����������˲�����*/
	FilterNum = Can_Cfg.pControllerCfg[ControllerCfgIndex].NumOfControllerFilter;
	pFilterCfg= Can_Cfg.pControllerCfg[ControllerCfgIndex].pControllerFilterCfg; 
	if((0 == FilterNum)||(NULL_PTR == pFilterCfg))
	{
		/*�˲�����������Ϊ����,��������*/
	}
	else
	{
		/*�˲����Կ�������Ϊ����,��������*/			
		Can_ConfigFilter(BaseAddr,IdCfgType,FilterNum,pFilterCfg);
	}

	/*�˳���ʼ��ģʽ*/
	Can_ExitInitMode(BaseAddr);

    /**************************************
           ��������ģʽ��,����������
     **************************************/
	pCanReg->CANRIER.Bits.WUPIE = 0u; /*��ֹ�����ж�*/
	pCanReg->CANRIER.Bits.OVRIE = 1u; /*ʹ�ܹ��ش�����*/
	pCanReg->CANRIER.Bits.RXFIE = 1u; /*ʹ�ܽ��ջ������ж�*/
	pCanReg->CANRIER.Bits.CSCIE = 1u; /*ʹ��CAN״̬�ı��ж�*/
	pCanReg->CANRIER.MergedBits.grpRSTATE = 1u; /*��ӦBusOff*/
	pCanReg->CANRIER.MergedBits.grpTSTATE = 1u;	/*��ӦBusOff*/

	/***************************************/
	for(WaitTimes=0u;WaitTimes<50000u;WaitTimes++)
	{
		if(1u == pCanReg->CANCTL0.Bits.SYNCH)
		{
		    /*ͬ��������ɹ�*/
			break;
		}
	}
	if(50000u == WaitTimes)
	{
		/*CAN���ͬ����������*/
//#if(STD_ON == CAN_DEV_ERROR_DETECT)
//		Det_ReportError(MODULE_ID_CAN,
//						DevId,
//						CAN_INITCONTROLLER_ID,
//						CAN_E_SYNCH_ERROR);				
//#endif
	}
}


#endif


/************************************************************
* ��������:Can0_TansmitIsr_C
* ��������:Can0��������������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can0_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* ��������:Can0_ReceiveIsr_C
* ��������:Can0��������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can0_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* ��������:Can0_ErrorIsr_C
* ��������:Can0�����������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :���ش����жϻ�����busoff�ж�
*************************************************************/
void  Can0_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* ��������:Can1_TansmitIsr_C
* ��������:Can1��������������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can1_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* ��������:Can1_ReceiveIsr_C
* ��������:Can1��������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can1_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* ��������:Can1_ErrorIsr_C
* ��������:Can1�����������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :���ش����жϻ�����busoff�ж�
*************************************************************/
void  Can1_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* ��������:Can2_TansmitIsr_C
* ��������:Can2��������������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can2_TansmitIsr_C(void)
{
    Can_TansmitIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* ��������:Can2_ReceiveIsr_C
* ��������:Can2��������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can2_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* ��������:Can2_ErrorIsr_C
* ��������:Can2�����������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :���ش����жϻ�����busoff�ж�
*************************************************************/
void  Can2_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* ��������:Can3_TansmitIsr_C
* ��������:Can3��������������жϺ���
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can3_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* ��������:Can3_ReceiveIsr_C
* ��������:Can3��������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can3_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* ��������:Can3_ErrorIsr_C
* ��������:Can3�����������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :���ش����жϻ�����busoff�ж�
*************************************************************/
void  Can3_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* ��������:Can4_TansmitIsr_C
* ��������:Can4��������������жϺ���
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can4_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_4);
}

/************************************************************
* ��������:Can4_ReceiveIsr_C
* ��������:Can4��������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :
*************************************************************/
void  Can4_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_4);
}

/************************************************************
* ��������:Can4_ErrorIsr_C
* ��������:Can4�����������ж�
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ��ע	  :���ش����жϻ�����busoff�ж�
*************************************************************/
void  Can4_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_4);
}

