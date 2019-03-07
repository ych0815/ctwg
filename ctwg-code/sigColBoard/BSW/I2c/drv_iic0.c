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
  Object              : ��ʱ1uS
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
  Object              : ��ʼ��MC9S12EXP100ģ��IIC1.
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
    /* ģ��IIC��SCL��SDA����� */
    DRV_SCL0     = 1;
    DRV_SDA0     = 1;
    DRV_SCL0_DIR = DRV_IIC0_DIR_OUTPUT;
    DRV_SDA0_DIR = DRV_IIC0_DIR_OUTPUT;
}


/*
*********************************************************************************************************
  Function Name       : drv_iic0_start
  Object              : ��ʼ��MC9S12EXP100ģ��IIC1.
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
  Object              : ģ��IIC����1�ֽ�����.
                      : 
  Input Parameters    : ParaDate ��Ҫ���͵�����
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
  Object              : ģ��IIC����1�ֽ�����.
                      : 
  Input Parameters    : ParaTxAck
                      :    == FASLE ��ֹ����ACK
                      :    == TRUE  ����ACK
                      : 
  Output Parameters   : ��������
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
  Object              : ģ��IICֹͣ�ź�
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




