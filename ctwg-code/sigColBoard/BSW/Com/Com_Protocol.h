/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Com_Protocol.h
* ��������  : ͨѶģ��Э�����ͷ�ļ�(Com_Protocol.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_PROTOCOL_H_
#define  _COM_PROTOCOL_H_


/**************************************
              	ͷ�ļ�
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"
#include "os_cpu.h"
#include "TrainInOutCheck.h"
#include "MoniDataCol.h"

/**************************************
             	���Ͷ���
 **************************************/
typedef union
{
	uint32	ExtId;
	struct
	{
		uint8 FrameType :5; /*ID28~ID24:֡���� */
		uint8 Reserve0  :3; /*ID31~ID29:����   */
		uint8 DestAddr  :5; /*ID20~ID16:Ŀ�ĵ�ַ*/
		uint8 Reserve1  :3; /*ID23~ID21:����   */
		uint8 SourceAddr:5; /*ID12~ID8 :Դ��ַ */
		uint8 Reserve2  :3; /*ID15~ID13:����   */
		uint8 heatbeatCount:8; /*ID7~ID0  :��������,ȡֵ��Χ:0~255*/
	}bit;
}Com_ProtocolIdType;


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern boolean g_boardCAN_info[2];	  /*�忨CAN������Ϣ��TRUE��ʾCAN���� FALSE��ʾCAN����*/

#pragma DATA_SEG DEFAULT

/**************************************
             	�궨��
 **************************************/
/**************************FRAME TYPE**************************/ 
#define FRAME_TYPE_SIGCOLBOARD_COl            1   /*�źŲɼ���ɼ�����*/
#define	FRAME_TYPE_GPKZX_STATEMONI            4   /*���Կ�����״̬��ⱨ��*/
#define FRAME_TYPE_BOARD_INFO		          5	  /*�忨��Ϣ����*/ 

/**************************ADDR**************************/
#define ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD   1   /*�豸�����ذ��ַ*/
#define ADDR_SIGNAL_COLLECT_BOARD             2   /*�źŲɼ����ַ*/
#define ADDR_BOTTOM_MODULE_CTRL_BOARD         3   /*������ư��ַ*/
#define ADDR_SIDE_MODULE_CTRL_BOARD           4   /*������ư��ַ*/
#define ADDR_TOP_MODULE_CTRL_BOARD            5   /*�������ư��ַ*/
#define ADDR_BROADCAST                        31  /*�㲥��ַ*/

/**************************BOARD INFO**************************/
#define HARDWARE_MAIN_VERSION				  0	  /*Ӳ�����汾��*/
#define HARDWARE_MINOR_VERSION  			  1   /*Ӳ���ΰ汾��*/

#define SOFTWARE_MAIN_VERSION				  0	  /*������汾��*/
#define SOFTWARE_MINOR_VERSION  			  1   /*����ΰ汾��*/

/**************************************
             	��������
 **************************************/
extern	Std_ReturnType Com_ReceSysSynch(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBack(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtrl(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddle(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceInputArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBackArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddleArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtlArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceInputCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddleCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtrlCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBackCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitSysSynchInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitCanLinkStatusAtV4TrustInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitSigColBoradColMessage(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitBoardInfoMessage(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitGPKZXStateMoniMessage(const PduInfoType *pPduInfo);
#endif

