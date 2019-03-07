/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : drv_ect.c
* ��������  : 9s12xep100-drv_ect��Դ�ļ�(drv_ect.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj                New
**------------------------------------------------------------------------------------------------*/
#include "drv_ect.h"
#include "drv_sci.h"
#include "Osal.h"
#include "MeaVel.h"



void Drv_Ect_Init(void) 
{
    /*����ECT0Ϊ���벶׽ ���Ͻ��ش��� �����ж�*/
    Ect_IC_OC_Sel_Channel_Config(0,Ect_IC_Type);
    Ect_IC_Edg_Channel_Config(0,1);
    Ect_Enable_IC_OC_Interrupt(0,TRUE);   

    /*����ECT1Ϊ���벶׽ ���Ͻ��ش��� �����ж�*/
    Ect_IC_OC_Sel_Channel_Config(1,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(1,1); 
    Ect_Enable_IC_OC_Interrupt(1,TRUE);     

    /*����ECT2Ϊ���벶׽ ���Ͻ��ش��� �����ж�*/
    Ect_IC_OC_Sel_Channel_Config(2,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(2,1); 
    Ect_Enable_IC_OC_Interrupt(2,TRUE);     
    
    /*����ECT3Ϊ���벶׽ ���Ͻ��ش��� �����ж�*/
    Ect_IC_OC_Sel_Channel_Config(3,Ect_IC_Type);     
    Ect_IC_Edg_Channel_Config(3,1); 
    Ect_Enable_IC_OC_Interrupt(3,TRUE);                
}
 
/*ECT0 �жϺ���*/
void drv_ect0_int(void) 
{
    ECT_TFLG1 |= 0x01;
    trainVelMeaMd1_STA_INT();
}

/*ECT1 �жϺ���*/
void drv_ect1_int(void) 
{
    ECT_TFLG1 |= 0x02;
    trainVelMeaMd1_END_INT();
}

/*ECT2 �жϺ���*/
void drv_ect2_int(void) 
{
    ECT_TFLG1 |= 0x04;
    trainVelMeaMd2_STA_INT();
}

/*ECT3 �жϺ���*/
void drv_ect3_int(void) 
{
    ECT_TFLG1 |= 0x08;
    trainVelMeaMd2_END_INT();
}