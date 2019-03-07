/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : w5300.h
* ��������  : w5300����Դ�ļ�(w5300.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/19        sunj              New
**------------------------------------------------------------------------------------------------*/

#ifndef _W5300_H__
#define _W5300_H__

/*W5300 SOCKET�Ĵ����ṹ���Ͷ���*/
typedef struct
{
    volatile uint16 S_MR;            /*0x200 ģʽ�Ĵ���*/
    volatile uint16 S_CR;            /*0x202 ͨ�üĴ���*/
    volatile uint16 S_IMR;           /*0x204 �ж����μĴ���*/
    volatile uint16 S_IR;            /*0x206 �жϼĴ���*/
    volatile uint16 S_SSR;           /*0x208 ״̬�Ĵ���*/
    volatile uint16 S_PORTR;         /*0x20A Դ�˿ڼĴ���*/
    volatile uint16 S_DHAR;          /*0x20C Ŀ��Ӳ����ַ�Ĵ���*/
    volatile uint16 S_DHAR2;
    volatile uint16 S_DHAR4;
    volatile uint16 S_DPORTR;        /*0x212 Ŀ�Ķ˿ڼĴ���*/
    volatile uint16 S_DIPR;          /*0x214 Ŀ��IP��ַ�Ĵ���*/
    volatile uint16 S_DIPR2;         
    volatile uint16 S_MSSR;          /*0x218 ���δ�С�Ĵ���*/
    volatile uint16 S_PORTOR;        /*0x21A ���ֻ���ʱ��Ĵ���   0x21B Э��żĴ���*/
    volatile uint16 S_TOSR;          /*0x21C TOS�Ĵ���*/
    volatile uint16 S_TTLR;          /*0x21E TTL�Ĵ���*/
    volatile uint16 S_TX_WRSR;       /*0x220 TXд����¼Ĵ���*/
    volatile uint16 S_TX_WRSR2;      
    volatile uint16 S_TX_FSR;        /*0x224 TX ʣ���С�Ĵ���*/
    volatile uint16 S_TX_FSR2;
    volatile uint16 S_RX_RSR;        /*0x228 RX ���մ�С�Ĵ���*/
    volatile uint16 S_RX_RSR2;       
    volatile uint16 S_FRAGR;         /*0x22C FLAG�Ĵ���*/
    volatile uint16 S_TX_FIFOR;      /*0x22E TX FIFO�Ĵ���*/
    volatile uint16 S_RX_FIFOR;      /*0x230 RX FIFO�Ĵ���*/
    volatile uint16 reserve0;        /*0x232 ����*/
    volatile uint16 reserve1;        /*0x234 ����*/
    volatile uint16 reserve2;        /*0x236 ����*/
    volatile uint16 reserve3;        /*0x238 ����*/
    volatile uint16 reserve4;        /*0x23A ����*/
    volatile uint16 reserve5;        /*0x23C ����*/
    volatile uint16 reserve6;        /*0x23E ����*/
}W5300_SOCKET_REG_TypeDef;

/*W5300��ʼ���ṹ���Ͷ���*/
typedef struct
{
    uint32 IpAddr;          /*IP��ַ*/
    uint32 SubnetMask;      /*��������*/
    uint32 GatewayAddr;     /*���ص�ַ*/
    uint16 MacAddr[3];      /*MAC��ַ*/
}W5300_InitTypeDef;

/*Socket��ʼ���ṹ���Ͷ���*/
typedef struct
{
    uint16 Port;            /*�˿�*/
    uint32 DestIpAddr;      /*Ŀ���豸IP��ַ*/
    uint16 DestPort;        /*Ŀ���豸�˿�*/
    uint16 MTU;             /*����䵥Ԫ*/
    uint16 Mode;            /*ģʽ*/
}SOCKET_InitTypeDef;

#define         W5300_BASE      ((uint32)0x400000)                            /*W5300����ַ*/
#define         MR              ((uint16 * __far)(W5300_BASE + 0x0000))       /*ģʽ�Ĵ���*/
#define         IR              ((uint16 * __far)(W5300_BASE + 0x0002))       /*�жϼĴ���*/
#define         IMR             ((uint16 * __far)(W5300_BASE + 0x0004))       /*�ж����μĴ���*/

#define         SHAR            ((uint16 * __far)(W5300_BASE + 0x0008))       /*����Ӳ����ַ�Ĵ���*/
#define         SHAR2           ((uint16 * __far)(W5300_BASE + 0x000A))
#define         SHAR4           ((uint16 * __far)(W5300_BASE + 0x000C))

#define         GAR             ((uint16 * __far)(W5300_BASE + 0x0010))       /*���ص�ַ�Ĵ���*/
#define         GAR2            ((uint16 * __far)(W5300_BASE + 0x0012))
#define         SUBR            ((uint16 * __far)(W5300_BASE + 0x0014))       /*��������Ĵ���*/
#define         SUBR2           ((uint16 * __far)(W5300_BASE + 0x0016))
#define         SIPR            ((uint16 * __far)(W5300_BASE + 0x0018))       /*����IP��ַ�Ĵ���*/
#define         SIPR2           ((uint16 * __far)(W5300_BASE + 0x001A))
#define         RTR             ((uint16 * __far)(W5300_BASE + 0x001C))       /*�ش���ʱֵ�Ĵ���*/
#define         RCR             ((uint16 * __far)(W5300_BASE + 0x001E))       /*���´�������Ĵ���*/
#define         TMS01R          ((uint16 * __far)(W5300_BASE + 0x0020))       /*�˿�0��1����洢����С���üĴ���*/
#define         TMS23R          ((uint16 * __far)(W5300_BASE + 0x0022))       /*�˿�2��3����洢����С���üĴ���*/
#define         TMS45R          ((uint16 * __far)(W5300_BASE + 0x0024))       /*�˿�4��5����洢����С���üĴ���*/
#define         TMS67R          ((uint16 * __far)(W5300_BASE + 0x0026))       /*�˿�6��7����洢����С���üĴ���*/
#define         RMS01R          ((uint16 * __far)(W5300_BASE + 0x0028))       /*�˿�0��1���մ洢����С���üĴ���*/
#define         RMS23R          ((uint16 * __far)(W5300_BASE + 0x002A))       /*�˿�2��3���մ洢����С���üĴ���*/
#define         RMS45R          ((uint16 * __far)(W5300_BASE + 0x002C))       /*�˿�4��5���մ洢����С���üĴ���*/
#define         RMS67R          ((uint16 * __far)(W5300_BASE + 0x002E))       /*�˿�6��7���մ洢����С���üĴ���*/
#define         MTYPER          ((uint16 * __far)(W5300_BASE + 0x0030))       /*�洢����Ԫ���ͼĴ���*/
#define         PATR            ((uint16 * __far)(W5300_BASE + 0x0032))       /*PPPoE��֤�Ĵ���*/

#define         PTIMER          ((uint16 * __far)(W5300_BASE + 0x0036))       /*PPP LCP����ʱ��Ĵ���*/
#define         PMAGICR         ((uint16 * __far)(W5300_BASE + 0x0038))       /*PPP LCPħ�����Ĵ���*/

#define         PSIDR           ((uint16 * __far)(W5300_BASE + 0x003C))       /*PPP �ỰID�Ĵ���*/

#define         PDHAR           ((uint16 * __far)(W5300_BASE + 0x0040))       /*PPP Ŀ��Ӳ����ַ�Ĵ���*/   
#define         PDHAR2          ((uint16 * __far)(W5300_BASE + 0x0042))
#define         PDHAR4          ((uint16 * __far)(W5300_BASE + 0x0044))

#define         SOCKET0         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0200))         /*�׽ӿ�0�Ĵ�����ַ*/
#define         SOCKET1         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0240))         /*�׽ӿ�1�Ĵ�����ַ*/
#define         SOCKET2         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0280))         /*�׽ӿ�2�Ĵ�����ַ*/
#define         SOCKET3         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x02C0))         /*�׽ӿ�3�Ĵ�����ַ*/
#define         SOCKET4         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0300))         /*�׽ӿ�4�Ĵ�����ַ*/
#define         SOCKET5         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0340))         /*�׽ӿ�5�Ĵ�����ַ*/
#define         SOCKET6         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x0380))         /*�׽ӿ�6�Ĵ�����ַ*/
#define         SOCKET7         ((W5300_SOCKET_REG_TypeDef * __far)(W5300_BASE + 0x03C0))         /*�׽ӿ�7�Ĵ�����ַ*/

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
 * ��������
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
