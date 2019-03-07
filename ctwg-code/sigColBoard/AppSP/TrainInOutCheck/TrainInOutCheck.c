/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : TrainInOutCheck.c
* 功能描述  : 车辆入/出检测模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "TrainInOutCheck.h"


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
BOOLEAN g_trainInOut_info;    /*车辆入/出库信息，TRUE表示车辆入库 FALSE表示车辆出库*/

#pragma DATA_SEG DEFAULT


/***************************************************************************//*!
 * \brief    车辆入/出检测模块初始化
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void TrainInOutCheck_Init(void)
{
    g_trainInOut_info = FALSE;      /*初始化为车辆出库状态*/
}

/***************************************************************************//*!
 * \brief    车辆入/出检测函数
 *
 * \param   state 车辆入/出监测标志指针
 *                TRUE = 车辆入库
 *                FALSE= 车辆出库
 *
 * \return  无
 *
 *****************************************************************************/
void trainInOutCheck (BOOLEAN *state)
{
    BOOLEAN trainIN1_val,trainIN2_val;
    BOOLEAN trainOUT1_val,trainOUT2_val;

    /*读取车辆入库检测开关的引脚电平*/
    Port_ReadPinValue(PIN_TRAIN_IN1,&trainIN1_val);
    Port_ReadPinValue(PIN_TRAIN_IN2,&trainIN2_val);

    /*检测到车辆入库*/
    if((trainIN1_val==TRUE)||(trainIN2_val==TRUE))
    {
        /*将车辆入/出库标志位置为入库标志*/
        OSAL_ENTER_CRITICAL();
        *state = TRUE;
        OSAL_EXIT_CRITICAL(); 
    }

    /*读取车辆出库检测开关的引脚电平*/
    Port_ReadPinValue(PIN_TRAIN_OUT1,&trainOUT1_val);
    Port_ReadPinValue(PIN_TRAIN_OUT2,&trainOUT2_val);

    /*检测到车辆出库*/
    if((trainOUT1_val==TRUE)||(trainOUT2_val==TRUE))
    {
        /*将车辆入/出库标志位置为出库标志*/
        OSAL_ENTER_CRITICAL();
        *state = FALSE;
        OSAL_EXIT_CRITICAL();
    }
}
