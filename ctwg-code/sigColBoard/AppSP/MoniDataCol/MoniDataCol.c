/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : MoniDataCol.c
* 功能描述  : 监测数据采集与散热控制模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "Bsw.h"


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
BOOLEAN g_fanOpenSta_info;	  /*轨旁控制箱散热风扇开启控制*/
//BOOLEAN g_DC5VErrSta_info;	  /*DC5V电源故障状态*/
BOOLEAN g_DC12VErrSta_info;	  /*DC12V电源故障状态*/
BOOLEAN g_DC24VErrSta_info;	  /*DC24V电源故障状态*/
BOOLEAN g_tempErrSta_info;    /*温度传感器故障状态*/
INT8S	g_temp_info;		  /*环境温度信息*/
uint16  g_DC5VVol_info;       /*DC5V电源电压(单位:0.01V)*/

#pragma DATA_SEG DEFAULT


/***************************************************************************//*!
 * \brief   监测数据采集模块初始化
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void MoniDataCol_Init(void)
{
    char iRet;

    /*初始化相关变量*/
    g_fanOpenSta_info   = FALSE;
//    g_DC5VErrSta_info   = FALSE;
    g_DC12VErrSta_info  = FALSE;
    g_DC24VErrSta_info  = FALSE;
    g_tempErrSta_info   = FALSE; 
    g_temp_info         = 0;

    OSAL_ENTER_CRITICAL();
    iRet = drv_tmp1075_init(BSP_TMP1075_SLAVE_ADDR);
    OSAL_EXIT_CRITICAL();
    
    if(iRet==0)
    {
        g_tempErrSta_info = FALSE;
        Drv_Sci_Write("\r\ntmp1075 init successed",0,0);
    } 
    else
    {
        g_tempErrSta_info = TRUE;
        Drv_Sci_Write("\r\ntmp1075 init failed",0,0); 
    }
}


/***************************************************************************//*!
 * \brief   获取DC5V、12V、24V电源故障状态
 *
 * \param   DC5V_state   DC5V电源故障状态指针
 *          DC12V_state  DC5V电源故障状态指针
 *          DC24V_state  DC5V电源故障状态指针
 *
 * \return  0  表示成功
 *          -1 表示失败
 *
 *****************************************************************************/
INT8S getDCPowerErrState(BOOLEAN * __far DC12V_state,BOOLEAN * __far DC24V_state)
{
    BOOLEAN sta_12V,sta_24V;

    /*获取DC5V电源状态*/
    //Port_ReadPinValue(PORT_PIN_PB2,&sta_5V);
    /*获取DC12V电源状态*/
    Port_ReadPinValue(PORT_PIN_PB0,&sta_12V);
    /*获取DC24V电源状态*/
    Port_ReadPinValue(PORT_PIN_PC7,&sta_24V);

    if(sta_12V==TRUE)
    {
        *DC12V_state = FALSE;
    }
    else
    {
        *DC12V_state = TRUE;
    }

    if(sta_24V==TRUE)
    {
        *DC24V_state = FALSE;
    }
    else
    {
        *DC24V_state = TRUE;
    }   

}

/***************************************************************************//*!
 * \brief   获取轨旁控制箱散热风扇开启状态
 *
 * \param   state   轨旁控制箱散热风扇开启状态
 *
 * \return  0  表示成功
 *          -1 表示失败
 *
 *****************************************************************************/
INT8S getFanOpenState(INT8S temp,BOOLEAN * __far state)
{
    if(temp > HIGH_TEMP_LIMIT)
    {
        /*开启风扇进行散热控制*/
        *state = TRUE;
    }
    else
    {
        *state = FALSE;
    }

    return 0;  
}

/***************************************************************************//*!
 * \brief   根据风扇开启状态控制散热风扇开启或关闭
 *
 * \param   state   轨旁控制箱散热风扇开启状态
 *
 * \return  0  表示成功
 *          -1 表示失败
 *
 *****************************************************************************/
INT8S setFanOpenOrClose(BOOLEAN state)
{
    if(state)
    {
        /*引脚输出_电平,开启风扇*/
        Port_WritePinValue(PIN_SR_FAN1,PORT_PIN_LEVEL_HIGH);
        Port_WritePinValue(PIN_SR_FAN2,PORT_PIN_LEVEL_HIGH);
    }
    else
    {
        /*引脚输出_电平，关闭风扇*/
        Port_WritePinValue(PIN_SR_FAN1,PORT_PIN_LEVEL_LOW);
        Port_WritePinValue(PIN_SR_FAN2,PORT_PIN_LEVEL_LOW);
    }

    return 0;
}


