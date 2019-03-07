/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : MeaVel.c
* 功能描述  : 测速模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/7        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "MeaVel.h"
#include "os_cpu.h"
#include "Com_Protocol.h"
#include "drv_sci.h"

#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
T_MeaVel g_meavel_info[2];
T_TrainVel  g_trainVeal_info;	  /*车速信息，由2个测速模块仲裁出的，单位:km/h*/

#pragma DATA_SEG DEFAULT

/***************************************************************************//*!
 * \brief   测速模块初始化
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void MeaVel_Init(void)
{
    INT8U i;
    for(i=0;i<2;i++)
    {
        g_meavel_info[i].errState   = FALSE;
        g_meavel_info[i].flag[0]    = FALSE;
        g_meavel_info[i].flag[1]    = FALSE;
        g_meavel_info[i].timeCnt[0] = 0;
        g_meavel_info[i].timeCnt[1] = 0;
        g_meavel_info[i].timeOut    = FALSE;
        g_meavel_info[i].errorCnt   = 0;
        g_meavel_info[i].curTicks   = 0;
        g_meavel_info[i].trainVel   = 0;
    }

    g_trainVeal_info.IsFinish = FALSE;
    g_trainVeal_info.value = 0;
}

/***************************************************************************//*!
 * \brief   测速模块重新初始化，用于车辆出库后使用
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void MeaVel_ReInit(void)
{
    INT8U i;
    for(i=0;i<2;i++)
    {
        g_meavel_info[i].errState   = FALSE;
        g_meavel_info[i].flag[0]    = FALSE;
        g_meavel_info[i].flag[1]    = FALSE;
        g_meavel_info[i].timeCnt[0] = 0;
        g_meavel_info[i].timeCnt[1] = 0;
        g_meavel_info[i].timeOut    = FALSE;
        // g_meavel_info[i].errorCnt   = 0;
        g_meavel_info[i].curTicks   = 0;
        g_meavel_info[i].trainVel   = 0;
    }

    g_trainVeal_info.IsFinish = FALSE;
    g_trainVeal_info.value = 0;
}

/***************************************************************************//*!
 * \brief   测速计算后台主循环函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void MeaVel_MainFunction(void)
{
    INT8U i;
    
    for(i=0;i<2;i++)
    {
        if((g_meavel_info[i].timeOut != TRUE)&&(g_meavel_info[i].errState != TRUE))
        {
            if(g_meavel_info[i].flag[0] == TRUE)
            {
                if((OSTimeGet()-g_meavel_info[i].curTicks)>700)
                {
                    /*超时处理*/
                    g_meavel_info[i].timeOut = TRUE;//将超时表示位置位

                    if(g_meavel_info[i].errorCnt++>5)
                    {
                        /*判定测速模块故障*/
                        g_meavel_info[i].errState = TRUE;

                        if(i==0)
                            Drv_Sci_Write("\r\nMeaVel_1 error",0,0);
                        if(i==1)
                            Drv_Sci_Write("\r\nMeaVel_2 error",0,0);
                    }
                }
                else
                {
                    if(g_meavel_info[i].flag[1] == TRUE)
                    {
                        /*计算车速*/
                        g_meavel_info[i].trainVel = ((INT32U)(MEAVEL_LENGTH*281.25f))/((INT32U)(g_meavel_info[i].timeCnt[1]-g_meavel_info[i].timeCnt[0]));
#if 1
                        Drv_Sci_Write("\r\ng1_trainVeal_info = ",0,0);
                        Drv_Sci_WriteShortAscii(g_meavel_info[i].trainVel);
#endif
                    }
                }        
            }
        }       
    }

    /*仲裁速度信息*/
    if(g_trainVeal_info.IsFinish == FALSE)
    {
        if(g_meavel_info[0].trainVel>0)
        {
            g_trainVeal_info.value = g_meavel_info[0].trainVel;
        }
        else if(g_meavel_info[1].trainVel>0)
        {
            g_trainVeal_info.value = g_meavel_info[1].trainVel;
        }
        else
        {
            g_trainVeal_info.value = 0;
        }

        if(g_trainVeal_info.value>0)
        {
            g_trainVeal_info.IsFinish = TRUE;
            Com_SetTrigerCnt(0u,COM_SIGCOLBOARD_COl,5);     /*设为5次立即触发*/
            Drv_Sci_Write("\r\ng2_trainVeal_info = ",0,0);
            Drv_Sci_WriteShortAscii(g_trainVeal_info.value);
        }        
    }

}

/***************************************************************************//*!
 * \brief   测速传感器1磁钢A信号触发的中断服务函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void trainVelMeaMd1_STA_INT(void)
{
    Drv_Sci_Write("\r\nECT_TC0:",0,0);
    Drv_Sci_WriteShortAscii(ECT_TC0);

    g_meavel_info[0].flag[0] = TRUE;
    g_meavel_info[0].timeCnt[0] = ECT_TC0;
    g_meavel_info[0].curTicks = OSTimeGet();
}

/***************************************************************************//*!
 * \brief  测速传感器1磁钢B信号触发的中断服务函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void trainVelMeaMd1_END_INT(void)
{
    Drv_Sci_Write("\r\nECT_TC1:",0,0);
    Drv_Sci_WriteShortAscii(ECT_TC1);
    
    g_meavel_info[0].flag[1] = TRUE;
    g_meavel_info[0].timeCnt[1] = ECT_TC1;
}

/***************************************************************************//*!
 * \brief   测速传感器2磁钢A信号触发的中断服务函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void trainVelMeaMd2_STA_INT(void)
{
    Drv_Sci_Write("\r\nECT_TC2:",0,0);
    Drv_Sci_WriteShortAscii(ECT_TC2);

    g_meavel_info[1].flag[0] = TRUE;
    g_meavel_info[1].timeCnt[0] = ECT_TC2;
    g_meavel_info[1].curTicks = OSTimeGet();
}

/***************************************************************************//*!
 * \brief  测速传感器2磁钢B信号触发的中断服务函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void trainVelMeaMd2_END_INT(void)
{
    Drv_Sci_Write("\r\nECT_TC3:",0,0);
    Drv_Sci_WriteShortAscii(ECT_TC3);

    g_meavel_info[1].flag[1] = TRUE;
    g_meavel_info[1].timeCnt[1] = ECT_TC3;
}