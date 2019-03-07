/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : drv_ect.c
* 功能描述  : 9s12xep100-drv_ect驱源文件(drv_ect.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj                New
**------------------------------------------------------------------------------------------------*/
#include "drv_ect.h"
#include "drv_sci.h"
#include "Osal.h"
#include "MeaVel.h"



void Drv_Ect_Init(void) 
{
    /*设置ECT0为输入捕捉 仅上降沿触发 开启中断*/
    Ect_IC_OC_Sel_Channel_Config(0,Ect_IC_Type);
    Ect_IC_Edg_Channel_Config(0,1);
    Ect_Enable_IC_OC_Interrupt(0,TRUE);   

    /*设置ECT1为输入捕捉 仅上降沿触发 开启中断*/
    Ect_IC_OC_Sel_Channel_Config(1,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(1,1); 
    Ect_Enable_IC_OC_Interrupt(1,TRUE);     

    /*设置ECT2为输入捕捉 仅上降沿触发 开启中断*/
    Ect_IC_OC_Sel_Channel_Config(2,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(2,1); 
    Ect_Enable_IC_OC_Interrupt(2,TRUE);     
    
    /*设置ECT3为输入捕捉 仅上降沿触发 开启中断*/
    Ect_IC_OC_Sel_Channel_Config(3,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(3,1); 
    Ect_Enable_IC_OC_Interrupt(3,TRUE);                
}
 
/*ECT0 中断函数*/
void drv_ect0_int(void) 
{
    ECT_TFLG1 |= 0x01;
    trainVelMeaMd1_STA_INT();
}

/*ECT1 中断函数*/
void drv_ect1_int(void) 
{
    ECT_TFLG1 |= 0x02;
    trainVelMeaMd1_END_INT();
}

/*ECT2 中断函数*/
void drv_ect2_int(void) 
{
    ECT_TFLG1 |= 0x04;
    trainVelMeaMd2_STA_INT();
}

/*ECT3 中断函数*/
void drv_ect3_int(void) 
{
    ECT_TFLG1 |= 0x08;
    trainVelMeaMd2_END_INT();
}