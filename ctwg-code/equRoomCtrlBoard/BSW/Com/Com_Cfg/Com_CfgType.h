/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Com_CfgType.h
* ��������  : ͨѶģ���������Ͷ���ͷ�ļ�(Com_CfgType.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            		New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_CFGTYPE_H_
#define  _COM_CFGTYPE_H_

#include "Com_Cfg.h"
/**************************************
           ��̬�������Ͷ���
 **************************************/
typedef  enum
{
	COM_RECEIVE  = 0u,     
	COM_TRANSMIT = 1u 
}Com_DirectionType;

typedef  enum
{
	COM_INVALID = 0u,
	COM_TRIGER  = 1u,  /*��������*/
	COM_PERIOD  = 2u,  /*���ڷ���*/
	COM_MIXED   = 3u   /*����+���ڷ���*/
}Com_TransmitModeType;

typedef  Std_ReturnType function(const PduInfoType *pPduInfo);
typedef  struct
{
    uint32	IPduId;     		 /* ����ID(ֻ��֡�����ֶ�) 	*/
    Com_DirectionType  Direction;/* ���䷽��(����/����) 	*/
    Com_TransmitModeType TxMode; /* ���ͷ�ʽ(����/����/���)*/
    uint32  PeriodTimes;		 /* ���ڷ���ʱ��(��λ:tick) */ 
	function *pFunctionName;	 /* ���Ļص�����			*/
}Com_IPduCfgType;

/****************************/
/*����Э�������*/
typedef  struct
{
    uint8  protocolId;    	/*����Э��ID�� 				*/
    uint8  NumOfIPdu;     	/*����Э������ı��ĸ���(����+����)*/
    const  Com_IPduCfgType  *pIPduCfg; /*ָ��Э�鱨�������׵�ַ	*/
}Com_SingleProtocoCfgType;

/****************************/
/*ģ��֧��Э������*/
typedef  struct
{
	uint8  NumOfProtocol;  		/*ģ��֧�ֵ�Э�����*/
	const  Com_SingleProtocoCfgType *pProtocoCfg; /*ģ��֧�ֵ�Э������*/
}Com_ProtocoCfgType;

#endif

