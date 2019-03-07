/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Ect.h
* ��������  : 9s12xep100-Can����ͷ�ļ�(Ect.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj               New
**------------------------------------------------------------------------------------------------*/
#ifndef _ECT_H_
#define _ECT_H_

/************************************************/
#include  "MC9S12XEP100.h" 	/*����оƬ�Ĵ�������*/
#include  "Std_Types.h"

/************************************************/
typedef  enum
{
	Ect_IC_Type = 0u,   //���벶׽
	Ect_OC_Type = 1u    //����Ƚ�
}Ect_ICOC_Type;

/************************************************/
extern void Ect_IC_OC_Sel_Channel_Config(uint8 channel, Ect_ICOC_Type type);
extern void Ect_IC_Edg_Channel_Config(uint8 channel,uint8 edgModel);
extern void Ect_Enable_IC_OC_Interrupt(uint8 channel,boolean enable);



#endif