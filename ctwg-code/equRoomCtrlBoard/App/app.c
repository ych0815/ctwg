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
/*内部函数声明*/
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

    /* 创建综合管理任务 */
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

    /*创建状态显示任务*/
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

    /*创建状态控制任务*/
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
        
        /* 如果初始化失败，再进行一次初始化 */
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
	    /* 完成CAN报文收发 */
		ComM_MainFunction();
		CanIf_Mainfunction();
		Com_MainFunction();
		
		/* 完成UDP报文收发 */
		UDP_MainFunction();
       
        /*延时10ms*/
		OSTimeDly(10u);
	}
}

/***************************************************************************//*!
 * \brief   状态显示任务函数
 *
 * \param   p_arg   任务函数参数，未使用
 *
 * \return  无
 *
 *****************************************************************************/
static  void  AppTaskStateShow (void *p_arg)
{
    (void)p_arg;      /* Prevent compiler warning */
    
    /***************************/
	while (1) 
	{          
        /*状态显示模块后台主循环*/ 
        app_stateShow_MainFunction();

        /*延时500ms*/
        OSTimeDly(500u);
	}
}

/***************************************************************************//*!
 * \brief   状态控制任务函数
 *
 * \param   p_arg   任务函数参数，未使用
 *
 * \return  无
 *
 *****************************************************************************/
static  void  AppTaskStateCtrl (void *p_arg)
{
    (void)p_arg;      /* Prevent compiler warning */
    
    /***************************/
	while (1) 
	{    
        /*状态控制模块后台主循环*/
        app_stateCtrl_MainFunction();
        
        /*执行喂狗操作*/
		app_clr_watchdog();
        
        /*延时50ms*/
        OSTimeDly(50u);
	}
}

/********************************************************************************//*！
*\brief      喂狗函数
*
*喂狗
*
*\param  
*
*\return    errno   错误值
*\retval    0       初始化正常
*
**********************************************************************************/
static void app_clr_watchdog(void)
{
     static boolean wdg_level = 0;       /*喂狗电平*/
     static uint8 dog_cnt = 0;
     
     if(dog_cnt == 10)
     {
         dog_cnt = 0;
         wdg_level = !wdg_level;
         Port_WritePinValue(PORT_PIN_PH0,wdg_level);
     }
     
     dog_cnt++;
}
