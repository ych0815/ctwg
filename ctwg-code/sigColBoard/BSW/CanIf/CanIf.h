/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : CanIf.h
* 功能描述  : CanIf模块头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            	New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CANIF_H_
#define  _CANIF_H_

#include "CanIf_Cfg.h"
#include "CanIf_CfgType.h"

/*******************************************
				宏定义
 ******************************************/
/*错误定义*/
#define 	CANIF_E_UNINIT						(0x10u) /*模块未初始化*/
#define 	CANIF_E_PARAM_INVALID			    (0x11u) /*输入参数无效*/
#define     CANIF_E_CONFIGPARAM_INVALID			(0x12u)	/*模块配置参数错误*/
#define     CANIF_E_TRANSBUFF_FULL              (0x13u) /*发送缓存满*/ 
#define     CANIF_E_RECEIVEBUFF_FULL            (0x14u) /*接收缓存满*/
#define     CANIF_E_CONTROLLER_BUSOFF           (0x15u) /*指定的发送控制器状态为BusOff*/

/* API Service ID's*/
#define 	CANIF_INIT_ID						(0x00u) /*CanIf_Init*/
#define 	CANIF_RXINDICATION_ID 			    (0x01u)	/*CanIf_RxIndication*/
#define 	CANIF_TRANSMIT_ID					(0x02u)	/*CanIf_Transmit*/
#define 	CANIF_RESET_TRANSMITQUENE_ID		(0x03u)	/*CanIf_ResetTransmitQueue*/
#define		CANIF_TRANSMITQUENE_ISEMPTY_ID		(0x04u) /*CanIf_TransmitQueueIsEmpty*/
#define     CANIF_GETNEXTPACKET_ID				(0x05u)	/*CanIf_GetNextPacket*/
#define     CANIF_MAINFUNCTION_ID				(0x06u)	/*CanIf_Mainfunction*/
#define     CANIF_TXCONFIRMHOOK_ID              (0x07u) /*CanIf_TxConfirmHook()*/
#define 	CANIF_RXINDICATIONHOOK_ID 			(0x08u)	/*CanIf_RxIndicationHook()*/
/**/
#define  	CAN_TXBUFFSIZE   					(64u) 	/*控制器发送队列缓存长度*/
#define  	CAN_RXBUFFSIZE	  					(64u) 	/*控制器接收队列缓存长度*/
/*******************************************
				静态配置资源声明
 ******************************************/
extern   const  CanIf_CfgType  CanIf_Cfg;


/************************************************************
* 函数名称:CanIf_Init
* 函数描述:CanIf模块初始化.
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性: 不可重入
* 备注	  :
*************************************************************/
extern  void  CanIf_Init(void);

/************************************************************
* 函数名称:CanIf_RxIndication
* 函数描述:通知CanIf模块,设备号为DevId的控制器接收到报文;
* 输入参数:DevId  :CAN控制器设备ID
		   PduInfo:接收到的报文信息
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :下层Can驱动模块调用
*************************************************************/
extern  Std_ReturnType CanIf_RxIndication(uint8 DevId, const PduInfoType PduInfo);

/************************************************************
* 函数名称:CanIf_Transmit
* 函数描述:通知DevId指定Can控制器发送一帧报文;
* 输入参数:DevId  :设备ID号;
           PduInfo:待发送报文;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :上层Com模块调用
*************************************************************/
extern  Std_ReturnType CanIf_Transmit(uint8 DevId,const PduInfoType PduInfo);

/************************************************************
* 函数名称:CanIf_ResetTransmitQueue
* 函数描述:通知CanIf模块,清除DevId指定控制器的发送队列;
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :下层Can驱动模块调用
*************************************************************/
extern  void  CanIf_ResetTransmitQueue(uint8 DevId);

/************************************************************
* 函数名称:CanIf_TransmitQueueIsEmpty
* 函数描述:通知CanIf模块,DevId指定控制器的发送队列已经为空;
* 输入参数:DevId:
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :下层Can驱动模块调用
*************************************************************/
extern  void  CanIf_TransmitQueueIsEmpty(uint8 DevId);

/************************************************************
* 函数名称:CanIf_GetNextPacket
* 函数描述:通知CanIf模块,从DevId指定的Can控制器发送队列中,
		   获取一帧待发送报文;
* 输入参数:DevId:
		  (*pPduInfo):
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :下层Can驱动模块调用
*************************************************************/
extern  Std_ReturnType CanIf_GetNextPacket(uint8 DevId,PduInfoType *pPduInfo);

/************************************************************
* 函数名称:CanIf_Mainfunction
* 函数描述:CanIf模块提供的后台主循环
* 输入参数:DevId  :设备ID号;
           PduInfo:待发送报文;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :周期调用
*************************************************************/
extern  void CanIf_Mainfunction(void); 

/************************************************************
* 函数名称:CanIf_RxIndicationHook
* 函数描述:Can控制器接收中断通知钩子函数
* 输入参数:DevId  :设备ID号;
           (*pPduInfo):接收到的CAN报文
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无;
* 备注	  :下层Can驱动模块接收中断(Rx ISR)调用
*************************************************************/
extern  Std_ReturnType CanIf_RxIndicationHook(uint8 DevId, const PduInfoType *pPduInfo);

/************************************************************
* 函数名称:CanIf_TxConfirmHook
* 函数描述:Can控制器发送完成中断通知钩子函数
* 输入参数:DevId:设备ID号;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 返回值  :无;
* 备注	  :下层Can驱动模块发送完成中断(Tx ISR)调用
*************************************************************/
extern  Std_ReturnType CanIf_TxConfirmHook(uint8 DevId);

#endif
