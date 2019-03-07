#ifndef APP_UDP_H
#define APP_UDP_H

/********************************************
 * 变量外部声明
 *******************************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern uint8 ctrlHost_heartbeatCnt;/*控制主机生命信号*/
extern uint8 ctrlHost_SoftwareMainVer;/*控制主机软件主版本*/
extern uint8 ctrlHost_SoftwareMinorVer;/*控制主机软件次版本*/

#pragma DATA_SEG DEFAULT



/********************************************
 *函数外部声明
 *******************************************/
extern void UDP_MainFunction(void);
extern void UDP_Received(uint8 *data,uint16 size);

#endif
