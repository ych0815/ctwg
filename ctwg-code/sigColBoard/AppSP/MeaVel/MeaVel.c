/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : MeaVel.c
* ��������  : ����ģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/7        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "MeaVel.h"
#include "os_cpu.h"
#include "Com_Protocol.h"
#include "drv_sci.h"

#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
T_MeaVel g_meavel_info[2];
T_TrainVel  g_trainVeal_info;	  /*������Ϣ����2������ģ���ٲó��ģ���λ:km/h*/

#pragma DATA_SEG DEFAULT

/***************************************************************************//*!
 * \brief   ����ģ���ʼ��
 *
 * \param   ��
 *
 * \return  ��
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
 * \brief   ����ģ�����³�ʼ�������ڳ��������ʹ��
 *
 * \param   ��
 *
 * \return  ��
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
 * \brief   ���ټ����̨��ѭ������
 *
 * \param   ��
 *
 * \return  ��
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
                    /*��ʱ����*/
                    g_meavel_info[i].timeOut = TRUE;//����ʱ��ʾλ��λ

                    if(g_meavel_info[i].errorCnt++>5)
                    {
                        /*�ж�����ģ�����*/
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
                        /*���㳵��*/
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

    /*�ٲ��ٶ���Ϣ*/
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
            Com_SetTrigerCnt(0u,COM_SIGCOLBOARD_COl,5);     /*��Ϊ5����������*/
            Drv_Sci_Write("\r\ng2_trainVeal_info = ",0,0);
            Drv_Sci_WriteShortAscii(g_trainVeal_info.value);
        }        
    }

}

/***************************************************************************//*!
 * \brief   ���ٴ�����1�Ÿ�A�źŴ������жϷ�����
 *
 * \param   ��
 *
 * \return  ��
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
 * \brief  ���ٴ�����1�Ÿ�B�źŴ������жϷ�����
 *
 * \param   ��
 *
 * \return  ��
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
 * \brief   ���ٴ�����2�Ÿ�A�źŴ������жϷ�����
 *
 * \param   ��
 *
 * \return  ��
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
 * \brief  ���ٴ�����2�Ÿ�B�źŴ������жϷ�����
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void trainVelMeaMd2_END_INT(void)
{
    Drv_Sci_Write("\r\nECT_TC3:",0,0);
    Drv_Sci_WriteShortAscii(ECT_TC3);

    g_meavel_info[1].flag[1] = TRUE;
    g_meavel_info[1].timeCnt[1] = ECT_TC3;
}