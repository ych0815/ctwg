/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Com_Cfg.c
* ��������  : ͨѶģ������Դ�ļ�(Com_Cfg.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
/**************************************
              	ͷ�ļ�
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"
#include "Com_Protocol.h"

/************************************/
/*Э��1����/���ͱ�������*/
const Com_IPduCfgType   Com_Protocol1_IpduCfg[6] = 
{
	{COM_SIGCOLBOARD_COl	 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceSigColBoardCol		 },/*�źŲɼ���ɼ�����*/
	{COM_COL_MODULE_STA		 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceColModuleSta		 },/*�ɼ�ģ��״̬����*/
	{COM_GPKZX_STATEMONI	 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceGPKZXStaMoni		 },/*���Կ�����״̬��ⱨ��*/
	{COM_BOARD_INFO		     ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceBoardInfo			 },/*�忨��Ϣ����*/
    
	{COM_EQUROOM_CTRLBOARD_CTRL,COM_TRANSMIT,COM_PERIOD, 3ul,Com_TransmitEquRoomCtrlBoardCtrlInfo    }, /*ϵͳͬ��ʱ�ӱ���*/
    {COM_BOARD_INFO		       ,COM_TRANSMIT,COM_PERIOD, 9ul,Com_TransmitBoardInfo}, /*�忨˫CAN��·״̬������*/
};

/*******************/
const  Com_SingleProtocoCfgType  Com_ProtocolCfg[1] = 
{
 	{
		0u,   						/* Э��ID��  */
 		6u,   						/* Э�����õ�Pdu����(����+����)*/
 		&Com_Protocol1_IpduCfg[0]  	/* Э�����IPdu�����׵�ַ*/
	}
};

/*******************/
const  Com_ProtocoCfgType   Com_Cfg = 
{
	1u,								/*ģ��֧�ֵ�Э�����*/
	&Com_ProtocolCfg[0],			/*ģ��֧�ֵ�Э������*/
};









