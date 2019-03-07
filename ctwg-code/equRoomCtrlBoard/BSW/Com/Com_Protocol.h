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

/**************************************
             	CAN报文类型定义
 **************************************/
/*扩展帧ID数据结构*/
typedef union
{
	uint32	ExtId;
	struct
	{
		uint8 FrameType :5; 	/*ID28~ID24:帧类型 */
		uint8 Reserve0  :3; 	/*ID31~ID29:保留   */
		uint8 DestAddr  :5; 	/*ID20~ID16:目的地址*/
		uint8 Reserve1  :3; 	/*ID23~ID21:保留   */
		uint8 SourceAddr:5; 	/*ID12~ID8 :源地址 */
		uint8 Reserve2  :3; 	/*ID15~ID13:保留   */
		uint8 heatbeatCount:8; 	/*ID7~ID0  :心跳计数,取值范围:0~255*/
	}bit;
}Com_ProtocolIdType;

/*板卡信息数据结构*/
typedef struct board_info
{
	uint8 hearBeatCnt; 					/**brief 生命信号 0~255 */
	union
	{
		uint16 hardwareVer;				/**brief 硬件版本*/
		struct
		{
			uint8 hardwareMainVer; 		/**brief 硬件主版本号 */
			uint8 hardwareMinorVer; 	/**brief 硬件次版本号 */			
		}bytes;	
	}word1;

	union
	{
		uint16 softwareVer;				/**brief 软件版本*/
		struct
		{
			uint8 softwareMainVer; 		/**brief 软件主版本号 */
			uint8 softwareMinorVer;     /**brief 软件次版本号 */			
		}bytes;
	}word2;
	
	union
	{
		uint8 val;
		struct
		{
			uint8 reserve1			:2;		/**brief 预留 */
			uint8 reserve0			:2;		/**brief 预留 */
			uint8 boardCan2ErrSta	:2;		/**brief 板卡CAN2故障状态 1表示正常 2表示故障*/
			uint8 boardCan1ErrSta	:2;		/**brief 板卡CAN1故障状态 1表示正常 2表示故障*/
		}bits;
	}Byte5;
}BOARD_INFO;

/*采集模块状态数据结构*/
typedef struct col_module_sta
{
	union 
	{
		uint8 val;
		struct 
		{
			uint8 moduleWorkSta		:4;		/**brief 采集模块工作状态*/
			uint8 moduleType		:4;		/**brief 采集模块类型 */
		}bits;
	}Byte0;


	uint8 moduleNum;				/**brief 采集模块编号 */

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2LightErrSta	:1;		/*brief 相机2光源故障状态 */
			uint8 cam2LightCtrl		:1;		/*brief 相机2光源触发控制 */
			uint8 cam1CamErrSta 	:1;		/*brief 相机1相机故障状态(预留) */
			uint8 cam1CamCtrl 		:1;		/*brief 相机1相机触发控制 */
			uint8 cam1LightErrSta 	:1;		/*brief 相机1光源故障状态 */
			uint8 cam1LightCtrl 	:1;		/*brief 相机1光源触发控制 */
			uint8 moduleWorkModel 	:2;		/*brief 采集模块工作状态 */
		}bits;
	}Byte2;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam1CCFanErrSta 	:1;		/*brief 相机1除尘风扇故障状态 */
			uint8 cam1CCFanOpenCtrl :1;		/*brief 相机1除尘风扇开启控制 */
			uint8 cam3CamErrSta 	:1;		/*brief 相机3相机故障状态(预留) */
			uint8 cam3CamCtrl 		:1;		/*brief 相机3相机触发控制 */
			uint8 cam3LightErrSta 	:1;		/*brief 相机3光源故障状态 */
			uint8 cam3LightCtrl 	:1;		/*brief 相机3光源触发控制 */
			uint8 cam2CamErrSta 	:1;		/*brief 相机2相机故障状态(预留) */
			uint8 cam2CamCtrl 		:1;		/*brief 相机2相机触发控制 */		
		}bits;
	}Byte3;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2SRFanOpenCtrl :1; 	/*brief 相机2散热风扇开启控制 */
			uint8 cam1SRFan2ErrSta 	:1;		/*brief 相机1散热风扇2故障状态 */
			uint8 cam1SRFan1ErrSta 	:1;		/*brief 相机1散热风扇1故障状态 */
			uint8 cam1SRFanOpenCtrl :1; 	/*brief 相机1散热风扇开启控制 */
			uint8 cam3CCFanErrSta 	:1;		/*brief 相机3除尘风扇故障状态 */
			uint8 cam3CCFanOpenCtrl :1;		/*brief 相机3除尘风扇开启控制 */
			uint8 cam2CCFanErrSta 	:1;		/*brief 相机2除尘风扇故障状态 */
			uint8 cam2CCFanOpenCtrl :1;		/*brief 相机2除尘风扇开启控制 */	
		}bits;
	}Byte4;

	union
	{
		uint8 val;
		struct
		{
			uint8 camDoorSta		:2;		/*brief 防护门状态 */
			uint8 waterAlarm		:1;		/*brief 水位报警 */
			uint8 cam3SRFan2ErrSta 	:1;		/*brief 相机3散热风扇2故障状态 */
			uint8 cam3SRFan1ErrSta 	:1;		/*brief 相机3散热风扇1故障状态 */
			uint8 cam3SRFanOpenCtrl :1; 	/*brief 相机3散热风扇开启控制 */
			uint8 cam2SRFan2ErrSta 	:1;		/*brief 相机2散热风扇2故障状态 */
			uint8 cam2SRFan1ErrSta 	:1;		/*brief 相机2散热风扇1故障状态 */		
		}bits;
	}Byte5;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:1;		/*brief 预留 */
			uint8 reserve1			:1;		/*brief 预留 */
			uint8 reserve0			:1;		/*brief 预留 */
			uint8 boxSRFanOpenCtrl	:1;		/*brief 箱体散热风扇开启控制 */
			uint8 heaterErrSta		:1;		/*brief	加热器故障状态(预留) */
			uint8 heaterSupSta		:1;		/*brief 加热器供电状态(预留)*/
			uint8 camDoorCloseCtrl 	:1;		/*brief	防护门关闭控制 */
			uint8 camDoorOpenCtrl	:1;		/*brief 防护门开启控制 */		
		}bits;
	}Byte6;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve3; 				/*brief 预留 */
		}bits;
	}Byte7;	
}COL_MODULE_STA;

/*设备间主控箱控制指令数据结构*/
typedef struct ctrl_cmd
{
	union
	{
		uint8 val;
		struct
		{
			uint8 ccOpenOrClose		:2;		/*除尘开/关指令*/
			uint8 doorOpenOrClose 	:2;		/*开门/关门指令*/
			uint8 localOrRemote		:2;		/*本地/远方指令*/
			uint8 runOrService 		:2;		/*运行/维护指令*/
		}bits;
	}Byte0;
	
	union
	{
		uint8 val;
		struct
		{
			uint8 mzOpenOrClose		:2;		/*面阵开/关指令*/
			uint8 xzOpenOrClose		:2;		/*线阵开/关指令*/
			uint8 heatOpenOrClose	:2;		/*加热开/关指令(预留)*/
			uint8 srOpenOrClose		:2;		/*散热开/关指令*/
		}bits;
	}Byte1;
		
	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:2;		/*预留*/
			uint8 reserve1			:2;		/*预留*/
			uint8 reserve0			:2;		/*预留*/
			uint8 simuOpenOrClose	:2;		/*模拟开/关指令*/
		}bits;
	}Byte2;

}CTRL_CMD;

/*功能数据结构*/
typedef struct fun_stru
{
	union
	{
		uint8 val;
		struct
		{
			uint8 bit1_0 :2;
			uint8 bit3_2 :2;
			uint8 bit5_4 :2;
			uint8 bit7_6 :2;
		}bits;
	}Byte;
}FUN_STRU;

/**************************************
             	ETH报文类型定义
 **************************************/
typedef struct ctrl_board_info
{
	uint8 board_heartBeat;				/*采集模块控制板生命信号*/
	uint16 board_softwareVer;			/*采集模块控制板软件版本*/
	uint16 board_hardwareVer;			/*采集模块控制板硬件版本*/

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve0 			:2;	/*预留*/
			uint8 board_Can2ErrSta 	:2;	/*采集模块控制板CAN2故障状态*/
			uint8 board_Can1ErrSta 	:2; /*采集模块控制板CAN2故障状态*/
			uint8 board_ErrSta		:2;	/*采集模块控制板故障状态*/
		}bits;
	}Byte3; 
}CTRL_BOARD_INFO;


typedef struct col_module_sta_err_info
{
	COL_MODULE_STA _col_module_sta;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2LightErrSta	:2;		/*brief 相机2光源故障状态 */
			uint8 cam2CamErrSta 	:2;		/*brief 相机2相机故障状态(预留) */
			uint8 cam1LightErrSta	:2;		/*brief 相机1光源故障状态 */
			uint8 cam1CamErrSta 	:2;		/*brief 相机1相机故障状态(预留) */
		}bits;	
	}Byte8;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2CCFanErrSta 	:2;		/*brief 相机2除尘风扇故障状态 */
			uint8 cam1CCFanErrSta 	:2;		/*brief 相机1除尘风扇故障状态 */
			uint8 cam3LightErrSta	:2;		/*brief 相机3光源故障状态 */
			uint8 cam3CamErrSta 	:2;		/*brief 相机3相机故障状态(预留) */
		}bits;	
	}Byte9;

    union
	{
		uint8 val;
		struct
		{
			uint8 cam2SRFan1ErrSta 	:2;		/*brief 相机2散热风扇1故障状态 */
			uint8 cam1SRFan2ErrSta 	:2;		/*brief 相机1散热风扇2故障状态 */
			uint8 cam1SRFan1ErrSta 	:2;		/*brief 相机1散热风扇2故障状态 */
			uint8 cam3CCFanErrSta 	:2;		/*brief 相机2除尘风扇故障状态 */
		}bits;	
	}Byte10;

	union
	{
		uint8 val;
		struct
		{
			uint8 camDoorErrSta		:2;		/*brief 防护门故障状态 */
			uint8 cam3SRFan2ErrSta 	:2;		/*brief 相机3散热风扇2故障状态 */
			uint8 cam3SRFan1ErrSta 	:2;		/*brief 相机3散热风扇1故障状态 */ 
			uint8 cam2SRFan2ErrSta 	:2;		/*brief 相机2散热风扇2故障状态 */
		}bits;	
	}Byte11;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:2; 	/*brief 预留 */
			uint8 reserve1			:2; 	/*brief 预留 */
			uint8 reserve0			:2; 	/*brief 预留 */
			uint8 waterAlarm		:2;		/*brief 水位报警 */ 
		}bits;	
	}Byte12;			
}COL_MODULE_STA_ERR_INFO;

/**************************************
             	宏定义
 **************************************/
/**************************FRAME TYPE**************************/ 
#define FRAME_TYPE_SIGCOLBOARD_COl            1   /*信号采集板采集报文*/
#define FRAME_TYPE_EQU_ROOM_CTRL_BORAD_CRL 	  2   /*设备间主控箱控制报文*/
#define FRAME_TYPE_COL_MODULE_STA             3   /*采集模块状态报文*/
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
extern	Std_ReturnType Com_ReceSigColBoardCol(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceColModuleSta(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceBoardInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceGPKZXStaMoni(const PduInfoType *pPduInfo);

extern	Std_ReturnType Com_TransmitEquRoomCtrlBoardCtrlInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitBoardInfo(const PduInfoType *pPduInfo);
#endif

