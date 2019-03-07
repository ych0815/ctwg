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
static  volatile  OS_STK  AppTaskTrainInOutCheckStk[APP_TASK_TRAININOUTCHECK_STK_SIZE];
static  volatile  OS_STK  AppTaskMoniDataColStk[APP_TASK_MONIDATACOL_STK_SIZE];

/*重新初始化标志定义*/
static BOOLEAN init_isFinish = FALSE;

/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*内部函数声明*/
static  void  AppTaskStart(void *p_arg);
static  void  AppTaskTrainInOutCheck (void *p_arg);
static  void  AppTaskStateShow (void *p_arg);
static  void  AppTaskMoniDataCol(void *p_arg);
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
    INT8U iRet;
  
    BSP_IntDisAll();                                                    /* Disable ALL interrupts to the interrupt controller       */

    OSInit();                                                           /* Initialize uC/OS-II                                      */
    BSP_Init();                                                         /* Initialize the BSP                                       */
    Drv_Sci_Init(9600);                                                 /* Initialize the SCI                                       */
    
    /*创建综合管理任务*/                                                            
    iRet = OSTaskCreateExt(AppTaskStart,
                        NULL,
                        (OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
                        APP_TASK_START_PRIO,
                        APP_TASK_START_PRIO,
                        (OS_STK *)&AppTaskStartStk[0],
                        APP_TASK_START_STK_SIZE,
                        NULL,
                        OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if(STD_ON == APP_DEV_ERROR_DETECT)
    if(iRet == OS_ERR_NONE)
        Drv_Sci_Write("\r\nTaskStart create successful!",0,0);
    else
        Drv_Sci_Write("\r\nTaskStart create error!",0,0);
#endif    
           
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
    INT8U iRet;
    (void)p_arg;                                                        /* Prevent compiler warning                                 */
    

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /* Start stats task                                         */
#endif

#if (uC_PROBE_OS_PLUGIN > 0) || (uC_PROBE_COM_MODULE > 0)
    AppProbeInit();                                                     /* Initialize uC/Probe modules                              */
#endif

    /***************************/
	Port_Init(&Port_Config);
	Com_Init();	
	ComM_Init();
 	CanIf_Init();
    Can_Init();
    MeaVel_Init();                  /*测速模块初始化*/
    

    g_boardCAN_info[0] = FALSE;     /*初始化为板卡CAN1正常*/
    g_boardCAN_info[1] = FALSE;     /*初始化为板卡CAN2正常*/
                                                     
    /**************Com_EnablePacket*************/
    Com_EnablePacketTx(0u,COM_SIGCOLBOARD_COl);
    Com_EnablePacketTx(0u,COM_BOARD_INFO);
    Com_EnablePacketTx(0u,COM_GPKZX_STATEMONI);
    
    /*创建车辆入/出库检测任务*/
    iRet = OSTaskCreateExt(AppTaskTrainInOutCheck,
                    NULL,
                    (OS_STK *)&AppTaskTrainInOutCheckStk[APP_TASK_TRAININOUTCHECK_STK_SIZE - 1],
                    APP_TASK_TRAININOUTCHECK_PRIO,
                    APP_TASK_TRAININOUTCHECK_PRIO,
                    (OS_STK *)&AppTaskTrainInOutCheckStk[0],
                    APP_TASK_TRAININOUTCHECK_STK_SIZE,
                    NULL,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if(STD_ON == APP_DEV_ERROR_DETECT)
    if(iRet == OS_ERR_NONE)
        Drv_Sci_Write("\r\nTaskTrainInOutCheck create successful!",0,0);
    else
        Drv_Sci_Write("\r\nTaskTrainInOutCheck create error!",0,0);  
#endif

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

    /*创建监测数据采集与散热控制任务*/
    iRet = OSTaskCreateExt(AppTaskMoniDataCol,
                    NULL,
                    (OS_STK *)&AppTaskMoniDataColStk[APP_TASK_MONIDATACOL_STK_SIZE - 1],
                    APP_TASK_MONIDATACOL_PRIO,
                    APP_TASK_MONIDATACOL_PRIO,
                    (OS_STK *)&AppTaskMoniDataColStk[0],
                    APP_TASK_MONIDATACOL_STK_SIZE,
                    NULL,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if(STD_ON == APP_DEV_ERROR_DETECT)                    
    if(iRet == OS_ERR_NONE)
        Drv_Sci_Write("\r\nTaskMoniDataColStk create successful!",0,0);
    else
        Drv_Sci_Write("\r\nTaskMoniDataColStk create error!",0,0);    
#endif
  
    //OSTimeDly(10u);
    Drv_Sci_Write("\r\nSignal Collect Board-System Start-up Successful",0,0);
    Drv_Sci_Write("\r\nSoftWare Version:V1.00\r\n",0,0);

	while (1) 
	{    
		ComM_MainFunction();
		CanIf_Mainfunction();
		Com_MainFunction();
        MeaVel_MainFunction();      /*测速计算后台主循环函数*/
        app_clr_watchdog();         /*喂狗*/
        OSTimeDly(5u);
	}
}

/***************************************************************************//*!
 * \brief   车辆入/出库检测任务函数
 *
 * \param   p_arg   任务函数参数，未使用
 *
 * \return  无
 *
 *****************************************************************************/
static  void  AppTaskTrainInOutCheck (void *p_arg)
{
    (void)p_arg;                /* Prevent compiler warning  */
    
    TrainInOutCheck_Init();     /* Initialize global variabel*/
    /***************************/
	while (1) 
	{    
        /*每隔5ms检测一次车辆入/出库传感器*/
        OSTimeDly(5u);

        /*车辆入/出库检测*/
        trainInOutCheck(&g_trainInOut_info);
        
        /*检测到车辆出库后需要对部分变量重新初始化*/
        if(g_trainInOut_info == TRUE) 
        {
            /*将重新初始化标志位置为FALSE*/
            init_isFinish = FALSE;  
        } 
        else
        {
            /*判断重新初始化标志位*/
            if(init_isFinish == FALSE)
            {
                /*测速模块部分变量重新初始化*/
                MeaVel_ReInit();
                /*将重新初始化标志位置为TRUE*/
                init_isFinish = TRUE;
            }
        }         
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
        /*设置运行灯状态*/
        setRunLedState();

        /*设置CAN1通讯灯状态*/
        setCAN1LedState(g_boardCAN_info[0]); 

        /*设置CAN2通讯灯状态*/
        setCAN2LedState(g_boardCAN_info[1]); 

        /*延时500ms*/
        OSTimeDly(500u);
	}
}

/***************************************************************************//*!
 * \brief   监测数据采集与散热控制任务函数
 *
 * \param   p_arg   任务函数参数，未使用
 *
 * \return  无
 *
 *****************************************************************************/
static  void  AppTaskMoniDataCol (void *p_arg)
{ 
    char tmp;
    uint8 iRet;
    (void)p_arg;                /* Prevent compiler warning*/
   
    MoniDataCol_Init();         /*监测数据采集模块初始化*/
   
    /***************************/
	while (1) 
	{               
        /*获取环境温度*/
        OSAL_ENTER_CRITICAL();
        iRet = getEnvTemp(&tmp);
        OSAL_EXIT_CRITICAL();   
        if(iRet==0)    
        {/*获取温度成功*/
            g_tempErrSta_info = FALSE;
            g_temp_info = tmp;
#if 1            
        Drv_Sci_Write("\r\ng_temp_info = ",0,0);
        Drv_Sci_WriteCharAscii(g_temp_info);
#endif        
        } 
        else
        {/*获取温度失败*/
            g_tempErrSta_info = TRUE;
        }

        
        /*获取轨旁控制箱散热风扇开启控制状态*/
        getFanOpenState(g_temp_info,&g_fanOpenSta_info);

        /*获取DC12V、24V电源故障状态*/
        getDCPowerErrState(&g_DC12VErrSta_info,&g_DC24VErrSta_info);
        
        /*获取DC5V电源电压值*/
        

        /*根据风扇开启状态控制散热风扇开启或关闭  暂定为500ms判定一次*/
        setFanOpenOrClose(g_fanOpenSta_info);

        /*延时500ms*/
        OSTimeDly(500u);
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
 
         //drv_pioh_write(WATDG_IO,wdg_level);
         Port_WritePinValue(PORT_PIN_PH0,wdg_level);
     }
     
     dog_cnt++;
}