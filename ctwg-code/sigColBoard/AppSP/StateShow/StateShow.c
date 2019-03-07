/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateShow.c
* ��������  : ״̬��ʾģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "StateShow.h"

/***************************************************************************//*!
 * \brief   �������е�״̬
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void setRunLedState(void)
{
    static BOOLEAN runLedPinLevel = PORT_PIN_LEVEL_HIGH;

    runLedPinLevel = !runLedPinLevel;
    Port_WritePinValue(RUN_LED,runLedPinLevel);
}
 
/***************************************************************************//*!
 * \brief   ����CAN1ͨѶ��״̬
 *
 * \param   errSta CAN1ͨѶ����״̬
 *                 TRUE  = ����
 *                 FALSE = ����
 *
 * \return  ��
 *
 *****************************************************************************/
void setCAN1LedState(BOOLEAN errSta)
{
    if(errSta == TRUE)
    {
        Port_WritePinValue(CAN1_LED,PORT_PIN_LEVEL_HIGH);   /*����*/
    }
    else
    {
        Port_WritePinValue(CAN1_LED,PORT_PIN_LEVEL_LOW);    /*����*/
    }
}

/***************************************************************************//*!
 * \brief   ����CAN2ͨѶ��״̬
 *
 * \param   errSta CAN1ͨѶ����״̬
 *                 TRUE  = ����
 *                 FALSE = ����
 *
 * \return  ��
 *
 *****************************************************************************/
void setCAN2LedState(BOOLEAN errSta)
{
    if(errSta == TRUE)
    {
        Port_WritePinValue(CAN2_LED,PORT_PIN_LEVEL_HIGH);   /*����*/
    }
    else
    {
        Port_WritePinValue(CAN2_LED,PORT_PIN_LEVEL_LOW);    /*����*/
    }
}