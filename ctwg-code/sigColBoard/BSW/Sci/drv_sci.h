/********************************************************************************//*��
*\file
*\brief      sci��������ͷ�ļ�

*\version    1.0.0
*\date       2015\12\24
*\author     zdj
*
*sci��������ͷ�ļ�
*
\verbatim
------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
                 
                 +------(NEW | MODify |ADD |DELete)------+
                 |
version          |    date(yyyy/mm/dd)  name        brief

---------------------+----------------+---------------------------------------------
 1.0.0         NEW       2015/12/24     zdj         create
------------------------------------------------------------------------------------
\endverbatim
************************************************************************************/

#ifndef DRV_SCI_H
#define DRV_SCI_H

#include "sci.h"

/*==================================================================================
*---------�궨��
===================================================================================*/

/**\brief  ����������*/
#define    DRV_SCI0_BDH            TNP16_3       /*BDH�Ĵ�����������*/
#define    DRV_SCI0_BAUD           115200        /*SCI0 ������(bps)*/
#define    DRV_SCI0_MODE           0             /*SCI0ģʽ����*/
#define    DRV_SCI0_INTCFG         SCI_TREN |SCI_RVEN |SCI_RIEN     /*�ж�����*/


#define    DRV_SCI2_BDH            TNP16_3       /*BDH�Ĵ�����������*/
#define    DRV_SCI2_BAUD           115200        /*SCI2 ������(bps)*/
#define    DRV_SCI2_MODE           0             /*SCI2ģʽ����*/
#define    DRV_SCI2_INTCFG         SCI_TREN |SCI_RVEN |SCI_RIEN     /*�ж�����*/


/**\brief  ��������*/
#define    DRV_SCI_RXBUFSIZE      (128u)   		/*���ܴ���FIFO��С*/
#define    DRV_SCI_RXBUFMASK      (128u - 1)   	/*���մ���FIFO����*/

#define    DRV_SCI_TXBUFSIZE      (128u)   		/*���ʹ���FIFO��С*/
#define    DRV_SCI_TXBUFMASK      (128u - 1)   	/*���ʹ���FIFO����*/

/**\brief  FLAG��־*/
#define    FLAG_EN                (1u)          /*��־��Ч*/
#define    FLAG_DIS               (0u)          /*��־��Ч*/

/*==================================================================================
*---------�������Ͷ���
===================================================================================*/    
/**\brief  SCI����FIFO����ṹ*/
typedef struct 
{
    uint8 in;
    uint8 out;
    uint8 err_flag;                 /*�����־*/
    uint8 buf[DRV_SCI_RXBUFSIZE];
}drv_sci_rxbuf;                         /*����fifo*/

/**\brief  SCI����FIFO����ṹ*/
typedef struct 
{
    uint8 in;
    uint8 out;
    uint8 buf[DRV_SCI_TXBUFSIZE];
}drv_sci_txbuf;                         /*����fifo*/


/*==================================================================================
*---------ȫ�ֱ�������
===================================================================================*/    


/*==================================================================================
*---------��������
===================================================================================*/ 
extern	uint16 Drv_Sci_Init(uint32 drv_sci_baud); 
extern	uint16 Drv_Sci_Read(uint8 *data,uint8 size, uint16 timeout);
extern	uint16 Drv_Sci_Write(const uint8 *data,uint8 size,uint16 timeout);
extern	void   Drv_Sci_WriteCharAscii(unsigned char c);
extern	void   Drv_Sci_WriteShortAscii(unsigned short s);
extern	void   Drv_Sci_WriteLongAscii(unsigned long l);
extern	void   Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);


#endif  /*#ifdef DRV_SCI_H*/        
