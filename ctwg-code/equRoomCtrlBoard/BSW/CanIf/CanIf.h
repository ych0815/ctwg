/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : CanIf.h
* ��������  : CanIfģ��ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            	New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CANIF_H_
#define  _CANIF_H_

#include "CanIf_Cfg.h"
#include "CanIf_CfgType.h"

/*******************************************
				�궨��
 ******************************************/
/*������*/
#define 	CANIF_E_UNINIT						(0x10u) /*ģ��δ��ʼ��*/
#define 	CANIF_E_PARAM_INVALID			    (0x11u) /*���������Ч*/
#define     CANIF_E_CONFIGPARAM_INVALID			(0x12u)	/*ģ�����ò�������*/
#define     CANIF_E_TRANSBUFF_FULL              (0x13u) /*���ͻ�����*/ 
#define     CANIF_E_RECEIVEBUFF_FULL            (0x14u) /*���ջ�����*/
#define     CANIF_E_CONTROLLER_BUSOFF           (0x15u) /*ָ���ķ��Ϳ�����״̬ΪBusOff*/

/* API Service ID's*/
#define 	CANIF_INIT_ID						(0x00u) /*CanIf_Init*/
#define 	CANIF_RXINDICATION_ID 			    (0x01u)	/*CanIf_RxIndication*/
#define 	CANIF_TRANSMIT_ID					(0x02u)	/*CanIf_Transmit*/
#define 	CANIF_RESET_TRANSMITQUENE_ID		(0x03u)	/*CanIf_ResetTransmitQueue*/
#define		CANIF_TRANSMITQUENE_ISEMPTY_ID		(0x04u) /*CanIf_TransmitQueueIsEmpty*/
#define     CANIF_GETNEXTPACKET_ID				(0x05u)	/*CanIf_GetNextPacket*/
#define     CANIF_MAINFUNCTION_ID				(0x06u)	/*CanIf_Mainfunction*/
#define     CANIF_TXCONFIRMHOOK_ID              (0x07u) /*CanIf_TxConfirmHook()*/
#define 	CANIF_RXINDICATIONHOOK_ID 			(0x08u)	/*CanIf_RxIndicationHook()*/
/**/
#define  	CAN_TXBUFFSIZE   					(64u) 	/*���������Ͷ��л��泤��*/
#define  	CAN_RXBUFFSIZE	  					(64u) 	/*���������ն��л��泤��*/
/*******************************************
				��̬������Դ����
 ******************************************/
extern   const  CanIf_CfgType  CanIf_Cfg;


/************************************************************
* ��������:CanIf_Init
* ��������:CanIfģ���ʼ��.
* �������:��
* �������:��
* ����/�������:��
* ��������: ��������
* ��ע	  :
*************************************************************/
extern  void  CanIf_Init(void);

/************************************************************
* ��������:CanIf_RxIndication
* ��������:֪ͨCanIfģ��,�豸��ΪDevId�Ŀ��������յ�����;
* �������:DevId  :CAN�������豸ID
		   PduInfo:���յ��ı�����Ϣ
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :�²�Can����ģ�����
*************************************************************/
extern  Std_ReturnType CanIf_RxIndication(uint8 DevId, const PduInfoType PduInfo);

/************************************************************
* ��������:CanIf_Transmit
* ��������:֪ͨDevIdָ��Can����������һ֡����;
* �������:DevId  :�豸ID��;
           PduInfo:�����ͱ���;
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :�ϲ�Comģ�����
*************************************************************/
extern  Std_ReturnType CanIf_Transmit(uint8 DevId,const PduInfoType PduInfo);

/************************************************************
* ��������:CanIf_ResetTransmitQueue
* ��������:֪ͨCanIfģ��,���DevIdָ���������ķ��Ͷ���;
* �������:DevId:
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :�²�Can����ģ�����
*************************************************************/
extern  void  CanIf_ResetTransmitQueue(uint8 DevId);

/************************************************************
* ��������:CanIf_TransmitQueueIsEmpty
* ��������:֪ͨCanIfģ��,DevIdָ���������ķ��Ͷ����Ѿ�Ϊ��;
* �������:DevId:
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :�²�Can����ģ�����
*************************************************************/
extern  void  CanIf_TransmitQueueIsEmpty(uint8 DevId);

/************************************************************
* ��������:CanIf_GetNextPacket
* ��������:֪ͨCanIfģ��,��DevIdָ����Can���������Ͷ�����,
		   ��ȡһ֡�����ͱ���;
* �������:DevId:
		  (*pPduInfo):
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :�²�Can����ģ�����
*************************************************************/
extern  Std_ReturnType CanIf_GetNextPacket(uint8 DevId,PduInfoType *pPduInfo);

/************************************************************
* ��������:CanIf_Mainfunction
* ��������:CanIfģ���ṩ�ĺ�̨��ѭ��
* �������:DevId  :�豸ID��;
           PduInfo:�����ͱ���;
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :���ڵ���
*************************************************************/
extern  void CanIf_Mainfunction(void); 

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
extern  Std_ReturnType CanIf_RxIndicationHook(uint8 DevId, const PduInfoType *pPduInfo);

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
extern  Std_ReturnType CanIf_TxConfirmHook(uint8 DevId);

#endif
