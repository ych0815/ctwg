/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Port_CfgType.c
* ��������      : Portģ��������������ͷ�ļ�(.h)����
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����             �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/
#ifndef  _PORT_CFGTYPE_H_
#define  _PORT_CFGTYPE_H_

/**************************** ���ò��� *************************************/
#include "Port_Cfg.h"

/**************************** ���岿�� *************************************/
/* �������� */
typedef uint8 Port_PinType;  

/* ���Ź���ģʽ */
typedef enum
{
	PORT_PIN_MODE_ADC = 1u,
	PORT_PIN_MODE_CAN = 2u,
	PORT_PIN_MODE_DIO = 3u,
	PORT_PIN_MODE_DIO_GPT = 4u,
	PORT_PIN_MODE_DIO_WDG = 5u,
	PORT_PIN_MODE_FLEXRAY = 6u,
	PORT_PIN_MODE_ICU = 7u,
	PORT_PIN_MODE_LIN = 8u,
	PORT_PIN_MODE_MEM = 9u,
	PORT_PIN_MODE_PWM = 10u,
	PORT_PIN_MODE_SPI = 11u,
	PORT_PIN_MODE_SCI = 12u
}Port_PinModeType;

/* �������ŵ�ƽ */
typedef enum
{
    PORT_PIN_LEVEL_LOW  = 0u,
    PORT_PIN_LEVEL_HIGH = 1u
} Port_PinLevelValueType;

/* �������ŷ���*/
typedef enum   
{
    PORT_PIN_IN  = 0u,
    PORT_PIN_OUT = 1u
} Port_PinDirectionType;

/* ��֧�������ýṹ�� */
typedef struct
{   
    Port_PinType		PortPinId;		/* ����ID(Ӧ�ÿɼ�) */	
	uint8               PortType;		/* �˿�����(A/B/C....)*/
	Port_PinType        PortDrvPinId;   /* ��������ģ����ID*//*add by chenms 2017-10-27*/
    Port_PinModeType	PortPinMode;  	/* ���Ź���ģʽ */	
	boolean 	PortPinModeChangeable;  /* ���Ź���ģʽ�ܷ�̬�ı�*/
    boolean 	PortPinDirection;  		/* ���ŷ���(����/���) */  	
    boolean		PortPinDirectionChangeable;	/* ���ŷ����ܷ�̬�ı� */		 
    boolean		PortPinLevelValue;			/* ����Ĭ�ϵ�ƽ */
}Port_PinConfigurationType;

/* ģ�����ýṹ�� */
typedef struct
{
    uint8 PortNumberOfPortPins;
    const Port_PinConfigurationType *Port_PinConfiguration;
}Port_ConfigType;

#endif

