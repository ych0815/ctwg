/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Port.c
* ��������      : Portģ��Դ�ļ�(.c)����
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����         �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms          NEW
**------------------------------------------------------------------------------------------------*/

/**************************** ���ò��� *************************************/
#include "Port.h"
#include "drv_sci.h"
#include "drv_pio.h"  /*add by chenms 2017-10-27*/
#include "Osal.h"
/**********************************************************
						����ʱ���ݽṹ����
 **********************************************************/
/* ģ��״̬ */
typedef enum
{
    PORT_UNINIT = 0u,  /*ģ��δ��ʼ��*/
    PORT_INITI  = 1u
}Port_MkStateType;

typedef  struct
{
	Port_MkStateType  MkState;
}Port_MkCtrlType;

/**********************************************************
						����ʱ���ݶ���
 **********************************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile Port_MkCtrlType Port_MkCtrl;
#pragma DATA_SEG DEFAULT


/*****************************�������� *************************************/
#if 1
STATIC void Port_CalcPinRegPhyAddress(uint8 PinGroupNum,uint16 *pDataRegAddr,uint16 *pDireRegAddr);
#endif

/*****************************ʵ�ֲ��� *************************************/

/************************************************************
* ��������: Port_Init
* ��������: Portģ���ʼ��.
* �������: (*ConfigPtr):ģ�龲̬���ò���;
* �������: ��
* ����/�������:��
* ��������: �������롡
* ��ע	  : �ú���ֻ��ʼ������Ϊ"PORT_PIN_MODE_DIO"ģʽ��IO��;
            ����ģʽ��IO�ڱ�����;
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
			/* �������ù���ģʽ = DIO */
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
			/* �������ù���ģʽ != DIO, 
               Nothing to do */
		}
	}
   	/***********************/
	OSAL_ENTER_CRITICAL();
	Port_MkCtrl.MkState = PORT_INITI;
	OSAL_EXIT_CRITICAL();
}


/************************************************************
* ��������: Port_SetPinMode
* ��������: ����ָ�����ŵĹ���ģʽ.
* �������: PinId:����ID��;
			Mode :���Ŵ��޸Ĺ���ģʽ;
* �������: ��
* ����/�������:��
* ��������: �������롡
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((Mode < PORT_PIN_MODE_ADC) || (Mode > PORT_PIN_MODE_SCI))
	{
		/*�������Mode����*/
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
		/*����PinId����û�о�̬����*/
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
		/*Pin�ž�̬����Ϊ������̬�޸����Ź���ģʽ*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_MODE_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
    /***********************************/
    /*Ӳ����֧��ֱ���������ŵ�ģʽ��ֱ�ӷ���*/
	
	return;	
#endif
}


/************************************************************
* ��������: Port_SetPinDirection
* ��������: ����ָ�����ŵ�����/�������.
* �������: PinId:����ID��;
			Mode :���Ŵ��޸ķ���;
* �������: ��
* ����/�������:��
* ��������: �������롡
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((PORT_PIN_IN != PinDirection) && (PORT_PIN_OUT != PinDirection))
	{
		/*�������PinDirection����*/
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
		/*����PinId����û������*/
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
		/*Pin�ž�̬����Ϊ������̬�޸����ŷ���*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_SET_PIN_DIRECTION_ID, 
						PORT_E_PARAM_CONFIG);		
#endif
		return;
	}
	
    /***********************************/
	PinOffsetInGroup = PinId % 8u;
	
	/*����PinId,����+����Ĵ������Ե�ַ*/
	Port_CalcPinRegPhyAddress(	PinId,
								&PinGroupDataRegAddr,
								&PinGroupDireRegAddr );

	pDireRegAddr = (volatile uint8 *)PinGroupDireRegAddr;
	RegData      = *pDireRegAddr;
	
	if(PORT_PIN_OUT == PinDirection)
	{
		/* �����޸�Ϊ��� */
		(*pDireRegAddr) = RegData | ((uint8)(1u << PinOffsetInGroup));
	}
	else
	{
		/* �����޸�Ϊ���� */
		(*pDireRegAddr) = RegData & ((uint8)(~(1u << PinOffsetInGroup)));
	}
	return;
#endif
}

/************************************************************
* ��������: Port_WritePinValue
* ��������: ����ָ�����ŵ�ֵ(��/�͵�ƽ)
* �������: PinId��Pin��Id�š�
 *          PinLevelValue: Pin�Ŵ�����ֵ.
* �������: ��
* ����/�������:��
* ��������: �������롡
* ��ע	  :
 * 		���PinId����=In, ��ֱ�ӷ���,������ֵ����;			
 * 		���PinId����=Out,����ж�Ӧ��ֵ����;
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
		/*ģ��δ��ʼ��*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_WRITE_PIN_VALUE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((PORT_PIN_LEVEL_LOW != PinLevelValue) 
		&& (PORT_PIN_LEVEL_HIGH != PinLevelValue))
	{
		/*�������PinLevelValue����ȷ*/
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
		/*����PinId����û������*/
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
		/*PIN������!=DIO*/
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
* ��������: Port_ReadPinValue
* ��������: ��ȡָ�����ŵ�ֵ(��/�͵�ƽ)
* �������: PinId��Pin��Id�š�
* �������: *pPinLevelValue: ��ȡ����Pin�ŵ�ƽֵ
* ����/�������:��
* ��������: �������롡
* ��ע	  :
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
		/*ģ��δ��ʼ��*/
	  	Det_ReportError(MODULE_ID_PORT, 
						0u, 
						PORT_READ_PIN_VALUE_ID, 
						PORT_E_UNINIT);	
		return;
	}

	if((NULL_PTR == pPinLevelValue))
	{
		/*����pPinLevelValue��Ч*/
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
		/*����PinId����û������*/
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
		/*PIN������!=DIO*/
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
* ��������: Port_CalcPinRegPhyAddress
* ��������: ����Pin�ŵ����ݼĴ���+����Ĵ����������ַ��
* �������: PinId��Pin��Id�š�
* �������: (*pDataRegAddr):���ݼĴ�����ַ;
			(*pDireRegAddr):����Ĵ�����ַ;
* ����/�������:��
* ��������: �������롡
* ��ע	  :
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

