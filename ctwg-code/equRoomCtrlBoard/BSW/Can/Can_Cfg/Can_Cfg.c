/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Can_Cfg.c
* ��������  : 9s12xep100-Can��������Դ�ļ�(Can_Cfg.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New

˵��:
1)Ŀǰ�汾��ģ���߼�:��֧��2��32λ��Filter: bitX=1:����;bitX=0:�Ƚ�;
  ��չ֡:����Bit28~bit0��Ч;
  ��׼֡:����Bit10~bit0��Ч;
2)Ŀǰ�汾ֻ֧�����õ�������Ӳ������,���������еķ��ͱ��ľ�ͨ���÷���Ӳ�����淢��;
3)Ŀǰ�汾��������û�����ý�������,��Ĭ�Ͽ�����������չ֡;
          ��������û�����÷�������,��Ĭ�Ͽ�����������չ֡;
**------------------------------------------------------------------------------------------------*/
#include "Can_Cfg.h"
#include "Can_CfgType.h"

/*****************************************
(received id��FilterAcceptId,��ͨ��FilterMaskId������˲�����
(bitX=0:��Ӧλ�Ƚ�;bitX=1:��Ӧλ����),����� )
 *****************************************/
const Can_FilterCfgType  Can_FilterIdCfg[2] = 
{
	{
		0xFFFFFFFF,  /*FilterMaskId  (���Ƚ�)*/
		0x400   	 /*FilterAcceptId		 */
	},
	{
		0xFFFFFFFF,	 /*FilterMaskId  (���Ƚ�)*/
		0x08000000	 /*FilterAcceptId        */
	}		
};

const Can_ControllerCfgType Can_ControllerCfg[2] = 
{
	{
		CAN_CONTROLLER_0,	/*ControllerId*/
		CAN_BPS_100K,	 	/*BaudRate*/
		NULL_PTR,         	/*pInterruptCfg*/
		2u,					/*NumOfControllerFilter*/		
		&Can_FilterIdCfg[0] /*pControllerFilterCfg*/
	},
	{
		CAN_CONTROLLER_1,
		CAN_BPS_100K,
		NULL_PTR,
		2u,
		&Can_FilterIdCfg[0]
	}
};

const Can_HardwareObjectCfgType  Can_HardwareObjectCfg[4] = 
{
	{
		0x00ul,					/*CanId*/
		0,						/*CanObjectId*/
		CANID_EXTENDED, 		/*CanIdType*/
		CANID_RECEIVE,			/*CanObjectTrans*/
		NULL_PTR,				/*pFilterMaskRef*/
		&Can_ControllerCfg[0] 	/*pCanControlRef*/
	},
	{
		0x1000,				 	/*��������ֵ�Է�����Ӱ��*/
		3,					 	/*��������ֵ�Է�����Ӱ��*/	
		CANID_EXTENDED,	
		CANID_TRANSMIT,	
		NULL_PTR,			 	/*��������ֵ�Է�����Ӱ��*/
		&Can_ControllerCfg[0]
	},
	/**********************/
	{
		0x00ul,					/*CanId*/
		0,						/*CanObjectId*/
		CANID_EXTENDED, 		/*CanIdType*/
		CANID_RECEIVE,			/*CanObjectTrans*/
		NULL_PTR,				/*pFilterMaskRef*/
		&Can_ControllerCfg[1] 	/*pCanControlRef*/
	},
	{
		0x1000,				 	/*��������ֵ�Է�����Ӱ��*/
		3,					 	/*��������ֵ�Է�����Ӱ��*/		
		CANID_EXTENDED,	
		CANID_TRANSMIT,	
		NULL_PTR,			 	/*��������ֵ�Է�����Ӱ��*/
		&Can_ControllerCfg[1]
	}
};

const  Can_CfgType  Can_Cfg= 
{
	2u,							/*NumOfController*/
	&Can_ControllerCfg[0],		/*pControllerCfg*/
	4u,							/*NumOfMailBox*/
	&Can_HardwareObjectCfg[0]  	/*pHardwareObjectCfg*/
};

