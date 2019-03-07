/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : CanIf_Cfg.c
* ��������  : CanIfģ������Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            			 New
**------------------------------------------------------------------------------------------------*/
#include "CanIf_Cfg.h"
#include "CanIf_CfgType.h"

const  CanIf_ControllerCfgType CanIf_ControllerCfg[2]= 
{
	{CAN_CONTROLLER_0, 0u}, /*ControllerId,ProtocolId*/
	{CAN_CONTROLLER_1, 0u}
};

/*�����������ñ�����ComMģ��������һ��(GroupId��ControllerId)*/
const  CanIf_ControllerGroupCfgType	CanIf_ControllerGroupCfg[1] = 
{
	{
		0u,						 /*GroupId*/ 			
	 	&CanIf_ControllerCfg[0], /*pController1*/
	 	&CanIf_ControllerCfg[1]  /*pController2*/
	} 
};

const  CanIf_CfgType  CanIf_Cfg = 
{
	2u,						 /*ģ�����õĿ���������*/
	&CanIf_ControllerCfg[0],
	1u,						 /*ģ�����õ�����������*/
	&CanIf_ControllerGroupCfg[0]
};





