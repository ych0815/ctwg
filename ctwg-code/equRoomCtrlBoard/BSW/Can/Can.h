/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Can.h
* ��������  : 9s12xep100-Can����ͷ�ļ�(Can.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CAN_H_
#define  _CAN_H_

/**************************************
              	ͷ�ļ�
 **************************************/
#include "Can_Cfg.h"
#include "Can_CfgType.h"
#include "Can_Register.h"

/**************************************
             		�궨��
 **************************************/
/*������*/
#define 	CAN_E_UNINIT						(0x10u) /*ģ��δ��ʼ��*/
#define 	CAN_E_PARAM_INVALID			    	(0x11u) /*���������Ч*/
#define     CAN_E_CONFIGPARAM_INVALID			(0x12u)	/*ģ�����ò�������*/
#define     CAN_E_ENTER_INITMODE_INVALID        (0x13u) /*�����������ʼ��ģʽʧ��*/
#define     CAN_E_EXIT_INITMODE_INVALID         (0x14u) /*�������˳���ʼ��ģʽʧ��*/
#define     CAN_E_SYNCH_ERROR					(0x15u) /*CAN���ͬ����������ʧ��*/
#define     CAN_E_ENTER_SLEEPMODE_INVALID       (0x16u) /*����������˯��ģʽʧ��*/

/* API Service ID's*/
#define 	CAN_INIT_ID							(0x00u) /*Can_Init*/
#define 	CAN_ENABLE_TXINTERRUPT_ID			(0x02u)	/*Can_EnableTxInterrupt*/
#define 	CAN_DISABLE_TXINTERRUPT_ID			(0x03u)	/*Can_DisableTxInterrupt*/
#define		CAN_ENTERSTOP_ID					(0x04u) /*Can_EnterStopMode*/
#define     CAN_CALCBASEADDRBYCONTROLLERID_ID   (0x05u) /*Can_CalcBaseAddrByControllerId*/
#define     CAN_ENTER_INITMODE                  (0x06u) /*Can_EnterInitMode*/
#define     CAN_EXIT_INITMODE                   (0x07u) /*Can_ExitInitMode*/
#define 	CAN_REQUESTMESSAGEABORT_ID			(0x08u) /*Can_RequestTransmitterMessageAbort()*/
#define     CAN_GETCONTROLLERSTATUS_ID			(0x09u) /*Can_GetControllerStatus()*/
/**********************/
#define     CAN_REQUEST_CONFIRM_TIMES 		(1000u)   /*��������ʼ��(˯��)ģʽ,ȷ�����ѭ������*/

/*******************************************
				��̬������Դ����
 ******************************************/
extern  const  Can_CfgType  Can_Cfg;


/************************************************************
* ��������:Can_Init
* ��������:Can����ģ���ʼ��,�ú�����Ҫ��ģ�龲̬���õ����п�������ʼ��.
* �������:��
* �������:��
* ����/�������:��
* ��������: ��������
* ��ע	  :
*************************************************************/
extern  void  Can_Init(void);

/************************************************************
* ��������:Can_InitController
* ��������:��ʼ��ָ��������
* �������:DevId:Can�������豸ID��;
* �������:��
* ����/�������:��
* ��������: ��������
* ��ע	  :
*************************************************************/
//extern  void  Can_InitController(uint8 DevId);

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
extern  void  Can_Write(uint8  DevId,PduInfoType PduInfo);

/************************************************************
* ��������:Can_EnableTxInterrupt
* ��������:ʹ��DevIdָ��Can�����������ж�;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
extern  void  Can_EnableTxInterrupt(uint8  DevId);

/************************************************************
* ��������:Can_DisableTxInterrupt
* ��������:��ֹDevIdָ��Can�����������ж�;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
extern  void  Can_DisableTxInterrupt(uint8  DevId);

/************************************************************
* ��������:Can_RequestTransmitterMessageAbort
* ��������:������ָֹ��������Ӳ��Buffer�е�Pending����;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
extern  void  Can_RequestTransmitterMessageAbort(uint8  DevId);

/************************************************************
* ��������:Can_EnterStopMode
* ��������:ֹͣDevIdָ��Can����������;
* �������:DevId:Can�������豸ID��;
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
//extern  void  Can_EnterStopMode(uint8  DevId);

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
extern  void  Can_GetControllerStatus(uint8  DevId,uint8 *pCanStatus);

#endif
































