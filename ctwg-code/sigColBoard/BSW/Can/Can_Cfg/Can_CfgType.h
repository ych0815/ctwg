/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Can_CfgType.h
* ��������  : 9s12xep100-Can�����������Ͷ���ͷ�ļ�(Can_CfgType.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            			 New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CAN_CFGTYPE_H_
#define  _CAN_CFGTYPE_H_

/**************************************
              	ͷ�ļ�
 *************************************/
#include "Can_Cfg.h"

/**************************************
		�����˲����Ͷ���
 *************************************/
typedef struct
{
	uint32  FilterMaskId;   /*�˲�����Id*/
	uint32  FilterAcceptId; /*�˲�����Id*/
}Can_FilterCfgType;

/**************************************
		�������������Ͷ���
 *************************************/
/*CAN������֧�ֵĲ�����*/
typedef enum
{
	CAN_BPS_100K  = 0u,		/*BPS=100K*/
	CAN_BPS_125K  = 1u,		/*BPS=125K*/
	CAN_BPS_250K  = 2u,		/*BPS=250K*/
	CAN_BPS_500K  = 3u,		/*BPS=500K*/
	CAN_BPS_1000K = 4u 		/*BPS=1000K*/
}Can_ControllerBpsType;

/*CAN�������ж���������*/
typedef void (*pIntFunction)(void);
typedef struct
{
	uint8  	IntPriority; 				 /*�ж����ȼ�*/
	pIntFunction InterruptCallback; 	 /*�жϻص�����*/
}Can_ControllerIntType;

typedef struct
{
	uint8  ControllerId;  				 /*Ƭ�ڿ�����ID��*/
	Can_ControllerBpsType BaudRate;		 /*������������*/
	const  Can_ControllerIntType *pInterruptCfg;/*�������ж��������*/
	uint8   NumOfControllerFilter;		 /*�������˲���������*/
	const  Can_FilterCfgType 	 *pControllerFilterCfg;/*ָ��������˲�����*/
}Can_ControllerCfgType;

/************************************
		����������������������
 ************************************/
typedef enum
{
	CANID_STANDARD = 0u, /*��׼֡*/
	CANID_EXTENDED = 1u  /*��չ֡*/
}Can_IdType;

typedef enum 
{
	CANID_RECEIVE  = 0u, /*����*/	
	CANID_TRANSMIT = 1u	 /*����*/
}Can_ObjectType;

typedef struct
{
	uint32  CanId;		  /*Can Idֵ:��������ֵ�Է�����Ӱ��*/
	uint8   CanObjectId;  /*Ӳ������ID��(0~[������֧�����ֵ-1)],��������ֵ�Է�����Ӱ��*/
	Can_IdType 	CanIdType;/*CanId����(��׼/��չ)*/
	Can_ObjectType  	  CanObjectTrans;   /*���䷽��*/
	const  Can_FilterCfgType     *pFilterMaskRef; 	/*�����˲�����,��������ֵ�Է�����Ӱ��*/
	const  Can_ControllerCfgType *pCanControlRef; 	/*�����������CAN������*/
}Can_HardwareObjectCfgType;

/************************************
		ģ�龲̬��������
 ************************************/
typedef  struct
{
	uint8  NumOfController; 			/*ģ��֧�ֵĿ���������*/
	const  Can_ControllerCfgType     *pControllerCfg;
	uint8  NumOfHardwareObject;     	/*ģ��֧�ֵ��������*/ 
	const  Can_HardwareObjectCfgType *pHardwareObjectCfg;
}Can_CfgType;

#endif

