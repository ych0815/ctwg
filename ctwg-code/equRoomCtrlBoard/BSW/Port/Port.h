/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Port.h
* ��������      : Portģ��ͷ�ļ�(.h)����
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����             �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms             NEW
**------------------------------------------------------------------------------------------------*/ 
#ifndef _PORT_H_
#define _PORT_H_

/**************************** ���ò��� *************************************/
#include "Port_Cfg.h"
#include "Port_CfgType.h"
#include "Port_Define.h"

/****************************�궨�岿��*************************************/
/*������*/
#define PORT_E_PARAM_PIN					(0x0au) /*PIN�������������*/
#define PORT_E_DIRECTION_UNCHANGEABLE		(0x0bu) /*���ŷ���Ϊ���ɸı�*/
#define PORT_E_PARAM_CONFIG					(0x0cu) /*ģ�����ò�������*/
#define PORT_E_PARAM_INVALID			    (0x0du) /*���������Ч*/
#define PORT_E_MODE_UNCHANGEABLE			(0x0eu) /*����ģʽΪ���ɸı�*/
#define PORT_E_UNINIT						(0x0fu) /*ģ��δ��ʼ��*/
#define PORT_E_DIRECTION_IN					(0x10u) /*���ŷ���=����*/
#define PORT_E_DIRECTION_OUT				(0x11u) /*���ŷ���=���*/

/* API Service ID's*/
#define PORT_INIT_ID						(0x00u)
#define PORT_SET_PIN_MODE_ID 			    (0x01u)
#define PORT_SET_PIN_DIRECTION_ID			(0x02u)
#define PORT_WRITE_PIN_VALUE_ID				(0x03u)
#define PORT_READ_PIN_VALUE_ID				(0x04u)



/**************************** ȫ�ֱ����������� *************************************/
extern const Port_ConfigType  Port_Config;


/**************************** ȫ�ֺ����������� *************************************/
/************************************************************
* ��������: Port_Init
* ��������: Portģ���ʼ��.
* �������: (*ConfigPtr):ģ�龲̬���ò���;
* �������: ��
* ����/�������:��
* ��������: �������롡
* ��ע	  :
*************************************************************/
extern	void   Port_Init(const Port_ConfigType *ConfigPtr);

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
extern	void   Port_SetPinMode(Port_PinType PinId, Port_PinModeType Mode);

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
extern	void Port_SetPinDirection(Port_PinType PinId,boolean PinDirection);

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
extern	void Port_WritePinValue(Port_PinType PinId,boolean PinLevelValue);

/************************************************************
* ��������: Port_ReadPinValue
* ��������: ��ȡָ�����ŵ�ֵ(��/�͵�ƽ)
* �������: PinId��Pin��Id�š�
* �������: *pPinLevelValue: ��ȡ����Pin�ŵ�ƽֵ
* ����/�������:��
* ��������: �������롡
* ��ע	  :
*************************************************************/
extern	void Port_ReadPinValue(Port_PinType PinId,boolean *pPinLevelValue);

#endif /*_PORT_H_*/

