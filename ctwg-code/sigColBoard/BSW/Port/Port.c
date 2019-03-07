/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Port.c
* 功能描述      : Port模块源文件(.c)定义
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名         版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms          NEW
**------------------------------------------------------------------------------------------------*/

/**************************** 引用部分 *************************************/
#include "Port.h"
#include "drv_sci.h"
#include "drv_pio.h"  /*add by chenms 2017-10-27*/
#include "Osal.h"
/**********************************************************
						运行时数据结构定义
 **********************************************************/
/* 模块状态 */
typedef enum
{
    PORT_UNINIT = 0u,  /*模块未初始化*/
    PORT_INITI  = 1u
}Port_MkStateType;

typedef  struct
{
	Port_MkStateType  MkState;
}Port_MkCtrlType;

/**********************************************************
						运行时数据定义
 **********************************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Port_MkCtrlType Port_MkCtrl;
#pragma DATA_SEG DEFAULT


/*****************************声明部分 *************************************/
#if 1
STATIC void Port_CalcPinRegPhyAddress(uint8 PinGroupNum,uint16 *pDataRegAddr,uint16 *pDireRegAddr);
#endif

/*****************************实现部分 *************************************/

/************************************************************
* 函数名称: Port_Init
* 函数描述: Port模块初始化.
* 输入参数: (*ConfigPtr):模块静态配置参数;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  : 该函数只初始化配置为"PORT_PIN_MODE_DIO"模式的IO口;
            其他模式的IO口被忽略;
*************************************************************/
void   Port_Init(const Port_ConfigType *ConfigPtr)
{
	uint8  Index = 0u;
	uint8  PinType = 0xFFu;
	Port_PinType  DrvPinId = 0xFFu;
	boolean  PinDirection= 0u;   
	boolean  Initlevel = 0u;
	
	/***********************/
#if(STD_ON == PORT_DEV_ERROR_DETECT)
	if( NULL_PTR == ConfigPtr )
	{
		Det_ReportError(MODULE_ID_PORT,
						0u,
						PORT_INIT_ID,
						PORT_E_PARAM_CONFIG);
	    return;
	}
#endif

	/***********************/
	for(Index=0u;Index<(ConfigPtr->PortNumberOfPortPins);Index++)
	{
		if(PORT_PIN_MODE_DIO == ConfigPtr->Port_PinConfiguration[Index].PortPinMode)
		{
			/* 引脚配置工作模式 = DIO */
			PinType  = ConfigPtr->Port_PinConfiguration[Index].PortType;
			DrvPinId = ConfigPtr->Port_PinConfiguration[Index].PortDrvPinId;
			Initlevel= ConfigPtr->Port_PinConfiguration[Index].PortPinLevelValue;
			PinDirection = ConfigPtr->Port_PinConfiguration[Index].PortPinDirection;
			switch(PinType)
			{
				case PORT_A:
					 (void)drv_pioa_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pioa_tris(DrvPinId, (uint8)PinDirection);
					 break;

				case PORT_B:
					 (void)drv_piob_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piob_tris(DrvPinId, (uint8)PinDirection);
					 break;

				case PORT_C:
					 (void)drv_pioc_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pioc_tris(DrvPinId, (uint8)PinDirection);
					 break;

				case PORT_D:
					 (void)drv_piod_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piod_tris(DrvPinId, (uint8)PinDirection);
					 break;

				case PORT_E:
					 (void)drv_pioe_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pioe_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_K:
					 (void)drv_piok_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piok_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_T:
					 (void)drv_piot_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piot_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_S:
					 (void)drv_pios_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pios_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_M:
					 (void)drv_piom_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piom_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_P:
					 (void)drv_piop_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_piop_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_H:
					 (void)drv_pioh_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pioh_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_J:
					 (void)drv_pioj_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pioj_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_PAD:
					 (void)drv_pad_write(DrvPinId,(uint8)Initlevel);
					 (void)drv_pad_tris(DrvPinId, (uint8)PinDirection);
					 break;
					 
				case PORT_R:
					 break;
					 
				case PORT_L:
					 break;
					 
				case PORT_F:
					 break;
					 
				default:
					 break;
			}
		}
		else
		{
			/* 引脚配置工作模式 != DIO, 
               Nothing to do */
		}
	}
   	/***********************/
	OSAL_ENTER_CRITICAL();
	Port_MkCtrl.MkState = PORT_INITI;
	OSAL_EXIT_CRITICAL();
}


/************************************************************
* 函数名称: Port_SetPinMode
* 函数描述: 设置指定引脚的工作模式.
* 输入参数: PinId:引脚ID号;
			Mode :引脚待修改工作模式;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
void   Port_SetPinMode(Port_PinType PinId, Port_PinModeType Mode)
{
#if 0
	uint8  Index = 0u;
    uint8  PinCfgIndex = 0xFFu;
	
	/**************************/
#if(STD_ON == PORT_DEV_ERROR_DETECT)
	if(PORT_UNINIT == Port_MkCtrl.MkState)
	{
		/*模块未初始化*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((Mode < PORT_PIN_MODE_ADC) || (Mode > PORT_PIN_MODE_SCI))
	{
		/*输入参数Mode错误*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_PARAM_INVALID);	
		return;
	}
#endif

    /***********************************/
	for(Index=0u;Index<(Port_Config.PortNumberOfPortPins);Index++)
	{
		if( PinId == Port_Config.Port_PinConfiguration[Index].PortPinId )
		{
		    break;
		}
	}
	if(Index == Port_Config.PortNumberOfPortPins)
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*输入PinId参数没有静态配置*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
	
    /***********************************/
	PinCfgIndex = Index;
	if(FALSE == (Port_Config.Port_PinConfiguration[PinCfgIndex].PortPinModeChangeable))
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*Pin脚静态配置为不允许动态修改引脚工作模式*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
    /***********************************/
    /*硬件不支持直接设置引脚的模式，直接返回*/
	
	return;	
#endif
}


/************************************************************
* 函数名称: Port_SetPinDirection
* 函数描述: 设置指定引脚的输入/输出方向.
* 输入参数: PinId:引脚ID号;
			Mode :引脚待修改方向;
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
void Port_SetPinDirection(Port_PinType PinId,boolean PinDirection)
{
#if 0
	uint8  Index = 0u;
	uint8  RegData = 0u;
	uint8  PinCfgIndex = 0u;
	uint8  PinOffsetInGroup = 0u;
    uint16 PinGroupDataRegAddr = 0u;
	uint16 PinGroupDireRegAddr = 0u;
	volatile uint8 *pDataRegAddr = NULL_PTR;
	volatile uint8 *pDireRegAddr = NULL_PTR;
	
	/**************************/
#if(STD_ON == PORT_DEV_ERROR_DETECT)
	if(PORT_UNINIT == Port_MkCtrl.MkState)
	{
		/*模块未初始化*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((PORT_PIN_IN != PinDirection) && (PORT_PIN_OUT != PinDirection))
	{
		/*输入参数PinDirection错误*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_PARAM_INVALID);	
		return;
	}
#endif

    /***********************************/
	for(Index=0u;Index<(Port_Config.PortNumberOfPortPins);Index++)
	{
		if( PinId == Port_Config.Port_PinConfiguration[Index].PortPinId )
		{
		    break;
		}
	}
	if(Index == Port_Config.PortNumberOfPortPins)
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*输入PinId参数没有配置*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
	
    /***********************************/
    PinCfgIndex = Index;
	
	if(FALSE == (Port_Config.Port_PinConfiguration[PinCfgIndex].PortPinDirectionChangeable))
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*Pin脚静态配置为不允许动态修改引脚方向*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
	
    /***********************************/
	PinOffsetInGroup = PinId % 8u;
	
	/*计算PinId,数据+方向寄存器绝对地址*/
	Port_CalcPinRegPhyAddress(	PinId,
								&PinGroupDataRegAddr,
								&PinGroupDireRegAddr );

	pDireRegAddr = (volatile uint8 *)PinGroupDireRegAddr;
	RegData      = *pDireRegAddr;
	
	if(PORT_PIN_OUT == PinDirection)
	{
		/* 方向修改为输出 */
		(*pDireRegAddr) = RegData | ((uint8)(1u << PinOffsetInGroup));
	}
	else
	{
		/* 方向修改为输入 */
		(*pDireRegAddr) = RegData & ((uint8)(~(1u << PinOffsetInGroup)));
	}
	return;
#endif
}

/************************************************************
* 函数名称: Port_WritePinValue
* 函数描述: 设置指定引脚的值(高/低电平)
* 输入参数: PinId：Pin脚Id号。
 *          PinLevelValue: Pin脚待设置值.
* 输出参数: 无
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
 * 		如果PinId方向=In, 则直接返回,不进行值更新;			
 * 		如果PinId方向=Out,则进行对应的值更新;
*************************************************************/
void Port_WritePinValue(Port_PinType PinId,boolean PinLevelValue)
{
	uint8  Index = 0u;
	uint8  PinType = 0xFFu;
	Port_PinType  DrvPinId = 0xFFu;

	/**************************/
#if(STD_ON == PORT_DEV_ERROR_DETECT)
	if(PORT_UNINIT == Port_MkCtrl.MkState)
	{
		/*模块未初始化*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_WRITE_PIN_VALUE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((PORT_PIN_LEVEL_LOW != PinLevelValue) 
		&& (PORT_PIN_LEVEL_HIGH != PinLevelValue))
	{
		/*输入参数PinLevelValue不正确*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_WRITE_PIN_VALUE_ID, 
						PORT_E_PARAM_INVALID);	
		return;
	}
#endif

    /***********************************/
	for(Index=0u;Index<(Port_Config.PortNumberOfPortPins);Index++)
	{
		if( PinId == Port_Config.Port_PinConfiguration[Index].PortPinId )
		{
		    break;
		}
	}
	if(Index == Port_Config.PortNumberOfPortPins)
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*输入PinId参数没有配置*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_WRITE_PIN_VALUE_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
    /***********************************/
	if(PORT_PIN_MODE_DIO != Port_Config.Port_PinConfiguration[Index].PortPinMode)
	{
		/*PIN脚配置!=DIO*/
		return;
	}
	PinType  = Port_Config.Port_PinConfiguration[Index].PortType;
	DrvPinId = Port_Config.Port_PinConfiguration[Index].PortDrvPinId;
	switch(PinType)
	{
		case PORT_A:
			 (void)drv_pioa_write(DrvPinId,(uint8)PinLevelValue);
			 break;

		case PORT_B:
			 (void)drv_piob_write(DrvPinId,(uint8)PinLevelValue);
			 break;

		case PORT_C:
			 (void)drv_pioc_write(DrvPinId,(uint8)PinLevelValue);
			 break;

		case PORT_D:
			 (void)drv_piod_write(DrvPinId,(uint8)PinLevelValue);
			 break;

		case PORT_E:
			 (void)drv_pioe_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_K:
			(void) drv_piok_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_T:
			 (void)drv_piot_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_S:
			 (void)drv_pios_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_M:
			 (void)drv_piom_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_P:
			 (void)drv_piop_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_H:
			 (void)drv_pioh_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_J:
			 (void)drv_pioj_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_PAD:
			 (void)drv_pad_write(DrvPinId,(uint8)PinLevelValue);
			 break;
			 
		case PORT_R:
			 break;
			 
		case PORT_L:
			 break;
			 
		case PORT_F:
			 break;
			 
		default:
			 break;
	}	
}

/************************************************************
* 函数名称: Port_ReadPinValue
* 函数描述: 读取指定引脚的值(高/低电平)
* 输入参数: PinId：Pin脚Id号。
* 输出参数: *pPinLevelValue: 读取到的Pin脚电平值
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
void Port_ReadPinValue(Port_PinType PinId,boolean *pPinLevelValue)
{
	uint8  Index = 0u;
	uint8  PinType = 0xFFu;
	Port_PinType  DrvPinId = 0xFFu;

	/**************************/
#if(STD_ON == PORT_DEV_ERROR_DETECT)
	if(PORT_UNINIT == Port_MkCtrl.MkState)
	{
		/*模块未初始化*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_READ_PIN_VALUE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((NULL_PTR == pPinLevelValue))
	{
		/*参数pPinLevelValue无效*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_READ_PIN_VALUE_ID, 
						PORT_E_PARAM_INVALID);	
		return;
	}
#endif

    /***********************************/
	for(Index=0u;Index<(Port_Config.PortNumberOfPortPins);Index++)
	{
		if( PinId == Port_Config.Port_PinConfiguration[Index].PortPinId )
		{
		    break;
		}
	}
	if(Index == Port_Config.PortNumberOfPortPins)
	{
#if(STD_ON == PORT_DEV_ERROR_DETECT)
		/*输入PinId参数没有配置*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_READ_PIN_VALUE_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
	
    /***********************************/
	if(PORT_PIN_MODE_DIO != Port_Config.Port_PinConfiguration[Index].PortPinMode)
	{
		/*PIN脚配置!=DIO*/
		return;
	}
	PinType  = Port_Config.Port_PinConfiguration[Index].PortType;
	DrvPinId = Port_Config.Port_PinConfiguration[Index].PortDrvPinId;
	switch(PinType)
	{
		case PORT_A:
			 (void)drv_pioa_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;

		case PORT_B:
			 (void)drv_piob_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;

		case PORT_C:
			 (void)drv_pioc_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;

		case PORT_D:
			 (void)drv_piod_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;

		case PORT_E:
			 (void)drv_pioe_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_K:
			 (void)drv_piok_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_T:
			 (void)drv_piot_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_S:
			 (void)drv_pios_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_M:
			 (void)drv_piom_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_P:
			 (void)drv_piop_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_H:
			 (void)drv_pioh_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_J:
			 (void)drv_pioj_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_PAD:
			 (void)drv_pad_read(DrvPinId,(uint8 *)pPinLevelValue);
			 break;
			 
		case PORT_R:
			 break;
			 
		case PORT_L:
			 break;
			 
		case PORT_F:
			 break;
			 
		default:
			 break;
	}	

}


#if 1
/************************************************************
* 函数名称: Port_CalcPinRegPhyAddress
* 函数描述: 计算Pin脚的数据寄存器+方向寄存器的物理地址。
* 输入参数: PinId：Pin脚Id号。
* 输出参数: (*pDataRegAddr):数据寄存器地址;
			(*pDireRegAddr):方向寄存器地址;
* 输入/输出参数:无
* 可重入性: 不可重入　
* 备注	  :
*************************************************************/
STATIC void Port_CalcPinRegPhyAddress(Port_PinType PinId,uint16 *pDataRegAddr,uint16 *pDireRegAddr)
{
	uint8  PinGroupNum = 0u;

	PinGroupNum = (PinId / 8u);
  	switch(PinGroupNum)
	{  
	 	case  0x00u:  
	          /*PORT P */
	          (*pDataRegAddr) = (uint16)PORT_DATA_P;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_P;
	          break; 
	          
	 	case  0x01u: 
	          /*PAD0~PAD7,  PORT AD0_1 */
	          (*pDataRegAddr) = (uint16)PORT_DATA_AD0_1;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_AD0_1 ;
	          break;
	          
	 	case  0x02u:
	          /*PAD8~PAD15, PORT AD0_0 */
	          (*pDataRegAddr) = (uint16)PORT_DATA_AD0_0 ;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_AD0_0 ;
	          break;
	          
	 	case  0x03u:  
	          /*PAD16~PAD23, PORT AD1_1 */
	          (*pDataRegAddr) = (uint16)PORT_DATA_AD1_1;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_AD1_1;
	          break;
	          
	 	case  0x04u:
	          /*PAD24~PAD31, PORT AD1_0 */
	          (*pDataRegAddr) = (uint16)PORT_DATA_AD1_0;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_AD1_0;
	          break;
	          
	 	case  0x05u: 
	          /*PORT S    */
	          (*pDataRegAddr) = (uint16)PORT_DATA_S;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_S;
	          break;
	          
	 	case  0x06u:
	          /*PORT M     */
	          (*pDataRegAddr) = (uint16)PORT_DATA_M;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_M;
	          break;
	          
	 	case  0x07u:  
	          /*PORT H    */
	          (*pDataRegAddr) = (uint16)PORT_DATA_H;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_H;
	          break;
	          
	 	case  0x08u:  
	          /*PORT J    */
	          (*pDataRegAddr) = (uint16)PORT_DATA_J;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_J;
	          break;
	          
	 	case  0x09u: 
	          /*PORT L    */
	          (*pDataRegAddr) = (uint16)PORT_DATA_L;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_L;
	          break;
	          
	 	case  0x0Au: 
	          /*PORT F     */
	          (*pDataRegAddr) = (uint16)PORT_DATA_F;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_F;
	          break;
	          
	 	case  0x0Bu: 
	          /*PORT A      */
	          (*pDataRegAddr) = (uint16)PORT_DATA_A;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_A;
	          break;
	          
	 	case  0x0Cu: 
	          /*PORT B       */
	          (*pDataRegAddr) = (uint16)PORT_DATA_B;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_B;
	          break;
	          
	 	case  0x0Du: 
	          /*PORT C      */
	          (*pDataRegAddr) = (uint16)PORT_DATA_C;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_C;
	          break;
	          
		case  0x0Eu: 
	          /*PORT D       */
	          (*pDataRegAddr) = (uint16)PORT_DATA_D;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_D;
	          break;
	          
	 	case 0x0Fu: 
	          /*PORT E        */
	          (*pDataRegAddr) = (uint16)PORT_DATA_E;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_E;
	          break;
	          
	 	case  0x10u: 
	          /*PORT K        */
	          (*pDataRegAddr) = (uint16)PORT_DATA_K;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_K;
	          break;
	          
	 	case  0x11u: 
	          /*PORT T         */
	          (*pDataRegAddr) = (uint16)PORT_DATA_T;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_T;
	          break;
	          
	 	case  0x12u: 
	          /*PORT R          */
	          (*pDataRegAddr) = (uint16)PORT_DATA_R;
	          (*pDireRegAddr) = (uint16)PORT_DIRECTION_R;        
	          break;
	   
	   default:
#if(STD_ON == PORT_DEV_ERROR_DETECT)
			  Det_ReportError(	MODULE_ID_PORT, 
								0u, 
								PORT_INIT_ID, 
								PORT_E_PARAM_CONFIG);
#endif
	   		  break;        
	}
}

#endif

