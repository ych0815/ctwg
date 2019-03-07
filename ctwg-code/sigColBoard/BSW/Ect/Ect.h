/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Ect.h
* 功能描述  : 9s12xep100-Can驱动头文件(Ect.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj               New
**------------------------------------------------------------------------------------------------*/
#ifndef _ECT_H_
#define _ECT_H_

/************************************************/
#include  "MC9S12XEP100.h" 	/*包含芯片寄存器定义*/
#include  "Std_Types.h"

/************************************************/
typedef  enum
{
	Ect_IC_Type = 0u,   //输入捕捉
	Ect_OC_Type = 1u    //输出比较
}Ect_ICOC_Type;

/************************************************/
extern void Ect_IC_OC_Sel_Channel_Config(uint8 channel, Ect_ICOC_Type type);
extern void Ect_IC_Edg_Channel_Config(uint8 channel,uint8 edgModel);
extern void Ect_Enable_IC_OC_Interrupt(uint8 channel,boolean enable);



#endif