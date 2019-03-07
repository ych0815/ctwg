/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : MoniDataCol.h
* ��������  : ������ݲɼ���ɢ�ȿ���ģ�����ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef MONIDATACOL_H
#define MONIDATACOL_H

/**********************************
 * ͷ�ļ�
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"

/**********************************
 * �궨��
 * ********************************/
#define         HIGH_TEMP_LIMIT         50u         /**brief ɢ�ȿ����ٽ��¶�ֵ */
#define         PIN_SR_FAN1             PORT_PIN_PC5 
#define         PIN_SR_FAN2             PORT_PIN_PC6 

/**********************************
 * ȫ�ֱ����ⲿ����
 * ********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern BOOLEAN g_fanOpenSta_info;	  /*���Կ�����ɢ�ȷ��ȿ�������*/
//extern BOOLEAN g_DC5VErrSta_info;	  /*DC5V��Դ����״̬*/
extern BOOLEAN g_DC12VErrSta_info;	  /*DC12V��Դ����״̬*/
extern BOOLEAN g_DC24VErrSta_info;	  /*DC24V��Դ����״̬*/
extern BOOLEAN g_tempErrSta_info;     /*�¶ȴ���������״̬*/
extern INT8S   g_temp_info;		  	  /*�����¶���Ϣ*/
extern uint16  g_DC5VVol_info;               /*DC5V��Դ��ѹ(��λ:0.01V)*/

#pragma DATA_SEG DEFAULT

/**********************************
 * �����ⲿ����
 * ********************************/
void MoniDataCol_Init(void);
INT8S getDCPowerErrState(BOOLEAN * __far DC12V_state,BOOLEAN * __far DC24V_state);
INT8S getFanOpenState(INT8S temp,BOOLEAN * __far state);
INT8S setFanOpenOrClose(BOOLEAN state);

#endif
