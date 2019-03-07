/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Can.h
* 功能描述  : 9s12xep100-Can驱动头文件(Can.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CAN_H_
#define  _CAN_H_

/**************************************
              	头文件
 **************************************/
#include "Can_Cfg.h"
#include "Can_CfgType.h"
#include "Can_Register.h"

/**************************************
             		宏定义
 **************************************/
/*错误定义*/
#define 	CAN_E_UNINIT						(0x10u) /*模块未初始化*/
#define 	CAN_E_PARAM_INVALID			    	(0x11u) /*输入参数无效*/
#define     CAN_E_CONFIGPARAM_INVALID			(0x12u)	/*模块配置参数错误*/
#define     CAN_E_ENTER_INITMODE_INVALID        (0x13u) /*控制器进入初始化模式失败*/
#define     CAN_E_EXIT_INITMODE_INVALID         (0x14u) /*控制器退出初始化模式失败*/
#define     CAN_E_SYNCH_ERROR					(0x15u) /*CAN结点同步进入网络失败*/
#define     CAN_E_ENTER_SLEEPMODE_INVALID       (0x16u) /*控制器进入睡眠模式失败*/

/* API Service ID's*/
#define 	CAN_INIT_ID							(0x00u) /*Can_Init*/
#define 	CAN_ENABLE_TXINTERRUPT_ID			(0x02u)	/*Can_EnableTxInterrupt*/
#define 	CAN_DISABLE_TXINTERRUPT_ID			(0x03u)	/*Can_DisableTxInterrupt*/
#define		CAN_ENTERSTOP_ID					(0x04u) /*Can_EnterStopMode*/
#define     CAN_CALCBASEADDRBYCONTROLLERID_ID   (0x05u) /*Can_CalcBaseAddrByControllerId*/
#define     CAN_ENTER_INITMODE                  (0x06u) /*Can_EnterInitMode*/
#define     CAN_EXIT_INITMODE                   (0x07u) /*Can_ExitInitMode*/
#define 	CAN_REQUESTMESSAGEABORT_ID			(0x08u) /*Can_RequestTransmitterMessageAbort()*/
#define     CAN_GETCONTROLLERSTATUS_ID			(0x09u) /*Can_GetControllerStatus()*/
/**********************/
#define     CAN_REQUEST_CONFIRM_TIMES 		(1000u)   /*请求进入初始化(睡眠)模式,确认软件循环次数*/

/*******************************************
				静态配置资源声明
 ******************************************/
extern  const  Can_CfgType  Can_Cfg;


/************************************************************
* 函数名称:Can_Init
* 函数描述:Can驱动模块初始化,该函数需要将模块静态配置的所有控制器初始化.
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性: 不可重入
* 备注	  :
*************************************************************/
extern  void  Can_Init(void);

/************************************************************
* 函数名称:Can_InitController
* 函数描述:初始化指定控制器
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:无
* 输入/输出参数:无
* 可重入性: 不可重入
* 备注	  :
*************************************************************/
//extern  void  Can_InitController(uint8 DevId);

/************************************************************
* 函数名称:Can_Write
* 函数描述:指定DevId对应的Can控制器发送,将PduInfo内容写入Can硬件缓存;
* 输入参数:DevId  :Can控制器设备ID号;
		   PduInfo:
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  void  Can_Write(uint8  DevId,PduInfoType PduInfo);

/************************************************************
* 函数名称:Can_EnableTxInterrupt
* 函数描述:使能DevId指定Can控制器发送中断;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  void  Can_EnableTxInterrupt(uint8  DevId);

/************************************************************
* 函数名称:Can_DisableTxInterrupt
* 函数描述:禁止DevId指定Can控制器发送中断;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  void  Can_DisableTxInterrupt(uint8  DevId);

/************************************************************
* 函数名称:Can_RequestTransmitterMessageAbort
* 函数描述:请求终止指定控制器硬件Buffer中的Pending报文;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  void  Can_RequestTransmitterMessageAbort(uint8  DevId);

/************************************************************
* 函数名称:Can_EnterStopMode
* 函数描述:停止DevId指定Can控制器工作;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
//extern  void  Can_EnterStopMode(uint8  DevId);

/************************************************************
* 函数名称:Can_GetControllerStatus
* 函数描述:读取DevId指定Can控制器状态;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:(*pCanStatus): =0:CAN控制器没有进入BusOff;
                          =1:CAN控制器进入BusOff;
* 输入/输出参数:
* 可重入性:
* 备注	  :(pCanReg->CANRFLG.MergedBits.grpTSTAT) 
			=0:TxOK; 发送控制器正常;
			=1:TxWRN;发送控制器警告;
			=2:TxERR;发送控制器错误;
			=3:Bus-Off;发送控制器总线关闭;
*************************************************************/
extern  void  Can_GetControllerStatus(uint8  DevId,uint8 *pCanStatus);

#endif
































