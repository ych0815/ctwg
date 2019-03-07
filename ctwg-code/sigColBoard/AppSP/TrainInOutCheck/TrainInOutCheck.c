/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : TrainInOutCheck.c
* ��������  : ������/�����ģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "TrainInOutCheck.h"


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
BOOLEAN g_trainInOut_info;    /*������/������Ϣ��TRUE��ʾ������� FALSE��ʾ��������*/

#pragma DATA_SEG DEFAULT


/***************************************************************************//*!
 * \brief    ������/�����ģ���ʼ��
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void TrainInOutCheck_Init(void)
{
    g_trainInOut_info = FALSE;      /*��ʼ��Ϊ��������״̬*/
}

/***************************************************************************//*!
 * \brief    ������/����⺯��
 *
 * \param   state ������/������־ָ��
 *                TRUE = �������
 *                FALSE= ��������
 *
 * \return  ��
 *
 *****************************************************************************/
void trainInOutCheck (BOOLEAN *state)
{
    BOOLEAN trainIN1_val,trainIN2_val;
    BOOLEAN trainOUT1_val,trainOUT2_val;

    /*��ȡ��������⿪�ص����ŵ�ƽ*/
    Port_ReadPinValue(PIN_TRAIN_IN1,&trainIN1_val);
    Port_ReadPinValue(PIN_TRAIN_IN2,&trainIN2_val);

    /*��⵽�������*/
    if((trainIN1_val==TRUE)||(trainIN2_val==TRUE))
    {
        /*��������/�����־λ��Ϊ����־*/
        OSAL_ENTER_CRITICAL();
        *state = TRUE;
        OSAL_EXIT_CRITICAL(); 
    }

    /*��ȡ���������⿪�ص����ŵ�ƽ*/
    Port_ReadPinValue(PIN_TRAIN_OUT1,&trainOUT1_val);
    Port_ReadPinValue(PIN_TRAIN_OUT2,&trainOUT2_val);

    /*��⵽��������*/
    if((trainOUT1_val==TRUE)||(trainOUT2_val==TRUE))
    {
        /*��������/�����־λ��Ϊ�����־*/
        OSAL_ENTER_CRITICAL();
        *state = FALSE;
        OSAL_EXIT_CRITICAL();
    }
}
