#ifndef APP_UDP_H
#define APP_UDP_H

/********************************************
 * �����ⲿ����
 *******************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern uint8 ctrlHost_heartbeatCnt;/*�������������ź�*/
extern uint8 ctrlHost_SoftwareMainVer;/*��������������汾*/
extern uint8 ctrlHost_SoftwareMinorVer;/*������������ΰ汾*/

#pragma DATA_SEG DEFAULT



/********************************************
 *�����ⲿ����
 *******************************************/
extern void UDP_MainFunction(void);
extern void UDP_Received(uint8 *data,uint16 size);

#endif
