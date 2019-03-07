/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Can.c
* 功能描述  : 9s12xep100-Can驱源文件(Can.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms              New
* 1.0.1       2019/1/4        sunj                MODify
**------------------------------------------------------------------------------------------------*/
#include "Can.h"
#include "CanIf.h"
#include "ComM.h"
#include "drv_sci.h"

/****************************************
           运行时数据结构类型定义
 ****************************************/
typedef  enum
{
	CAN_UNINIT = 0u,
	CAN_INIT   = 1u
}Can_MkStatusType;

typedef struct
{
	Can_MkStatusType  MkStatus;
}Can_MkCtrlType;
/*****************************************
            运行时数据结构定义
 ****************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Can_MkCtrlType  Can_MkCtrl;
#pragma DATA_SEG DEFAULT

/*****************************************
            静态函数声明
 ****************************************/
#if 1
STATIC void Can_CalcBaseAddrByControllerId(uint8 DevId,uint32 *pBaseAddr);
STATIC void	Can_EnterInitMode(uint32 BaseAddr);
STATIC void	Can_ExitInitMode(uint32 BaseAddr);
STATIC void	Can_ConfigBaudRate(uint32 BaseAddr,Can_ControllerBpsType Bps);
STATIC void Can_ConfigFilter(uint32 BaseAddr,Can_IdType IdType,uint8 FilterNum,Can_FilterCfgType *pFilterCfg);
STATIC Std_ReturnType Can_SearchControllerFromRxObjectCfg(uint8  DevId,uint8 *pObjectIndex);
STATIC Std_ReturnType Can_SearchControllerFromTxObjectCfg(uint8  DevId,uint8 *pObjectIndex);
STATIC Std_ReturnType Can_SearchControllerFromControllerCfg(uint8  DevId,uint8 *pControllerIndex);
STATIC void  Can_Write(uint8  DevId,PduInfoType PduInfo);
STATIC void  Can_TansmitIsrProcess(uint8 DevId);
STATIC void  Can_ReceiveIsrProcess(uint8 DevId);
STATIC void  Can_ErrorIsrProcess(uint8 DevId);
STATIC void  Can_InitController(uint8 DevId);
#endif

/*********************************************
         正常ID转换成S12规定的ID格式
 *********************************************/
/*扩展帧*/
#define CAN_R0_EID(x)		((uint8)(((x) >> 21) & 0xff))   		/*ID28~ID21*/ 
#define CAN_R1_EID(x)		((uint8)(((x) >> 15) & 0x07) | (uint8)(((x) >> 13) & 0xe0) | 0x18)/*ID17~ID15,ID20~ID18,SRR=1,IDE=1*/
#define CAN_R2_EID(x)		((uint8)(((x) >> 7) & 0xff)) 	   	/*ID14~ID07*/
#define CAN_R3_EID(x,y)		((uint8)  ((x) << 1) | (uint8)(y))	/*ID06~ID00,y=RTR*/
/*********************/
/*标准帧*/
#define CAN_R0_SID(x)		((uint8)(((x) >> 3) & 0xff))							/*ID10~ID3*/
#define CAN_R1_SID(x,y)		((uint8)(((x) << 5) & 0xe0)) | (((uint8)(y)) << 4) 	/*ID2~ID0,y=RTR,IDE=0*/

/************************************************************
* 函数名称:Can_Init
* 函数描述:Can驱动模块初始化,该函数需要将模块静态配置的所有控制器初始化.
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性: 不可重入
* 备注	  :
*************************************************************/
void  Can_Init(void)
{
	uint8  ControllerIndex = 0u;
	uint8  ControllerId = 0u;
	
	/********************/
	for(ControllerIndex=0u;ControllerIndex<(Can_Cfg.NumOfController);ControllerIndex++)
	{
		ControllerId = Can_Cfg.pControllerCfg[ControllerIndex].ControllerId;
		Can_InitController(ControllerId);
	}
	OSAL_ENTER_CRITICAL();
	Can_MkCtrl.MkStatus = CAN_INIT;
	OSAL_EXIT_CRITICAL();
}

/************************************************************
* 函数名称:Can_EnableTxInterrupt
* 函数描述:使能DevId指定Can控制器发送中断;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
void  Can_EnableTxInterrupt(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENABLE_TXINTERRUPT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENABLE_TXINTERRUPT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTIER.Bits.TXEIE0 = 1u;
}


/************************************************************
* 函数名称:Can_DisableTxInterrupt
* 函数描述:禁止DevId指定Can控制器发送中断;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
void  Can_DisableTxInterrupt(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_DISABLE_TXINTERRUPT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_DISABLE_TXINTERRUPT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTIER.Bits.TXEIE0 = 0u;
}

/************************************************************
* 函数名称:Can_RequestTransmitterMessageAbort
* 函数描述:请求终止发送指定控制器硬件Buffer中的Pending报文;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
void  Can_RequestTransmitterMessageAbort(uint8  DevId)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_REQUESTMESSAGEABORT_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_REQUESTMESSAGEABORT_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;	

	pCanReg->CANTARQ.Bits.ABTRQ0 = 1u;
}

/************************************************************
* 函数名称:Can_EnterStopMode
* 函数描述:停止DevId指定Can控制器工作;
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
void  Can_EnterStopMode(uint8  DevId)
{
#if 0
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTERSTOP_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTERSTOP_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);

	/*进入初始化模式,CAN控制器停止*/	
	Can_EnterInitMode(BaseAddr);
#endif
}
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
void  Can_GetControllerStatus(uint8  DevId,uint8 *pCanStatus)
{
	uint32 BaseAddr = 0ul;
	uint8  ControllerIndex = 0u;	
	Std_ReturnType  ret = E_NOT_OK;
	volatile Can_RegType *pCanReg = NULL_PTR;

	(*pCanStatus) = 0xFFu; 
	/******************************/
	if(CAN_UNINIT == Can_MkCtrl.MkStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_UNINIT);				
#endif
		return;
	}
	
	if(NULL_PTR == pCanStatus)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}
	
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerIndex);
	if(E_NOT_OK == ret)
	{
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_GETCONTROLLERSTATUS_ID,
						CAN_E_PARAM_INVALID);				
#endif
		return;
	}	
	
	/*************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;
    if(3u == (pCanReg->CANRFLG.MergedBits.grpTSTAT))
	{
		/*控制器处于"BusOff"状态*/
		(*pCanStatus) = 1u;
	}
	else
	{
		/*控制器处于"TxOK","TxWRN" "TxERR"状态*/
		(*pCanStatus) = 0u;
	}
}

/************************************************************
					静态函数实现
 ***********************************************************/
#if	1
/************************************************************
* 函数名称:Can_CalcBaseAddrByControllerId
* 函数描述:根据控制器ID,计算控制器寄存器基地址;
* 输入参数:DevId:CAN控制器ID;
* 输出参数:(*pBaseAddr):控制器寄存器基地址；
* 输入/输出参数:无
* 可重入性:可重入
* 备注	  :
*************************************************************/
STATIC void Can_CalcBaseAddrByControllerId(uint8 DevId,uint32 *pBaseAddr)
{
	switch(DevId)
	{
		case CAN_CONTROLLER_0:
			 (*pBaseAddr) = 0x140u;
			 break;
			 
		case CAN_CONTROLLER_1:
			 (*pBaseAddr) = 0x180u;
			 break;
			 
		case CAN_CONTROLLER_2:
			 (*pBaseAddr) = 0x1C0u;
			 break;
			 
		case CAN_CONTROLLER_3:
			 (*pBaseAddr) = 0x200u;
			 break;
			 
		case CAN_CONTROLLER_4:
			 (*pBaseAddr) = 0x280u;
			 break;	
			 
		default:
#if 0
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		/*参数无效*/
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_CALCBASEADDRBYCONTROLLERID_ID,
						CAN_E_PARAM_INVALID);				
#endif
#endif
			break;
	}
}

/************************************************************
* 函数名称:Can_EnterInitMode
* 函数描述:Can控制器进入初始化模式。
* 输入参数:BaseAddr:设备寄存器基地址;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :
*************************************************************/
STATIC void  Can_EnterInitMode(uint32 BaseAddr)
{
	volatile uint16   WaitTimes = 0u;
	volatile Can_RegType *pCanReg = NULL_PTR;

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	/**********************************/
	/*请求进入初始化模式*/
	pCanReg->CANCTL0.Bits.INITRQ = 1u;  
	for(WaitTimes=0u;WaitTimes<CAN_REQUEST_CONFIRM_TIMES;WaitTimes++)
	{
		if(1u == pCanReg->CANCTL1.Bits.INITAK)
		{
			/*确认控制器进入初始化模式*/
			break;
		}
	}
	if(CAN_REQUEST_CONFIRM_TIMES == WaitTimes)
	{
		/*控制器进入初始化模式,失败*/
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_ENTER_INITMODE,
						CAN_E_ENTER_INITMODE_INVALID);			
#endif
	}	
}

/************************************************************
* 函数名称:Can_ExitInitMode
* 函数描述:Can控制器退出初始化模式。
* 输入参数:BaseAddr:设备寄存器基地址;
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  :
*************************************************************/
STATIC void  Can_ExitInitMode(uint32 BaseAddr)
{
	volatile uint16   WaitTimes = 0u;
	volatile Can_RegType *pCanReg = NULL_PTR;

	/******************************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	/*请求退出初始化模式*/
	pCanReg->CANCTL0.Bits.INITRQ = 0u;  
	for(WaitTimes=0u;WaitTimes<CAN_REQUEST_CONFIRM_TIMES;WaitTimes++)
	{
		if(0u == pCanReg->CANCTL1.Bits.INITAK)
		{
			/*确认控制器退出初始化模式*/
			break;
		}
	}
	if(CAN_REQUEST_CONFIRM_TIMES == WaitTimes)
	{
		/*控制器退出初始化模式,失败*/
#if(STD_ON == CAN_DEV_ERROR_DETECT)
		Det_ReportError(MODULE_ID_CAN,
						0u,
						CAN_EXIT_INITMODE,
						CAN_E_EXIT_INITMODE_INVALID);			
#endif
	}	
}

/************************************************************
* 函数名称:Can_ConfigBaudRate
* 函数描述:配置CAN控制器波特率
* 输入参数:BaseAddr:设备寄存器基地址;
           Bps:待配置波特率类型
* 输出参数:无
* 输入/输出参数:无
* 可重入性:不可重入
* 备注	  : 该函数的波特率初值是在模块
            BusClock=50兆的情况下进行的计算.
            Bps = fBus/(Prescaler value *(1+TimeSegment1+TimeSegment2))
            
            OscClock=4M的情况下进行的计算  modify by sunj 2019/1/4 14:54
            Bps = fOsc/(Prescaler value *(1+TimeSegment1+TimeSegment2))
            仅对100k 125k 250k 500K做了修改,并通过测试   1000k未调通
*************************************************************/
STATIC void  Can_ConfigBaudRate(uint32 BaseAddr,Can_ControllerBpsType Bps)
{
	volatile Can_RegType *pCanReg = NULL_PTR;

	/*********************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	switch(Bps)
	{
		case CAN_BPS_100K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 3u;//24  
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 5u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 2u;//12
			 break;

		case CAN_BPS_125K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 1u;//19
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 4u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 9u;//12
			 break;
			 
		case CAN_BPS_250K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u; //9
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 4u; //5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 9u;//12
			 break;
			 
		case CAN_BPS_500K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u;//4
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 1u;//5
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 4u;//12
			 break;
			 
		case CAN_BPS_1000K:
			 pCanReg->CANBTR0.MergedBits.grpSJW = 0u; /*1 tq clock cycle*/
			 pCanReg->CANBTR0.MergedBits.grpBRP = 0u;//9
			 pCanReg->CANBTR1.Bits.SAMP = 0u; 		  /*One sample per bit*/
			 pCanReg->CANBTR1.MergedBits.grpTSEG_20 = 1u;//1
			 pCanReg->CANBTR1.MergedBits.grpTSEG_10 = 0u;//1
			 break;
			 
		default:
			 break;			 
	}    	
}

/************************************************************
* 函数名称:Can_ConfigFilter
* 函数描述:配置CAN控制器滤波器
* 输入参数:BaseAddr:设备寄存器基地址;
           FilterNum:设备待配置滤波器个数;
           pFilterCfg:设备待配置滤波器内容首地址;
* 输出参数:无
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  Can_ConfigFilter(uint32 BaseAddr,Can_IdType IdType,uint8 FilterNum,Can_FilterCfgType *pFilterCfg)
{
    uint32  FilterMaskId = 0ul;
	uint32  FilterAcceptId = 0ul;
	volatile Can_RegType *pCanReg = NULL_PTR;
	
	/*********************/
	pCanReg = (volatile Can_RegType *)BaseAddr;

	switch(FilterNum)
	{
		case 2u:
			 /*CANIDAC,选择2个32位滤波器*/
			 pCanReg->CANIDAC.Bits.IDAM0 = 0u;
			 pCanReg->CANIDAC.Bits.IDAM1 = 0u;
             if(CANID_STANDARD == IdType)
         	 {	
         	 	/*==标准帧==*/
				/*MaskId*/
				FilterMaskId = pFilterCfg[0].FilterMaskId;
				pCanReg->CANIDMR0.Byte = CAN_R0_SID(FilterMaskId); 
				pCanReg->CANIDMR1.Byte = CAN_R1_SID(FilterMaskId,0) & 0xE7;   /*Bit4=0,Bit3=0:标示需要比较(RTR && IDE)位*/
				FilterMaskId = pFilterCfg[1].FilterMaskId;
				pCanReg->CANIDMR4.Byte = CAN_R0_SID(FilterMaskId);
				pCanReg->CANIDMR5.Byte = CAN_R1_SID(FilterMaskId,0) & 0xE7;   /*Bit4=0,Bit3=0:标示需要比较(RTR && IDE)位*/ 

				/*AcceptId*/
				FilterAcceptId = pFilterCfg[0].FilterAcceptId;
				pCanReg->CANIDAR0.Byte = CAN_R0_SID(FilterAcceptId);
				pCanReg->CANIDAR1.Byte = CAN_R1_SID(FilterAcceptId,0); /*Bit4=0,Bit3=0:标示只接收(标准帧&&数据帧)*/
				FilterAcceptId = pFilterCfg[1].FilterAcceptId;
				pCanReg->CANIDAR4.Byte = CAN_R0_SID(FilterAcceptId);
				pCanReg->CANIDAR5.Byte = CAN_R1_SID(FilterAcceptId,0); /*Bit4=0,Bit3=0:标示只接收(标准帧&&数据帧)*/
         	 }
			 else
		 	 {
		 	 	/*==扩展帧==*/
				/*MaskId*/
				FilterMaskId = pFilterCfg[0].FilterMaskId;
				pCanReg->CANIDMR0.Byte = CAN_R0_EID(FilterMaskId);
				pCanReg->CANIDMR1.Byte = CAN_R1_EID(FilterMaskId) & 0xE7;/*SRR(Bit4)=0,IDE(Bit3)=0:标示需要比较SRR && IDE位*/  
				pCanReg->CANIDMR2.Byte = CAN_R2_EID(FilterMaskId);
				pCanReg->CANIDMR3.Byte = CAN_R3_EID(FilterMaskId,0);     /*RTR(Bit0)=0:标示需要比较RTR位*/
				FilterMaskId = pFilterCfg[1].FilterMaskId;
				pCanReg->CANIDMR4.Byte = CAN_R0_EID(FilterMaskId);
				pCanReg->CANIDMR5.Byte = CAN_R1_EID(FilterMaskId) & 0xE7;/*SRR(Bit4)=0,IDE(Bit3)=0:标示需要比较SRR && IDE位*/ 
				pCanReg->CANIDMR6.Byte = CAN_R2_EID(FilterMaskId);
				pCanReg->CANIDMR7.Byte = CAN_R3_EID(FilterMaskId,0);     /*RTR(Bit0)=0:标示需要比较RTR位*/

				/*AcceptId*/
				FilterAcceptId = pFilterCfg[0].FilterAcceptId;
				pCanReg->CANIDAR0.Byte = CAN_R0_EID(FilterAcceptId);
				pCanReg->CANIDAR1.Byte = CAN_R1_EID(FilterAcceptId); 	/*SRR(Bit4)=1,IDE(Bit3)=1:标示只接收扩展帧*/  
				pCanReg->CANIDAR2.Byte = CAN_R2_EID(FilterAcceptId);
				pCanReg->CANIDAR3.Byte = CAN_R3_EID(FilterAcceptId,0);  /*RTR(Bit0)=0:标示只接收数据帧*/
				FilterAcceptId = pFilterCfg[1].FilterAcceptId;
				pCanReg->CANIDAR4.Byte = CAN_R0_EID(FilterAcceptId);
				pCanReg->CANIDAR5.Byte = CAN_R1_EID(FilterAcceptId); 	/*SRR(Bit4)=1,IDE(Bit3)=1:标示只接收扩展帧*/   
				pCanReg->CANIDAR6.Byte = CAN_R2_EID(FilterAcceptId);
				pCanReg->CANIDAR7.Byte = CAN_R3_EID(FilterAcceptId,0);  /*RTR(Bit0)=0:标示只接收数据帧*/
		 	 }
			 break;
			 
		case 4u:
			 /*暂不支持4个16位滤波*/
			 break;
			 
		case 8u:
			 /*暂不支持8个8位滤波*/
			 break;
			 
		default:
			 break;
	}
}
/************************************************************
* 函数名称:Can_SearchControllerFromRxObjectCfg
* 函数描述:在邮箱的静态配置中查找DevId对应配置索引;
* 输入参数:DevId:控制器ID号;
* 输出参数:(*pObjectIndex):静态配置索引号;
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromRxObjectCfg(uint8  DevId,uint8 *pObjectIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;
		
	for(Index=0u;Index<(Can_Cfg.NumOfHardwareObject);Index++)
	{
		if(   (DevId == Can_Cfg.pHardwareObjectCfg[Index].pCanControlRef->ControllerId)
			&&(CANID_RECEIVE == Can_Cfg.pHardwareObjectCfg[Index].CanObjectTrans))
		{
			/*查找到关联该控制器的邮箱*/
			(*pObjectIndex) = Index;
			break;
		}
	}
	if(Index < Can_Cfg.NumOfHardwareObject)
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

/************************************************************
* 函数名称:Can_SearchControllerFromRxObjectCfg
* 函数描述:在邮箱的静态配置中查找DevId对应配置索引;
* 输入参数:DevId:控制器ID号;
* 输出参数:(*pObjectIndex):静态配置索引号;
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromTxObjectCfg(uint8  DevId,uint8 *pObjectIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;
		
	for(Index=0u;Index<(Can_Cfg.NumOfHardwareObject);Index++)
	{
		if(   (DevId == Can_Cfg.pHardwareObjectCfg[Index].pCanControlRef->ControllerId)
			&&(CANID_TRANSMIT == Can_Cfg.pHardwareObjectCfg[Index].CanObjectTrans))
		{
			/*查找到关联该控制器的邮箱*/
			(*pObjectIndex) = Index;
			break;
		}
	}
	if(Index < Can_Cfg.NumOfHardwareObject)
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

/************************************************************
* 函数名称:Can_SearchControllerIndex
* 函数描述:在控制器静态配置中查找DevId对应的配置索引;
* 输入参数:DevId:控制器ID号;
* 输出参数:(*pObjectIndex):静态配置控制器索引号;
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC Std_ReturnType  Can_SearchControllerFromControllerCfg(uint8  DevId,uint8 *pControllerIndex)
{
	uint8  Index = 0u;
	Std_ReturnType ret = E_NOT_OK;

	for(Index=0u;Index<(Can_Cfg.NumOfController);Index++)
	{
		if(DevId == Can_Cfg.pControllerCfg[Index].ControllerId)
		{
			/*查找到指定控制器的配置*/
		   (*pControllerIndex) = Index;
		   break;
		}
	}
	if(Index < (Can_Cfg.NumOfController))
	{
		ret = E_OK;
	}
	else
	{
		ret = E_NOT_OK;
	}
	return(ret);
}

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
STATIC void  Can_Write(uint8  DevId,PduInfoType PduInfo)
{
    Std_ReturnType  ret = E_NOT_OK;
	uint8 HardTxObjectIndex = 0u;
	uint32 BaseAddr = 0ul;
	Can_IdType  IdCfgType;
	volatile Can_RegType  *pCanReg = NULL_PTR;
    uint8  TxBuffNum = 0u;

	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;

	/*选择发送缓存*/
	pCanReg->CANTBSEL.MergedBits.grpTX = pCanReg->CANTFLG.MergedBits.grpTXE;
	TxBuffNum = pCanReg->CANTBSEL.MergedBits.grpTX;
	/******************************/
	ret = Can_SearchControllerFromTxObjectCfg(DevId,&HardTxObjectIndex);
	if(E_NOT_OK == ret)
	{
		/*该控制器无发送邮箱配置,默认发送扩展帧*/
		IdCfgType = CANID_EXTENDED;
	}
	else
	{
		IdCfgType = Can_Cfg.pHardwareObjectCfg[HardTxObjectIndex].CanIdType;
	}
	/* ID */
	if(CANID_EXTENDED == IdCfgType)
	{
		/*扩展帧*/
		pCanReg->CANTXIDR0.Byte = CAN_R0_EID(PduInfo.PduId);
		pCanReg->CANTXIDR1.Byte = CAN_R1_EID(PduInfo.PduId);
		pCanReg->CANTXIDR2.Byte = CAN_R2_EID(PduInfo.PduId);
		pCanReg->CANTXIDR3.Byte = CAN_R3_EID(PduInfo.PduId,0);
	}
	else
	{
		/*标准帧*/
		pCanReg->CANTXIDR0.Byte = CAN_R0_SID(PduInfo.PduId);
		pCanReg->CANTXIDR1.Byte = CAN_R1_SID(PduInfo.PduId,0);
	}
	/* DLC */
	pCanReg->CANTXDLR.MergedBits.grpDLC = PduInfo.PduLength;

	/* DATA */
	pCanReg->CANTXDSR0.Byte = PduInfo.PduData[0];
	pCanReg->CANTXDSR1.Byte = PduInfo.PduData[1];
	pCanReg->CANTXDSR2.Byte = PduInfo.PduData[2];
	pCanReg->CANTXDSR3.Byte = PduInfo.PduData[3];
	pCanReg->CANTXDSR4.Byte = PduInfo.PduData[4];
	pCanReg->CANTXDSR5.Byte = PduInfo.PduData[5];
	pCanReg->CANTXDSR6.Byte = PduInfo.PduData[6];
	pCanReg->CANTXDSR7.Byte = PduInfo.PduData[7];	

	/* 清除选择发送buffer的空标示 */
	pCanReg->CANTFLG.MergedBits.grpTXE = TxBuffNum;
}

/************************************************************
* 函数名称:Can0_TansmitIsrProcess
* 函数描述:Can控制器发送中断处理公用函数;
* 输入参数:DevId:控制器ID号;
* 输出参数:无
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void  Can_TansmitIsrProcess(uint8 DevId)
{
	PduInfoType  PduInfo;
	Std_ReturnType ret = E_NOT_OK;

	/***********************/
	/*added by chenms 2018-5-23,am10:10*/
	CanIf_TxConfirmHook(DevId);
	
	/***********************/
	ret = CanIf_GetNextPacket(DevId,&PduInfo);
	if(E_NOT_OK == ret)
	{
		/*报文发送完成，通知上层模块停止发送*/
		CanIf_TransmitQueueIsEmpty(DevId);
	}
	else
	{
		/*发送报文*/
		Can_Write(DevId,PduInfo);
	}
}

/************************************************************
* 函数名称:Can_ReceiveIsrProcess
* 函数描述:Can控制器接收中断处理公用函数;
* 输入参数:
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void Can_ReceiveIsrProcess(uint8 DevId)
{
    uint8  ID[4] = {0u};
	uint32 BaseAddr = 0ul;
	PduInfoType  PduInfo;
	volatile Can_RegType  *pCanReg = NULL_PTR;
    
	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;
	
	/***********/
	/*重组CanId*/
	if(1u == pCanReg->CANRXIDR1.Bits.IDE)
	{
		/*扩展帧ID*/		
		ID[0] = pCanReg->CANRXIDR0.Byte; /*ID28~ID21*/	
		ID[1] = pCanReg->CANRXIDR1.Byte; /*ID20~ID15*/
		ID[2] = pCanReg->CANRXIDR2.Byte; /*ID14~ID7 */	
		ID[3] = pCanReg->CANRXIDR3.Byte; /*ID6~ID0  */
		PduInfo.PduId =   (((uint32) ID[0]) << 21u)\
			            | (((uint32)(ID[1] & 0xE0))<< 13u)\
			            | (((uint32)(ID[1] & 0x07))<< 15u)\
			            | (((uint32)ID[2]) << 7u)\
			            | (((uint32)(ID[3] & 0xFE))>> 1u);
	}
	else
	{
		/*标准帧ID*/		
		ID[0] = pCanReg->CANRXIDR0.Byte; 	/*ID10~ID3*/		
		ID[1] = pCanReg->CANRXIDR1.Byte; 	/*ID2 ~ID0*/
		PduInfo.PduId =  (((uint32) ID[0]) << 3u)|(((uint32)(ID[1] & 0xE0))>>5u);
	}	
	/*Dlc*/
	PduInfo.PduLength = (pCanReg->CANRXDLR.Byte) & 0x0F;	

	/*Data0~Data7*/
	PduInfo.PduData[0]= pCanReg->CANRXDSR0.Byte;
	PduInfo.PduData[1]= pCanReg->CANRXDSR1.Byte;
	PduInfo.PduData[2]= pCanReg->CANRXDSR2.Byte;
	PduInfo.PduData[3]= pCanReg->CANRXDSR3.Byte;
	PduInfo.PduData[4]= pCanReg->CANRXDSR4.Byte;
	PduInfo.PduData[5]= pCanReg->CANRXDSR5.Byte;
	PduInfo.PduData[6]= pCanReg->CANRXDSR6.Byte;
	PduInfo.PduData[7]= pCanReg->CANRXDSR7.Byte;

	/*清除接收完成中断标示*/
	pCanReg->CANRFLG.Bits.RXF = 1u;

    /*通知CanIf模块保存报文*/
	CanIf_RxIndication(DevId,PduInfo);  

	/*通知ComM模块接收到报文*/
	ComM_RxIndication(DevId);

    /*通知CanIf模块进行部分报文特殊处理*/
    /*added by chenms 2018-5-3*/
	CanIf_RxIndicationHook(DevId,&PduInfo);
}


/************************************************************
* 函数名称:Can_ErrorIsrProcess
* 函数描述:Can控制器错误中断处理公用函数;
* 输入参数:
* 输出参数:
* 输入/输出参数:
* 可重入性:
* 备注	  :
*************************************************************/
STATIC void Can_ErrorIsrProcess(uint8 DevId)
{
	uint32 BaseAddr = 0ul;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	/******************************/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType  *)BaseAddr;

	if(1u == pCanReg->CANRFLG.Bits.OVRIF)
	{
		/*控制器产生过载错误中断*/
		pCanReg->CANRFLG.Bits.OVRIF = 1u; /*清除过载错误*/
	}
	if(1u == pCanReg->CANRFLG.Bits.CSCIF)
	{
		/*控制器产生进入或退出bufOff中断*/
		if(3u == pCanReg->CANRFLG.MergedBits.grpTSTAT)
		{
			/*产生BusOff进入中断*/
			ComM_BusOffIndication(DevId);
		}
		else
		{
			/*退出BusOff中断*/
			/*TOdo*/
		}
		pCanReg->CANRFLG.Bits.CSCIF = 1u; /*清除状态改变标示*/
	}
}

/************************************************************
* 函数名称:Can_InitController
* 函数描述:初始化指定控制器
* 输入参数:DevId:Can控制器设备ID号;
* 输出参数:无
* 输入/输出参数:无
* 可重入性: 不可重入
* 备注	  :
*************************************************************/
STATIC void  Can_InitController(uint8 DevId)
{
	uint8  HardRxObjectIndex = 0u;
	uint8  ControllerCfgIndex   = 0u;
	uint8  FilterNum = 0u;
	uint32 BaseAddr  = 0ul;
	Can_IdType  IdCfgType;
	Can_ControllerBpsType BaudRate = 0u;
	Can_FilterCfgType  *pFilterCfg = NULL_PTR;
	volatile Can_RegType  *pCanReg = NULL_PTR;
	Std_ReturnType ret = E_NOT_OK;
	volatile uint16 WaitTimes = 0u;

	/****************************/  
	ret = Can_SearchControllerFromControllerCfg(DevId,&ControllerCfgIndex);
	if(E_NOT_OK == ret)
	{
	    /*DevId未配置*/
//#if(STD_ON == CAN_DEV_ERROR_DETECT)
//		Det_ReportError(MODULE_ID_CAN,
//						0u,
//						CAN_INITCONTROLLER_ID,
//						CAN_E_PARAM_INVALID);				
//#endif
		return;
	}
	/****************************/
	/*计算控制器基地址*/
	Can_CalcBaseAddrByControllerId(DevId,&BaseAddr);
	pCanReg = (volatile Can_RegType *)BaseAddr;

    /****************************************
             初始化模式下,控制器配置
     ***************************************/
	/*进入初始化模式*/
	Can_EnterInitMode(BaseAddr);

	/*使能CAN控制器*/
	pCanReg->CANCTL1.Bits.CANE   = 1u; 
	
	/*选择晶振时钟OscClk----modify by sunj 2019/1/4 14:54*/
	pCanReg->CANCTL1.Bits.CLKSRC = 0u; 

	/*退出侦听模式*/
	pCanReg->CANCTL1.Bits.LISTEN = 0u; 
			
	/*bus-Off自动恢复*/
	pCanReg->CANCTL1.Bits.BORM   = 0u;

	/*控制器波特率配置*/
	BaudRate  = Can_Cfg.pControllerCfg[ControllerCfgIndex].BaudRate;
	Can_ConfigBaudRate(BaseAddr,BaudRate);

	/*查找指定控制器对应的接收CANID类型*/
	ret = Can_SearchControllerFromRxObjectCfg(DevId,&HardRxObjectIndex);
	if(E_NOT_OK == ret)
	{
		/*该控制器无接收邮箱配置,默认滤波扩展帧*/
		IdCfgType = CANID_EXTENDED;
	}
	else
	{
		IdCfgType = Can_Cfg.pHardwareObjectCfg[HardRxObjectIndex].CanIdType;		
	}
	/*控制器接收滤波配置*/
	FilterNum = Can_Cfg.pControllerCfg[ControllerCfgIndex].NumOfControllerFilter;
	pFilterCfg= Can_Cfg.pControllerCfg[ControllerCfgIndex].pControllerFilterCfg; 
	if((0 == FilterNum)||(NULL_PTR == pFilterCfg))
	{
		/*滤波是以邮箱作为对象,进行配置*/
	}
	else
	{
		/*滤波是以控制器作为对象,进行配置*/			
		Can_ConfigFilter(BaseAddr,IdCfgType,FilterNum,pFilterCfg);
	}

	/*退出初始化模式*/
	Can_ExitInitMode(BaseAddr);

    /**************************************
           正常工作模式下,控制器配置
     **************************************/
	pCanReg->CANRIER.Bits.WUPIE = 0u; /*禁止唤醒中断*/
	pCanReg->CANRIER.Bits.OVRIE = 1u; /*使能过载错误检测*/
	pCanReg->CANRIER.Bits.RXFIE = 1u; /*使能接收缓存满中断*/
	pCanReg->CANRIER.Bits.CSCIE = 1u; /*使能CAN状态改变中断*/
	pCanReg->CANRIER.MergedBits.grpRSTATE = 1u; /*响应BusOff*/
	pCanReg->CANRIER.MergedBits.grpTSTATE = 1u;	/*响应BusOff*/

	/***************************************/
	for(WaitTimes=0u;WaitTimes<50000u;WaitTimes++)
	{
		if(1u == pCanReg->CANCTL0.Bits.SYNCH)
		{
		    /*同步入网络成功*/
			break;
		}
	}
	if(50000u == WaitTimes)
	{
		/*CAN结点同步不到网络*/
//#if(STD_ON == CAN_DEV_ERROR_DETECT)
//		Det_ReportError(MODULE_ID_CAN,
//						DevId,
//						CAN_INITCONTROLLER_ID,
//						CAN_E_SYNCH_ERROR);				
//#endif
	}
}


#endif


/************************************************************
* 函数名称:Can0_TansmitIsr_C
* 函数描述:Can0控制器发送完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can0_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* 函数名称:Can0_ReceiveIsr_C
* 函数描述:Can0接收完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can0_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* 函数名称:Can0_ErrorIsr_C
* 函数描述:Can0控制器错误中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :过载错误中断或总线busoff中断
*************************************************************/
void  Can0_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_0);
}

/************************************************************
* 函数名称:Can1_TansmitIsr_C
* 函数描述:Can1控制器发送完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can1_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* 函数名称:Can1_ReceiveIsr_C
* 函数描述:Can1接收完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can1_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* 函数名称:Can1_ErrorIsr_C
* 函数描述:Can1控制器错误中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :过载错误中断或总线busoff中断
*************************************************************/
void  Can1_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_1);
}

/************************************************************
* 函数名称:Can2_TansmitIsr_C
* 函数描述:Can2控制器发送完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can2_TansmitIsr_C(void)
{
    Can_TansmitIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* 函数名称:Can2_ReceiveIsr_C
* 函数描述:Can2接收完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can2_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* 函数名称:Can2_ErrorIsr_C
* 函数描述:Can2控制器错误中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :过载错误中断或总线busoff中断
*************************************************************/
void  Can2_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_2);
}

/************************************************************
* 函数名称:Can3_TansmitIsr_C
* 函数描述:Can3控制器发送完成中断函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can3_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* 函数名称:Can3_ReceiveIsr_C
* 函数描述:Can3接收完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can3_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* 函数名称:Can3_ErrorIsr_C
* 函数描述:Can3控制器错误中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :过载错误中断或总线busoff中断
*************************************************************/
void  Can3_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_3);
}

/************************************************************
* 函数名称:Can4_TansmitIsr_C
* 函数描述:Can4控制器发送完成中断函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can4_TansmitIsr_C(void)
{
   Can_TansmitIsrProcess(CAN_CONTROLLER_4);
}

/************************************************************
* 函数名称:Can4_ReceiveIsr_C
* 函数描述:Can4接收完成中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :
*************************************************************/
void  Can4_ReceiveIsr_C(void)
{
	Can_ReceiveIsrProcess(CAN_CONTROLLER_4);
}

/************************************************************
* 函数名称:Can4_ErrorIsr_C
* 函数描述:Can4控制器错误中断
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 备注	  :过载错误中断或总线busoff中断
*************************************************************/
void  Can4_ErrorIsr_C(void)
{
	Can_ErrorIsrProcess(CAN_CONTROLLER_4);
}

