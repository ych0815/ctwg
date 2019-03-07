/********************************************************************************//*！
*\file
*\brief      sci驱动程序
*\version    1.0.0
*\date       2015\12\24
*\author     zdj
*
*sci驱动程序 (485---SCI3\SCI1   232---SCI6\SCI7)
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

#include "string.h"	/*add by chenms for strlen() function*/	
#include "drv_sci.h"
#include "bsp.h"	/*包含总线时钟资源声明*/

/**********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile drv_sci_rxbuf drv_sci0_rxbuf;   	/*SCI1接收FIFO*/ 
STATIC  volatile drv_sci_txbuf drv_sci0_txbuf;   	/*SCI1发送FIFO*/
STATIC  volatile uint8 drv_sci0_sendtag = 0;    	/*SCI1发送标记*/

STATIC  volatile drv_sci_rxbuf drv_sci2_rxbuf;
STATIC  volatile drv_sci_txbuf drv_sci2_txbuf;
STATIC  volatile uint8 	drv_sci2_sendtag = 0;
#pragma DATA_SEG DEFAULT

/*==================================================================================
*---------函数定义
===================================================================================*/
#if 1
static uint16 drv_sci0_init(uint32 drv_sci0_baud); 
static uint16 drv_sci0_writeLow(const uint8 *data,uint8 size); 
static uint16 drv_sci0_write(const uint8 *data,uint8 size,uint16 timeout); 
static uint16 drv_sci0_read(uint8 *data,uint8 size, uint16 timeout); 
static void   drv_sci0_txint(void); 
static void   drv_sci0_rxint(void); 
static void   drv_sci0_framerr(void); 
static void   drv_sci0_perr(void); 
static void   drv_Sci0_WriteCharAscii(unsigned char c);
static void   drv_Sci0_WriteShortAscii(unsigned short s);
static void   drv_Sci0_WriteLongAscii(unsigned long l);
static void   Det_Sci0_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);

static uint16 drv_sci2_init(uint32 drv_sci_baud); 
static uint16 drv_sci2_writeLow(const uint8 *data,uint8 size); 
static uint16 drv_sci2_write(const uint8 *data,uint8 size,uint16 timeout); 
static uint16 drv_sci2_read(uint8 *data,uint8 size, uint16 timeout); 
static void   drv_sci2_txint(void);
static void   drv_sci2_rxint(void); 
static void   drv_sci2_framerr(void); 
static void   drv_sci2_perr(void); 
static void   drv_Sci2_WriteCharAscii(unsigned char c);
static void   drv_Sci2_WriteShortAscii(unsigned short s);
static void   drv_Sci2_WriteLongAscii(unsigned long l);
static void   Det_Sci2_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId);
#endif


/********************************************************************************//*！
*\brief      SCI0中断函数
*
*====SCI0中断处理函数
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/  
void drv_sci0_int(void) 
{ 
    SCI0SR1STR scisr1_code;
	
    scisr1_code = _SCI0SR1;  
    if(scisr1_code.Bits.TDRE == FLAG_EN)    /*发送中断*/
    {
       drv_sci0_txint();
    }
         
    if(scisr1_code.Bits.RDRF_bit == FLAG_EN)  /*接收中断*/
    {
       drv_sci0_rxint();
    }
     
    if(scisr1_code.Bits.FE == FLAG_EN)   /*帧格式错误中断*/
    {
       drv_sci0_framerr();
    }
    
    if(scisr1_code.Bits.PF == FLAG_EN)   /*奇偶校验错误中断*/  
    {
       drv_sci0_perr();
    }
}

/********************************************************************************//*！
*\brief      SCI2中断函数
*
*====SCI2中断处理函数
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/  
void drv_sci2_int(void) 
{ 
    SCI2SR1STR scisr1_code;
	
    scisr1_code = _SCI2SR1;  
    if(scisr1_code.Bits.TDRE == FLAG_EN)    /*发送中断*/
    {
       drv_sci2_txint();
    }
         
    if(scisr1_code.Bits.RDRF_bit == FLAG_EN)  /*接收中断*/
    {
       drv_sci2_rxint();
    }
     
    if(scisr1_code.Bits.FE == FLAG_EN)   /*帧格式错误中断*/
    {
       drv_sci2_framerr();
    }
    
    if(scisr1_code.Bits.PF == FLAG_EN)   /*奇偶校验错误中断*/  
    {
       drv_sci2_perr();
    }
}


#if  1
/*******************************************************************************
             				SCI0实现为RS232
*******************************************************************************/
/**********************************************************************************
*\brief      SCI0初始化函数
*
*SCI0初始化设置
*
*\param    CPU_clk  :  
*
*return    无返回值
*
**********************************************************************************/
static uint16 drv_sci0_init(uint32 drv_sci0_baud) 
{
     uint16 errno;
     uint32 sci0_count_baud = 0;
     uint32  sci0_reg_baud = 0;
     uint32 sci0_baud_diff = 0;
     float   compare_num = 0.0;
	 uint32  bus_clock = 0u;

     /**********************/
	 Bsp_GetBusClock(&bus_clock);
     sci0_reg_baud   = bus_clock/16/drv_sci0_baud;
     sci0_count_baud = bus_clock/16/sci0_reg_baud;
     if(drv_sci0_baud >= sci0_count_baud)
     {
        sci0_baud_diff = drv_sci0_baud - sci0_count_baud; 
     }
     else
     {
        sci0_baud_diff = sci0_count_baud - drv_sci0_baud;
     }
     
     compare_num = sci0_baud_diff / drv_sci0_baud;
     
     if(compare_num >0.05)
     {
 		/*串口波特率配置值误差值过大*/
    	return 0x21;                                
     }
	 
     /**********************/
     sci_sbr_config(DRV_SCI0_BDH,	/*波特率配置*/
     				sci0_reg_baud,
     				0 );	
	 
     sci_config(	DRV_SCI0_MODE,	/*模式、中断配置*/
	 				DRV_SCI0_INTCFG,
	 				0 );
     
     drv_sci0_txbuf.in  = 0u; 	/*发送FIFO指针初始化*/
     drv_sci0_txbuf.out = 0u; 
     drv_sci0_sendtag 	= 0u; 	/*发送标记初始化*/
     
     drv_sci0_rxbuf.in  = 0u;	/*接收FIFO指针初始化*/	
     drv_sci0_rxbuf.out = 0u;
     return errno;
}

/********************************************************************************//*！
*\brief      SCI写函数
*
*SCI初始化设置
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:发送缓冲满,失败;
           =0:发送成功;
*
**********************************************************************************/
static uint16 drv_sci0_writeLow(const uint8 *data,uint8 size) 
{                                                                        
	uint16 index;
	uint8 dis = 0u;
	uint8 Tin = 0u;

	if(!size) 
	{
		size = (uint8)strlen(data);
	}

	/*计算发送剩余缓存是否足够*/
	dis = (uint8)(drv_sci0_txbuf.in - drv_sci0_txbuf.out);
	if((dis + size) > DRV_SCI_TXBUFSIZE )
	{
		/*发送缓存满,直接返回*/
		return(1u);
	}

	for(index=0u;index<size;index++)
	{
		Tin = drv_sci0_txbuf.in;
		drv_sci0_txbuf.buf[Tin & (DRV_SCI_TXBUFSIZE - 1u)] = data[index];
		drv_sci0_txbuf.in++;
	}
	
	if(0u == drv_sci0_sendtag)
	{
		/*发送未启动,启动发送*/
		drv_sci0_sendtag = 1u;
		SCI0CR2_TIE = 1;      /*使能发送中断*/
	}
    return 0;
}


/********************************************************************************//*！
*\brief      SCI写函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:发送缓冲满,失败;
           =0:发送成功;
*
**********************************************************************************/
static uint16 drv_sci0_write(const uint8 *data,uint8 size,uint16 timeout) 
{
#if 0
	uint16 ret = 0u;

	do
	{
		ret = drv_sci0_writeLow(data,size);
	}while(1u == ret);
	return(ret);
#else
    uint16 ret = 0u;

	ret = drv_sci0_writeLow(data,size);
	return(ret);
#endif
}
/********************************************************************************//*！
*\brief      SCI读函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:接收缓存中数据<指定接收数据长度(SIZE)
           =0:成功
*
**********************************************************************************/
static uint16 drv_sci0_read(uint8 *data,uint8 size, uint16 timeout) 
{
	uint8  dis = 0u;
	uint8  Tout = 0u; 
	uint8  index = 0u;
	
	dis = (uint8)(drv_sci0_rxbuf.in - drv_sci0_rxbuf.out);
	if(dis < size)
	{
		/*已接收到字节数量 < 期望字节数量*/
		return 1u;
	}

	for(index=0u;index<size;index++)
	{
		Tout = drv_sci0_rxbuf.out;
		data[index] = drv_sci0_rxbuf.buf[Tout & (DRV_SCI_RXBUFSIZE - 1u)];
		drv_sci0_rxbuf.out++;
	}
	return(0u);
}


/********************************************************************************//*！
*\brief      SCI(232)发送中断函数
*
*SCI(485)发送中断处理函数
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/  
static void drv_sci0_txint(void) 
{
	uint8 SendData = 0u;
	uint8 Tout = 0u;
	
    if(drv_sci0_txbuf.out == drv_sci0_txbuf.in)   /*fifo中无数据*/
    {
        drv_sci0_sendtag = 0;       /*正在发送标志清空*/
        SCI0CR2_TIE = 0;      		/*关闭发送中断*/
    }   
    else 
    {
    	Tout = drv_sci0_txbuf.out;
		SendData = drv_sci0_txbuf.buf[Tout & (DRV_SCI_TXBUFSIZE - 1u)];
		drv_sci0_txbuf.out++;
		sci_put_reg(SendData,10);
    }
}

/********************************************************************************//*！
*\brief      SCI接收中断函数
*
*SCI接收中断处理函数
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci0_rxint(void) 
{
    uint8 dis = 0u;
    uint8 data;
    uint8 Rin = 0u;
	
    data = sci_get_reg(10); /*从寄存器中读数据*/
	
	dis = (uint8)(drv_sci0_rxbuf.in - drv_sci0_rxbuf.out);
	if(dis < DRV_SCI_RXBUFSIZE)
	{
		/*已存储空间<设定空间,接收缓存未满*/
		Rin = drv_sci0_rxbuf.in;
		drv_sci0_rxbuf.buf[Rin & (DRV_SCI_RXBUFSIZE - 1u)] = data;
		drv_sci0_rxbuf.in++;
	}
	else
	{
		/*接收缓存满*/
	}
}

/********************************************************************************//*！
*\brief      SCI帧错误中断函数
*
*SCI帧错误中断处理函数.
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci0_framerr(void) 
{
    uint8 data;

	data = sci_get_reg(10); /*帧错误时从寄存器中读数，以清除中断标志位*/     
}

/********************************************************************************//*！
*\brief      SCI奇偶校验位错误中断函数
*
*SCI帧错误中断处理函数.
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci0_perr(void) 
{
     uint8 data;
     data = sci_get_reg(10); /*帧错误时从寄存器中读数，以清除中断标志位*/     
}

/*************************************************************************
* 函数名称: drv_Sci0_WriteCharAscii
* 函数描述: 以ASCII码形式，发送数据
* 可重入性: 不可重入
* 输入参数: c:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void drv_Sci0_WriteCharAscii(unsigned char c)
{
  unsigned char HalfByte;
  unsigned char i;
  
  for (i=0;i<2;i++)
  {
    if (i==0)
    {
        HalfByte=(c>>4)&0x0f;
    }
    else
    {
        HalfByte=(c&0x0f);
    }
    if (HalfByte<0x0a)
    {
        HalfByte = HalfByte+0x30;
        (void)drv_sci0_write(&HalfByte,1,0);
    }
    else
    {
        HalfByte = HalfByte-0x0a+'A';
        (void)drv_sci0_write(&HalfByte,1,52);
    }
  }
}

/*************************************************************************
* 函数名称: drv_Sci0_WriteShortAscii
* 函数描述: 以ASCII码形式，发送short型数据
* 可重入性: 不可重入
* 输入参数: s:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void drv_Sci0_WriteShortAscii(unsigned short s)
{
    drv_Sci0_WriteCharAscii((unsigned char)(s>>8));
    drv_Sci0_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* 函数名称: drv_Sci0_WriteLongAscii
* 函数描述: 以ASCII码形式，发送long型数据
* 可重入性: 不可重入
* 输入参数: l:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 硬件抽象层
*************************************************************************/
static void drv_Sci0_WriteLongAscii(unsigned long l)
{
    drv_Sci0_WriteShortAscii((unsigned short)(l>>16));
    drv_Sci0_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* 函数名称: Det_Sci0_ReportError
* 函数描述: 报告开发时错误;
* 可重入性: 不可重入
* 输入参数: ModuleId:模块Id号;
            InstanceId:
            ApiId   :API Id号;
            ErrorId :错误ID号  
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void  Det_Sci0_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
	(void)drv_sci0_write((const uint8 *)"\r\nDevelopment Error:ModuleId=0x",0,0);
	(void)drv_Sci0_WriteCharAscii(ModuleId);
	
	(void)drv_sci0_write((const uint8 *)",InstanceId=0x",0,0);
	(void)drv_Sci0_WriteCharAscii(InstanceId);
	
	(void)drv_sci0_write((const uint8 *)",ApiId=0x",0,0);
	(void)drv_Sci0_WriteCharAscii(ApiId);
	
	(void)drv_sci0_write((const uint8 *)",ErrorId=0x",0,0);
	(void)drv_Sci0_WriteCharAscii(ErrorId);
}


/*******************************************************************************
             				SCI2实现为RS232
*******************************************************************************/
/********************************************************************************//*！
*\brief    SCI2初始化函数
*
*SCI2初始化设置
*
*\param    CPU_clk  :  
*
*return    无返回值
*
**********************************************************************************/
static uint16 drv_sci2_init(uint32 drv_sci_baud) 
{
     uint16  errno;
     uint32  sci_count_baud = 0;
     uint32  sci_reg_baud = 0;
     uint32  sci_baud_diff = 0;
     float   compare_num = 0.0;
	 uint32  bus_clock = 0u;

     /**********************/
	 Bsp_GetBusClock(&bus_clock);  /*获取总线时钟*/
     sci_reg_baud   = bus_clock/16/drv_sci_baud;  /*计算波特率寄存器值*/
     sci_count_baud = bus_clock/16/sci_reg_baud;  /*根据计算波特率寄存器值,反算对应波特率*/
	 
     if(drv_sci_baud >= sci_count_baud)
     {	
        sci_baud_diff = drv_sci_baud - sci_count_baud; 
     }
     else
     {
        sci_baud_diff = sci_count_baud - drv_sci_baud;
     }
     
     compare_num = sci_baud_diff / drv_sci_baud; /*计算波特率误差百分比*/
     
     if(compare_num >0.05)
     {
 		/*串口波特率配置值误差值过大*/
    	return 0x21;                                
     }
	 
     /**********************/
     sci_sbr_config(DRV_SCI2_BDH,	/*波特率配置*/
     				sci_reg_baud,
     				2u );	
	 
     sci_config(	DRV_SCI2_MODE,	/*模式、中断配置*/
	 				DRV_SCI2_INTCFG,
	 				2u );
     
     drv_sci2_txbuf.in  = 0u;
     drv_sci2_txbuf.out = 0u; 
     drv_sci2_sendtag 	= 0u;
	 
     drv_sci2_rxbuf.in  = 0u;
     drv_sci2_rxbuf.out = 0u;
     return errno;
}

/********************************************************************************//*！
*\brief      SCI2写函数
*
*SCI初始化设置
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:发送缓冲满,失败;
           =0:发送成功;
*
**********************************************************************************/
static uint16 drv_sci2_writeLow(const uint8 *data,uint8 size) 
{                                                                        
	uint16 index;
	uint8 dis = 0u;
	uint8 Tin = 0u;

	if(!size) 
	{
		size = (uint8)strlen(data);
	}

	/*计算发送剩余缓存是否足够*/
	dis = (uint8)(drv_sci2_txbuf.in - drv_sci2_txbuf.out);
	if((dis + size) > DRV_SCI_TXBUFSIZE )
	{
		/*发送缓存满,直接返回*/
		return(1u);
	}

	for(index=0u;index<size;index++)
	{
		Tin = drv_sci2_txbuf.in;
		drv_sci2_txbuf.buf[Tin & (DRV_SCI_TXBUFSIZE - 1u)] = data[index];
		drv_sci2_txbuf.in++;
	}
	
	if(0u == drv_sci2_sendtag)
	{
		/*发送未启动,启动发送*/
		drv_sci2_sendtag = 1u;
		SCI2CR2_TIE = 1;      /*使能发送中断*/
	}
    return 0;
}

/********************************************************************************//*！
*\brief      SCI2写函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:发送缓冲满,失败;
           =0:发送成功;
*
**********************************************************************************/
static uint16 drv_sci2_write(const uint8 *data,uint8 size,uint16 timeout) 
{
#if 1
#if 0
	uint16 ret = 0u;
	uint16 count = 1000u;
	do
	{
		ret = drv_sci2_writeLow(data,size);
		count--;
	}while((1u == ret)&&(count>0u));
	return(ret);
#else
    uint16 ret = 0u;

	ret = drv_sci2_writeLow(data,size);
	return(ret);
#endif
#endif
}

/********************************************************************************//*！
*\brief      SCI读函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:接收缓存中数据<指定接收数据长度(SIZE)
           =0:成功
*
**********************************************************************************/
static uint16 drv_sci2_read(uint8 *data,uint8 size, uint16 timeout) 
{
	uint8  dis = 0u;
	uint8  Tout = 0u; 
	uint8  index = 0u;
	
	dis = (uint8)(drv_sci2_rxbuf.in - drv_sci2_rxbuf.out);
	if(dis < size)
	{
		/*已接收到字节数量 < 期望字节数量*/
		return 1u;
	}

	for(index=0u;index<size;index++)
	{
		Tout = drv_sci2_rxbuf.out;
		data[index] = drv_sci2_rxbuf.buf[Tout & (DRV_SCI_RXBUFSIZE - 1u)];
		drv_sci2_rxbuf.out++;
	}
	return(0u);
}

/********************************************************************************//*！
*\brief      SCI(232)发送中断函数
*
*
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/  
static void drv_sci2_txint(void) 
{
	uint8 SendData = 0u;
	uint8 Tout = 0u;
	
    if(drv_sci2_txbuf.out == drv_sci2_txbuf.in)   /*fifo中无数据*/
    {
        drv_sci2_sendtag = 0;       /*正在发送标志清空*/
        SCI2CR2_TIE = 0;      		/*关闭发送中断*/
    }   
    else 
    {
    	Tout = drv_sci2_txbuf.out;
		SendData = drv_sci2_txbuf.buf[Tout & (DRV_SCI_TXBUFSIZE - 1u)];
		drv_sci2_txbuf.out++;
		sci_put_reg(SendData,2);
    }
}

/********************************************************************************//*！
*\brief      SCI接收中断函数
*
*SCI接收中断处理函数
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci2_rxint(void) 
{
    uint8 dis = 0u;
    uint8 data;
    uint8 Rin = 0u;
	
    data = sci_get_reg(2); /*从寄存器中读数据*/
	
	dis = (uint8)(drv_sci2_rxbuf.in - drv_sci2_rxbuf.out);
	if(dis < DRV_SCI_RXBUFSIZE)
	{
		/*已存储空间<设定空间,接收缓存未满*/
		Rin = drv_sci2_rxbuf.in;
		drv_sci2_rxbuf.buf[Rin & (DRV_SCI_RXBUFSIZE - 1u)] = data;
		drv_sci2_rxbuf.in++;
	}
	else
	{
		/*接收缓存满*/
	}
}


/********************************************************************************//*！
*\brief      SCI帧错误中断函数
*
*SCI帧错误中断处理函数.
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci2_framerr(void) 
{
    volatile uint8 data;

	  data = sci_get_reg(2); /*帧错误时从寄存器中读数，以清除中断标志位*/     
}

/********************************************************************************//*！
*\brief      SCI奇偶校验位错误中断函数
*
*SCI帧错误中断处理函数.
*
*\param    无参数值
*
*return    无返回值
*
**********************************************************************************/ 
static void drv_sci2_perr(void) 
{
     volatile uint8 data;
     
     data = sci_get_reg(2); /*帧错误时从寄存器中读数，以清除中断标志位*/     
}

/*************************************************************************
* 函数名称: drv_Sci2_WriteCharAscii
* 函数描述: 以ASCII码形式，发送数据
* 可重入性: 不可重入
* 输入参数: c:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void drv_Sci2_WriteCharAscii(unsigned char c)
{
  unsigned char HalfByte;
  unsigned char i;
  
  for (i=0;i<2;i++)
  {
    if (i==0)
    {
        HalfByte=(c>>4)&0x0f;
    }
    else
    {
        HalfByte=(c&0x0f);
    }
    if (HalfByte<0x0a)
    {
        HalfByte = HalfByte+0x30;
        (void)drv_sci2_write(&HalfByte,1,0);
    }
    else
    {
        HalfByte = HalfByte-0x0a+'A';
        (void)drv_sci2_write(&HalfByte,1,52);
    }
  }
}

/*************************************************************************
* 函数名称: drv_Sci2_WriteShortAscii
* 函数描述: 以ASCII码形式，发送short型数据
* 可重入性: 不可重入
* 输入参数: s:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void drv_Sci2_WriteShortAscii(unsigned short s)
{
    drv_Sci2_WriteCharAscii((unsigned char)(s>>8));
    drv_Sci2_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* 函数名称: drv_Sci2_WriteLongAscii
* 函数描述: 以ASCII码形式，发送long型数据
* 可重入性: 不可重入
* 输入参数: l:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 硬件抽象层
*************************************************************************/
static void drv_Sci2_WriteLongAscii(unsigned long l)
{
    drv_Sci2_WriteShortAscii((unsigned short)(l>>16));
    drv_Sci2_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* 函数名称: Det_Sci2_ReportError
* 函数描述: 报告开发时错误;
* 可重入性: 不可重入
* 输入参数: ModuleId:模块Id号;
            InstanceId:
            ApiId   :API Id号;
            ErrorId :错误ID号  
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
static void  Det_Sci2_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
	(void)drv_sci2_write((const uint8 *)"\r\nDevelopment Error:ModuleId=0x",0,0);
	(void)drv_Sci2_WriteCharAscii((uint8)ModuleId);
	
	(void)drv_sci2_write((const uint8 *)",InstanceId=0x",0,0);
	(void)drv_Sci2_WriteCharAscii(InstanceId);
	
	(void)drv_sci2_write((const uint8 *)",ApiId=0x",0,0);
	(void)drv_Sci2_WriteCharAscii(ApiId);
	
	(void)drv_sci2_write((const uint8 *)",ErrorId=0x",0,0);
	(void)drv_Sci2_WriteCharAscii(ErrorId);
}
#endif


/********************************************************************************//*！
*\brief      SCI初始化函数
*
*SCI初始化设置
*
*\param    CPU_clk  :  
*
*return    无返回值
*
**********************************************************************************/
uint16 Drv_Sci_Init(uint32 drv_sci_baud) 
{
	uint16  Ret = 0u;
	
    Ret = drv_sci2_init(drv_sci_baud);
	return(Ret);
}

/********************************************************************************//*！
*\brief      SCI读函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:接收缓存中数据<指定接收数据长度(SIZE)
           =0:成功
*
**********************************************************************************/
uint16 Drv_Sci_Read(uint8 *data,uint8 size, uint16 timeout)
{
	uint16  Ret = 0u;

	Ret = drv_sci2_read(data,size,timeout);
	return(Ret);
}

/********************************************************************************//*！
*\brief      SCI写函数
*
*
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    =1:发送缓冲满,失败;
           =0:发送成功;
*
**********************************************************************************/
uint16 Drv_Sci_Write(const uint8 *data,uint8 size,uint16 timeout)
{
	uint16  Ret = 0u;
	
//	do
//	{
		Ret = drv_sci2_write(data,size,timeout);
	//}while(1u == Ret);
	return(Ret);
}

/*************************************************************************
* 函数名称: Drv_Sci_WriteCharAscii
* 函数描述: 以ASCII码形式，发送数据
* 可重入性: 不可重入
* 输入参数: c:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
void   Drv_Sci_WriteCharAscii(unsigned char c)
{
  unsigned char HalfByte;
  unsigned char i;
  
  for (i=0;i<2;i++)
  {
    if (i==0)
    {
        HalfByte=(c>>4)&0x0f;
    }
    else
    {
        HalfByte=(c&0x0f);
    }
    if (HalfByte<0x0a)
    {
        HalfByte = HalfByte+0x30;
        (void)Drv_Sci_Write(&HalfByte,1,0);
    }
    else
    {
        HalfByte = HalfByte-0x0a+'A';
        (void)Drv_Sci_Write(&HalfByte,1,52);
    }
  }
}

/*************************************************************************
* 函数名称: Drv_Sci_WriteShortAscii
* 函数描述: 以ASCII码形式，发送short型数据
* 可重入性: 不可重入
* 输入参数: s:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
void   Drv_Sci_WriteShortAscii(unsigned short s)
{
    Drv_Sci_WriteCharAscii((unsigned char)(s>>8));
    Drv_Sci_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* 函数名称: Drv_Sci_WriteLongAscii
* 函数描述: 以ASCII码形式，发送long型数据
* 可重入性: 不可重入
* 输入参数: l:待发送数据;
* 输出参数: 无
* 返回值:   无
* 备    注: 硬件抽象层
*************************************************************************/
void   Drv_Sci_WriteLongAscii(unsigned long l)
{
    Drv_Sci_WriteShortAscii((unsigned short)(l>>16));
    Drv_Sci_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* 函数名称: Det_ReportError
* 函数描述: 报告开发时错误;
* 可重入性: 不可重入
* 输入参数: ModuleId:模块Id号;
            InstanceId:
            ApiId   :API Id号;
            ErrorId :错误ID号  
* 输出参数: 无
* 返回值:   无
* 备    注: 
*************************************************************************/
void  Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
	Det_Sci2_ReportError(ModuleId,InstanceId,ApiId,ErrorId);
}


