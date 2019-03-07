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
#include "GateWay.h"

/*added by chenms 2018-11-10 20:48 */
extern  void  App_GetMainFunctionSoftVersion(uint8 *pVersion);
/*************************************************************
                        接收报文解析函数
 ************************************************************/
/************************************************************
* 函数名称:	Com_ReceSigColBoardCol
* 函数描述: 解析信号采集板采集报文
* 输入参数:	(*pPduInfo):接收报文内容;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_ReceSigColBoardCol(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}
	/***************************/
	Com_Id.ExtId = pPduInfo->PduId;

	if(Com_Id.bit.SourceAddr == ADDR_SIGNAL_COLLECT_BOARD)
	{
		// g_trainInOut_info = pPduInfo->PduData[0]>>6;
		// g_xzCamTri_info = (pPduInfo->PduData[0]&0x30)>>4;
		// g_meavelerrState_info[0] = (pPduInfo->PduData[0]&0x0C)>>2;
		// g_meavelerrState_info[0] = pPduInfo->PduData[0]&0x03;
		fun_stru1.Byte.val = pPduInfo->PduData[0];

		g_trainSpeed_info = ((uint16)pPduInfo->PduData[1]<<8)|(uint16)pPduInfo->PduData[2];
		g_osTime_info = ((uint32)pPduInfo->PduData[3]<<24)|((uint32)pPduInfo->PduData[4]<<16)|((uint32)pPduInfo->PduData[5]<<8)|(uint32)pPduInfo->PduData[6];
	}


	return(E_OK);
}

/************************************************************
* 函数名称:	Com_ReceColModuleSta
* 函数描述: 解析采集模块状态报文
* 输入参数:	(*pPduInfo):接收报文内容;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_ReceColModuleSta(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;
	uint8 tmp = 0;
	
    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}
	/***************************/
	Com_Id.ExtId = pPduInfo->PduId;
	tmp = pPduInfo->PduData[1];

	if((Com_Id.bit.SourceAddr == ADDR_BOTTOM_MODULE_CTRL_BOARD)
		||(Com_Id.bit.SourceAddr == ADDR_SIDE_MODULE_CTRL_BOARD)||
		(Com_Id.bit.SourceAddr == ADDR_TOP_MODULE_CTRL_BOARD))
	{
		if((tmp>0)&&(tmp<12))
		{/*采集模块编号在正常范围内*/
			col_module_sta_info[tmp-1].Byte0.val = pPduInfo->PduData[0];
			col_module_sta_info[tmp-1].moduleNum = pPduInfo->PduData[1];
			col_module_sta_info[tmp-1].Byte2.val = pPduInfo->PduData[2];
			col_module_sta_info[tmp-1].Byte3.val = pPduInfo->PduData[3];
			col_module_sta_info[tmp-1].Byte4.val = pPduInfo->PduData[4];
			col_module_sta_info[tmp-1].Byte5.val = pPduInfo->PduData[5];
			col_module_sta_info[tmp-1].Byte6.val = pPduInfo->PduData[6];
			col_module_sta_info[tmp-1].Byte7.val = pPduInfo->PduData[7];
		}
	}

	return(E_OK);
}

/************************************************************
* 函数名称:	Com_ReceBoardInfo
* 函数描述: 解析板卡信息报文
* 输入参数:	(*pPduInfo):接收报文内容;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_ReceBoardInfo(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}
	/***************************/
	Com_Id.ExtId = pPduInfo->PduId;

	switch(Com_Id.bit.SourceAddr)	/*判断源地址*/
	{
		case ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD:/*设备间主控板地址*/
		{
			equRoomCtrlBoardInfo.hearBeatCnt 					= pPduInfo->PduData[0];
			equRoomCtrlBoardInfo.word1.bytes.hardwareMainVer 	= pPduInfo->PduData[1];
			equRoomCtrlBoardInfo.word1.bytes.hardwareMinorVer 	= pPduInfo->PduData[2];
			equRoomCtrlBoardInfo.word2.bytes.softwareMainVer 	= pPduInfo->PduData[3];
			equRoomCtrlBoardInfo.word2.bytes.softwareMinorVer 	= pPduInfo->PduData[4];
			equRoomCtrlBoardInfo.Byte5.val						= pPduInfo->PduData[5];
		}
		break;

		case ADDR_SIGNAL_COLLECT_BOARD:/*信号采集板地址*/
		{
			sigColBoardInfo.hearBeatCnt 					= pPduInfo->PduData[0];
			sigColBoardInfo.word1.bytes.hardwareMainVer 	= pPduInfo->PduData[1];
			sigColBoardInfo.word1.bytes.hardwareMinorVer 	= pPduInfo->PduData[2];
			sigColBoardInfo.word2.bytes.softwareMainVer 	= pPduInfo->PduData[3];
			sigColBoardInfo.word2.bytes.softwareMinorVer 	= pPduInfo->PduData[4];
			sigColBoardInfo.Byte5.val						= pPduInfo->PduData[5];
		}
		break;

		case ADDR_BOTTOM_MODULE_CTRL_BOARD:/*沉箱控制板地址*/
		{
			XZCtrlBoardInfo[0].hearBeatCnt 					= pPduInfo->PduData[0];
			XZCtrlBoardInfo[0].word1.bytes.hardwareMainVer 	= pPduInfo->PduData[1];
			XZCtrlBoardInfo[0].word1.bytes.hardwareMinorVer 	= pPduInfo->PduData[2];
			XZCtrlBoardInfo[0].word2.bytes.softwareMainVer 	= pPduInfo->PduData[3];
			XZCtrlBoardInfo[0].word2.bytes.softwareMinorVer 	= pPduInfo->PduData[4];
			XZCtrlBoardInfo[0].Byte5.val						= pPduInfo->PduData[5];
		}
		break;

		case ADDR_SIDE_MODULE_CTRL_BOARD:/*侧箱控制板地址*/
		{
			XZCtrlBoardInfo[1].hearBeatCnt 					= pPduInfo->PduData[0];
			XZCtrlBoardInfo[1].word1.bytes.hardwareMainVer 	= pPduInfo->PduData[1];
			XZCtrlBoardInfo[1].word1.bytes.hardwareMinorVer 	= pPduInfo->PduData[2];
			XZCtrlBoardInfo[1].word2.bytes.softwareMainVer 	= pPduInfo->PduData[3];
			XZCtrlBoardInfo[1].word2.bytes.softwareMinorVer 	= pPduInfo->PduData[4];
			XZCtrlBoardInfo[1].Byte5.val						= pPduInfo->PduData[5];
		}
		break;

		case ADDR_TOP_MODULE_CTRL_BOARD:/*车顶控制板地址*/
		{
			XZCtrlBoardInfo[2].hearBeatCnt 					= pPduInfo->PduData[0];
			XZCtrlBoardInfo[2].word1.bytes.hardwareMainVer 	= pPduInfo->PduData[1];
			XZCtrlBoardInfo[2].word1.bytes.hardwareMinorVer 	= pPduInfo->PduData[2];
			XZCtrlBoardInfo[2].word2.bytes.softwareMainVer 	= pPduInfo->PduData[3];
			XZCtrlBoardInfo[2].word2.bytes.softwareMinorVer 	= pPduInfo->PduData[4];
			XZCtrlBoardInfo[2].Byte5.val						= pPduInfo->PduData[5];
		}
		break;

		default:
		break;
	}

	return(E_OK);
}

/************************************************************
* 函数名称:	Com_ReceGPKZXStaMoni
* 函数描述: 解析轨旁控制箱状态监测报文
* 输入参数:	(*pPduInfo):接收报文内容;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
Std_ReturnType Com_ReceGPKZXStaMoni(const PduInfoType *pPduInfo)
{
	Com_ProtocolIdType Com_Id;

    if(NULL_PTR == pPduInfo)
	{
		return(E_NOT_OK);
	}
	/***************************/
	Com_Id.ExtId = pPduInfo->PduId;
	if(Com_Id.bit.SourceAddr==ADDR_SIGNAL_COLLECT_BOARD)
	{
		fun_stru2.Byte.val 	= pPduInfo->PduData[0];
		g_envTemp_info 		= pPduInfo->PduData[1];
		g_DC5VVol_info 		= ((uint16)pPduInfo->PduData[2]<<8)|(uint16)pPduInfo->PduData[3];
	}

	return(E_OK);
}


/*************************************************************
                        发送报文解析函数
 ************************************************************/

#if 1
/************************************************************
* 函数名称:	Com_TransmitEquRoomCtrlBoardCtrlInfo
* 函数描述: 组装设备间主控箱控制报文，并发送。
* 输入参数:	(*pPduInfo):报文内容;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  : 该函数被Com模块调用
*************************************************************/
Std_ReturnType Com_TransmitEquRoomCtrlBoardCtrlInfo(const PduInfoType *pPduInfo)
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
	Com_Id.bit.FrameType        = FRAME_TYPE_EQU_ROOM_CTRL_BORAD_CRL;
	Com_Id.bit.DestAddr         = ADDR_BROADCAST;
	Com_Id.bit.SourceAddr       = ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD;
	Com_Id.bit.heatbeatCount    = cnt;
	
	PduInfo.PduId               = Com_Id.ExtId;
	PduInfo.PduLength           = 8u;
	PduInfo.PduData[0]			= ctrl_cmd_info.Byte0.val;									
	PduInfo.PduData[1]			= ctrl_cmd_info.Byte1.val;		
	PduInfo.PduData[2]			= ctrl_cmd_info.Byte2.val;


	CanIf_Transmit(CAN_CONTROLLER_0,PduInfo);
    CanIf_Transmit(CAN_CONTROLLER_1,PduInfo);    /*发送*/

    cnt++;
	return(E_OK);
}
/************************************************************
* 函数名称:	Com_TransmitBoardInfo
* 函数描述: 组装设备间控制板板卡信息报文并发送。
* 输入参数:	无;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  : 该函数被Com模块调用
*************************************************************/
Std_ReturnType Com_TransmitBoardInfo(const PduInfoType *pPduInfo)
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
	Com_Id.bit.SourceAddr       = ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD;
	Com_Id.bit.heatbeatCount    = cnt;
	
	PduInfo.PduId               = Com_Id.ExtId;
	PduInfo.PduLength           = 8u;
	PduInfo.PduData[0]			= cnt;													/*生命信号*/
	PduInfo.PduData[1]			= equRoomCtrlBoardInfo.word1.bytes.hardwareMainVer;		/*硬件主版本号*/
	PduInfo.PduData[2]			= equRoomCtrlBoardInfo.word1.bytes.hardwareMinorVer;	/*硬件次版本号*/
	PduInfo.PduData[3]			= equRoomCtrlBoardInfo.word2.bytes.softwareMainVer;		/*软件主版本号*/
	PduInfo.PduData[4]			= equRoomCtrlBoardInfo.word2.bytes.softwareMinorVer;	/*软件次版本号*/
	PduInfo.PduData[5]			= equRoomCtrlBoardInfo.Byte5.val;						/*板卡CAN故障信息*/

	CanIf_Transmit(CAN_CONTROLLER_0,PduInfo);
    CanIf_Transmit(CAN_CONTROLLER_1,PduInfo);    /*发送*/

    cnt++;
	return(E_OK);
}
#endif

