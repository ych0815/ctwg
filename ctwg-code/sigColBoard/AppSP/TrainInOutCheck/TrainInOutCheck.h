/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : TrainInOutCheck.h
* ��������  : ������/�����ģ�����ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef TRAININOUTCHECK_H
#define TRAININOUTCHECK_H

/**********************************
 * ͷ�ļ�
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"


#define         PIN_TRAIN_IN1           PORT_PIN_PD7
#define         PIN_TRAIN_IN2           PORT_PIN_PC0
#define         PIN_TRAIN_OUT1          PORT_PIN_PC1
#define         PIN_TRAIN_OUT2          PORT_PIN_PC2


/**********************************
 * ȫ�ֱ����ⲿ����
 * ********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern BOOLEAN g_trainInOut_info;    /*������/������Ϣ��TRUE��ʾ������� FALSE��ʾ��������*/

#pragma DATA_SEG DEFAULT

/**********************************
 * �����ⲿ����
 * ********************************/
void TrainInOutCheck_Init(void);
void trainInOutCheck (BOOLEAN *state);


#endif
