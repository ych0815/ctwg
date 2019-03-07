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
const Com_IPduCfgType   Com_Protocol1_IpduCfg[3] = 
{
	{COM_SIGCOLBOARD_COl     ,COM_TRANSMIT,COM_MIXED ,  50ul,Com_TransmitSigColBoradColMessage}, 	/*�źŲɼ���ɼ�����*/
	{COM_BOARD_INFO          ,COM_TRANSMIT,COM_PERIOD , 500ul,Com_TransmitBoardInfoMessage}, 		/*�忨��Ϣ����*/
	{COM_GPKZX_STATEMONI     ,COM_TRANSMIT,COM_PERIOD , 500ul,Com_TransmitGPKZXStateMoniMessage}	/*���Կ�����״̬��ⱨ��*/
};

/*******************/
const  Com_SingleProtocoCfgType  Com_ProtocolCfg[1] = 
{
 	{
		0u,   						/* Э��ID��  */
 		3u,   						/* Э�����õ�Pdu����(����+����)*/
 		&Com_Protocol1_IpduCfg[0]  	/* Э�����IPdu�����׵�ַ*/
	}
};

/*******************/
const  Com_ProtocoCfgType   Com_Cfg = 
{
	1u,								/*ģ��֧�ֵ�Э�����*/
	&Com_ProtocolCfg[0],			/*ģ��֧�ֵ�Э������*/
};









