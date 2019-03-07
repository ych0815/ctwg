/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com_Protocol.h
* 功能描述  : 通讯模块协议解析头文件(Com_Protocol.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_PROTOCOL_H_
#define  _COM_PROTOCOL_H_


/**************************************
              	头文件
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"
#include "os_cpu.h"
#include "TrainInOutCheck.h"
#include "MoniDataCol.h"

/**************************************
             	类型定义
 **************************************/
typedef union
{
	uint32	ExtId;
	struct
	{
		uint8 FrameType :5; /*ID28~ID24:帧类型 */
		uint8 Reserve0  :3; /*ID31~ID29:保留   */
		uint8 DestAddr  :5; /*ID20~ID16:目的地址*/
		uint8 Reserve1  :3; /*ID23~ID21:保留   */
		uint8 SourceAddr:5; /*ID12~ID8 :源地址 */
		uint8 Reserve2  :3; /*ID15~ID13:保留   */
		uint8 heatbeatCount:8; /*ID7~ID0  :心跳计数,取值范围:0~255*/
	}bit;
}Com_ProtocolIdType;


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern boolean g_boardCAN_info[2];	  /*板卡CAN故障信息，TRUE表示CAN故障 FALSE表示CAN正常*/

#pragma DATA_SEG DEFAULT

/**************************************
             	宏定义
 **************************************/
/**************************FRAME TYPE**************************/ 
#define FRAME_TYPE_SIGCOLBOARD_COl            1   /*信号采集板采集报文*/
#define	FRAME_TYPE_GPKZX_STATEMONI            4   /*轨旁控制箱状态监测报文*/
#define FRAME_TYPE_BOARD_INFO		          5	  /*板卡信息报文*/ 

/**************************ADDR**************************/
#define ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD   1   /*设备间主控板地址*/
#define ADDR_SIGNAL_COLLECT_BOARD             2   /*信号采集板地址*/
#define ADDR_BOTTOM_MODULE_CTRL_BOARD         3   /*沉箱控制板地址*/
#define ADDR_SIDE_MODULE_CTRL_BOARD           4   /*侧箱控制板地址*/
#define ADDR_TOP_MODULE_CTRL_BOARD            5   /*车顶控制板地址*/
#define ADDR_BROADCAST                        31  /*广播地址*/

/**************************BOARD INFO**************************/
#define HARDWARE_MAIN_VERSION				  0	  /*硬件主版本号*/
#define HARDWARE_MINOR_VERSION  			  1   /*硬件次版本号*/

#define SOFTWARE_MAIN_VERSION				  0	  /*软件主版本号*/
#define SOFTWARE_MINOR_VERSION  			  1   /*软件次版本号*/

/**************************************
             	函数声明
 **************************************/
extern	Std_ReturnType Com_ReceSysSynch(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBack(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtrl(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddle(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceInputArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBackArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddleArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtlArbitration(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceInputCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceMiddleCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceOutCtrlCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceFeedBackCascade(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitSysSynchInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitCanLinkStatusAtV4TrustInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitSigColBoradColMessage(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitBoardInfoMessage(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitGPKZXStateMoniMessage(const PduInfoType *pPduInfo);
#endif

