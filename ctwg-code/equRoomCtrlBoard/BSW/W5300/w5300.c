/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : w5300.c
* 功能描述  : w5300驱动源文件(w5300.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/19        sunj              New
**------------------------------------------------------------------------------------------------*/

#include "Bsw.h"

boolean SendOK,TimeOut;

/***************************************************************************//*!
 * \brief  EBI配置函数
 *         
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void BSP_EBI_Cfg(void)
{
    MMCCTL0_CS0E = 1;       /*使能片选0*/
	MODE         = 0xA0;    /*扩展模式*/
    MMCCTL1     |= 0x01;    /*暂未修改*/
	 
	EBICTL0      = 0x2A;    /*16位数据总线 10位地址总线*/
	EBICTL1      = 0x55; 
	ECLKCTL     |= 0X40; 
	
//	PLLCTL      &= (~0x80);   
}

/***************************************************************************//*!
 * \brief   W5300初始化函数
 *          初始化单片的IP地址 子网掩码 网关地址 MAC地址
 *
 * \param   W5300_InitStruct W5300初始化数据变量指针
 *
 * \return  无
 *
 *****************************************************************************/
void W5300_Init(W5300_InitTypeDef *W5300_InitStruct)
{
	/* Set IP address*/
	*SIPR = W5300_InitStruct->IpAddr >> 16;
	*SIPR2= W5300_InitStruct->IpAddr & 0xFFFF; 

	/* Set Subnet mask*/
	*SUBR = W5300_InitStruct->SubnetMask >> 16;
	*SUBR2= W5300_InitStruct->SubnetMask & 0xFFFF;	

	/* Set Gateway address*/
	*GAR  = W5300_InitStruct->GatewayAddr >> 16;
	*GAR2 = W5300_InitStruct->GatewayAddr & 0xFFFF;
	
	/* Set MAC address*/
	*SHAR = W5300_InitStruct->MacAddr[0];
	*SHAR2= W5300_InitStruct->MacAddr[1];
	*SHAR4= W5300_InitStruct->MacAddr[2];

	SendOK = TRUE;
	TimeOut = FALSE;
}

/***************************************************************************//*!
 * \brief   SOCKET初始化函数
 *          绑定本地端口 设置目标IP和端口 设置MTU 设置通信方式
 *
 * \param   SOCKETx SOCKET指针
 *          SOCKET_InitStruct SOCKET初始化数据变量指针
 *
 * \return  无
 *
 *****************************************************************************/
void SOCKET_Init(W5300_SOCKET_REG_TypeDef * __far SOCKETx,SOCKET_InitTypeDef *SOCKET_InitStruct)
{
	/* Set Socket Source Port Number */
	SOCKETx->S_PORTOR = SOCKET_InitStruct->Port;

	/* Set Destination IP */
	SOCKETx->S_DIPR = SOCKET_InitStruct->DestIpAddr >> 16;
	SOCKETx->S_DIPR2 = SOCKET_InitStruct->DestIpAddr & 0xFFFF;

	/* Set Destination Port number */
	SOCKETx->S_DPORTR = SOCKET_InitStruct->DestPort;

	/* Set Max. segment size */
	SOCKETx->S_MSSR = SOCKET_InitStruct->MTU;

	/* Set SOCKETx in TCP/UDP mode */
	SOCKETx->S_MR = SOCKET_InitStruct->Mode;	
}

/***************************************************************************//*!
 * \brief   SOCKET控制函数
 *  
 * \param   SOCKETx SOCKET指针
 *          NewState 控制状态
 *
 * \return  无
 *
 *****************************************************************************/
void SOCKET_Cmd(W5300_SOCKET_REG_TypeDef * __far SOCKETx,uint16 NewState)
{
	SOCKETx->S_CR = NewState;
}

/***************************************************************************//*!
 * \brief   W5300配置操作函数
 *          配置单片的IP地址 子网掩码 网关地址 MAC地址
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void W5300_Config(void)
{   	
	W5300_InitTypeDef W5300_InitStructure;

	/* Set IP address as "192.168.0.20" */
	W5300_InitStructure.IpAddr = 0xC0A80014;

	/* Set Subnet mask as "255.255.255.0" */
	W5300_InitStructure.SubnetMask = 0xFFFFFF00;

	/* Set Gateway address as "192.168.0.1" */
	W5300_InitStructure.GatewayAddr = 0xC0A80001;

	/* Set MAC address as "48 53 00 31 30 33"*/
	W5300_InitStructure.MacAddr[0] = 0x4853;
	W5300_InitStructure.MacAddr[1] = 0x0031;
	W5300_InitStructure.MacAddr[2] = 0x3033;

	W5300_Init(&W5300_InitStructure);
	
	/* Set interrupt mask */
	*IMR = 0x01;
}

/***************************************************************************//*!
 * \brief   W5300中断触发函数
 *          函数中的打印信息仅用于调试，调试完成后须注释掉
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void drv_xirq_int(void)
{
	uint16 tmp,tmpS;
	
    tmp = *IR;	/* Read IR Register */
    *IR = tmp;  /* Clear IR Token */          

	/* Socket0 events */
	if((tmp&0x01)==0x01)
	{
	   Drv_Sci_Write("\r\n Come in SOCKET0 INT function",0,0);  
	   
	   tmpS = SOCKET0->S_IR;	/* Read SOCKET0 IR Register */
	   SOCKET0->S_IR = tmpS;	/* Clear SOCKET0 IR Token */
	   
	   if((tmpS&0x80)==0x80)/*PPP接收中断*/
	   {
	       Drv_Sci_Write("\r\n PREV ",0,0);  
	   }	
	   
	   if((tmpS&0x40)==0x40)/*PPP失败中断*/
	   {
	       Drv_Sci_Write("\r\n PFALL ",0,0);
	   } 
	   
	   if((tmpS&0x20)==0x20)/*PPP下一过程中断*/
	   {
	       Drv_Sci_Write("\r\n PNEXT ",0,0);
	   }
	   
	   if((tmpS&0x10)==0x10)/*发送完成中断*/
	   {
	       Drv_Sci_Write("\r\n SENDOK ",0,0);
		   SendOK = TRUE;
	   }
	   
	   if((tmpS&0x08)==0x08)/*超时中断*/
	   {
	       Drv_Sci_Write("\r\n TIMEOUT ",0,0);
		   TimeOut = TRUE;
	   }	
	   
	   if((tmpS&0x04)==0x04)/*接收中断*/
	   {
	       Drv_Sci_Write("\r\n RECV",0,0);

		   UDP_ReceiveProcess();
	   } 
	   
	   if((tmpS&0x02)==0x02)/*断开连接中断*/
	   {
	       Drv_Sci_Write("\r\n DISCON ",0,0);
	   }
	   
	   if((tmpS&0x01)==0x01)/*连接中断*/
	   {
	       Drv_Sci_Write("\r\n CON ",0,0);
	   } 
	}
}

/***************************************************************************//*!
 * \brief   UDP初始化
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
boolean UDP_Init(void)
{
    uint16 tmp;

	SOCKET_InitTypeDef SOCKET_InitStructure;

	/* Set Socket Port Number as 5000*/
	SOCKET_InitStructure.Port = 5000;

	/* Set Destination IP  as "192.168.0.30" */
	SOCKET_InitStructure.DestIpAddr = 0xC0A8001E;

	/* Set Destination Port number as 5000 */
	SOCKET_InitStructure.DestPort = 5000;

	/* Set Max. segment size  as 1472 */
	SOCKET_InitStructure.MTU = 1472;

	/* Set Socket0 in UDP mode */
	SOCKET_InitStructure.Mode = Sn_MR_UDP;

	SOCKET_Init(SOCKET0,&SOCKET_InitStructure);

	/* Open Socket0 */
	SOCKET_Cmd(SOCKET0,Sn_CR_OPEN);

    /* Delay 100ms*/
	OSTimeDly(10u);

	tmp = SOCKET0->S_SSR;
	if((tmp&0xFF)!=SOCK_UDP)		/* If failed to open Socket0, close Socket0 and reurn false */
	{
	    SOCKET_Cmd(SOCKET0,Sn_CR_CLOSE);
		return FALSE;
	}
	
	return TRUE;
}


/***************************************************************************//*!
 * \brief   发送UDP报文
 *
 * \param   data 		UDP报文数据地址
 * 			size 		UDP报文数据大小
 * 			remoteIp 	远端目的IP地址
 * 			remotePort 	远端目的端口
 *
 * \return  无
 *
 *****************************************************************************/
void UDP_Send(uint16 *data,uint16 size,uint32 remoteIp,uint16 remotePort)
{
	unsigned short *ptr;
	unsigned short i,j;

	/* Set new Destination IP Address as remoteIp*/
	SOCKET0->S_DIPR = remoteIp >> 16;
	SOCKET0->S_DIPR2= remoteIp & 0xFFFF;
	
	/* Set new Destination Port number as remotePort*/
	SOCKET0->S_DPORTR = remotePort;
    
	if(size&0x0001)
		i=(size+1)/2;
	else
		i=size/2;

	for(j=0;j<i;j++)
		SOCKET0->S_TX_FIFOR = *(data+j);

	SOCKET0->S_TX_WRSR = 0;
	SOCKET0->S_TX_WRSR2= size;

//    if((SendOK==TRUE)&&(TimeOut==FALSE))
//	{
		/* Set SEND command */
		SOCKET0->S_CR = Sn_CR_SEND;	
//		SendOK = FALSE;	
//	}


}

/***************************************************************************//*!
 * \brief   接收UDP报文函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
uint16 dataBuf[800]; 
void UDP_ReceiveProcess(void)
{
	uint32 destIp;
	uint16 destPort;
	uint16 packSize;
	uint16 readCnt;
    uint16 temp,i;
    
	/* 获取目的IP */
	temp = SOCKET0->S_RX_FIFOR;
	destIp = (uint32)temp<<16;
	temp = SOCKET0->S_RX_FIFOR;
	destIp += temp;

	/*获取目的端口号*/
	destPort = SOCKET0->S_RX_FIFOR;

	/*获取数据报文大小*/
	packSize = SOCKET0->S_RX_FIFOR;

	if((packSize&0x01)==0x01)
	{
		readCnt = (packSize+1)/2;
	}
	else
	{
		readCnt = packSize/2;
	}

	for(i = 0; i< readCnt; i++)
	{
		dataBuf[i] = SOCKET0->S_RX_FIFOR;
	}

	/*set RECV command*/
	SOCKET_Cmd(SOCKET0,Sn_CR_RECV);
	
	/*传递给上层进行处理,对报文进行解析*/
	UDP_Received(dataBuf,packSize);
	
}