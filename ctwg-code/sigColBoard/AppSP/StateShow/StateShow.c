/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : StateShow.c
* 功能描述  : 状态显示模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "StateShow.h"

/***************************************************************************//*!
 * \brief   设置运行灯状态
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void setRunLedState(void)
{
    static BOOLEAN runLedPinLevel = PORT_PIN_LEVEL_HIGH;

    runLedPinLevel = !runLedPinLevel;
    Port_WritePinValue(RUN_LED,runLedPinLevel);
}
 
/***************************************************************************//*!
 * \brief   设置CAN1通讯灯状态
 *
 * \param   errSta CAN1通讯故障状态
 *                 TRUE  = 灯灭
 *                 FALSE = 灯亮
 *
 * \return  无
 *
 *****************************************************************************/
void setCAN1LedState(BOOLEAN errSta)
{
    if(errSta == TRUE)
    {
        Port_WritePinValue(CAN1_LED,PORT_PIN_LEVEL_HIGH);   /*灯灭*/
    }
    else
    {
        Port_WritePinValue(CAN1_LED,PORT_PIN_LEVEL_LOW);    /*灯亮*/
    }
}

/***************************************************************************//*!
 * \brief   设置CAN2通讯灯状态
 *
 * \param   errSta CAN1通讯故障状态
 *                 TRUE  = 灯灭
 *                 FALSE = 灯亮
 *
 * \return  无
 *
 *****************************************************************************/
void setCAN2LedState(BOOLEAN errSta)
{
    if(errSta == TRUE)
    {
        Port_WritePinValue(CAN2_LED,PORT_PIN_LEVEL_HIGH);   /*灯灭*/
    }
    else
    {
        Port_WritePinValue(CAN2_LED,PORT_PIN_LEVEL_LOW);    /*灯亮*/
    }
}