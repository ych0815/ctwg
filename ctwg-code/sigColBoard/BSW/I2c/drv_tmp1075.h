/*
*********************************************************************************************************
*
*                                      BOARD SUPPORT PACKAGE (BSP)
*                                         Frescale MC9S12
*
* File name   :   bsp_TMP1075.h
* Description :   TMP1075  driver.
* ===================================================================
*  History
* ===================================================================
*  Version 0.10    22 Oct. 2017    wangsq 
*      - original version
*********************************************************************************************************
*/

#ifndef DRV_TMP1075_H
#define DRV_TMP1075_H


/*
*********************************************************************************************************
*                                         PROCESSOR SPECIFICS
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

/* TMP1075设备地址数据结构定义 */
typedef union {
  byte Byte;
  struct {
    byte rw      :1;          /* Write/Read control bit. bit0==1,read;bit0==0, write. */
    byte sa      :7;          /* bit7-bit4=0100b,device addr bit3-bit1, */
  } Bits;
} BSP_TMP1075_DEVICE_ADDR_STR;



    

							   
/*
*********************************************************************************************************
*                                        MACROS
*********************************************************************************************************
*/

/* Read TMP1075 */
#define BSP_TMP1075_READ      (unsigned char)1

/* Write TMP1075 */
#define BSP_TMP1075_WRITE     (unsigned char)0

/* TMP1075 slave device base address */
#define BSP_TMP1075_SLAVE_BASE_ADDR     (unsigned char)0x48

/* TMP1075 slave address maximum */ 
#define BSP_TMP1075_SLAVE_ADDR_MAX      (unsigned char)0x07

/* TMP1075 slave address*/
#define BSP_TMP1075_SLAVE_ADDR          (unsigned char)0x00

/* TMP1075 temp register address*/
#define BSP_TMP1075_TEMP_ADDR           (unsigned char)0x00

/* TMP1075 config  register address*/
#define BSP_TMP1075_CFGR_ADDR           (unsigned char)0x01

/* TMP1075 low limit  register address*/
#define BSP_TMP1075_L_LIM_ADDR          (unsigned char)0x02

/* TMP1075 high limit  register address*/
#define BSP_TMP1075_H_LIM_ADDR          (unsigned char)0x03


#define BSP_TMP1075_DIE_ID_ADDR         (unsigned char)0x0F




/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/*
*********************************************************************************************************
  Function Name       : bsp_TMP1075_init
  Object              : 初始化TMP1075.
                      : 
  Input Parameters    : ParaSlaveAddr TMP1075 IC address .
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
unsigned char drv_tmp1075_init ( unsigned char ParaSlaveAddr );

/***************************************************************************//*!
 * \brief   获取环境温度值
 *
 * \param   无
 *
 * \return  温度值
 *          
 *
 *****************************************************************************/
unsigned char getEnvTemp(char *temp);
/*
*********************************************************************************************************
*                                           ERROR CHECKING
*********************************************************************************************************
*/


#endif        /* End of file                                          */

