/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com_CfgType.h
* 功能描述  : 通讯模块配置类型定义头文件(Com_CfgType.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            		New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_CFGTYPE_H_
#define  _COM_CFGTYPE_H_

#include "Com_Cfg.h"
/**************************************
           静态配置类型定义
 **************************************/
typedef  enum
{
	COM_RECEIVE  = 0u,     
	COM_TRANSMIT = 1u 
}Com_DirectionType;

typedef  enum
{
	COM_INVALID = 0u,
	COM_TRIGER  = 1u,  /*触发发送*/
	COM_PERIOD  = 2u,  /*周期发送*/
	COM_MIXED   = 3u   /*触发+周期发送*/
}Com_TransmitModeType;

typedef  Std_ReturnType function(const PduInfoType *pPduInfo);
typedef  struct
{
    uint32	IPduId;     		 /* 报文ID(只含帧类型字段) 	*/
    Com_DirectionType  Direction;/* 传输方向(接收/发送) 	*/
    Com_TransmitModeType TxMode; /* 发送方式(周期/触发/混合)*/
    uint32  PeriodTimes;		 /* 周期发送时间(单位:tick) */ 
	function *pFunctionName;	 /* 报文回调函数			*/
}Com_IPduCfgType;

/****************************/
/*单个协议的配置*/
typedef  struct
{
    uint8  protocolId;    	/*具体协议ID号 				*/
    uint8  NumOfIPdu;     	/*具体协议包括的报文个数(接收+发送)*/
    const  Com_IPduCfgType  *pIPduCfg; /*指向协议报文配置首地址	*/
}Com_SingleProtocoCfgType;

/****************************/
/*模块支持协议配置*/
typedef  struct
{
	uint8  NumOfProtocol;  		/*模块支持的协议个数*/
	const  Com_SingleProtocoCfgType *pProtocoCfg; /*模块支持的协议配置*/
}Com_ProtocoCfgType;

#endif

