/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Com.h
* 功能描述  : 通讯模块头文件(Com.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_H_
#define  _COM_H_

/**************************************
              	头文件
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"

/**************************************
             	宏定义
 **************************************/

/*错误定义*/
#define 	COM_E_UNINIT						(0x10u) /*模块未初始化*/
#define 	COM_E_PARAM_INVALID			    	(0x11u) /*输入参数无效*/
#define     COM_E_CONFIGPARAM_INVALID			(0x12u)	/*模块配置参数错误*/
#define     COM_E_WORKMODE                      (0x13u) /*指定报文的工作模式错误*/

/* API Service ID's*/
#define 	COM_INIT_ID							(0x00u) /*Com_Init*/
#define 	COM_RXINDICATION_ID 			    (0x01u)	/*Com_RxIndication*/
#define 	COM_ENABLEPACKET_RX_ID				(0x02u)	/*Com_EnablePacketRx*/
#define 	COM_DISABLEPACKET_RX_ID				(0x03u)	/*Com_DisablePacketRx*/
#define		COM_ENABLEPACKET_TX_ID				(0x04u) /*Com_EnablePacketTx*/
#define     COM_DISABLEPACKET_TX_ID				(0x05u)	/*Com_DisablePacketTx*/
#define     COM_MAINFUNCTION_ID					(0x06u)	/*Com_MainFunction*/
#define 	COM_RXINDICATIONHOOK_ID 			(0x07u)	/*Com_RxIndicationHook()*/

/*******************************************
				静态配置资源声明
 ******************************************/
extern	const  Com_ProtocoCfgType   Com_Cfg;

/************************************************************
* 函数名称:Com_Init
* 函数描述:Com模块初始化
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:	不可重入
* 返回值  : 无
* 备注	  :
*************************************************************/
extern  void  Com_Init(void);

/************************************************************
* 函数名称:Com_RxIndication
* 函数描述:通知Com模块接收的指定协议ID号的报文
* 输入参数:
* 输出参数:
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_RxIndication(uint8 ProtocolId,const PduInfoType PduInfo);

/************************************************************
* 函数名称:Com_EnablePacketRx
* 函数描述:使能Com模块接收指定协议中的某一报文
* 输入参数:
* 输出参数:
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_EnablePacketRx(uint8 ProtocolId,uint32 PduId);

/************************************************************
* 函数名称:Com_DisablePacketRx
* 函数描述:禁止Com模块接收指定协议中的某一报文
* 输入参数:
* 输出参数:
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_DisablePacketRx(uint8 ProtocolId,uint32 PduId);

/************************************************************
* 函数名称:Com_EnablePacketTx
* 函数描述:使能Com模块发送指定协议中的某一报文
* 输入参数:
* 输出参数:
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_EnablePacketTx(uint8 ProtocolId,uint32 PduId);

/************************************************************
* 函数名称:Com_DisablePacketTx
* 函数描述:禁止Com模块发送指定协议中的某一报文
* 输入参数:
* 输出参数:
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_DisablePacketTx(uint8 ProtocolId,uint32 PduId);

/************************************************************
* 函数名称:Com_MainFunction
* 函数描述:Com模块后台主循环函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :该函数被周期任务调用
*************************************************************/
extern  void  Com_MainFunction(void);

/************************************************************
* 函数名称:Com_RxIndicationHook
* 函数描述:通知Com模块,对应控制器接收到报文;
* 输入参数:DevCfgId:接收到报文的控制器在CanIf模块中的配置索引;
           			= 0u:Can0控制器;
           			= 1u:Can1控制器;
           (*pPduInfo):接收到报文内容;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:可重入
* 返回值  :E_OK:操作成功;
           E_NOT_OK:操作失败;
* 备注	  :
*************************************************************/
extern  Std_ReturnType  Com_RxIndicationHook(uint8 DevCfgId,const PduInfoType *pPduInfo);

#endif

