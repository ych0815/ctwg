/********************************************************************************//*��
*\file
*\brief      sci��������
*\version    1.0.0
*\date       2015\12\24
*\author     zdj
*
*sci�������� (485---SCI3\SCI1   232---SCI6\SCI7)
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
#include "bsp.h"	/*��������ʱ����Դ����*/

/**********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
STATIC  volatile drv_sci_rxbuf drv_sci0_rxbuf;   	/*SCI1����FIFO*/ 
STATIC  volatile drv_sci_txbuf drv_sci0_txbuf;   	/*SCI1����FIFO*/
STATIC  volatile uint8 drv_sci0_sendtag = 0;    	/*SCI1���ͱ��*/

STATIC  volatile drv_sci_rxbuf drv_sci2_rxbuf;
STATIC  volatile drv_sci_txbuf drv_sci2_txbuf;
STATIC  volatile uint8 	drv_sci2_sendtag = 0;
#pragma DATA_SEG DEFAULT

/*==================================================================================
*---------��������
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


/********************************************************************************//*��
*\brief      SCI0�жϺ���
*
*====SCI0�жϴ�����
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/  
void drv_sci0_int(void) 
{ 
    SCI0SR1STR scisr1_code;
	
    scisr1_code = _SCI0SR1;  
    if(scisr1_code.Bits.TDRE == FLAG_EN)    /*�����ж�*/
    {
       drv_sci0_txint();
    }
         
    if(scisr1_code.Bits.RDRF_bit == FLAG_EN)  /*�����ж�*/
    {
       drv_sci0_rxint();
    }
     
    if(scisr1_code.Bits.FE == FLAG_EN)   /*֡��ʽ�����ж�*/
    {
       drv_sci0_framerr();
    }
    
    if(scisr1_code.Bits.PF == FLAG_EN)   /*��żУ������ж�*/  
    {
       drv_sci0_perr();
    }
}

/********************************************************************************//*��
*\brief      SCI2�жϺ���
*
*====SCI2�жϴ�����
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/  
void drv_sci2_int(void) 
{ 
    SCI2SR1STR scisr1_code;
	
    scisr1_code = _SCI2SR1;  
    if(scisr1_code.Bits.TDRE == FLAG_EN)    /*�����ж�*/
    {
       drv_sci2_txint();
    }
         
    if(scisr1_code.Bits.RDRF_bit == FLAG_EN)  /*�����ж�*/
    {
       drv_sci2_rxint();
    }
     
    if(scisr1_code.Bits.FE == FLAG_EN)   /*֡��ʽ�����ж�*/
    {
       drv_sci2_framerr();
    }
    
    if(scisr1_code.Bits.PF == FLAG_EN)   /*��żУ������ж�*/  
    {
       drv_sci2_perr();
    }
}


#if  1
/*******************************************************************************
             				SCI0ʵ��ΪRS232
*******************************************************************************/
/**********************************************************************************
*\brief      SCI0��ʼ������
*
*SCI0��ʼ������
*
*\param    CPU_clk  :  
*
*return    �޷���ֵ
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
 		/*���ڲ���������ֵ���ֵ����*/
    	return 0x21;                                
     }
	 
     /**********************/
     sci_sbr_config(DRV_SCI0_BDH,	/*����������*/
     				sci0_reg_baud,
     				0 );	
	 
     sci_config(	DRV_SCI0_MODE,	/*ģʽ���ж�����*/
	 				DRV_SCI0_INTCFG,
	 				0 );
     
     drv_sci0_txbuf.in  = 0u; 	/*����FIFOָ���ʼ��*/
     drv_sci0_txbuf.out = 0u; 
     drv_sci0_sendtag 	= 0u; 	/*���ͱ�ǳ�ʼ��*/
     
     drv_sci0_rxbuf.in  = 0u;	/*����FIFOָ���ʼ��*/	
     drv_sci0_rxbuf.out = 0u;
     return errno;
}

/********************************************************************************//*��
*\brief      SCIд����
*
*SCI��ʼ������
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ͻ�����,ʧ��;
           =0:���ͳɹ�;
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

	/*���㷢��ʣ�໺���Ƿ��㹻*/
	dis = (uint8)(drv_sci0_txbuf.in - drv_sci0_txbuf.out);
	if((dis + size) > DRV_SCI_TXBUFSIZE )
	{
		/*���ͻ�����,ֱ�ӷ���*/
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
		/*����δ����,��������*/
		drv_sci0_sendtag = 1u;
		SCI0CR2_TIE = 1;      /*ʹ�ܷ����ж�*/
	}
    return 0;
}


/********************************************************************************//*��
*\brief      SCIд����
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ͻ�����,ʧ��;
           =0:���ͳɹ�;
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
/********************************************************************************//*��
*\brief      SCI������
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ջ���������<ָ���������ݳ���(SIZE)
           =0:�ɹ�
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
		/*�ѽ��յ��ֽ����� < �����ֽ�����*/
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


/********************************************************************************//*��
*\brief      SCI(232)�����жϺ���
*
*SCI(485)�����жϴ�����
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/  
static void drv_sci0_txint(void) 
{
	uint8 SendData = 0u;
	uint8 Tout = 0u;
	
    if(drv_sci0_txbuf.out == drv_sci0_txbuf.in)   /*fifo��������*/
    {
        drv_sci0_sendtag = 0;       /*���ڷ��ͱ�־���*/
        SCI0CR2_TIE = 0;      		/*�رշ����ж�*/
    }   
    else 
    {
    	Tout = drv_sci0_txbuf.out;
		SendData = drv_sci0_txbuf.buf[Tout & (DRV_SCI_TXBUFSIZE - 1u)];
		drv_sci0_txbuf.out++;
		sci_put_reg(SendData,10);
    }
}

/********************************************************************************//*��
*\brief      SCI�����жϺ���
*
*SCI�����жϴ�����
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci0_rxint(void) 
{
    uint8 dis = 0u;
    uint8 data;
    uint8 Rin = 0u;
	
    data = sci_get_reg(10); /*�ӼĴ����ж�����*/
	
	dis = (uint8)(drv_sci0_rxbuf.in - drv_sci0_rxbuf.out);
	if(dis < DRV_SCI_RXBUFSIZE)
	{
		/*�Ѵ洢�ռ�<�趨�ռ�,���ջ���δ��*/
		Rin = drv_sci0_rxbuf.in;
		drv_sci0_rxbuf.buf[Rin & (DRV_SCI_RXBUFSIZE - 1u)] = data;
		drv_sci0_rxbuf.in++;
	}
	else
	{
		/*���ջ�����*/
	}
}

/********************************************************************************//*��
*\brief      SCI֡�����жϺ���
*
*SCI֡�����жϴ�����.
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci0_framerr(void) 
{
    uint8 data;

	data = sci_get_reg(10); /*֡����ʱ�ӼĴ����ж�����������жϱ�־λ*/     
}

/********************************************************************************//*��
*\brief      SCI��żУ��λ�����жϺ���
*
*SCI֡�����жϴ�����.
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci0_perr(void) 
{
     uint8 data;
     data = sci_get_reg(10); /*֡����ʱ�ӼĴ����ж�����������жϱ�־λ*/     
}

/*************************************************************************
* ��������: drv_Sci0_WriteCharAscii
* ��������: ��ASCII����ʽ����������
* ��������: ��������
* �������: c:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
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
* ��������: drv_Sci0_WriteShortAscii
* ��������: ��ASCII����ʽ������short������
* ��������: ��������
* �������: s:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
*************************************************************************/
static void drv_Sci0_WriteShortAscii(unsigned short s)
{
    drv_Sci0_WriteCharAscii((unsigned char)(s>>8));
    drv_Sci0_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* ��������: drv_Sci0_WriteLongAscii
* ��������: ��ASCII����ʽ������long������
* ��������: ��������
* �������: l:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: Ӳ�������
*************************************************************************/
static void drv_Sci0_WriteLongAscii(unsigned long l)
{
    drv_Sci0_WriteShortAscii((unsigned short)(l>>16));
    drv_Sci0_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* ��������: Det_Sci0_ReportError
* ��������: ���濪��ʱ����;
* ��������: ��������
* �������: ModuleId:ģ��Id��;
            InstanceId:
            ApiId   :API Id��;
            ErrorId :����ID��  
* �������: ��
* ����ֵ:   ��
* ��    ע: 
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
             				SCI2ʵ��ΪRS232
*******************************************************************************/
/********************************************************************************//*��
*\brief    SCI2��ʼ������
*
*SCI2��ʼ������
*
*\param    CPU_clk  :  
*
*return    �޷���ֵ
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
	 Bsp_GetBusClock(&bus_clock);  /*��ȡ����ʱ��*/
     sci_reg_baud   = bus_clock/16/drv_sci_baud;  /*���㲨���ʼĴ���ֵ*/
     sci_count_baud = bus_clock/16/sci_reg_baud;  /*���ݼ��㲨���ʼĴ���ֵ,�����Ӧ������*/
	 
     if(drv_sci_baud >= sci_count_baud)
     {	
        sci_baud_diff = drv_sci_baud - sci_count_baud; 
     }
     else
     {
        sci_baud_diff = sci_count_baud - drv_sci_baud;
     }
     
     compare_num = sci_baud_diff / drv_sci_baud; /*���㲨�������ٷֱ�*/
     
     if(compare_num >0.05)
     {
 		/*���ڲ���������ֵ���ֵ����*/
    	return 0x21;                                
     }
	 
     /**********************/
     sci_sbr_config(DRV_SCI2_BDH,	/*����������*/
     				sci_reg_baud,
     				2u );	
	 
     sci_config(	DRV_SCI2_MODE,	/*ģʽ���ж�����*/
	 				DRV_SCI2_INTCFG,
	 				2u );
     
     drv_sci2_txbuf.in  = 0u;
     drv_sci2_txbuf.out = 0u; 
     drv_sci2_sendtag 	= 0u;
	 
     drv_sci2_rxbuf.in  = 0u;
     drv_sci2_rxbuf.out = 0u;
     return errno;
}

/********************************************************************************//*��
*\brief      SCI2д����
*
*SCI��ʼ������
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ͻ�����,ʧ��;
           =0:���ͳɹ�;
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

	/*���㷢��ʣ�໺���Ƿ��㹻*/
	dis = (uint8)(drv_sci2_txbuf.in - drv_sci2_txbuf.out);
	if((dis + size) > DRV_SCI_TXBUFSIZE )
	{
		/*���ͻ�����,ֱ�ӷ���*/
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
		/*����δ����,��������*/
		drv_sci2_sendtag = 1u;
		SCI2CR2_TIE = 1;      /*ʹ�ܷ����ж�*/
	}
    return 0;
}

/********************************************************************************//*��
*\brief      SCI2д����
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ͻ�����,ʧ��;
           =0:���ͳɹ�;
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

/********************************************************************************//*��
*\brief      SCI������
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ջ���������<ָ���������ݳ���(SIZE)
           =0:�ɹ�
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
		/*�ѽ��յ��ֽ����� < �����ֽ�����*/
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

/********************************************************************************//*��
*\brief      SCI(232)�����жϺ���
*
*
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/  
static void drv_sci2_txint(void) 
{
	uint8 SendData = 0u;
	uint8 Tout = 0u;
	
    if(drv_sci2_txbuf.out == drv_sci2_txbuf.in)   /*fifo��������*/
    {
        drv_sci2_sendtag = 0;       /*���ڷ��ͱ�־���*/
        SCI2CR2_TIE = 0;      		/*�رշ����ж�*/
    }   
    else 
    {
    	Tout = drv_sci2_txbuf.out;
		SendData = drv_sci2_txbuf.buf[Tout & (DRV_SCI_TXBUFSIZE - 1u)];
		drv_sci2_txbuf.out++;
		sci_put_reg(SendData,2);
    }
}

/********************************************************************************//*��
*\brief      SCI�����жϺ���
*
*SCI�����жϴ�����
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci2_rxint(void) 
{
    uint8 dis = 0u;
    uint8 data;
    uint8 Rin = 0u;
	
    data = sci_get_reg(2); /*�ӼĴ����ж�����*/
	
	dis = (uint8)(drv_sci2_rxbuf.in - drv_sci2_rxbuf.out);
	if(dis < DRV_SCI_RXBUFSIZE)
	{
		/*�Ѵ洢�ռ�<�趨�ռ�,���ջ���δ��*/
		Rin = drv_sci2_rxbuf.in;
		drv_sci2_rxbuf.buf[Rin & (DRV_SCI_RXBUFSIZE - 1u)] = data;
		drv_sci2_rxbuf.in++;
	}
	else
	{
		/*���ջ�����*/
	}
}


/********************************************************************************//*��
*\brief      SCI֡�����жϺ���
*
*SCI֡�����жϴ�����.
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci2_framerr(void) 
{
    volatile uint8 data;

	  data = sci_get_reg(2); /*֡����ʱ�ӼĴ����ж�����������жϱ�־λ*/     
}

/********************************************************************************//*��
*\brief      SCI��żУ��λ�����жϺ���
*
*SCI֡�����жϴ�����.
*
*\param    �޲���ֵ
*
*return    �޷���ֵ
*
**********************************************************************************/ 
static void drv_sci2_perr(void) 
{
     volatile uint8 data;
     
     data = sci_get_reg(2); /*֡����ʱ�ӼĴ����ж�����������жϱ�־λ*/     
}

/*************************************************************************
* ��������: drv_Sci2_WriteCharAscii
* ��������: ��ASCII����ʽ����������
* ��������: ��������
* �������: c:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
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
* ��������: drv_Sci2_WriteShortAscii
* ��������: ��ASCII����ʽ������short������
* ��������: ��������
* �������: s:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
*************************************************************************/
static void drv_Sci2_WriteShortAscii(unsigned short s)
{
    drv_Sci2_WriteCharAscii((unsigned char)(s>>8));
    drv_Sci2_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* ��������: drv_Sci2_WriteLongAscii
* ��������: ��ASCII����ʽ������long������
* ��������: ��������
* �������: l:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: Ӳ�������
*************************************************************************/
static void drv_Sci2_WriteLongAscii(unsigned long l)
{
    drv_Sci2_WriteShortAscii((unsigned short)(l>>16));
    drv_Sci2_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* ��������: Det_Sci2_ReportError
* ��������: ���濪��ʱ����;
* ��������: ��������
* �������: ModuleId:ģ��Id��;
            InstanceId:
            ApiId   :API Id��;
            ErrorId :����ID��  
* �������: ��
* ����ֵ:   ��
* ��    ע: 
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


/********************************************************************************//*��
*\brief      SCI��ʼ������
*
*SCI��ʼ������
*
*\param    CPU_clk  :  
*
*return    �޷���ֵ
*
**********************************************************************************/
uint16 Drv_Sci_Init(uint32 drv_sci_baud) 
{
	uint16  Ret = 0u;
	
    Ret = drv_sci2_init(drv_sci_baud);
	return(Ret);
}

/********************************************************************************//*��
*\brief      SCI������
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ջ���������<ָ���������ݳ���(SIZE)
           =0:�ɹ�
*
**********************************************************************************/
uint16 Drv_Sci_Read(uint8 *data,uint8 size, uint16 timeout)
{
	uint16  Ret = 0u;

	Ret = drv_sci2_read(data,size,timeout);
	return(Ret);
}

/********************************************************************************//*��
*\brief      SCIд����
*
*
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    =1:���ͻ�����,ʧ��;
           =0:���ͳɹ�;
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
* ��������: Drv_Sci_WriteCharAscii
* ��������: ��ASCII����ʽ����������
* ��������: ��������
* �������: c:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
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
* ��������: Drv_Sci_WriteShortAscii
* ��������: ��ASCII����ʽ������short������
* ��������: ��������
* �������: s:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: 
*************************************************************************/
void   Drv_Sci_WriteShortAscii(unsigned short s)
{
    Drv_Sci_WriteCharAscii((unsigned char)(s>>8));
    Drv_Sci_WriteCharAscii((unsigned char)s);
}

/*************************************************************************
* ��������: Drv_Sci_WriteLongAscii
* ��������: ��ASCII����ʽ������long������
* ��������: ��������
* �������: l:����������;
* �������: ��
* ����ֵ:   ��
* ��    ע: Ӳ�������
*************************************************************************/
void   Drv_Sci_WriteLongAscii(unsigned long l)
{
    Drv_Sci_WriteShortAscii((unsigned short)(l>>16));
    Drv_Sci_WriteShortAscii((unsigned short)l);
}

/*************************************************************************
* ��������: Det_ReportError
* ��������: ���濪��ʱ����;
* ��������: ��������
* �������: ModuleId:ģ��Id��;
            InstanceId:
            ApiId   :API Id��;
            ErrorId :����ID��  
* �������: ��
* ����ֵ:   ��
* ��    ע: 
*************************************************************************/
void  Det_ReportError(uint16 ModuleId,uint8 InstanceId,uint8 ApiId,uint8 ErrorId)
{
	Det_Sci2_ReportError(ModuleId,InstanceId,ApiId,ErrorId);
}


