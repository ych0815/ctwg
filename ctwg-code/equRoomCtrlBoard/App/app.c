/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                 (c) Copyright 2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                         Freescale MC9S12XEP100
*                                              Sample code
* File : APP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>
#include "Bsw.h"
#include "app.h"
/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
 
static  volatile  OS_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  volatile  OS_STK  AppTaskStateShowStk[APP_TASK_STATESHOW_STK_SIZE];
static  volatile  OS_STK  AppTaskStateCtrlStk[APP_TASK_STATECTRL_STK_SIZE];
/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*�ڲ���������*/
static  void  AppTaskStart(void *p_arg);
static  void  AppTaskStateShow (void *p_arg);
static  void  AppTaskStateCtrl (void *p_arg);
static void app_clr_watchdog(void);

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
extern  void    AppProbeInit(void);
#endif

/*
*********************************************************************************************************
*                                             C ENTRY POINT
*********************************************************************************************************
*/

void main (void)
{
    CPU_INT08U  err;

    BSP_IntDisAll();                                                    /* Disable ALL interrupts to the interrupt controller       */

    OSInit();                                                           /* Initialize uC/OS-II                                      */

    /* �����ۺϹ������� */
    OSTaskCreateExt(AppTaskStart,
                    NULL,
                    (OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppTaskStartStk[0],
                    APP_TASK_START_STK_SIZE,
                    NULL,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

                                                                        /* Assign names to created tasks                            */
#if OS_TASK_NAME_SIZE > 11
    OSTaskNameSet(APP_TASK_START_PRIO, (CPU_CHAR *)"Start Task", &err);
#endif

    OSStart();                                                          /* Start uC/OS-II                                           */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                              STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/
static  void  AppTaskStart (void *p_arg)
{
    INT8U iRet = 0;
    
    (void)p_arg;                                                        /* Prevent compiler warning                                 */
    
    BSP_Init();                                                         /* Initialize the BSP                                       */

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /* Start stats task                                         */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit();                                                     /* Initialize uC/Probe modules                              */
#endif
    
    /***************************/
    Drv_Sci_Init(9600); 
	Port_Init(&Port_Config);
	Com_Init();	
	ComM_Init();
 	CanIf_Init();
    Can_Init();
    
    BSP_EBI_Cfg();
    W5300_Config();

    Com_EnablePacketRx(0u,COM_SIGCOLBOARD_COl);
    Com_EnablePacketRx(0u,COM_COL_MODULE_STA);
    Com_EnablePacketRx(0u,COM_GPKZX_STATEMONI);
    Com_EnablePacketRx(0u,COM_BOARD_INFO);

    Com_EnablePacketTx(0u,COM_EQUROOM_CTRLBOARD_CTRL);
    Com_EnablePacketTx(0u,COM_BOARD_INFO);

    /*����״̬��ʾ����*/
    iRet = OSTaskCreateExt(AppTaskStateShow,
                NULL,
                (OS_STK *)&AppTaskStateShowStk[APP_TASK_STATESHOW_STK_SIZE - 1],
                APP_TASK_STATESHOW_PRIO,
                APP_TASK_STATESHOW_PRIO,
                (OS_STK *)&AppTaskStateShowStk[0],
                APP_TASK_STATESHOW_STK_SIZE,
                NULL,
                OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if(STD_ON == APP_DEV_ERROR_DETECT)
    if(iRet == OS_ERR_NONE)
        Drv_Sci_Write("\r\nTaskStateShow create successful!",0,0);
    else
        Drv_Sci_Write("\r\nTaskStateShow create error!",0,0);  
#endif

    /*����״̬��������*/
    iRet = OSTaskCreateExt(AppTaskStateCtrl,
                NULL,
                (OS_STK *)&AppTaskStateCtrlStk[APP_TASK_STATECTRL_STK_SIZE - 1],
                APP_TASK_STATECTRL_PRIO,
                APP_TASK_STATECTRL_PRIO,
                (OS_STK *)&AppTaskStateCtrlStk[0],
                APP_TASK_STATECTRL_STK_SIZE,
                NULL,
                OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if(STD_ON == APP_DEV_ERROR_DETECT)
    if(iRet == OS_ERR_NONE)
        Drv_Sci_Write("\r\nTaskStateCtrl create successful!",0,0);
    else
        Drv_Sci_Write("\r\nTaskStateCtrl create error!",0,0);  
#endif

#if 1 
    if(UDP_Init()==TRUE)
    {
        Drv_Sci_Write("\r\nUDP init successed",0,0); 
    } 
    else
    {
        Drv_Sci_Write("\r\nUDP init failed",0,0);
        
        OSTimeDly(100u);
        
        /* �����ʼ��ʧ�ܣ��ٽ���һ�γ�ʼ�� */
        if(UDP_Init()==TRUE)
        {
            Drv_Sci_Write("\r\nUDP init successed",0,0); 
        } 
        else
        {
            Drv_Sci_Write("\r\nUDP init failed",0,0);
        }       
    }
#endif

    /***************************/
	while (1) 
	{    
	    /* ���CAN�����շ� */
		ComM_MainFunction();
		CanIf_Mainfunction();
		Com_MainFunction();
		
		/* ���UDP�����շ� */
		UDP_MainFunction();
       
        /*��ʱ10ms*/
		OSTimeDly(10u);
	}
}

/***************************************************************************//*!
 * \brief   ״̬��ʾ������
 *
 * \param   p_arg   ������������δʹ��
 *
 * \return  ��
 *
 *****************************************************************************/
static  void  AppTaskStateShow (void *p_arg)
{
    (void)p_arg;      /* Prevent compiler warning */
    
    /***************************/
	while (1) 
	{          
        /*״̬��ʾģ���̨��ѭ��*/ 
        app_stateShow_MainFunction();

        /*��ʱ500ms*/
        OSTimeDly(500u);
	}
}

/***************************************************************************//*!
 * \brief   ״̬����������
 *
 * \param   p_arg   ������������δʹ��
 *
 * \return  ��
 *
 *****************************************************************************/
static  void  AppTaskStateCtrl (void *p_arg)
{
    (void)p_arg;      /* Prevent compiler warning */
    
    /***************************/
	while (1) 
	{    
        /*״̬����ģ���̨��ѭ��*/
        app_stateCtrl_MainFunction();
        
        /*ִ��ι������*/
		app_clr_watchdog();
        
        /*��ʱ50ms*/
        OSTimeDly(50u);
	}
}

/********************************************************************************//*��
*\brief      ι������
*
*ι��
*
*\param  
*
*\return    errno   ����ֵ
*\retval    0       ��ʼ������
*
**********************************************************************************/
static void app_clr_watchdog(void)
{
     static boolean wdg_level = 0;       /*ι����ƽ*/
     static uint8 dog_cnt = 0;
     
     if(dog_cnt == 10)
     {
         dog_cnt = 0;
         wdg_level = !wdg_level;
         Port_WritePinValue(PORT_PIN_PH0,wdg_level);
     }
     
     dog_cnt++;
}
