/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : ComM.h
* 功能描述  : 通讯管理模块头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COMM_H_
#define  _COMM_H_

/**************************************
              	头文件
 **************************************/
#include "ComM_Cfg.h"
#include "ComM_CfgType.h"

/*******************************************
				宏定义
 ******************************************/
/*错误定义*/
#define 	COMM_E_UNINIT						(0x10u) /*模块未初始化*/
#define 	COMM_E_PARAM_INVALID			    (0x11u) /*输入参数无效*/
#define     COMM_E_CONFIGPARAM_INVALID			(0x12u)	/*模块配置参数错误*/

/* API Service ID's*/
#define 	COMM_INIT_ID						(0x00u) /*ComM_Init*/
#define 	COMM_RXINDICATION_ID 			    (0x01u)	/*ComM_RxIndication*/
#define 	COMM_BUSOFFINDICATION_ID			(0x02u)	/*ComM_BusOffIndication*/
#define 	COMM_GETTRUSTINFO_ID				(0x03u)	/*ComM_GetTrustInfo*/
#define		COMM_GETCONTROLLERSTATUS_ID		    (0x04u) /*ComM_GetControllerStatus*/
#define     COMM_MAINFUNCTION_ID				(0x05u)	/*ComM_Mainfunction*/
#define 	COMM_INITGROUP_ID					(0x06u) /*ComM_InitGroup*/
#define     COMM_GETCONTROLLERCOMMSTATUS_ID     (0x07u) /*ComM_GetControllerCommStatus*/
/*******************************************
				静态配置资源声明
 ******************************************/
extern   const ComM_CfgType   ComM_Cfg;

/************************************************************
* 函数名称:ComM_Init
* 函数描述:ComM模块初始化
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :
*************************************************************/
extern  void ComM_Init(void);

/************************************************************
* 函数名称:ComM_RxIndication
* 函数描述:通知ComM模块,设备号=DevId的CAN控制器接收到报文
* 输入参数:DevId:
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  Std_ReturnType ComM_RxIndication(uint8 DevId);


/************************************************************
* 函数名称:ComM_BusOffIndication
* 函数描述:通知ComM模块,设备号=DevId的CAN控制器产生BusOff.
* 输入参数:DevId:
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
extern  Std_ReturnType ComM_BusOffIndication(uint8 DevId);


/************************************************************
* 函数名称:ComM_GetTrustInfo
* 函数描述:获取组号=GroupId的信任总线信息.
* 输入参数:GroupId:双CAN冗余组ID号;
* 输出参数:(*pTrustInfo):冗余组信任总线信息,内容为指定组内信任控制器ID号;
* 输入/输出参数:
* 返回值  :E_OK:成功读取冗余组信任总线信息
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
extern  Std_ReturnType ComM_GetTrustInfo(uint8 GroupId,uint8 *pTrustInfo);


/************************************************************
* 函数名称:ComM_GetControllerStatus
* 函数描述:获取设备号=DevId的CAN控制器状态信息.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pControllerStatus):Can控制器状态信息; 
           = 0:COMM_CONTROLLER_OK 控制器状态OK; 
           = 1:COMM_CONTROLLER_BUSOFF  控制器状态busOff;
* 输入/输出参数:
* 返回值  :E_OK:成功读取控制器状态信息;
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
extern  Std_ReturnType ComM_GetControllerStatus(uint8 DevId,uint8 *pControllerStatus);

/************************************************************
* 函数名称:ComM_GetControllerCommStatus
* 函数描述:获取设备号=DevId控制器的通讯状态信息.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pCommStatus):Can控制器通讯状态; 
    		= 0u:COMM_COMMUNICAITON_OK   控制器通信正常
    		= 1u:COMM_COMMUNICAITON_ERR  控制器通信故障
* 输入/输出参数:
* 返回值  :E_OK:成功读取控制器状态信息;
		   E_NOT_OK:模块未初始化或入口参数错误;
* 可重入性:
* 备注	  :
*************************************************************/
extern  Std_ReturnType ComM_GetControllerCommStatus(uint8 DevId,uint8 *pCommStatus);

/************************************************************
* 函数名称:ComM_MainFunction
* 函数描述:ComM模块后台主循环.
* 输入参数: DevId:Can控制器ID号;
* 输出参数:(*pControllerStatus):Can控制器状态信息;
* 输入/输出参数:
* 可重入性:
* 备注	  :该函数需要被周期调用
*************************************************************/
extern  void ComM_MainFunction(void);


#endif

