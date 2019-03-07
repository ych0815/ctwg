/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名   : Com_Cfg.h
* 功能描述 : 通讯模块配置头文件(Com_Cfg.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_CFG_H_
#define  _COM_CFG_H_

/**************************************
              	头文件
 **************************************/
#include "Std_Types.h"
#include "Modules.h"

/**************************************
             	宏定义
 **************************************/
#define   COM_DEV_ERROR_DETECT   	(STD_ON)    	/*开发时错误检测*/

#define   COM_MAX_PROTOCOLNUM   	(1u)        	/*模块支持的协议个数,该参数不能比配置参数NumOfProtocol小,但可以>=NumOfProtocol*/
#define   COM_MAX_IPDUNUM 			(14u)        	/*模块支持的协议中,单个协议支持的最大报文数量(接收+发送),该参数不能比配置参数NumOfIPdu值小,但可以>=NumOfIPdu*/      

/*************/
/*协议包含报文类型定义*/
#define   COM_SYS_SYNCH             (0x03000000ul)  /*系统同步时钟报文*/ 

#define   COM_FEEDBACK				(0x06000000ul)	/*输出反馈状态报文*/
#define   COM_MIDDLE				(0x07000000ul)  /*逻辑运算中间变量报文*/
#define   COM_OUTCTL                (0x08000000ul)  /*逻辑运算输出控制报文*/

#define   COM_MIDDLE_ARBITRATION    (0x04000000ul)  /*逻辑运算中间变量仲裁报文*/
#define   COM_OUTCTL_ARBITRATION	(0x05000000ul)  /*逻辑运算输出控制仲裁报文*/
#define   COM_FEEDBACK_ARBITRATION  (0x09000000ul)  /*输出反馈状态仲裁报文*/
#define   COM_INPUT_ARBITRATION  	(0x0A000000ul)  /*输入信息仲裁报文*/

#define   COM_INPUT_CASCADE			(0x0B000000ul)  /*级联机箱输入仲裁报文*/
#define   COM_MIDDLE_CASCADE		(0x0C000000ul)  /*级联机箱中间变量仲裁报文*/
#define   COM_OUTCTRL_CASCADE		(0x0D000000ul)  /*级联机箱输出控制仲裁报文*/
#define   COM_FEEDBACK_CASCADE		(0x0E000000ul)  /*级联机箱输出反馈仲裁报文*/

/*************/
#define   COM_CAN_LINKCHECK         (0x14000000ul)  /*CAN链路检测报文*/
#define   COM_CAN_LINKSTATUS        (0x15000000ul)  /*CAN链路状态共享报文*/     



/**********************************************************************
 * 设备间主控板
 * ********************************************************************/
#define   COM_SIGCOLBOARD_COl			(0x01000000ul)	/*信号采集板采集报文*/
#define   COM_EQUROOM_CTRLBOARD_CTRL	(0x02000000ul)	/*设备间主控箱控制报文*/
#define	  COM_COL_MODULE_STA			(0x03000000ul)	/*采集模块状态报文*/
#define	  COM_GPKZX_STATEMONI       	(0x04000000ul)  /*轨旁控制箱状态监测报文*/
#define   COM_BOARD_INFO				(0x05000000ul)  /*板卡信息报文*/


#endif
