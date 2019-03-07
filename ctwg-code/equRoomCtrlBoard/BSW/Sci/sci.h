/********************************************************************************//*��
*\file
*\brief      sci�Ĵ������ó���ͷ�ļ�
*\version    1.0.0
*\date       2015\12\23
*\author     zdj
*
*sci�Ĵ������ó���ͷ�ļ�
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
#include  "MC9S12XEP100.h" 	/*����оƬ�Ĵ�������*/
#include  "Std_Types.h"
/*==================================================================================
*---------�궨��
===================================================================================*/

/**\brief  SCI�Ĵ���ȡֵ����*/ 
/*SCIBDH*/
#define      TNP4_1       	  0x60      /*��������Ϊ1/4*/
#define      TNP32_1      	  0x40      /*��������Ϊ1/32*/
#define      TNP16_1      	  0x20      /*��������Ϊ1/16*/
#define      TNP16_3      	  0x00      /*��������Ϊ3/16*/

#define      SCI_IREN         0x80      /*������ʹ��*/
/*SCICR1*/
#define      SCI_ODD          0x01      /*��У��*/
#define      SCI_PE           0x02      /*У��λʹ��*/
#define      SCI_ILTST        0x04      /*����λ������ʼ��ֹͣλ֮��*/
#define      SCI_WAKEADDR     0x08      /*1��ʾ����*/
#define      SCI_MNINE        0x10      /*һλ��ʼλ����λ����λ��һλֹͣλ*/
#define      SCI_RSRCEX       0x20      /*��������Ϊ�ⲿ����Ĵ��� ��loopsΪ1ʱ�Ž���ѡ��*/
#define      SCI_WAIDIS       0x40      /*SCI�ڵȴ�ģʽ�²�ʹ��*/
#define      SCI_LOOPS        0x80      /*����ģʽʹ��*/

/*SCICR2*/
#define      SCI_SBK          0x01      /*����ֹͣ����*/
#define      SCI_RWU          0x02      /*���ջ���λ*/
#define      SCI_RVEN         0x04      /*����ʹ��λ*/
#define      SCI_TREN         0x08      /*����ʹ��λ*/
#define      SCI_ILIE         0x10      /*�����ж�ʹ��*/
#define      SCI_RIEN         0x20      /*������������ж�ʹ��*/
#define      SCI_TCIE         0x40      /*��������ж�ʹ��*/
#define      SCI_TIEN         0x80      /*�����ж�ʹ��*/
 
/*==================================================================================
*---------��������
===================================================================================*/
extern  void sci_sbr_config(uint8 config,uint16 sbr,uint8 channel);
extern  void sci_config(uint8 config1,uint8 config2,uint8 channel);
extern  void sci_put_reg(uint8 data,uint8 channel);
extern  uint8 sci_get_reg(uint8 channel);

 #endif  /*#ifdef SCI_H*/
