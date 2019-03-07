/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateShow.h
* ��������  : ״̬��ʾģ�����ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef STATESHOW_H
#define STATESHOW_H

/**********************************
 * ͷ�ļ�
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"

#define         RUN_LED         PORT_PIN_PA4
#define         CAN1_LED        PORT_PIN_PA3
#define         CAN2_LED        PORT_PIN_PA2


/**********************************
 * ȫ�ֱ����ⲿ����
 * ********************************/


/**********************************
 * �����ⲿ����
 * ********************************/
extern void setRunLedState(void);
extern void setCAN1LedState(BOOLEAN errSta);
extern void setCAN2LedState(BOOLEAN errSta);




#endif
