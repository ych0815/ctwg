/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com_Protocol.c
* 功能描述  : 通讯模块:协议报文分析/组装源文件(Com_Protocol.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "Com_Protocol.h"
#include "CanIf.h"
#include "Osal.h"
#include "drv_sci.h"
#include "ComM.h"	/*Added by chenms 2018-5-17 18:12*/
#include "Com.h"    /*Added by sunj 2018/01/02 13:20*/
#include "MeaVel.h"

/*added by chenms 2018-11-10 20:48 */
extern  void  App_GetMainFunctionSoftVersion(uint8 *pVersion);



#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
boolean g_boardCAN_info[2];	  /*板卡CAN1故障信息，TRUE表示CAN故障 FALSE表示CAN正常*/

#pragma DATA_SEG DEFAULT

/*************************************************************
                        接收报文解析函数
 ************************************************************/



/*************************************************************
                        发送报文解析函数
 ************************************************************/

#if 1
/************************************************************
* 函数名称:	Com_TransmitSigColBoradColMessage
* 函数描述: 组装信号采集板采集报文并发送。
* 输入参数:	无;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_TransmitSigColBoradColMessage(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;
	static uint8 cnt = 0;
	PduInfoType PduInfo;
	
	memset(PduInfo.PduData,0x00,8);

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}

	/***************************/
	Com_Id.ExtId = 0;
	Com_Id.bit.FrameType        = FRAME_TYPE_SIGCOLBOARD_COl;
	Com_Id.bit.DestAddr         = ADDR_BROADCAST;
	Com_Id.bit.SourceAddr       = ADDR_SIGNAL_COLLECT_BOARD;
	Com_Id.bit.heatbeatCount    = cnt;
	cnt++;

	PduInfo.PduId               = Com_Id.ExtId;
	PduInfo.PduLength           = 8u;
	Com_bit2Byte(&PduInfo.PduData[0],2,7,g_trainInOut_info);

	if(g_trainVeal_info.value > 0)
	{
		Com_bit2Byte(&PduInfo.PduData[0],2,7,FALSE);//线阵相机触发
	}
	else
	{
		Com_bit2Byte(&PduInfo.PduData[0],2,7,TRUE);//线阵相机不触发
	}

	Com_bit2Byte(&PduInfo.PduData[0],2,3,g_meavel_info[0].errState);
	Com_bit2Byte(&PduInfo.PduData[0],2,3,g_meavel_info[1].errState);
	
	if(g_trainVeal_info.value > 0)
	{
		PduInfo.PduData[1] = (uint8)(((g_trainVeal_info.value * 100u) >> 8) & 0xFF);
		PduInfo.PduData[2] = (uint8)((g_trainVeal_info.value * 100u) & 0xFF);		
	}

	CanIf_Transmit(CAN_CONTROLLER_0,PduInfo);
    CanIf_Transmit(CAN_CONTROLLER_1,PduInfo);    /*发送*/

#if 0    
    Drv_Sci_Write("\r\ng_trainInOut_info:",0,0);
	Drv_Sci_WriteCharAscii(g_trainInOut_info);
#endif

	return(E_OK);
}

/************************************************************
* 函数名称:	Com_TransmitSigColBoradColMessage
* 函数描述: 组装板卡信息报文并发送。
* 输入参数:	无;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_TransmitBoardInfoMessage(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;
	static uint8 cnt = 0;
	PduInfoType PduInfo;
	
	memset(PduInfo.PduData,0x00,8);

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}

	/***************************/
	Com_Id.ExtId = 0;
	Com_Id.bit.FrameType        = FRAME_TYPE_BOARD_INFO;
	Com_Id.bit.DestAddr         = ADDR_BROADCAST;
	Com_Id.bit.SourceAddr       = ADDR_SIGNAL_COLLECT_BOARD;
	Com_Id.bit.heatbeatCount    = cnt;
	

	PduInfo.PduId               = Com_Id.ExtId;
	PduInfo.PduLength           = 8u;
	PduInfo.PduData[0]			= cnt;						/*生命信号*/
	PduInfo.PduData[1]			= HARDWARE_MAIN_VERSION;	/*硬件主版本号*/
	PduInfo.PduData[2]			= HARDWARE_MINOR_VERSION;	/*硬件次版本号*/
	PduInfo.PduData[3]			= SOFTWARE_MAIN_VERSION;	/*软件主版本号*/
	PduInfo.PduData[4]			= SOFTWARE_MINOR_VERSION;	/*软件次版本号*/
	Com_bit2Byte(&PduInfo.PduData[5],2,7,g_boardCAN_info[0]);
	Com_bit2Byte(&PduInfo.PduData[5],2,5,g_boardCAN_info[1]);

	CanIf_Transmit(CAN_CONTROLLER_0,PduInfo);
    CanIf_Transmit(CAN_CONTROLLER_1,PduInfo);    /*发送*/

    cnt++;

	return(E_OK);
}

/************************************************************
* 函数名称:	Com_TransmitGPKZXMoniMessage
* 函数描述: 组装轨旁控制箱状态监测报文并发送。
* 输入参数:	无;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_TransmitGPKZXStateMoniMessage(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;
	static uint8 cnt = 0;
	PduInfoType PduInfo;
	
	memset(PduInfo.PduData,0x00,8);

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}

	/***************************/
	Com_Id.ExtId = 0;
	Com_Id.bit.FrameType        = FRAME_TYPE_GPKZX_STATEMONI;
	Com_Id.bit.DestAddr         = ADDR_BROADCAST;
	Com_Id.bit.SourceAddr       = ADDR_SIGNAL_COLLECT_BOARD;
	Com_Id.bit.heatbeatCount    = cnt;
	cnt++;

	PduInfo.PduId               = Com_Id.ExtId;
	PduInfo.PduLength           = 8u;
	
	Com_bit2Byte(&PduInfo.PduData[0],2,7,!g_fanOpenSta_info);
	Com_bit2Byte(&PduInfo.PduData[1],2,5,g_tempErrSta_info);
	//Com_bit2Byte(&PduInfo.PduData[0],2,5,g_DC5VErrSta_info);
	Com_bit2Byte(&PduInfo.PduData[0],2,3,g_DC12VErrSta_info);
    Com_bit2Byte(&PduInfo.PduData[0],2,1,g_DC24VErrSta_info);
	
	
	PduInfo.PduData[1]			= g_temp_info;	                /*环境温度*/

	CanIf_Transmit(CAN_CONTROLLER_0,PduInfo);
    CanIf_Transmit(CAN_CONTROLLER_1,PduInfo);    /*发送*/

	return(E_OK);
}


#endif

