/*
*********************************************************************************************************
*
*                                      BOARD SUPPORT PACKAGE (BSP)
*                                         Frescale MC9S12
*
* File name   :   bsp_iic1.c
* Description :   Frescale MC9S12EXP100 simulating IIC1 driver.
* ===================================================================
*  History
* ===================================================================
*  Version 0.10    5 Oct 2017    wangsq 
*      - original version
*********************************************************************************************************
*/

#include "bsw.h"

/*
*********************************************************************************************************
*                                        CONSTANTS
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                        MACROS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        PROTOTYPES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                        DATATYPES
*
* 
*          
*********************************************************************************************************
*/
 





/*
*********************************************************************************************************
*                                        GLOBALS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
  Function Name       : drv_iic0_delay
  Object              : 延时1uS
                      : 
  Input Parameters    : none
                      : 
  Output Parameters   : none
                      : 
  Functions called    : none
*********************************************************************************************************
*/
#define drv_iic0_delay()        asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                                asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                                asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");\
                                asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");
 /*
*********************************************************************************************************
  Function Name       : drv_iic0_init
  Object              : 初始化MC9S12EXP100模拟IIC1.
                      : 
  Input Parameters    : none
                      : 
  Output Parameters   : none
                      : 
  Functions called    : none
*********************************************************************************************************
*/
void drv_iic0_init(void) 
{
    /* 模拟IIC的SCL和SDA输出高 */
    DRV_SCL0     = 1;
    DRV_SDA0     = 1;
    DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
    DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
}


/*
*********************************************************************************************************
  Function Name       : drv_iic0_start
  Object              : 初始化MC9S12EXP100模拟IIC1.
                      : 
  Input Parameters    : none
                      : 
  Output Parameters   : none
                      : 
  Functions called    : none
*********************************************************************************************************
*/
void drv_iic0_start(void)    
{
    DRV_SDA0 = 1;
    DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
    DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
    drv_iic0_delay();
    DRV_SCL0 = 1;
    drv_iic0_delay();
    drv_iic0_delay();
    DRV_SDA0 = 0;
    drv_iic0_delay();
    drv_iic0_delay();
    DRV_SCL0 = 0;
}

/*
*********************************************************************************************************
  Function Name       : drv_iic0_send
  Object              : 模拟IIC发送1字节数据.
                      : 
  Input Parameters    : ParaDate 需要发送的数据
                      : 
  Output Parameters   : 
                      : == 0 success 
                      : != 0 false
  Functions called    : none
*********************************************************************************************************
*/
unsigned char  drv_iic0_send(unsigned char ParaDate)  //
{
    unsigned char i=8;
    
    /* send data */
    DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
    DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
    while(i) 
    {
        DRV_SCL0 = 0;  
        drv_iic0_delay();
        DRV_SDA0=(ParaDate&0x80)>>7; 
        ParaDate<<=1; 
        drv_iic0_delay();
        DRV_SCL0 = 1;
        drv_iic0_delay();
        drv_iic0_delay();
        i--;     
    }
    
    /* read ack signal */
    DRV_SCL0     = 0;
    DRV_SDA0_DIR = DRV_IIC0_DIR_INPUT;
    drv_iic0_delay();
    drv_iic0_delay();
    DRV_SCL0     = 1;
    drv_iic0_delay();
    if( DRV_SDA0 == 0 ) 
    {/* succedd */
        i=0;
    }else 
    {/* false */
        i=1;
    }
    drv_iic0_delay();
    DRV_SCL0 = 0;

    
    return i;  
}

/*
*********************************************************************************************************
  Function Name       : drv_iic0_receive
  Object              : 模拟IIC接收1字节数据.
                      : 
  Input Parameters    : ParaTxAck
                      :    == FASLE 禁止发送ACK
                      :    == TRUE  发送ACK
                      : 
  Output Parameters   : 接收数据
                      : 
  Functions called    : none
*********************************************************************************************************
*/
unsigned char drv_iic0_receive ( unsigned char ParaTxAck ) 
{
    unsigned char i=8;
    unsigned char data=0;

    DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
    DRV_SDA0_DIR = DRV_IIC0_DIR_INPUT;
    while(i) 
    {
        DRV_SCL0 = 0;  
        drv_iic0_delay();
        drv_iic0_delay();
        DRV_SCL0 = 1;
        drv_iic0_delay();
        data<<=1;
        data|=DRV_SDA0;
        drv_iic0_delay();
        i--;     
    }
    
    if(ParaTxAck) 
    {
        /* send ack signal */
        DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
        DRV_SCL0 = 0;
        drv_iic0_delay();
        DRV_SDA0 = 0;
        drv_iic0_delay();
        DRV_SCL0 = 1;
        drv_iic0_delay();
        drv_iic0_delay();
    }
    
    DRV_SCL0 = 0;
    return(data); 

}

/*
*********************************************************************************************************
  Function Name       : drv_iic0_stop
  Object              : 模拟IIC停止信号
                      : 
  Input Parameters    : none
                      : 
  Output Parameters   : none
                      : 
  Functions called    : none
*********************************************************************************************************
*/
void drv_iic0_stop(void) 
{
  DRV_SCL0     = 0;
  DRV_SDA0     = 0;
  DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
  DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
  drv_iic0_delay(); 
  drv_iic0_delay();
  DRV_SCL0 = 1;
  drv_iic0_delay();
  DRV_SDA0 = 1; 
  drv_iic0_delay(); 
  drv_iic0_delay();
  DRV_SCL0_DIR = DRV_IIC0_DIR_INPUT;
  DRV_SDA0_DIR = DRV_IIC0_DIR_INPUT;
}




