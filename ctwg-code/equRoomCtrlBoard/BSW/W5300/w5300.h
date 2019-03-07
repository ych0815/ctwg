/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : w5300.h
* 功能描述  : w5300驱动源文件(w5300.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/19        sunj              New
**------------------------------------------------------------------------------------------------*/

#ifndef _W5300_H__
#define _W5300_H__

/*W5300 SOCKET寄存器结构类型定义*/
typedef struct
{
    volatile uint16 S_MR;            /*0x200 模式寄存器*/
    volatile uint16 S_CR;            /*0x202 通用寄存器*/
    volatile uint16 S_IMR;           /*0x204 中断屏蔽寄存器*/
    volatile uint16 S_IR;            /*0x206 中断寄存器*/
    volatile uint16 S_SSR;           /*0x208 状态寄存器*/
    volatile uint16 S_PORTR;         /*0x20A 源端口寄存器*/
    volatile uint16 S_DHAR;          /*0x20C 目的硬件地址寄存器*/
    volatile uint16 S_DHAR2;
    volatile uint16 S_DHAR4;
    volatile uint16 S_DPORTR;        /*0x212 目的端口寄存器*/
    volatile uint16 S_DIPR;          /*0x214 目的IP地址寄存器*/
    volatile uint16 S_DIPR2;         
    volatile uint16 S_MSSR;          /*0x218 最大段大小寄存器*/
    volatile uint16 S_PORTOR;        /*0x21A 保持活性时间寄存器   0x21B 协议号寄存器*/
    volatile uint16 S_TOSR;          /*0x21C TOS寄存器*/
    volatile uint16 S_TTLR;          /*0x21E TTL寄存器*/
    volatile uint16 S_TX_WRSR;       /*0x220 TX写入带下寄存器*/
    volatile uint16 S_TX_WRSR2;      
    volatile uint16 S_TX_FSR;        /*0x224 TX 剩余大小寄存器*/
    volatile uint16 S_TX_FSR2;
    volatile uint16 S_RX_RSR;        /*0x228 RX 接收大小寄存器*/
    volatile uint16 S_RX_RSR2;       
    volatile uint16 S_FRAGR;         /*0x22C FLAG寄存器*/
    volatile uint16 S_TX_FIFOR;      /*0x22E TX FIFO寄存器*/
    volatile uint16 S_RX_FIFOR;      /*0x230 RX FIFO寄存器*/
    volatile uint16 reserve0;        /*0x232 保留*/
    volatile uint16 reserve1;        /*0x234 保留*/
    volatile uint16 reserve2;        /*0x236 保留*/
    volatile uint16 reserve3;        /*0x238 保留*/
    volatile uint16 reserve4;        /*0x23A 保留*/
    volatile uint16 reserve5;        /*0x23C 保留*/
    volatile uint16 reserve6;        /*0x23E 保留*/
}W5300_SOCKET_REG_TypeDef;

/*W5300初始化结构类型定义*/
typedef struct
{
    uint32 IpAddr;          /*IP地址*/
    uint32 SubnetMask;      /*子网掩码*/
    uint32 GatewayAddr;     /*网关地址*/
    uint16 MacAddr[3];      /*MAC地址*/
}W5300_InitTypeDef;

/*Socket初始化结构类型定义*/
typedef struct
{
    uint16 Port;            /*端口*/
    uint32 DestIpAddr;      /*目的设备IP地址*/
    uint16 DestPort;        /*目的设备端口*/
    uint16 MTU;             /*最大传输单元*/
    uint16 Mode;            /*模式*/
}SOCKET_InitTypeDef;

#define         W5300_BASE      ((uint32)0x400000)                            /*W5300基地址*/
#define         MR              ((uint16 * __far)(W5300_BASE + 0x0000))       /*模式寄存器*/
#define         IR              ((uint16 * __far)(W5300_BASE + 0x0002))       /*中断寄存器*/
#define         IMR             ((uint16 * __far)(W5300_BASE + 0x0004))       /*中断屏蔽寄存器*/

#define         SHAR            ((uint16 * __far)(W5300_BASE + 0x0008))       /*本地硬件地址寄存器*/
#define         SHAR2           ((uint16 * __far)(W5300_BASE + 0x000A))
#define         SHAR4           ((uint16 * __far)(W5300_BASE + 0x000C))

#define         GAR             ((uint16 * __far)(W5300_BASE + 0x0010))       /*网关地址寄存器*/
#define         GAR2            ((uint16 * __far)(W5300_BASE + 0x0012))
#define         SUBR            ((uint16 * __far)(W5300_BASE + 0x0014))       /*子网掩码寄存器*/
#define         SUBR2           ((uint16 * __far)(W5300_BASE + 0x0016))
#define         SIPR            ((uint16 * __far)(W5300_BASE + 0x0018))       /*本地IP地址寄存器*/
#define         SIPR2           ((uint16 * __far)(W5300_BASE + 0x001A))
#define         RTR             ((uint16 * __far)(W5300_BASE + 0x001C))       /*重传超时值寄存器*/
#define         RCR             ((uint16 * __far)(W5300_BASE + 0x001E))       /*重新传输计数寄存器*/
#define         TMS01R          ((uint16 * __far)(W5300_BASE + 0x0020))       /*端口0、1传输存储器大小配置寄存器*/
#define         TMS23R          ((uint16 * __far)(W5300_BASE + 0x0022))       /*端口2、3传输存储器大小配置寄存器*/
#define         TMS45R          ((uint16 * __far)(W5300_BASE + 0x0024))       /*端口4、5传输存储器大小配置寄存器*/
#define         TMS67R          ((uint16 * __far)(W5300_BASE + 0x0026))       /*端口6、7传输存储器大小配置寄存器*/
#define         RMS01R          ((uint16 * __far)(W5300_BASE + 0x0028))       /*端口0、1接收存储器大小配置寄存器*/
#define         RMS23R          ((uint16 * __far)(W5300_BASE + 0x002A))       /*端口2、3接收存储器大小配置寄存器*/
#define         RMS45R          ((uint16 * __far)(W5300_BASE + 0x002C))       /*端口4、5接收存储器大小配置寄存器*/
#define         RMS67R          ((uint16 * __far)(W5300_BASE + 0x002E))       /*端口6、7接收存储器大小配置寄存器*/
#define         MTYPER          ((uint16 * __far)(W5300_BASE + 0x0030))       /*存储器单元类型寄存器*/
#define         PATR            ((uint16 * __far)(W5300_BASE + 0x0032))       /*PPPoE认证寄存器*/

#define         PTIMER          ((uint16 * __far)(W5300_BASE + 0x0036))       /*PPP LCP请求时间寄存器*/
#define         PMAGICR         ((uint16 * __far)(W5300_BASE + 0x0038))       /*PPP LCP魔术数寄存器*/

#define         PSIDR           ((uint16 * __far)(W5300_BASE + 0x003C))       /*PPP 会话ID寄存器*/

#define         PDHAR           ((uint16 * __far)(W5300_BASE + 0x0040))       /*PPP 目的硬件地址寄存器*/   
#define         PDHAR2          ((uint16 * __far)(W5300_BASE + 0x0042))
#define         PDHAR4          ((uint16 * __far)(W5300_BASE + 0x0044))

#define         SOCKET0         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0200))         /*套接口0寄存器地址*/
#define         SOCKET1         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0240))         /*套接口1寄存器地址*/
#define         SOCKET2         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0280))         /*套接口2寄存器地址*/
#define         SOCKET3         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x02C0))         /*套接口3寄存器地址*/
#define         SOCKET4         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0300))         /*套接口4寄存器地址*/
#define         SOCKET5         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0340))         /*套接口5寄存器地址*/
#define         SOCKET6         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0380))         /*套接口6寄存器地址*/
#define         SOCKET7         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x03C0))         /*套接口7寄存器地址*/

/*Sn_MR values*/
#define Sn_MR_ALIGN         0x100 // 2 Byte Alignment Data Trnascation(No use TCP Header)
#define Sn_MR_MULTI         0x80 // support multicating
//#define Sn_MR_MF            0x40		
#define Sn_MR_ND            0x20 // No Delayed Ack(TCP) flag
//#define Sn_MR_ZC            0x10


#define Sn_MR_CLOSE         0x00 // unused socket
#define Sn_MR_TCP           0x01 // TCP
#define Sn_MR_UDP           0x02 // UDP
#define Sn_MR_IPRAW         0x03 // IP LAYER RAW SOCK
#define Sn_MR_MACRAW        0x04 // MAC LAYER RAW SOCK
#define Sn_MR_PPPOE         0x05 // PPPoE   

/* Sn_CR values */
#define Sn_CR_OPEN          0x01 // initialize or open socket
#define Sn_CR_LISTEN        0x02 // wait connection request in tcp mode(Server mode)
#define Sn_CR_CONNECT       0x04 // send connection request in tcp mode(Client mode)
#define Sn_CR_DISCON        0x08 // send closing reqeuset in tcp mode
#define Sn_CR_CLOSE         0x10 // close socket
#define Sn_CR_SEND          0x20 // updata txbuf pointer, send data
#define Sn_CR_SEND_MAC      0x21 // send data with MAC address, so without ARP process
#define Sn_CR_SEND_KEEP     0x22 // send keep alive message
#define Sn_CR_RECV          0x40 // update rxbuf pointer, recv data

#define Sn_CR_PCON          0x23 // 
#define Sn_CR_PDISCON       0x24 // 
#define Sn_CR_PCR           0x25 // 
#define Sn_CR_PCN           0x26 // 
#define Sn_CR_PCJ           0x27 // 

/* Sn_IR values */
#define Sn_IR_PRECV         0x80 // 
#define Sn_IR_PFAIL         0x40 // 
#define Sn_IR_PNEXT         0x20 // 
                         
#define Sn_IR_SEND_OK       0x10 // complete sending
#define Sn_IR_TIMEOUT       0x08 // assert timeout
#define Sn_IR_RECV          0x04 // receiving data
#define Sn_IR_DISCON        0x02 // closed socket
#define Sn_IR_CON           0x01 // established connection

/* Sn_SSR values */
#define SOCK_CLOSED         0x00 // closed
#define SOCK_INIT           0x13 // init state
#define SOCK_LISTEN         0x14 // listen state
#define SOCK_SYNSENT        0x15 // connection state
#define SOCK_SYNRECV        0x16 // connection state
#define SOCK_ESTABLISHED    0x17 // success to connect
#define SOCK_FIN_WAIT       0x18 // closing state
#define SOCK_CLOSING        0x1A // closing state
#define SOCK_TIME_WAIT      0x1B // closing state
#define SOCK_CLOSE_WAIT     0x1C // closing state
#define SOCK_LAST_ACK       0x1D // closing state
#define SOCK_UDP            0x22 // udp socket
#define SOCK_IPRAW          0x32 // ip raw mode socket
#define SOCK_MACRAW         0x42 // mac raw mode socket
#define SOCK_PPPOE          0x5F // pppoe socket

/* IP PROTOCOL */
#define IPPROTO_IP          0   /* Dummy for IP */
#define IPPROTO_ICMP        1   /* Control message protocol */
#define IPPROTO_IGMP        2   /* Internet group management protocol */
#define IPPROTO_GGP         3   /* Gateway^2 (deprecated) */
#define IPPROTO_TCP         6   /* TCP */
#define IPPROTO_PUP         12  /* PUP */
#define IPPROTO_UDP         17  /* UDP */
#define IPPROTO_IDP         22  /* XNS idp */
#define IPPROTO_ND          77  /* UNOFFICIAL net disk protocol */
#define IPPROTO_RAW         255 /* Raw IP packet */

/*************************
 * 函数声明
**************************/
extern void BSP_EBI_Cfg(void);
extern void W5300_Init(W5300_InitTypeDef *W5300_InitStruct);
extern void SOCKET_Init(W5300_SOCKET_REG_TypeDef * __far SOCKETx,SOCKET_InitTypeDef *SOCKET_InitStruct);
extern void SOCKET_Cmd(W5300_SOCKET_REG_TypeDef * __far SOCKETx,uint16 NewState);
extern void W5300_Config(void);
extern void drv_xirq_int(void);
extern boolean UDP_Init(void);
extern void UDP_Send(uint16 *data,uint16 size,uint32 remoteIp,uint16 remotePort);
extern void UDP_ReceiveProcess(void);

#endif
