/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : ComM.h
* ��������  : ͨѶ����ģ��ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COMM_H_
#define  _COMM_H_

/**************************************
              	ͷ�ļ�
 **************************************/
#include "ComM_Cfg.h"
#include "ComM_CfgType.h"

/*******************************************
				�궨��
 ******************************************/
/*������*/
#define 	COMM_E_UNINIT						(0x10u) /*ģ��δ��ʼ��*/
#define 	COMM_E_PARAM_INVALID			    (0x11u) /*���������Ч*/
#define     COMM_E_CONFIGPARAM_INVALID			(0x12u)	/*ģ�����ò�������*/

/* API Service ID's*/
#define 	COMM_INIT_ID						(0x00u) /*ComM_Init*/
#define 	COMM_RXINDICATION_ID 			    (0x01u)	/*ComM_RxIndication*/
#define 	COMM_BUSOFFINDICATION_ID			(0x02u)	/*ComM_BusOffIndication*/
#define 	COMM_GETTRUSTINFO_ID				(0x03u)	/*ComM_GetTrustInfo*/
#define		COMM_GETCONTROLLERSTATUS_ID		    (0x04u) /*ComM_GetControllerStatus*/
#define     COMM_MAINFUNCTION_ID				(0x05u)	/*ComM_Mainfunction*/
#define 	COMM_INITGROUP_ID					(0x06u) /*ComM_InitGroup*/
#define     COMM_GETCONTROLLERCOMMSTATUS_ID     (0x07u) /*ComM_GetControllerCommStatus*/
/*******************************************
				��̬������Դ����
 ******************************************/
extern   const ComM_CfgType   ComM_Cfg;

/************************************************************
* ��������:ComM_Init
* ��������:ComMģ���ʼ��
* �������:��
* �������:��
* ����/�������:��
* ��������:��������
* ��ע	  :
*************************************************************/
extern  void ComM_Init(void);

/************************************************************
* ��������:ComM_RxIndication
* ��������:֪ͨComMģ��,�豸��=DevId��CAN���������յ�����
* �������:DevId:
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
extern  Std_ReturnType ComM_RxIndication(uint8 DevId);


/************************************************************
* ��������:ComM_BusOffIndication
* ��������:֪ͨComMģ��,�豸��=DevId��CAN����������BusOff.
* �������:DevId:
* �������:
* ����/�������:
* ��������:
* ��ע	  :
*************************************************************/
extern  Std_ReturnType ComM_BusOffIndication(uint8 DevId);


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
extern  Std_ReturnType ComM_GetTrustInfo(uint8 GroupId,uint8 *pTrustInfo);


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
extern  Std_ReturnType ComM_GetControllerStatus(uint8 DevId,uint8 *pControllerStatus);

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
extern  Std_ReturnType ComM_GetControllerCommStatus(uint8 DevId,uint8 *pCommStatus);

/************************************************************
* ��������:ComM_MainFunction
* ��������:ComMģ���̨��ѭ��.
* �������: DevId:Can������ID��;
* �������:(*pControllerStatus):Can������״̬��Ϣ;
* ����/�������:
* ��������:
* ��ע	  :�ú�����Ҫ�����ڵ���
*************************************************************/
extern  void ComM_MainFunction(void);


#endif

