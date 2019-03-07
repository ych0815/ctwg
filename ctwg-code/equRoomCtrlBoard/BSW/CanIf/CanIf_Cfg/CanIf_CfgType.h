/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : CanIf_CfgType.h
* ��������  : CanIfģ���������Ͷ���ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CANIF_CFGTYPE_H_
#define  _CANIF_CFGTYPE_H_

/**************************************
              	ͷ�ļ�
 **************************************/
#include "CanIf_Cfg.h"

/**************************************
             	��̬�����������Ͷ���
 **************************************/
/*����������������������*/
typedef struct
{
	uint8  ControllerId;	/*ECU��(Ƭ��+����)������ID��*/
	uint8  ProtocolId;     	/*������֧�ֵ�Э��Id��*/
}CanIf_ControllerCfgType;

/*��������������������*/
typedef struct
{
	uint8  GroupId;		   /*������ID��*/
	const  CanIf_ControllerCfgType  *pController1;  /*���������������1*/  
	const  CanIf_ControllerCfgType  *pController2;  /*���������������2*/  
}CanIf_ControllerGroupCfgType;

typedef struct
{
	uint8  NumOfController;	/*ģ�����õĿ���������*/
	const  CanIf_ControllerCfgType *pControllerCfg;
	uint8  NumOfGroup;		/*ģ�����õ�����������*/
	const  CanIf_ControllerGroupCfgType *pGroupCfg;
}CanIf_CfgType;

#endif

