/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                                (c) Copyright 2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                      BOARD SUPPORT PACKAGE (BSP)
*                                         Freescale MC9S12X
*
* File : BSP.H
* By   : Eric Shufro
*********************************************************************************************************
*/

#ifndef BSP_H
#define BSP_H

#include "cpu.h"   /*add by chenms 2017-4-28*/
/*
*********************************************************************************************************
*                                         PROCESSOR SPECIFICS
*********************************************************************************************************
*/
							   
#define  OS_TICK_OC                  7                          /* Output comp. channel # used to generate OS Tick Int. */ 

#define  OSCFREQ               4000000L		                    /* Define the EVB crystal oscillator frequency          */

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/



static  void        BSP_SetECT_Prescaler(CPU_INT08U prescaler);
        void        BSP_Init            (void);
        void        BSP_IntDisAll       (void);         
        CPU_INT32U  BSP_CPU_ClkFreq     (void);
        void        Bus_Clk_Init        (void);
        
/************************************************************
* ��������: Bsp_GetBusClock
* ��������: ��ȡϵͳ��ǰ������ʱ��;
* �������: ��
* �������: (*pBusClock):��ȡ��������ʱ��ֵ;
* ����/�������:��
* ��������: �����롡
* ��ע	  :
*************************************************************/
extern	void  Bsp_GetBusClock(CPU_INT32U  *pBusClock);

/*
*********************************************************************************************************
*                                           ERROR CHECKING
*********************************************************************************************************
*/

#ifndef  OSCFREQ 
#error  "OSCFREQ must be defined in bsp.h"
#endif

#ifndef  OS_TICK_OC
#error  "OS_TICK_OC must be defined in bsp.h"
#endif


#endif                                                          /* End of file                                          */

