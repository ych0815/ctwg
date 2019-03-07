/********************************************************************************//*！
*\file
*\brief      sci驱动程序头文件

*\version    1.0.0
*\date       2015\12\24
*\author     zdj
*
*sci驱动程序头文件
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
*---------宏定义
===================================================================================*/

/**\brief  波特率设置*/
#define    DRV_SCI0_BDH            TNP16_3       /*BDH寄存器参数设置*/
#define    DRV_SCI0_BAUD           115200        /*SCI0 波特率(bps)*/
#define    DRV_SCI0_MODE           0             /*SCI0模式设置*/
#define    DRV_SCI0_INTCFG         SCI_TREN |SCI_RVEN |SCI_RIEN     /*中断设置*/


#define    DRV_SCI2_BDH            TNP16_3       /*BDH寄存器参数设置*/
#define    DRV_SCI2_BAUD           115200        /*SCI2 波特率(bps)*/
#define    DRV_SCI2_MODE           0             /*SCI2模式设置*/
#define    DRV_SCI2_INTCFG         SCI_TREN |SCI_RVEN |SCI_RIEN     /*中断设置*/


/**\brief  串口设置*/
#define    DRV_SCI_RXBUFSIZE      (128u)   		/*接受串口FIFO大小*/
#define    DRV_SCI_RXBUFMASK      (128u - 1)   	/*接收串口FIFO掩码*/

#define    DRV_SCI_TXBUFSIZE      (128u)   		/*发送串口FIFO大小*/
#define    DRV_SCI_TXBUFMASK      (128u - 1)   	/*发送串口FIFO掩码*/

/**\brief  FLAG标志*/
#define    FLAG_EN                (1u)          /*标志有效*/
#define    FLAG_DIS               (0u)          /*标志无效*/

/*==================================================================================
*---------数据类型定义
===================================================================================*/    
/**\brief  SCI接收FIFO定义结构*/
typedef struct 
{
    uint8 in;
    uint8 out;
    uint8 err_flag;                 /*错误标志*/
    uint8 buf[DRV_SCI_RXBUFSIZE];
}drv_sci_rxbuf;                         /*接收fifo*/

/**\brief  SCI发送FIFO定义结构*/
typedef struct 
{
    uint8 in;
    uint8 out;
    uint8 buf[DRV_SCI_TXBUFSIZE];
}drv_sci_txbuf;                         /*发送fifo*/


/*==================================================================================
*---------全局变量定义
===================================================================================*/    


/*==================================================================================
*---------函数声明
===================================================================================*/ 
extern	uint16 Drv_Sci_Init(uint32 drv_sci_baud); 
extern	uint16 Drv_Sci_Read(uint8 *data,uint8 size, uint16 timeout);
extern	uint16 Drv_Sci_Write(const uint8 *data,uint8 size,uint16 timeout);
extern	void   Drv_Sci_WriteCharAscii(unsigned char c);
extern	void   Drv_Sci_WriteShortAscii(unsigned short s);
extern	void   Drv_Sci_WriteLongAscii(unsigned long l);
extern	void   Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);


#endif  /*#ifdef DRV_SCI_H*/        
