/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Port_Cfg.c
* ��������      : Portģ������ͷ�ļ�(.h)����
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����             �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/

/**************************** ���ò��� *********************************/
#include "Port_Cfg.h"
#include "Port_CfgType.h"
#include "Port_Define.h"
#include "drv_pio.h"  /*add by chenms 2017-10-27*/
/**************************** ���岿�� *********************************/
/************************************
          2OO3LCU���ذ����Ŷ���
************************************/
const Port_PinConfigurationType Port_PinConfig[14]=
{    
    /*DC12V��24V��Դ����״̬����*/
	{PORT_PIN_PC5  ,PORT_C,  DRV_PIO_PC5,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*DC12V���ϼ��*/
	{PORT_PIN_PC4  ,PORT_C,  DRV_PIO_PC4,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*DC24V���ϼ��*/

    /*���Ź�ι����*/
	{PORT_PIN_PH0  ,PORT_H,  DRV_PIO_PH0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_LOW },/*WDI*/

	/*RUN LED*/
	{PORT_PIN_PA4  ,PORT_A,  DRV_PIO_PA4,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH },/*��Ӧ����LED5*/
	/*CAN1 LED*/
	{PORT_PIN_PA3,  PORT_A,  DRV_PIO_PA3,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH},/*��Ӧ����LED6*/
	/*CAN2 LED*/
	{PORT_PIN_PA2,  PORT_A,  DRV_PIO_PA2,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT,FALSE, PORT_PIN_LEVEL_HIGH},/*��Ӧ����LED7*/
	
	/*Ԥ��*/
	{PORT_PIN_PA1  ,PORT_A,  DRV_PIO_PA1,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_HIGH },/*��Ӧ����LED8*/
	{PORT_PIN_PA0  ,PORT_A,  DRV_PIO_PA0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_HIGH },/*��Ӧ����LED9*/

	/*������/����� 4������*/
	{PORT_PIN_PD2  ,PORT_D,  DRV_PIO_PD2,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*�����1*/
	{PORT_PIN_PD3  ,PORT_D,  DRV_PIO_PD3,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*�����2*/
	
	{PORT_PIN_PD0  ,PORT_D,  DRV_PIO_PD0,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*������1*/
	{PORT_PIN_PD1  ,PORT_D,  DRV_PIO_PD1,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_IN ,FALSE, PORT_PIN_LEVEL_LOW },/*������2*/

	/*ɢ�ȷ��ȿ��� 2������*/
	{PORT_PIN_PB5  ,PORT_B,  DRV_PIO_PB5,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_LOW },/*ɢ�ȷ���1*/
	{PORT_PIN_PB6  ,PORT_B,  DRV_PIO_PB6,  PORT_PIN_MODE_DIO, FALSE, PORT_PIN_OUT ,FALSE, PORT_PIN_LEVEL_LOW },/*ɢ�ȷ���2*/   
};  

const Port_ConfigType  Port_Config=
{
    14u,
    &Port_PinConfig[0]
};



