/********************************************************************************//*！
*\file
*\brief      sci寄存器配置程序头文件
*\version    1.0.0
*\date       2015\12\23
*\author     zdj
*
*sci寄存器配置程序头文件
*
\verbatim
------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
                 
                 +------(NEW | MODify |ADD |DELete)------+
                 |
version          |    date(yyyy/mm/dd)  name        brief

---------------------+----------------+---------------------------------------------
 1.0.0         NEW       2015/12/23    zdj         create
------------------------------------------------------------------------------------
\endverbatim
************************************************************************************/

#ifndef SCI_H
#define SCI_H

/************************************************/
#include  "MC9S12XEP100.h" 	/*包含芯片寄存器定义*/
#include  "Std_Types.h"
/*==================================================================================
*---------宏定义
===================================================================================*/

/**\brief  SCI寄存器取值定义*/ 
/*SCIBDH*/
#define      TNP4_1       	  0x60      /*传输脉宽为1/4*/
#define      TNP32_1      	  0x40      /*传输脉宽为1/32*/
#define      TNP16_1      	  0x20      /*传输脉宽为1/16*/
#define      TNP16_3      	  0x00      /*传输脉宽为3/16*/

#define      SCI_IREN         0x80      /*红外线使能*/
/*SCICR1*/
#define      SCI_ODD          0x01      /*奇校验*/
#define      SCI_PE           0x02      /*校验位使能*/
#define      SCI_ILTST        0x04      /*空闲位计数开始于停止位之后*/
#define      SCI_WAKEADDR     0x08      /*1表示唤醒*/
#define      SCI_MNINE        0x10      /*一位起始位，九位数据位，一位停止位*/
#define      SCI_RSRCEX       0x20      /*接收输入为外部传输寄存器 当loops为1时才进行选择*/
#define      SCI_WAIDIS       0x40      /*SCI在等待模式下不使能*/
#define      SCI_LOOPS        0x80      /*环回模式使能*/

/*SCICR2*/
#define      SCI_SBK          0x01      /*发送停止动作*/
#define      SCI_RWU          0x02      /*接收唤醒位*/
#define      SCI_RVEN         0x04      /*接收使能位*/
#define      SCI_TREN         0x08      /*发送使能位*/
#define      SCI_ILIE         0x10      /*空闲中断使能*/
#define      SCI_RIEN         0x20      /*接收满、溢出中断使能*/
#define      SCI_TCIE         0x40      /*传输完成中断使能*/
#define      SCI_TIEN         0x80      /*传输中断使能*/
 
/*==================================================================================
*---------函数声明
===================================================================================*/
extern  void sci_sbr_config(uint8 config,uint16 sbr,uint8 channel);
extern  void sci_config(uint8 config1,uint8 config2,uint8 channel);
extern  void sci_put_reg(uint8 data,uint8 channel);
extern  uint8 sci_get_reg(uint8 channel);

 #endif  /*#ifdef SCI_H*/
