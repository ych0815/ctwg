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

/*���³�ʼ����־����*/
static BOOLEAN init_isFinish = FALSE;

/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*�ڲ���������*/
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
    
    /*�����ۺϹ�������*/                                                            
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
    MeaVel_Init();                  /*����ģ���ʼ��*/
    

    g_boardCAN_info[0] = FALSE;     /*��ʼ��Ϊ�忨CAN1����*/
    g_boardCAN_info[1] = FALSE;     /*��ʼ��Ϊ�忨CAN2����*/
                                                     
    /**************Com_EnablePacket*************/
    Com_EnablePacketTx(0u,COM_SIGCOLBOARD_COl);
    Com_EnablePacketTx(0u,COM_BOARD_INFO);
    Com_EnablePacketTx(0u,COM_GPKZX_STATEMONI);
    
    /*����������/����������*/
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

    /*����������ݲɼ���ɢ�ȿ�������*/
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
        MeaVel_MainFunction();      /*���ټ����̨��ѭ������*/
        app_clr_watchdog();         /*ι��*/
        OSTimeDly(5u);
	}
}

/***************************************************************************//*!
 * \brief   ������/������������
 *
 * \param   p_arg   ������������δʹ��
 *
 * \return  ��
 *
 *****************************************************************************/
static  void  AppTaskTrainInOutCheck (void *p_arg)
{
    (void)p_arg;                /* Prevent compiler warning  */
    
    TrainInOutCheck_Init();     /* Initialize global variabel*/
    /***************************/
	while (1) 
	{    
        /*ÿ��5ms���һ�γ�����/���⴫����*/
        OSTimeDly(5u);

        /*������/������*/
        trainInOutCheck(&g_trainInOut_info);
        
        /*��⵽�����������Ҫ�Բ��ֱ������³�ʼ��*/
        if(g_trainInOut_info == TRUE) 
        {
            /*�����³�ʼ����־λ��ΪFALSE*/
            init_isFinish = FALSE;  
        } 
        else
        {
            /*�ж����³�ʼ����־λ*/
            if(init_isFinish == FALSE)
            {
                /*����ģ�鲿�ֱ������³�ʼ��*/
                MeaVel_ReInit();
                /*�����³�ʼ����־λ��ΪTRUE*/
                init_isFinish = TRUE;
            }
        }         
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
        /*�������е�״̬*/
        setRunLedState();

        /*����CAN1ͨѶ��״̬*/
        setCAN1LedState(g_boardCAN_info[0]); 

        /*����CAN2ͨѶ��״̬*/
        setCAN2LedState(g_boardCAN_info[1]); 

        /*��ʱ500ms*/
        OSTimeDly(500u);
	}
}

/***************************************************************************//*!
 * \brief   ������ݲɼ���ɢ�ȿ���������
 *
 * \param   p_arg   ������������δʹ��
 *
 * \return  ��
 *
 *****************************************************************************/
static  void  AppTaskMoniDataCol (void *p_arg)
{ 
    char tmp;
    uint8 iRet;
    (void)p_arg;                /* Prevent compiler warning*/
   
    MoniDataCol_Init();         /*������ݲɼ�ģ���ʼ��*/
   
    /***************************/
	while (1) 
	{               
        /*��ȡ�����¶�*/
        OSAL_ENTER_CRITICAL();
        iRet = getEnvTemp(&tmp);
        OSAL_EXIT_CRITICAL();   
        if(iRet==0)    
        {/*��ȡ�¶ȳɹ�*/
            g_tempErrSta_info = FALSE;
            g_temp_info = tmp;
#if 1            
        Drv_Sci_Write("\r\ng_temp_info = ",0,0);
        Drv_Sci_WriteCharAscii(g_temp_info);
#endif        
        } 
        else
        {/*��ȡ�¶�ʧ��*/
            g_tempErrSta_info = TRUE;
        }

        
        /*��ȡ���Կ�����ɢ�ȷ��ȿ�������״̬*/
        getFanOpenState(g_temp_info,&g_fanOpenSta_info);

        /*��ȡDC12V��24V��Դ����״̬*/
        getDCPowerErrState(&g_DC12VErrSta_info,&g_DC24VErrSta_info);
        
        /*��ȡDC5V��Դ��ѹֵ*/
        

        /*���ݷ��ȿ���״̬����ɢ�ȷ��ȿ�����ر�  �ݶ�Ϊ500ms�ж�һ��*/
        setFanOpenOrClose(g_fanOpenSta_info);

        /*��ʱ500ms*/
        OSTimeDly(500u);
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
 
         //drv_pioh_write(WATDG_IO,wdg_level);
         Port_WritePinValue(PORT_PIN_PH0,wdg_level);
     }
     
     dog_cnt++;
}