/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com_Cfg.c
* 功能描述  : 通讯模块配置源文件(Com_Cfg.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
/**************************************
              	头文件
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"
#include "Com_Protocol.h"

/************************************/
/*协议1接收/发送报文配置*/
const Com_IPduCfgType   Com_Protocol1_IpduCfg[6] = 
{
	{COM_SIGCOLBOARD_COl	 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceSigColBoardCol		 },/*信号采集板采集报文*/
	{COM_COL_MODULE_STA		 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceColModuleSta		 },/*采集模块状态报文*/
	{COM_GPKZX_STATEMONI	 ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceGPKZXStaMoni		 },/*轨旁控制箱状态监测报文*/
	{COM_BOARD_INFO		     ,COM_RECEIVE ,COM_INVALID, 0ul ,Com_ReceBoardInfo			 },/*板卡信息报文*/
    
	{COM_EQUROOM_CTRLBOARD_CTRL,COM_TRANSMIT,COM_PERIOD, 3ul,Com_TransmitEquRoomCtrlBoardCtrlInfo    }, /*系统同步时钟报文*/
    {COM_BOARD_INFO		       ,COM_TRANSMIT,COM_PERIOD, 9ul,Com_TransmitBoardInfo}, /*板卡双CAN链路状态共享报文*/
};

/*******************/
const  Com_SingleProtocoCfgType  Com_ProtocolCfg[1] = 
{
 	{
		0u,   						/* 协议ID号  */
 		6u,   						/* 协议配置的Pdu个数(接收+发送)*/
 		&Com_Protocol1_IpduCfg[0]  	/* 协议包含IPdu配置首地址*/
	}
};

/*******************/
const  Com_ProtocoCfgType   Com_Cfg = 
{
	1u,								/*模块支持的协议个数*/
	&Com_ProtocolCfg[0],			/*模块支持的协议配置*/
};









