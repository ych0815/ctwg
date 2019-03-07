/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���   : Com_Cfg.h
* �������� : ͨѶģ������ͷ�ļ�(Com_Cfg.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_CFG_H_
#define  _COM_CFG_H_

/**************************************
              	ͷ�ļ�
 **************************************/
#include "Std_Types.h"
#include "Modules.h"

/**************************************
             	�궨��
 **************************************/
#define   COM_DEV_ERROR_DETECT   	(STD_ON)    	/*����ʱ������*/

#define   COM_MAX_PROTOCOLNUM   	(1u)        	/*ģ��֧�ֵ�Э�����,�ò������ܱ����ò���NumOfProtocolС,������>=NumOfProtocol*/
#define   COM_MAX_IPDUNUM 			(14u)        	/*ģ��֧�ֵ�Э����,����Э��֧�ֵ����������(����+����),�ò������ܱ����ò���NumOfIPduֵС,������>=NumOfIPdu*/      

/*************/
/*Э������������Ͷ���*/
#define   COM_SYS_SYNCH             (0x03000000ul)  /*ϵͳͬ��ʱ�ӱ���*/ 

#define   COM_FEEDBACK				(0x06000000ul)	/*�������״̬����*/
#define   COM_MIDDLE				(0x07000000ul)  /*�߼������м��������*/
#define   COM_OUTCTL                (0x08000000ul)  /*�߼�����������Ʊ���*/

#define   COM_MIDDLE_ARBITRATION    (0x04000000ul)  /*�߼������м�����ٲñ���*/
#define   COM_OUTCTL_ARBITRATION	(0x05000000ul)  /*�߼�������������ٲñ���*/
#define   COM_FEEDBACK_ARBITRATION  (0x09000000ul)  /*�������״̬�ٲñ���*/
#define   COM_INPUT_ARBITRATION  	(0x0A000000ul)  /*������Ϣ�ٲñ���*/

#define   COM_INPUT_CASCADE			(0x0B000000ul)  /*�������������ٲñ���*/
#define   COM_MIDDLE_CASCADE		(0x0C000000ul)  /*���������м�����ٲñ���*/
#define   COM_OUTCTRL_CASCADE		(0x0D000000ul)  /*����������������ٲñ���*/
#define   COM_FEEDBACK_CASCADE		(0x0E000000ul)  /*����������������ٲñ���*/

/*************/
#define   COM_CAN_LINKCHECK         (0x14000000ul)  /*CAN��·��ⱨ��*/
#define   COM_CAN_LINKSTATUS        (0x15000000ul)  /*CAN��·״̬������*/     



/**********************************************************************
 * �豸�����ذ�
 * ********************************************************************/
#define   COM_SIGCOLBOARD_COl			(0x01000000ul)	/*�źŲɼ���ɼ�����*/
#define   COM_EQUROOM_CTRLBOARD_CTRL	(0x02000000ul)	/*�豸����������Ʊ���*/
#define	  COM_COL_MODULE_STA			(0x03000000ul)	/*�ɼ�ģ��״̬����*/
#define	  COM_GPKZX_STATEMONI       	(0x04000000ul)  /*���Կ�����״̬��ⱨ��*/
#define   COM_BOARD_INFO				(0x05000000ul)  /*�忨��Ϣ����*/


#endif
