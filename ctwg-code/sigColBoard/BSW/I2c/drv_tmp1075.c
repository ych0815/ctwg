/*
*********************************************************************************************************
*
*                                      BOARD SUPPORT PACKAGE (BSP)
*                                         Frescale MC9S12
*
* File name   :   drv_tmp1075.c
* Description :   tmp1075 driver.
* ===================================================================
*  History
* ===================================================================
*  Version 0.10    22 Oct 2017    wangsq 
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
  Function Name       : bsp_tmp1075_init
  Object              : 初始化tmp1075.
                      : 
  Input Parameters    : ParaSlaveAddr tmp1075 IC address .
                      :     Pin | A2 | A1 | A0 | parameter value
                      :     ----+----+----+----+-------------------
                      :         | 0  | 0  | 0  | ParaSlaveAddr = 0
                      :     ----+----+----+----+-------------------
                      :         | 0  | 0  | 1  | ParaSlaveAddr = 1
                      :     ----+----+----+----+-------------------
                      :         | 0  | 1  | 0  | ParaSlaveAddr = 2
                      :     ----+----+----+----+-------------------
                      :         | 0  | 1  | 1  | ParaSlaveAddr = 3
                      :     ----+----+----+----+-------------------
                      :         | 1  | 0  | 0  | ParaSlaveAddr = 4
                      :     ----+----+----+----+-------------------
                      :         | 1  | 0  | 1  | ParaSlaveAddr = 5
                      :     ----+----+----+----+-------------------
                      :         | 1  | 1  | 0  | ParaSlaveAddr = 6
                      :     ----+----+----+----+-------------------
                      :         | 1  | 1  | 1  | ParaSlaveAddr = 7
                      :
  Output Parameters   : ==0 success 
                      : !=0 fault
                      : 
  Functions called    : none
*********************************************************************************************************
*/
unsigned char drv_tmp1075_init ( unsigned char ParaSlaveAddr )
{
  unsigned char                 tmpErr;
  BSP_TMP1075_DEVICE_ADDR_STR   tmpSlaveAddr;
  
  /*****************************************************************/
  /*1. Parameter check */
  if ( ParaSlaveAddr>BSP_TMP1075_SLAVE_ADDR_MAX ) 
  {/* Parameter "ParaSlaveAddr" invalid */
      return (unsigned char)1; 
  }

  /*****************************************************************/
  /* 2、初始化IIC */
  drv_iic0_init();
  
  /*****************************************************************/
  /* 3、Set TTMP1075output port initial status */
  tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
  tmpSlaveAddr.Bits.rw = BSP_TMP1075_WRITE;
  
  /*****************************************************************/
  /* 3.1、Transmit start signal */
  /* send start signal */
  drv_iic0_start();
  
  /* 3.2 Transmit TMP1075 slave address */
  tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)2;  
  }
  
  /*****************************************************************/
  /* 3.3、Transmit TTMP1075 config register address */
  tmpErr = drv_iic0_send(BSP_TMP1075_CFGR_ADDR);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)3;  
  }
  
  /*****************************************************************/
  /* 3.4?TTransmit TMP1075 config register value */
  tmpErr = drv_iic0_send(0x00);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)4;  
  }

  tmpErr = drv_iic0_send(0xFF);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)5;  
  }
  
  /*****************************************************************/
  /* 3.5、Transmit stop signal  */
  drv_iic0_stop();
  
  /*****************************************************************/
  /* 4、Set TTMP1075 all port pin is enabled as output */
  tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
  tmpSlaveAddr.Bits.rw = BSP_TMP1075_WRITE;
  
  /*****************************************************************/
  /* 4.1、Transmit start signal */
  /* send start signal */
  drv_iic0_start();
  
  /* 4.2 Transmit TMP1075 slave address */
  tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)6;  
  }
  
  /*****************************************************************/
  /* 4.3、Transmit TTMP1075 low limit register address */
  tmpErr = drv_iic0_send(BSP_TMP1075_L_LIM_ADDR);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)7;  
  }
  
  /*****************************************************************/
  /* 4.4?TTransmit TMP1075 low limit register data  */
  tmpErr = drv_iic0_send(0xCE);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)8;  
  }

  tmpErr = drv_iic0_send(0x00);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)9;  
  }
  
  /*****************************************************************/
  /* 4.5、Transmit stop signal  */
  drv_iic0_stop();

    /*****************************************************************/
  /* 5、Set TTMP1075 all port pin is enabled as output */
  tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
  tmpSlaveAddr.Bits.rw = BSP_TMP1075_WRITE;
  
  /*****************************************************************/
  /* 5.1、Transmit start signal */
  /* send start signal */
  drv_iic0_start();
  
  /* 5.2 Transmit TMP1075 slave address */
  tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)10;  
  }
  
  /*****************************************************************/
  /* 5.3、Transmit TTMP1075 low limit register address */
  tmpErr = drv_iic0_send(BSP_TMP1075_H_LIM_ADDR);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)11;  
  }
  
  /*****************************************************************/
  /* 5.4?TTransmit TMP1075 low limit register data  */
  tmpErr = drv_iic0_send(0x78);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)12;  
  }

  tmpErr = drv_iic0_send(0x00);
  if (tmpErr!=0) 
  {/* Timeout */
      
      drv_iic0_stop();
      return (unsigned char)13;  
  }
  
  /*****************************************************************/
  /* 5.5、Transmit stop signal  */
  drv_iic0_stop();
  
  /*****************************************************************/
  /* 6. success*/
  return (unsigned char)0;
   
}


/***************************************************************************//*!
 * \brief   读取寄存器的值
 *
 * \param   ParaSlaveAddr 从机地址
 *          regAddr       寄存器地址
 *          data          寄存器数据指针
 *          size          寄存器数据大小
 *
 * \return  返回 0   表示成功
 *          返回 非0 表示失败
 *          
 *
 *****************************************************************************/
static unsigned char drv_tmp1075_read( unsigned char ParaSlaveAddr, unsigned char regAddr ,unsigned char *data,unsigned char size)
{
    /**/
    unsigned char                  tmpErr;
    BSP_TMP1075_DEVICE_ADDR_STR    tmpSlaveAddr;

    /*****************************************************************/
    /*1. Parameter check */
    if ( ParaSlaveAddr>BSP_TMP1075_SLAVE_ADDR_MAX ) 
    {/* Parameter "ParaSlaveAddr" invalid */
        return (unsigned char)1; 
    }

    /* 2、Set TTMP1075 */
    tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
    tmpSlaveAddr.Bits.rw = BSP_TMP1075_WRITE;

    /*****************************************************************/
    /* 2.1、Transmit start signal */
    /* send start signal */
    drv_iic0_start();

    /* 2.2 Transmit TMP1075 slave address */
    tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
    if (tmpErr!=0) 
    {/* Timeout */
        
        drv_iic0_stop();
        return (unsigned char)2;  
    }

    /*****************************************************************/
    /* 2.3、Transmit TTMP1075 dest register address */
    tmpErr = drv_iic0_send(regAddr);
    if (tmpErr!=0) 
    {/* Timeout */
        
        drv_iic0_stop();
        return (unsigned char)3;  
    }


    /* 2、Set TTMP1075  */
    tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
    tmpSlaveAddr.Bits.rw = BSP_TMP1075_WRITE;

    /*****************************************************************/
    /* 2.1、Transmit start signal */
    /* send start signal */
    drv_iic0_start();

    /* 2.2 Transmit TMP1075 slave address */
    tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
    if (tmpErr!=0) 
    {/* Timeout */
        
        drv_iic0_stop();
        return (unsigned char)4;  
    }

    /* 2、Set TTMP1075 output port value */
    tmpSlaveAddr.Bits.sa = BSP_TMP1075_SLAVE_BASE_ADDR | ParaSlaveAddr;
    tmpSlaveAddr.Bits.rw = BSP_TMP1075_READ;

    /*****************************************************************/
    /* 2.1、Transmit start signal */
    /* send start signal */
    drv_iic0_start();

    /* 2.2 Transmit TMP1075 slave address */
    tmpErr = drv_iic0_send( tmpSlaveAddr.Byte );
    if (tmpErr!=0) 
    {/* Timeout */
        
        drv_iic0_stop();
        return (unsigned char)5;  
    }

    /* Receive temp register value bit15~8 */
    *data = drv_iic0_receive(1);
    
    /* Receive temp register value bit7~0 */
    *(data+1) = drv_iic0_receive(1);

    /* Transmit stop signal  */
    drv_iic0_stop();

    return (unsigned char)0;
}

/***************************************************************************//*!
 * \brief   获取环境温度值
 *
 * \param   temp 温度值地址
 *
 * \return  0表示成功
            非0表示失败
 *          
 *
 *****************************************************************************/
unsigned char getEnvTemp(char *temp)
{
    unsigned char iRet = 0;
    unsigned char tmps1[2] = {0x00,0x00}; 
    unsigned int tmp = 0;

    /*read tmp1075 temp register value*/
    iRet = drv_tmp1075_read(BSP_TMP1075_SLAVE_ADDR,BSP_TMP1075_TEMP_ADDR,tmps1,2);
    if(iRet != 0)
    {   /*timeout*/
        Drv_Sci_Write("\r\ndrv_tmp1075_read failed",0,0);
        return 1;
    }

    /*get temp value 15~4bit*/
    tmp = (unsigned int)(((((unsigned int)tmps1[0])<<8)|((unsigned int)tmps1[1]))>>4);

    /*convert temp value*/
    if(tmp > 2048)
    {
        *temp = ((tmp-4096)*0.0625f);
    }
    else    
    {
        *temp = (tmp*0.0625f);
    }
    
    return 0;
}

