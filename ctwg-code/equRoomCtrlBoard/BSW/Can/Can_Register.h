/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名      : Can_Register.h
* 功能描述 : Can驱动寄存器数据类型定义文件(Can_Register.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/27       chenms            			 New
**------------------------------------------------------------------------------------------------*/
#ifndef  _CAN_REGISTER_H_
#define  _CAN_REGISTER_H_

/**************************************
              	头文件
 **************************************/
#include "Std_Types.h"
#include "Modules.h"
/**************************************
		CAN寄存器掩码宏定义
 **************************************/
/*** CANCTL0 - MSCAN Control 0 Register; baseaddr + 0u***/
#define CANCTL0_INITRQ_MASK		1U
#define CANCTL0_SLPRQ_MASK		2U
#define CANCTL0_WUPE_MASK		4U
#define CANCTL0_TIME_MASK		8U
#define CANCTL0_SYNCH_MASK		16U
#define CANCTL0_CSWAI_MASK		32U
#define CANCTL0_RXACT_MASK		64U
#define CANCTL0_RXFRM_MASK		128U

/*** CANCTL1 - MSCAN Control 1 Register; baseaddr + 1u ***/
#define CANCTL1_INITAK_MASK		1U
#define CANCTL1_SLPAK_MASK		2U
#define CANCTL1_WUPM_MASK		4U
#define CANCTL1_BORM_MASK		8U
#define CANCTL1_LISTEN_MASK		16U
#define CANCTL1_LOOPB_MASK		32U
#define CANCTL1_CLKSRC_MASK		64U
#define CANCTL1_CANE_MASK		128U

/*** CANBTR0 - MSCAN Bus Timing Register 0; baseaddr + 2u ***/
#define CANBTR0_BRP0_MASK		1U
#define CANBTR0_BRP1_MASK		2U
#define CANBTR0_BRP2_MASK		4U
#define CANBTR0_BRP3_MASK		8U
#define CANBTR0_BRP4_MASK		16U
#define CANBTR0_BRP5_MASK		32U
#define CANBTR0_SJW0_MASK		64U
#define CANBTR0_SJW1_MASK		128U
#define CANBTR0_BRP_MASK		63U
#define CANBTR0_BRP_BITNUM		0U
#define CANBTR0_SJW_MASK		192U
#define CANBTR0_SJW_BITNUM		6U

/*** CANBTR1 - MSCAN Bus Timing Register 1; baseaddr + 3u ***/
#define CANBTR1_TSEG10_MASK		1U
#define CANBTR1_TSEG11_MASK		2U
#define CANBTR1_TSEG12_MASK		4U
#define CANBTR1_TSEG13_MASK		8U
#define CANBTR1_TSEG20_MASK		16U
#define CANBTR1_TSEG21_MASK		32U
#define CANBTR1_TSEG22_MASK		64U
#define CANBTR1_SAMP_MASK		128U
#define CANBTR1_TSEG_10_MASK	15U
#define CANBTR1_TSEG_10_BITNUM	0U
#define CANBTR1_TSEG_20_MASK	112U
#define CANBTR1_TSEG_20_BITNUM	4U

/*** CANRFLG - MSCAN Receiver Flag Register; baseaddr + 4u ***/
#define CANRFLG_RXF_MASK		1U
#define CANRFLG_OVRIF_MASK		2U
#define CANRFLG_TSTAT0_MASK		4U
#define CANRFLG_TSTAT1_MASK		8U
#define CANRFLG_RSTAT0_MASK		16U
#define CANRFLG_RSTAT1_MASK		32U
#define CANRFLG_CSCIF_MASK		64U
#define CANRFLG_WUPIF_MASK		128U
#define CANRFLG_TSTAT_MASK		12U
#define CANRFLG_TSTAT_BITNUM	2U
#define CANRFLG_RSTAT_MASK		48U
#define CANRFLG_RSTAT_BITNUM	4U

/*** CANRIER - MSCAN Receiver Interrupt Enable Register; baseaddr + 5u ***/
#define CANRIER_RXFIE_MASK		1U
#define CANRIER_OVRIE_MASK		2U
#define CANRIER_TSTATE0_MASK	4U
#define CANRIER_TSTATE1_MASK	8U
#define CANRIER_RSTATE0_MASK	16U
#define CANRIER_RSTATE1_MASK	32U
#define CANRIER_CSCIE_MASK		64U
#define CANRIER_WUPIE_MASK		128U
#define CANRIER_TSTATE_MASK		12U
#define CANRIER_TSTATE_BITNUM	2U
#define CANRIER_RSTATE_MASK		48U
#define CANRIER_RSTATE_BITNUM	4U

/*** CANTFLG - MSCAN Transmitter Flag Register; baseaddr + 6u ***/
#define CANTFLG_TXE0_MASK		1U
#define CANTFLG_TXE1_MASK		2U
#define CANTFLG_TXE2_MASK		4U
#define CANTFLG_TXE_MASK		7U
#define CANTFLG_TXE_BITNUM		0U

/*** CANTIER - MSCAN Transmitter Interrupt Enable Register; baseaddr + 7u ***/
#define CANTIER_TXEIE0_MASK		1U
#define CANTIER_TXEIE1_MASK		2U
#define CANTIER_TXEIE2_MASK		4U
#define CANTIER_TXEIE_MASK		7U
#define CANTIER_TXEIE_BITNUM	0U

/*** CANTARQ - MSCAN Transmitter Message Abort Request; baseaddr + 8u ***/
#define CANTARQ_ABTRQ0_MASK		1U
#define CANTARQ_ABTRQ1_MASK		2U
#define CANTARQ_ABTRQ2_MASK		4U
#define CANTARQ_ABTRQ_MASK		7U
#define CANTARQ_ABTRQ_BITNUM	0U

/*** CANTAAK - MSCAN Transmitter Message Abort Acknowledge; baseaddr + 9u ***/
#define CANTAAK_ABTAK0_MASK		1U
#define CANTAAK_ABTAK1_MASK		2U
#define CANTAAK_ABTAK2_MASK		4U
#define CANTAAK_ABTAK_MASK		7U
#define CANTAAK_ABTAK_BITNUM	0U

/*** CANTBSEL - MSCAN Transmit Buffer Selection; baseaddr + 0x0A ***/
#define CANTBSEL_TX0_MASK		1U
#define CANTBSEL_TX1_MASK		2U
#define CANTBSEL_TX2_MASK		4U
#define CANTBSEL_TX_MASK		7U
#define CANTBSEL_TX_BITNUM		0U

/*** CANIDAC - MSCAN Identifier Acceptance Control Register; baseaddr + 0x0B ***/
#define CANIDAC_IDHIT0_MASK		1U
#define CANIDAC_IDHIT1_MASK		2U
#define CANIDAC_IDHIT2_MASK		4U
#define CANIDAC_IDAM0_MASK		16U
#define CANIDAC_IDAM1_MASK		32U
#define CANIDAC_IDHIT_MASK		7U
#define CANIDAC_IDHIT_BITNUM	0U
#define CANIDAC_IDAM_MASK		48U
#define CANIDAC_IDAM_BITNUM		4U

/*** CANMISC - MSCAN Miscellaneous Register; baseaddr + 0x0D ***/
#define CANMISC_BOHOLD_MASK     1U


/*** CANRXERR - MSCAN Receive Error Counter Register; baseaddr + 0x0E  ***/
#define CANRXERR_RXERR0_MASK	1U
#define CANRXERR_RXERR1_MASK	2U
#define CANRXERR_RXERR2_MASK	4U
#define CANRXERR_RXERR3_MASK	8U
#define CANRXERR_RXERR4_MASK	16U
#define CANRXERR_RXERR5_MASK	32U
#define CANRXERR_RXERR6_MASK	64U
#define CANRXERR_RXERR7_MASK	128U

/*** CANTXERR - MSCAN Transmit Error Counter Register; baseaddr + 0x0F  ***/
#define CANTXERR_TXERR0_MASK	1U
#define CANTXERR_TXERR1_MASK	2U
#define CANTXERR_TXERR2_MASK	4U
#define CANTXERR_TXERR3_MASK	8U
#define CANTXERR_TXERR4_MASK	16U
#define CANTXERR_TXERR5_MASK 	32U
#define CANTXERR_TXERR6_MASK	64U
#define CANTXERR_TXERR7_MASK	128U

/*** CANIDAR0 - MSCAN Identifier Acceptance Register 0; baseaddr + 0x10  ***/
#define CANIDAR0_AC0_MASK		1U
#define CANIDAR0_AC1_MASK		2U
#define CANIDAR0_AC2_MASK		4U
#define CANIDAR0_AC3_MASK		8U
#define CANIDAR0_AC4_MASK		16U
#define CANIDAR0_AC5_MASK		32U
#define CANIDAR0_AC6_MASK		64U
#define CANIDAR0_AC7_MASK		128U

/*** CANIDAR1 - MSCAN Identifier Acceptance Register 1; baseaddr + 0x11  ***/
#define CANIDAR1_AC0_MASK		1U
#define CANIDAR1_AC1_MASK		2U
#define CANIDAR1_AC2_MASK		4U
#define CANIDAR1_AC3_MASK		8U
#define CANIDAR1_AC4_MASK		16U
#define CANIDAR1_AC5_MASK		32U
#define CANIDAR1_AC6_MASK		64U
#define CANIDAR1_AC7_MASK		128U

/*** CANIDAR2 - MSCAN Identifier Acceptance Register 2; baseaddr + 0x12  ***/
#define CANIDAR2_AC0_MASK		1U
#define CANIDAR2_AC1_MASK		2U
#define CANIDAR2_AC2_MASK		4U
#define CANIDAR2_AC3_MASK		8U
#define CANIDAR2_AC4_MASK		16U
#define CANIDAR2_AC5_MASK		32U
#define CANIDAR2_AC6_MASK		64U
#define CANIDAR2_AC7_MASK		128U

/*** CANIDAR3 - MSCAN Identifier Acceptance Register 3; baseaddr + 0x13  ***/
#define CANIDAR3_AC0_MASK		1U
#define CANIDAR3_AC1_MASK		2U
#define CANIDAR3_AC2_MASK		4U
#define CANIDAR3_AC3_MASK		8U
#define CANIDAR3_AC4_MASK		16U
#define CANIDAR3_AC5_MASK		32U
#define CANIDAR3_AC6_MASK		64U
#define CANIDAR3_AC7_MASK		128U

/*** CANIDMR0 - MSCAN Identifier Mask Register 0; baseaddr + 0x14  ***/
#define CANIDMR0_AM0_MASK		1U
#define CANIDMR0_AM1_MASK		2U
#define CANIDMR0_AM2_MASK		4U
#define CANIDMR0_AM3_MASK		8U
#define CANIDMR0_AM4_MASK		16U
#define CANIDMR0_AM5_MASK		32U
#define CANIDMR0_AM6_MASK		64U
#define CANIDMR0_AM7_MASK		128U

/*** CANIDMR1 - MSCAN Identifier Mask Register 1; baseaddr + 0x15 ***/
#define CANIDMR1_AM0_MASK		1U
#define CANIDMR1_AM1_MASK		2U
#define CANIDMR1_AM2_MASK		4U
#define CANIDMR1_AM3_MASK		8U
#define CANIDMR1_AM4_MASK		16U
#define CANIDMR1_AM5_MASK		32U
#define CANIDMR1_AM6_MASK		64U
#define CANIDMR1_AM7_MASK		128U

/*** CANIDMR2 - MSCAN Identifier Mask Register 2; baseaddr + 0x16 ***/
#define CANIDMR2_AM0_MASK		1U
#define CANIDMR2_AM1_MASK		2U
#define CANIDMR2_AM2_MASK		4U
#define CANIDMR2_AM3_MASK		8U
#define CANIDMR2_AM4_MASK		16U
#define CANIDMR2_AM5_MASK		32U
#define CANIDMR2_AM6_MASK		64U
#define CANIDMR2_AM7_MASK		128U

/*** CANIDMR3 - MSCAN Identifier Mask Register 3; baseaddr + 0x17 ***/
#define CANIDMR3_AM0_MASK		1U
#define CANIDMR3_AM1_MASK		2U
#define CANIDMR3_AM2_MASK		4U
#define CANIDMR3_AM3_MASK		8U
#define CANIDMR3_AM4_MASK		16U
#define CANIDMR3_AM5_MASK		32U
#define CANIDMR3_AM6_MASK		64U
#define CANIDMR3_AM7_MASK		128U

/*** CANIDAR4 - MSCAN Identifier Acceptance Register 4; baseaddr + 0x18 ***/
#define CANIDAR4_AC0_MASK		1U
#define CANIDAR4_AC1_MASK		2U
#define CANIDAR4_AC2_MASK		4U
#define CANIDAR4_AC3_MASK		8U
#define CANIDAR4_AC4_MASK		16U
#define CANIDAR4_AC5_MASK		32U
#define CANIDAR4_AC6_MASK		64U
#define CANIDAR4_AC7_MASK		128U

/*** CANIDAR5 - MSCAN Identifier Acceptance Register 5; baseaddr + 0x19 ***/
#define CANIDAR5_AC0_MASK		1U
#define CANIDAR5_AC1_MASK		2U
#define CANIDAR5_AC2_MASK		4U
#define CANIDAR5_AC3_MASK		8U
#define CANIDAR5_AC4_MASK		16U
#define CANIDAR5_AC5_MASK		32U
#define CANIDAR5_AC6_MASK		64U
#define CANIDAR5_AC7_MASK		128U

/*** CANIDAR6 - MSCAN Identifier Acceptance Register 6; baseaddr + 0x1A ***/
#define CANIDAR6_AC0_MASK		1U
#define CANIDAR6_AC1_MASK		2U
#define CANIDAR6_AC2_MASK		4U
#define CANIDAR6_AC3_MASK		8U
#define CANIDAR6_AC4_MASK		16U
#define CANIDAR6_AC5_MASK		32U
#define CANIDAR6_AC6_MASK		64U
#define CANIDAR6_AC7_MASK		128U

/*** CANIDAR7 - MSCAN Identifier Acceptance Register 7; baseaddr + 0x1B ***/
#define CANIDAR7_AC0_MASK		1U
#define CANIDAR7_AC1_MASK		2U
#define CANIDAR7_AC2_MASK		4U
#define CANIDAR7_AC3_MASK		8U
#define CANIDAR7_AC4_MASK		16U
#define CANIDAR7_AC5_MASK		32U
#define CANIDAR7_AC6_MASK		64U
#define CANIDAR7_AC7_MASK		128U

/*** CANIDMR4 - MSCAN Identifier Mask Register 4; baseaddr + 0x1C ***/
#define CANIDMR4_AM0_MASK		1U
#define CANIDMR4_AM1_MASK		2U
#define CANIDMR4_AM2_MASK		4U
#define CANIDMR4_AM3_MASK		8U
#define CANIDMR4_AM4_MASK		16U
#define CANIDMR4_AM5_MASK		32U
#define CANIDMR4_AM6_MASK		64U
#define CANIDMR4_AM7_MASK		128U

/*** CANIDMR5 - MSCAN Identifier Mask Register 5; baseaddr + 0x1D ***/
#define CANIDMR5_AM0_MASK		1U
#define CANIDMR5_AM1_MASK		2U
#define CANIDMR5_AM2_MASK		4U
#define CANIDMR5_AM3_MASK		8U
#define CANIDMR5_AM4_MASK		16U
#define CANIDMR5_AM5_MASK		32U
#define CANIDMR5_AM6_MASK		64U
#define CANIDMR5_AM7_MASK		128U

/*** CANIDMR6 - MSCAN Identifier Mask Register 6; baseaddr + 0x1E ***/
#define CANIDMR6_AM0_MASK		1U
#define CANIDMR6_AM1_MASK		2U
#define CANIDMR6_AM2_MASK		4U
#define CANIDMR6_AM3_MASK		8U
#define CANIDMR6_AM4_MASK		16U
#define CANIDMR6_AM5_MASK		32U
#define CANIDMR6_AM6_MASK		64U
#define CANIDMR6_AM7_MASK		128U

/*** CANIDMR7 - MSCAN Identifier Mask Register 7; baseaddr + 0x1F ***/
#define CANIDMR7_AM0_MASK		1U
#define CANIDMR7_AM1_MASK		2U
#define CANIDMR7_AM2_MASK		4U
#define CANIDMR7_AM3_MASK		8U
#define CANIDMR7_AM4_MASK		16U
#define CANIDMR7_AM5_MASK		32U
#define CANIDMR7_AM6_MASK		64U
#define CANIDMR7_AM7_MASK		128U

/*** CANRXIDR0 - MSCAN Receive Identifier Register 0; baseaddr + 0x20 ***/
#define CANRXIDR0_ID21_MASK		1U
#define CANRXIDR0_ID22_MASK		2U
#define CANRXIDR0_ID23_MASK		4U
#define CANRXIDR0_ID24_MASK		8U
#define CANRXIDR0_ID25_MASK		16U
#define CANRXIDR0_ID26_MASK		32U
#define CANRXIDR0_ID27_MASK		64U
#define CANRXIDR0_ID28_MASK		128U

/*** CANRXIDR1 - MSCAN Receive Identifier Register 1; baseaddr + 0x21 ***/
#define CANRXIDR1_ID15_MASK		1U
#define CANRXIDR1_ID16_MASK		2U
#define CANRXIDR1_ID17_MASK		4U
#define CANRXIDR1_IDE_MASK		8U
#define CANRXIDR1_SRR_MASK		16U
#define CANRXIDR1_ID18_MASK		32U
#define CANRXIDR1_ID19_MASK		64U
#define CANRXIDR1_ID20_MASK		128U
#define CANRXIDR1_ID_15_MASK	7U
#define CANRXIDR1_ID_15_BITNUM	0U
#define CANRXIDR1_ID_18_MASK	224U
#define CANRXIDR1_ID_18_BITNUM	5U

/*** CANRXIDR2 - MSCAN Receive Identifier Register 2; baseaddr + 0x22 ***/
#define CANRXIDR2_ID7_MASK		1U
#define CANRXIDR2_ID8_MASK		2U
#define CANRXIDR2_ID9_MASK		4U
#define CANRXIDR2_ID10_MASK		8U
#define CANRXIDR2_ID11_MASK		16U
#define CANRXIDR2_ID12_MASK		32U
#define CANRXIDR2_ID13_MASK		64U
#define CANRXIDR2_ID14_MASK		128U

/*** CANRXIDR3 - MSCAN Receive Identifier Register 3; baseaddr + 0x23 ***/
#define CANRXIDR3_RTR_MASK		1U
#define CANRXIDR3_ID0_MASK		2U
#define CANRXIDR3_ID1_MASK		4U
#define CANRXIDR3_ID2_MASK		8U
#define CANRXIDR3_ID3_MASK		16U
#define CANRXIDR3_ID4_MASK		32U
#define CANRXIDR3_ID5_MASK		64U
#define CANRXIDR3_ID6_MASK		128U
#define CANRXIDR3_ID_MASK		254U
#define CANRXIDR3_ID_BITNUM		1U

/*** CANRXDSR0 - MSCAN Receive Data Segment Register 0; baseaddr + 0x24***/
#define CANRXDSR0_DB0_MASK		1U
#define CANRXDSR0_DB1_MASK		2U
#define CANRXDSR0_DB2_MASK		4U
#define CANRXDSR0_DB3_MASK		8U
#define CANRXDSR0_DB4_MASK		16U
#define CANRXDSR0_DB5_MASK		32U
#define CANRXDSR0_DB6_MASK		64U
#define CANRXDSR0_DB7_MASK		128U

/*** CANRXDSR1 - MSCAN Receive Data Segment Register 1; baseaddr + 0x25 ***/
#define CANRXDSR1_DB0_MASK		1U
#define CANRXDSR1_DB1_MASK		2U
#define CANRXDSR1_DB2_MASK		4U
#define CANRXDSR1_DB3_MASK		8U
#define CANRXDSR1_DB4_MASK		16U
#define CANRXDSR1_DB5_MASK		32U
#define CANRXDSR1_DB6_MASK		64U
#define CANRXDSR1_DB7_MASK		128U

/*** CANRXDSR2 - MSCAN Receive Data Segment Register 2; baseaddr + 0x26 ***/
#define CANRXDSR2_DB0_MASK		1U
#define CANRXDSR2_DB1_MASK		2U
#define CANRXDSR2_DB2_MASK		4U
#define CANRXDSR2_DB3_MASK		8U
#define CANRXDSR2_DB4_MASK		16U
#define CANRXDSR2_DB5_MASK		32U
#define CANRXDSR2_DB6_MASK		64U
#define CANRXDSR2_DB7_MASK		128U

/*** CANRXDSR3 - MSCAN Receive Data Segment Register 3; baseaddr + 0x27 ***/
#define CANRXDSR3_DB0_MASK		1U
#define CANRXDSR3_DB1_MASK		2U
#define CANRXDSR3_DB2_MASK		4U
#define CANRXDSR3_DB3_MASK		8U
#define CANRXDSR3_DB4_MASK		16U
#define CANRXDSR3_DB5_MASK		32U
#define CANRXDSR3_DB6_MASK		64U
#define CANRXDSR3_DB7_MASK		128U

/*** CANRXDSR4 - MSCAN Receive Data Segment Register 4; baseaddr + 0x28 ***/
#define CANRXDSR4_DB0_MASK		1U
#define CANRXDSR4_DB1_MASK		2U
#define CANRXDSR4_DB2_MASK		4U
#define CANRXDSR4_DB3_MASK		8U
#define CANRXDSR4_DB4_MASK		16U
#define CANRXDSR4_DB5_MASK		32U
#define CANRXDSR4_DB6_MASK		64U
#define CANRXDSR4_DB7_MASK		128U

/*** CANRXDSR5 - MSCAN Receive Data Segment Register 5; baseaddr + 0x29 ***/
#define CANRXDSR5_DB0_MASK		1U
#define CANRXDSR5_DB1_MASK		2U
#define CANRXDSR5_DB2_MASK		4U
#define CANRXDSR5_DB3_MASK		8U
#define CANRXDSR5_DB4_MASK		16U
#define CANRXDSR5_DB5_MASK		32U
#define CANRXDSR5_DB6_MASK		64U
#define CANRXDSR5_DB7_MASK		128U

/*** CANRXDSR6 - MSCAN Receive Data Segment Register 6; baseaddr + 0x2a ***/
#define CANRXDSR6_DB0_MASK		1U
#define CANRXDSR6_DB1_MASK		2U
#define CANRXDSR6_DB2_MASK		4U
#define CANRXDSR6_DB3_MASK		8U
#define CANRXDSR6_DB4_MASK		16U
#define CANRXDSR6_DB5_MASK		32U
#define CANRXDSR6_DB6_MASK		64U
#define CANRXDSR6_DB7_MASK		128U

/*** CANRXDSR7 - MSCAN Receive Data Segment Register 7; baseaddr + 0x2B ***/
#define CANRXDSR7_DB0_MASK		1U
#define CANRXDSR7_DB1_MASK		2U
#define CANRXDSR7_DB2_MASK		4U
#define CANRXDSR7_DB3_MASK		8U
#define CANRXDSR7_DB4_MASK		16U
#define CANRXDSR7_DB5_MASK		32U
#define CANRXDSR7_DB6_MASK		64U
#define CANRXDSR7_DB7_MASK		128U

/*** CANRXDLR - MSCAN Receive Data Length Register; baseaddr + 0x2C ***/
#define CANRXDLR_DLC0_MASK		1U
#define CANRXDLR_DLC1_MASK		2U
#define CANRXDLR_DLC2_MASK		4U
#define CANRXDLR_DLC3_MASK		8U
#define CANRXDLR_DLC_MASK		15U
#define CANRXDLR_DLC_BITNUM		0U

/*** CANRXTSR - MSCAN Receive Time Stamp Register; baseaddr + 0x2e~0x2F  ***/
#define CANRXTSRH_TSR8_MASK		1U
#define CANRXTSRH_TSR9_MASK		2U
#define CANRXTSRH_TSR10_MASK	4U
#define CANRXTSRH_TSR11_MASK	8U
#define CANRXTSRH_TSR12_MASK	16U
#define CANRXTSRH_TSR13_MASK	32U
#define CANRXTSRH_TSR14_MASK	64U
#define CANRXTSRH_TSR15_MASK	128U

#define CANRXTSRL_TSR0_MASK		1U
#define CANRXTSRL_TSR1_MASK		2U
#define CANRXTSRL_TSR2_MASK		4U
#define CANRXTSRL_TSR3_MASK		8U
#define CANRXTSRL_TSR4_MASK		16U
#define CANRXTSRL_TSR5_MASK		32U
#define CANRXTSRL_TSR6_MASK		64U
#define CANRXTSRL_TSR7_MASK		128U
    
#define CANRXTSR_TSR0_MASK		1U
#define CANRXTSR_TSR1_MASK		2U
#define CANRXTSR_TSR2_MASK		4U
#define CANRXTSR_TSR3_MASK		8U
#define CANRXTSR_TSR4_MASK		16U
#define CANRXTSR_TSR5_MASK		32U
#define CANRXTSR_TSR6_MASK		64U
#define CANRXTSR_TSR7_MASK		128U
#define CANRXTSR_TSR8_MASK		256U
#define CANRXTSR_TSR9_MASK		512U
#define CANRXTSR_TSR10_MASK		1024U
#define CANRXTSR_TSR11_MASK		2048U
#define CANRXTSR_TSR12_MASK		4096U
#define CANRXTSR_TSR13_MASK		8192U
#define CANRXTSR_TSR14_MASK		16384U
#define CANRXTSR_TSR15_MASK		32768U

/*** CANTXIDR0 - MSCAN Transmit Identifier Register 0; baseaddr + 0x30  ***/
#define CANTXIDR0_ID21_MASK		1U
#define CANTXIDR0_ID22_MASK		2U
#define CANTXIDR0_ID23_MASK		4U
#define CANTXIDR0_ID24_MASK		8U
#define CANTXIDR0_ID25_MASK		16U
#define CANTXIDR0_ID26_MASK		32U
#define CANTXIDR0_ID27_MASK		64U
#define CANTXIDR0_ID28_MASK		128U


/*** CANTXIDR1 - MSCAN Transmit Identifier Register 1; baseaddr + 0x31 ***/
#define CANTXIDR1_ID15_MASK		1U
#define CANTXIDR1_ID16_MASK		2U
#define CANTXIDR1_ID17_MASK		4U
#define CANTXIDR1_IDE_MASK		8U
#define CANTXIDR1_SRR_MASK		16U
#define CANTXIDR1_ID18_MASK		32U
#define CANTXIDR1_ID19_MASK		64U
#define CANTXIDR1_ID20_MASK		128U
#define CANTXIDR1_ID_15_MASK	7U
#define CANTXIDR1_ID_15_BITNUM	0U
#define CANTXIDR1_ID_18_MASK	224U
#define CANTXIDR1_ID_18_BITNUM	5U

/*** CANTXIDR2 - MSCAN Transmit Identifier Register 2; baseaddr + 0x32 ***/
#define CANTXIDR2_ID7_MASK		1U
#define CANTXIDR2_ID8_MASK		2U
#define CANTXIDR2_ID9_MASK		4U
#define CANTXIDR2_ID10_MASK		8U
#define CANTXIDR2_ID11_MASK		16U
#define CANTXIDR2_ID12_MASK		32U
#define CANTXIDR2_ID13_MASK		64U
#define CANTXIDR2_ID14_MASK		128U

/*** CANTXIDR3 - MSCAN Transmit Identifier Register 3; baseaddr + 0x33 ***/
#define CANTXIDR3_RTR_MASK		1U
#define CANTXIDR3_ID0_MASK		2U
#define CANTXIDR3_ID1_MASK		4U
#define CANTXIDR3_ID2_MASK		8U
#define CANTXIDR3_ID3_MASK		16U
#define CANTXIDR3_ID4_MASK		32U
#define CANTXIDR3_ID5_MASK		64U
#define CANTXIDR3_ID6_MASK		128U
#define CANTXIDR3_ID_MASK		254U
#define CANTXIDR3_ID_BITNUM		1U

/*** CANTXDSR0 - MSCAN Transmit Data Segment Register 0; baseaddr + 0x34 ***/
#define CANTXDSR0_DB0_MASK		1U
#define CANTXDSR0_DB1_MASK		2U
#define CANTXDSR0_DB2_MASK		4U
#define CANTXDSR0_DB3_MASK		8U
#define CANTXDSR0_DB4_MASK		16U
#define CANTXDSR0_DB5_MASK		32U
#define CANTXDSR0_DB6_MASK		64U
#define CANTXDSR0_DB7_MASK		128U

/*** CANTXDSR1 - MSCAN Transmit Data Segment Register 1; baseaddr + 0x35 ***/
#define CANTXDSR1_DB0_MASK		1U
#define CANTXDSR1_DB1_MASK		2U
#define CANTXDSR1_DB2_MASK		4U
#define CANTXDSR1_DB3_MASK		8U
#define CANTXDSR1_DB4_MASK		16U
#define CANTXDSR1_DB5_MASK		32U
#define CANTXDSR1_DB6_MASK		64U
#define CANTXDSR1_DB7_MASK		128U

/*** CANTXDSR2 - MSCAN Transmit Data Segment Register 2; baseaddr + 0x36 ***/
#define CANTXDSR2_DB0_MASK		1U
#define CANTXDSR2_DB1_MASK		2U
#define CANTXDSR2_DB2_MASK		4U
#define CANTXDSR2_DB3_MASK		8U
#define CANTXDSR2_DB4_MASK		16U
#define CANTXDSR2_DB5_MASK		32U
#define CANTXDSR2_DB6_MASK		64U
#define CANTXDSR2_DB7_MASK		128U

/*** CANTXDSR3 - MSCAN Transmit Data Segment Register 3; baseaddr + 0x37 ***/
#define CANTXDSR3_DB0_MASK		1U
#define CANTXDSR3_DB1_MASK		2U
#define CANTXDSR3_DB2_MASK		4U
#define CANTXDSR3_DB3_MASK		8U
#define CANTXDSR3_DB4_MASK		16U
#define CANTXDSR3_DB5_MASK		32U
#define CANTXDSR3_DB6_MASK		64U
#define CANTXDSR3_DB7_MASK		128U

/*** CANTXDSR4 - MSCAN Transmit Data Segment Register 4; baseaddr + 0x38 ***/
#define CANTXDSR4_DB0_MASK		1U
#define CANTXDSR4_DB1_MASK		2U
#define CANTXDSR4_DB2_MASK		4U
#define CANTXDSR4_DB3_MASK		8U
#define CANTXDSR4_DB4_MASK		16U
#define CANTXDSR4_DB5_MASK		32U
#define CANTXDSR4_DB6_MASK		64U
#define CANTXDSR4_DB7_MASK		128U

/*** CANTXDSR5 - MSCAN Transmit Data Segment Register 5; baseaddr + 0x39 ***/
#define CANTXDSR5_DB0_MASK		1U
#define CANTXDSR5_DB1_MASK		2U
#define CANTXDSR5_DB2_MASK		4U
#define CANTXDSR5_DB3_MASK		8U
#define CANTXDSR5_DB4_MASK		16U
#define CANTXDSR5_DB5_MASK		32U
#define CANTXDSR5_DB6_MASK		64U
#define CANTXDSR5_DB7_MASK		128U

/*** CANTXDSR6 - MSCAN Transmit Data Segment Register 6; baseaddr + 0x3a ***/
#define CANTXDSR6_DB0_MASK		1U
#define CANTXDSR6_DB1_MASK		2U
#define CANTXDSR6_DB2_MASK		4U
#define CANTXDSR6_DB3_MASK		8U
#define CANTXDSR6_DB4_MASK		16U
#define CANTXDSR6_DB5_MASK		32U
#define CANTXDSR6_DB6_MASK		64U
#define CANTXDSR6_DB7_MASK		128U

/*** CANTXDSR7 - MSCAN Transmit Data Segment Register 7; baseaddr + 0x3b ***/
#define CANTXDSR7_DB0_MASK		1U
#define CANTXDSR7_DB1_MASK		2U
#define CANTXDSR7_DB2_MASK		4U
#define CANTXDSR7_DB3_MASK		8U
#define CANTXDSR7_DB4_MASK		16U
#define CANTXDSR7_DB5_MASK		32U
#define CANTXDSR7_DB6_MASK		64U
#define CANTXDSR7_DB7_MASK		128U

/*** CANTXDLR - MSCAN Transmit Data Length Register; baseaddr + 0x3c ***/
#define CANTXDLR_DLC0_MASK		1U
#define CANTXDLR_DLC1_MASK		2U
#define CANTXDLR_DLC2_MASK		4U
#define CANTXDLR_DLC3_MASK		8U
#define CANTXDLR_DLC_MASK		15U
#define CANTXDLR_DLC_BITNUM		0U

/*** CANTXTBPR - MSCAN Transmit Buffer Priority; baseaddr + 0x3d ***/
#define CANTXTBPR_PRIO0_MASK	1U
#define CANTXTBPR_PRIO1_MASK	2U
#define CANTXTBPR_PRIO2_MASK	4U
#define CANTXTBPR_PRIO3_MASK	8U
#define CANTXTBPR_PRIO4_MASK	16U
#define CANTXTBPR_PRIO5_MASK	32U
#define CANTXTBPR_PRIO6_MASK	64U
#define CANTXTBPR_PRIO7_MASK	128U


/*** CANTXTSR - MSCAN Transmit Time Stamp Register; baseaddr + 0x3e~0x3F ***/
#define CANTXTSRH_TSR8_MASK		1U
#define CANTXTSRH_TSR9_MASK		2U
#define CANTXTSRH_TSR10_MASK	4U
#define CANTXTSRH_TSR11_MASK	8U
#define CANTXTSRH_TSR12_MASK	16U
#define CANTXTSRH_TSR13_MASK	32U
#define CANTXTSRH_TSR14_MASK	64U
#define CANTXTSRH_TSR15_MASK	128U
    
#define CANTXTSRL_TSR0_MASK		1U
#define CANTXTSRL_TSR1_MASK		2U
#define CANTXTSRL_TSR2_MASK		4U
#define CANTXTSRL_TSR3_MASK		8U
#define CANTXTSRL_TSR4_MASK		16U
#define CANTXTSRL_TSR5_MASK		32U
#define CANTXTSRL_TSR6_MASK		64U
#define CANTXTSRL_TSR7_MASK		128U

#define CANTXTSR_TSR0_MASK		1U
#define CANTXTSR_TSR1_MASK		2U
#define CANTXTSR_TSR2_MASK		4U
#define CANTXTSR_TSR3_MASK		8U
#define CANTXTSR_TSR4_MASK		16U
#define CANTXTSR_TSR5_MASK		32U
#define CANTXTSR_TSR6_MASK		64U
#define CANTXTSR_TSR7_MASK		128U
#define CANTXTSR_TSR8_MASK		256U
#define CANTXTSR_TSR9_MASK		512U
#define CANTXTSR_TSR10_MASK		1024U
#define CANTXTSR_TSR11_MASK		2048U
#define CANTXTSR_TSR12_MASK		4096U
#define CANTXTSR_TSR13_MASK		8192U
#define CANTXTSR_TSR14_MASK		16384U
#define CANTXTSR_TSR15_MASK		32768U



/**************************************
		CAN寄存器定义
 **************************************/
/*** CANCTL0 - MSCAN Control 0 Register;  baseaddr + 0x00u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 INITRQ      :1;                                       /* Initialization Mode Request */
    uint8 SLPRQ       :1;                                       /* Sleep Mode Request */
    uint8 WUPE        :1;                                       /* Wake-Up Enable */
    uint8 TIME        :1;                                       /* Timer Enable */
    uint8 SYNCH       :1;                                       /* Synchronized Status */
    uint8 CSWAI       :1;                                       /* CAN Stops in Wait Mode */
    uint8 RXACT       :1;                                       /* Receiver Active Status */
    uint8 RXFRM       :1;                                       /* Received Frame Flag */
  } Bits;
} CANCTL0STR;

/*** CANCTL1 - MSCAN Control 1 Register; baseaddr + 0x01u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 INITAK      :1;                                       /* Initialization Mode Acknowledge */
    uint8 SLPAK       :1;                                       /* Sleep Mode Acknowledge */
    uint8 WUPM        :1;                                       /* Wake-Up Mode */
    uint8 BORM        :1;                                       /* Bus-Off Recovery Mode */
    uint8 LISTEN      :1;                                       /* Listen Only Mode */
    uint8 LOOPB       :1;                                       /* Loop Back Self Test Mode */
    uint8 CLKSRC      :1;                                       /* MSCAN Clock Source */
    uint8 CANE        :1;                                       /* MSCAN Enable */
  } Bits;
} CANCTL1STR;

/*** CANBTR0 - MSCAN Bus Timing Register 0; baseaddr + 0x02u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 BRP0        :1;                                       /* Baud Rate Prescaler 0 */
    uint8 BRP1        :1;                                       /* Baud Rate Prescaler 1 */
    uint8 BRP2        :1;                                       /* Baud Rate Prescaler 2 */
    uint8 BRP3        :1;                                       /* Baud Rate Prescaler 3 */
    uint8 BRP4        :1;                                       /* Baud Rate Prescaler 4 */
    uint8 BRP5        :1;                                       /* Baud Rate Prescaler 5 */
    uint8 SJW0        :1;                                       /* Synchronization Jump Width 0 */
    uint8 SJW1        :1;                                       /* Synchronization Jump Width 1 */
  } Bits;
  struct {
    uint8 grpBRP  :6;
    uint8 grpSJW  :2;
  } MergedBits;
} CANBTR0STR;

/*** CANBTR1 - MSCAN Bus Timing Register 1; baseaddr + 0x03u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 TSEG10      :1;                                       /* Time Segment 10 */
    uint8 TSEG11      :1;                                       /* Time Segment 11 */
    uint8 TSEG12      :1;                                       /* Time Segment 12 */
    uint8 TSEG13      :1;                                       /* Time Segment 13 */
    uint8 TSEG20      :1;                                       /* Time Segment 20 */
    uint8 TSEG21      :1;                                       /* Time Segment 21 */
    uint8 TSEG22      :1;                                       /* Time Segment 22 */
    uint8 SAMP        :1;                                       /* Sampling */
  } Bits;
  struct {
    uint8 grpTSEG_10 :4;
    uint8 grpTSEG_20 :3;
    uint8         :1;
  } MergedBits;
} CANBTR1STR;


/*** CANRFLG - MSCAN Receiver Flag Register; baseaddr + 0x04u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 RXF         :1;                                       /* Receive Buffer Full */
    uint8 OVRIF       :1;                                       /* Overrun Interrupt Flag */
    uint8 TSTAT0      :1;                                       /* Transmitter Status Bit 0 */
    uint8 TSTAT1      :1;                                       /* Transmitter Status Bit 1 */
    uint8 RSTAT0      :1;                                       /* Receiver Status Bit 0 */
    uint8 RSTAT1      :1;                                       /* Receiver Status Bit 1 */
    uint8 CSCIF       :1;                                       /* CAN Status Change Interrupt Flag */
    uint8 WUPIF       :1;                                       /* Wake-up Interrupt Flag */
  } Bits;
  struct {
    uint8         :1;
    uint8         :1;
    uint8 grpTSTAT :2;
    uint8 grpRSTAT :2;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANRFLGSTR;

/*** CANRIER - MSCAN Receiver Interrupt Enable Register; baseaddr + 0x05u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 RXFIE       :1;                                       	/* Receiver Full Interrupt Enable */
    uint8 OVRIE       :1;                                       	/* Overrun Interrupt Enable */
    uint8 TSTATE0     :1;                                       	/* Transmitter Status Change Enable 0 */
    uint8 TSTATE1     :1;                                       	/* Transmitter Status Change Enable 1 */
    uint8 RSTATE0     :1;                                       	/* Receiver Status Change Enable 0 */
    uint8 RSTATE1     :1;                                       	/* Receiver Status Change Enable 1 */
    uint8 CSCIE       :1;                                      	 /* CAN Status Change Interrupt Enable */
    uint8 WUPIE       :1;                                       	/* Wake-up Interrupt Enable */
  } Bits;
  struct {
    uint8         :1;
    uint8         :1;
    uint8 grpTSTATE :2;
    uint8 grpRSTATE :2;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANRIERSTR;

/*** CANTFLG - MSCAN Transmitter Flag Register; baseaddr + 0x06u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 TXE0        :1;                                       /* Transmitter Buffer Empty 0 */
    uint8 TXE1        :1;                                       /* Transmitter Buffer Empty 1 */
    uint8 TXE2        :1;                                       /* Transmitter Buffer Empty 2 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpTXE  :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTFLGSTR;


/*** CANTIER - MSCAN Transmitter Interrupt Enable Register; baseaddr + 0x07u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 TXEIE0      :1;                                       /* Transmitter Empty Interrupt Enable 0 */
    uint8 TXEIE1      :1;                                       /* Transmitter Empty Interrupt Enable 1 */
    uint8 TXEIE2      :1;                                       /* Transmitter Empty Interrupt Enable 2 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpTXEIE :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTIERSTR;

/*** CANTARQ - MSCAN Transmitter Message Abort Request; baseaddr + 0x08u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ABTRQ0      :1;                                       /* Abort Request 0 */
    uint8 ABTRQ1      :1;                                       /* Abort Request 1 */
    uint8 ABTRQ2      :1;                                       /* Abort Request 2 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpABTRQ :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTARQSTR;

/*** CANTAAK - MSCAN Transmitter Message Abort Acknowledge; baseaddr + 0x09u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ABTAK0      :1;                                       /* Abort Acknowledge 0 */
    uint8 ABTAK1      :1;                                       /* Abort Acknowledge 1 */
    uint8 ABTAK2      :1;                                       /* Abort Acknowledge 2 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpABTAK :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTAAKSTR;

/*** CANTBSEL - MSCAN Transmit Buffer Selection;  baseaddr + 0x0Au  ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 TX0         :1;                                       /* Transmit Buffer Select 0 */
    uint8 TX1         :1;                                       /* Transmit Buffer Select 1 */
    uint8 TX2         :1;                                       /* Transmit Buffer Select 2 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpTX   :3;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTBSELSTR;

/*** CANIDAC - MSCAN Identifier Acceptance Control Register; baseaddr + 0x0Bu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 IDHIT0      :1;                                       /* Identifier Acceptance Hit Indicator 0 */
    uint8 IDHIT1      :1;                                       /* Identifier Acceptance Hit Indicator 1 */
    uint8 IDHIT2      :1;                                       /* Identifier Acceptance Hit Indicator 2 */
    uint8             :1; 
    uint8 IDAM0       :1;                                       /* Identifier Acceptance Mode 0 */
    uint8 IDAM1       :1;                                       /* Identifier Acceptance Mode 1 */
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpIDHIT :3;
    uint8         :1;
    uint8 grpIDAM :2;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANIDACSTR;

/*** CANMISC - MSCAN Miscellaneous Register; baseaddr + 0x0Du ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 BOHOLD      :1;                                       /* Bus-off State Hold Until User Request */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
} CANMISCSTR;

/*** CANRXERR - MSCAN Receive Error Counter Register; baseaddr + 0x0Eu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 RXERR0      :1;                                       /* Bit 0 */
    uint8 RXERR1      :1;                                       /* Bit 1 */
    uint8 RXERR2      :1;                                       /* Bit 2 */
    uint8 RXERR3      :1;                                       /* Bit 3 */
    uint8 RXERR4      :1;                                       /* Bit 4 */
    uint8 RXERR5      :1;                                       /* Bit 5 */
    uint8 RXERR6      :1;                                       /* Bit 6 */
    uint8 RXERR7      :1;                                       /* Bit 7 */
  } Bits;
} CANRXERRSTR;

/*** CANTXERR - MSCAN Transmit Error Counter Register; baseaddr + 0x0Fu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 TXERR0      :1;                                       /* Bit 0 */
    uint8 TXERR1      :1;                                       /* Bit 1 */
    uint8 TXERR2      :1;                                       /* Bit 2 */
    uint8 TXERR3      :1;                                       /* Bit 3 */
    uint8 TXERR4      :1;                                       /* Bit 4 */
    uint8 TXERR5      :1;                                       /* Bit 5 */
    uint8 TXERR6      :1;                                       /* Bit 6 */
    uint8 TXERR7      :1;                                       /* Bit 7 */
  } Bits;
} CANTXERRSTR;

/*** CANIDAR0 - MSCAN Identifier Acceptance Register 0; baseaddr + 0x10u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR0STR;

/*** CANIDAR1 - MSCAN Identifier Acceptance Register 1; baseaddr + 0x11u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR1STR;

/*** CANIDAR2 - MSCAN Identifier Acceptance Register 2; baseaddr + 0x12u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR2STR;

/*** CANIDAR3 - MSCAN Identifier Acceptance Register 3; baseaddr + 0x13u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR3STR;

/*** CANIDMR0 - MSCAN Identifier Mask Register 0; baseaddr + 0x14u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR0STR;

/*** CANIDMR1 - MSCAN Identifier Mask Register 1; baseaddr + 0x15u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR1STR;

/*** CANIDMR2 - MSCAN Identifier Mask Register 2; baseaddr + 0x16u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR2STR;

/*** CANIDMR3 - MSCAN Identifier Mask Register 3; baseaddr + 0x17u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR3STR;

/*** CANIDAR4 - MSCAN Identifier Acceptance Register 4; baseaddr + 0x18u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR4STR;

/*** CANIDAR5 - MSCAN Identifier Acceptance Register 5; baseaddr + 0x19u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR5STR;

/*** CANIDAR6 - MSCAN Identifier Acceptance Register 6; baseaddr + 0x1Au ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR6STR;

/*** CANIDAR7 - MSCAN Identifier Acceptance Register 7; baseaddr + 0x1Bu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AC0         :1;                                       /* Acceptance Code Bit 0 */
    uint8 AC1         :1;                                       /* Acceptance Code Bit 1 */
    uint8 AC2         :1;                                       /* Acceptance Code Bit 2 */
    uint8 AC3         :1;                                       /* Acceptance Code Bit 3 */
    uint8 AC4         :1;                                       /* Acceptance Code Bit 4 */
    uint8 AC5         :1;                                       /* Acceptance Code Bit 5 */
    uint8 AC6         :1;                                       /* Acceptance Code Bit 6 */
    uint8 AC7         :1;                                       /* Acceptance Code Bit 7 */
  } Bits;
} CANIDAR7STR;

/*** CANIDMR4 - MSCAN Identifier Mask Register 4; baseaddr + 0x1Cu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR4STR;

/*** CANIDMR5 - MSCAN Identifier Mask Register 5; baseaddr + 0x1Du ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR5STR;

/*** CANIDMR6 - MSCAN Identifier Mask Register 6; baseaddr + 0x1Eu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR6STR;

/*** CANIDMR7 - MSCAN Identifier Mask Register 7; baseaddr + 0x1Fu ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 AM0         :1;                                       /* Acceptance Mask Bit 0 */
    uint8 AM1         :1;                                       /* Acceptance Mask Bit 1 */
    uint8 AM2         :1;                                       /* Acceptance Mask Bit 2 */
    uint8 AM3         :1;                                       /* Acceptance Mask Bit 3 */
    uint8 AM4         :1;                                       /* Acceptance Mask Bit 4 */
    uint8 AM5         :1;                                       /* Acceptance Mask Bit 5 */
    uint8 AM6         :1;                                       /* Acceptance Mask Bit 6 */
    uint8 AM7         :1;                                       /* Acceptance Mask Bit 7 */
  } Bits;
} CANIDMR7STR;

/*** CANRXIDR0 - MSCAN Receive Identifier Register 0; baseaddr + 0x20u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID21        :1;                                       /* Extended format identifier Bit 21 */
    uint8 ID22        :1;                                       /* Extended format identifier Bit 22 */
    uint8 ID23        :1;                                       /* Extended format identifier Bit 23 */
    uint8 ID24        :1;                                       /* Extended format identifier Bit 24 */
    uint8 ID25        :1;                                       /* Extended format identifier Bit 25 */
    uint8 ID26        :1;                                       /* Extended format identifier Bit 26 */
    uint8 ID27        :1;                                       /* Extended format identifier Bit 27 */
    uint8 ID28        :1;                                       /* Extended format identifier Bit 28 */
  } Bits;
} CANRXIDR0STR;

/*** CANRXIDR1 - MSCAN Receive Identifier Register 1; baseaddr + 0x21u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID15        :1;                                       /* Extended format identifier Bit 15 */
    uint8 ID16        :1;                                       /* Extended format identifier Bit 16 */
    uint8 ID17        :1;                                       /* Extended format identifier Bit 17 */
    uint8 IDE         :1;                                       /* ID Extended */
    uint8 SRR         :1;                                       /* Substitute Remote Request */
    uint8 ID18        :1;                                       /* Extended format identifier Bit 18 */
    uint8 ID19        :1;                                       /* Extended format identifier Bit 19 */
    uint8 ID20        :1;                                       /* Extended format identifier Bit 20 */
  } Bits;
  struct {
    uint8 grpID_15 :3;
    uint8         :1;
    uint8         :1;
    uint8 grpID_18 :3;
  } MergedBits;
} CANRXIDR1STR;

/*** CANRXIDR2 - MSCAN Receive Identifier Register 2; baseaddr + 0x22u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID7         :1;                                       /* Extended format identifier Bit 7 */
    uint8 ID8         :1;                                       /* Extended format identifier Bit 8 */
    uint8 ID9         :1;                                       /* Extended format identifier Bit 9 */
    uint8 ID10        :1;                                       /* Extended format identifier Bit 10 */
    uint8 ID11        :1;                                       /* Extended format identifier Bit 11 */
    uint8 ID12        :1;                                       /* Extended format identifier Bit 12 */
    uint8 ID13        :1;                                       /* Extended format identifier Bit 13 */
    uint8 ID14        :1;                                       /* Extended format identifier Bit 14 */
  } Bits;
} CANRXIDR2STR;

/*** CANRXIDR3 - MSCAN Receive Identifier Register 3; baseaddr + 0x23u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 RTR         :1;                                       /* Remote Transmission Request */
    uint8 ID0         :1;                                       /* Extended format identifier Bit 0 */
    uint8 ID1         :1;                                       /* Extended format identifier Bit 1 */
    uint8 ID2         :1;                                       /* Extended format identifier Bit 2 */
    uint8 ID3         :1;                                       /* Extended format identifier Bit 3 */
    uint8 ID4         :1;                                       /* Extended format identifier Bit 4 */
    uint8 ID5         :1;                                       /* Extended format identifier Bit 5 */
    uint8 ID6         :1;                                       /* Extended format identifier Bit 6 */
  } Bits;
  struct {
    uint8         :1;
    uint8 grpID   :7;
  } MergedBits;
} CANRXIDR3STR;

/*** CANRXDSR0 - MSCAN Receive Data Segment Register 0; baseaddr + 0x24u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR0STR;

/*** CANRXDSR1 - MSCAN Receive Data Segment Register 1; baseaddr + 0x25u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR1STR;

/*** CANRXDSR2 - MSCAN Receive Data Segment Register 2; baseaddr + 0x26u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR2STR;

/*** CANRXDSR3 - MSCAN Receive Data Segment Register 3; baseaddr + 0x27u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR3STR;

/*** CANRXDSR4 - MSCAN Receive Data Segment Register 4; baseaddr + 0x28u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR4STR;

/*** CANRXDSR5 - MSCAN Receive Data Segment Register 5; baseaddr + 0x29u ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR5STR;

/*** CANRXDSR6 - MSCAN Receive Data Segment Register 6; baseaddr + 0x2au ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR6STR;


/*** CANRXDSR7 - MSCAN Receive Data Segment Register 7; baseaddr + 0x2b ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANRXDSR7STR;

/*** CANRXDLR - MSCAN Receive Data Length Register; baseaddr + 0x2c ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DLC0        :1;                                       /* Data Length Code Bit 0 */
    uint8 DLC1        :1;                                       /* Data Length Code Bit 1 */
    uint8 DLC2        :1;                                       /* Data Length Code Bit 2 */
    uint8 DLC3        :1;                                       /* Data Length Code Bit 3 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpDLC  :4;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANRXDLRSTR;


/*** CANRXTSR - MSCAN Receive Time Stamp Register; baseaddr + (0x2e~0x2f) ***/
typedef union {
  uint16 Word;
   /* Overlapped registers: */
  struct {
    /*** CANRXTSRH - MSCAN Receive Time Stamp Register High; baseaddr + 0x2e ***/
    union {
      uint8 Byte;
      struct {
        uint8 TSR8        :1;                                       /* Time Stamp Bit 8 */
        uint8 TSR9        :1;                                       /* Time Stamp Bit 9 */
        uint8 TSR10       :1;                                       /* Time Stamp Bit 10 */
        uint8 TSR11       :1;                                       /* Time Stamp Bit 11 */
        uint8 TSR12       :1;                                       /* Time Stamp Bit 12 */
        uint8 TSR13       :1;                                       /* Time Stamp Bit 13 */
        uint8 TSR14       :1;                                       /* Time Stamp Bit 14 */
        uint8 TSR15       :1;                                       /* Time Stamp Bit 15 */
      } Bits;
    } CANRXTSRHSTR;
    
    /*** CANRXTSRL - MSCAN Receive Time Stamp Register Low; baseaddr + 0x2F ***/
    union {
      uint8 Byte;
      struct {
        uint8 TSR0        :1;                                       /* Time Stamp Bit 0 */
        uint8 TSR1        :1;                                       /* Time Stamp Bit 1 */
        uint8 TSR2        :1;                                       /* Time Stamp Bit 2 */
        uint8 TSR3        :1;                                       /* Time Stamp Bit 3 */
        uint8 TSR4        :1;                                       /* Time Stamp Bit 4 */
        uint8 TSR5        :1;                                       /* Time Stamp Bit 5 */
        uint8 TSR6        :1;                                       /* Time Stamp Bit 6 */
        uint8 TSR7        :1;                                       /* Time Stamp Bit 7 */
      } Bits;
    } CANRXTSRLSTR; 
  } Overlap_STR;

  struct {
    uint16 TSR0        :1;                                       /* Time Stamp Bit 0 */
    uint16 TSR1        :1;                                       /* Time Stamp Bit 1 */
    uint16 TSR2        :1;                                       /* Time Stamp Bit 2 */
    uint16 TSR3        :1;                                       /* Time Stamp Bit 3 */
    uint16 TSR4        :1;                                       /* Time Stamp Bit 4 */
    uint16 TSR5        :1;                                       /* Time Stamp Bit 5 */
    uint16 TSR6        :1;                                       /* Time Stamp Bit 6 */
    uint16 TSR7        :1;                                       /* Time Stamp Bit 7 */
    uint16 TSR8        :1;                                       /* Time Stamp Bit 8 */
    uint16 TSR9        :1;                                       /* Time Stamp Bit 9 */
    uint16 TSR10       :1;                                       /* Time Stamp Bit 10 */
    uint16 TSR11       :1;                                       /* Time Stamp Bit 11 */
    uint16 TSR12       :1;                                       /* Time Stamp Bit 12 */
    uint16 TSR13       :1;                                       /* Time Stamp Bit 13 */
    uint16 TSR14       :1;                                       /* Time Stamp Bit 14 */
    uint16 TSR15       :1;                                       /* Time Stamp Bit 15 */
  } Bits;
} CANRXTSRSTR;



/*** CANTXIDR0 - MSCAN Transmit Identifier Register 0; baseaddr + 0x30***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID21        :1;                                       /* Extended format identifier Bit 21 */
    uint8 ID22        :1;                                       /* Extended format identifier Bit 22 */
    uint8 ID23        :1;                                       /* Extended format identifier Bit 23 */
    uint8 ID24        :1;                                       /* Extended format identifier Bit 24 */
    uint8 ID25        :1;                                       /* Extended format identifier Bit 25 */
    uint8 ID26        :1;                                       /* Extended format identifier Bit 26 */
    uint8 ID27        :1;                                       /* Extended format identifier Bit 27 */
    uint8 ID28        :1;                                       /* Extended format identifier Bit 28 */
  } Bits;
} CANTXIDR0STR;


/*** CANTXIDR1 - MSCAN Transmit Identifier Register 1; baseaddr + 0x31 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID15        :1;                                       /* Extended format identifier Bit 15 */
    uint8 ID16        :1;                                       /* Extended format identifier Bit 16 */
    uint8 ID17        :1;                                       /* Extended format identifier Bit 17 */
    uint8 IDE         :1;                                       /* ID Extended */
    uint8 SRR         :1;                                       /* Substitute Remote Request */
    uint8 ID18        :1;                                       /* Extended format identifier Bit 18 */
    uint8 ID19        :1;                                       /* Extended format identifier Bit 19 */
    uint8 ID20        :1;                                       /* Extended format identifier Bit 20 */
  } Bits;
  struct {
    uint8 grpID_15 :3;
    uint8         :1;
    uint8         :1;
    uint8 grpID_18 :3;
  } MergedBits;
} CANTXIDR1STR;

/*** CANTXIDR2 - MSCAN Transmit Identifier Register 2; baseaddr + 0x32 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 ID7         :1;                                       /* Extended format identifier Bit 7 */
    uint8 ID8         :1;                                       /* Extended format identifier Bit 8 */
    uint8 ID9         :1;                                       /* Extended format identifier Bit 9 */
    uint8 ID10        :1;                                       /* Extended format identifier Bit 10 */
    uint8 ID11        :1;                                       /* Extended format identifier Bit 11 */
    uint8 ID12        :1;                                       /* Extended format identifier Bit 12 */
    uint8 ID13        :1;                                       /* Extended format identifier Bit 13 */
    uint8 ID14        :1;                                       /* Extended format identifier Bit 14 */
  } Bits;
} CANTXIDR2STR;

/*** CANTXIDR3 - MSCAN Transmit Identifier Register 3; baseaddr + 0x33 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 RTR         :1;                                       /* Remote Transmission Request */
    uint8 ID0         :1;                                       /* Extended format identifier Bit 0 */
    uint8 ID1         :1;                                       /* Extended format identifier Bit 1 */
    uint8 ID2         :1;                                       /* Extended format identifier Bit 2 */
    uint8 ID3         :1;                                       /* Extended format identifier Bit 3 */
    uint8 ID4         :1;                                       /* Extended format identifier Bit 4 */
    uint8 ID5         :1;                                       /* Extended format identifier Bit 5 */
    uint8 ID6         :1;                                       /* Extended format identifier Bit 6 */
  } Bits;
  struct {
    uint8         :1;
    uint8 grpID   :7;
  } MergedBits;
} CANTXIDR3STR;

/*** CANTXDSR0 - MSCAN Transmit Data Segment Register 0; baseaddr + 0x34 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR0STR;


/*** CANTXDSR1 - MSCAN Transmit Data Segment Register 1; baseaddr + 0x35 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR1STR;


/*** CANTXDSR2 - MSCAN Transmit Data Segment Register 2; baseaddr + 0x36 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR2STR;


/*** CANTXDSR3 - MSCAN Transmit Data Segment Register 3; baseaddr + 0x37 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR3STR;


/*** CANTXDSR4 - MSCAN Transmit Data Segment Register 4; baseaddr + 0x38 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR4STR;


/*** CANTXDSR5 - MSCAN Transmit Data Segment Register 5; baseaddr + 0x39 ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR5STR;


/*** CANTXDSR6 - MSCAN Transmit Data Segment Register 6; baseaddr + 0x3a ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR6STR;


/*** CANTXDSR7 - MSCAN Transmit Data Segment Register 7; baseaddr + 0x3b ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DB0         :1;                                       /* Data Bit 0 */
    uint8 DB1         :1;                                       /* Data Bit 1 */
    uint8 DB2         :1;                                       /* Data Bit 2 */
    uint8 DB3         :1;                                       /* Data Bit 3 */
    uint8 DB4         :1;                                       /* Data Bit 4 */
    uint8 DB5         :1;                                       /* Data Bit 5 */
    uint8 DB6         :1;                                       /* Data Bit 6 */
    uint8 DB7         :1;                                       /* Data Bit 7 */
  } Bits;
} CANTXDSR7STR;


/*** CANTXDLR - MSCAN Transmit Data Length Register; baseaddr + 0x3c ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 DLC0        :1;                                       /* Data Length Code Bit 0 */
    uint8 DLC1        :1;                                       /* Data Length Code Bit 1 */
    uint8 DLC2        :1;                                       /* Data Length Code Bit 2 */
    uint8 DLC3        :1;                                       /* Data Length Code Bit 3 */
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
    uint8             :1; 
  } Bits;
  struct {
    uint8 grpDLC  :4;
    uint8         :1;
    uint8         :1;
    uint8         :1;
    uint8         :1;
  } MergedBits;
} CANTXDLRSTR;



/*** CANTXTBPR - MSCAN Transmit Buffer Priority; baseaddr + 0x3d ***/
typedef union {
  uint8 Byte;
  struct {
    uint8 PRIO0       :1;                                       /* Transmit Buffer Priority Bit 0 */
    uint8 PRIO1       :1;                                       /* Transmit Buffer Priority Bit 1 */
    uint8 PRIO2       :1;                                       /* Transmit Buffer Priority Bit 2 */
    uint8 PRIO3       :1;                                       /* Transmit Buffer Priority Bit 3 */
    uint8 PRIO4       :1;                                       /* Transmit Buffer Priority Bit 4 */
    uint8 PRIO5       :1;                                       /* Transmit Buffer Priority Bit 5 */
    uint8 PRIO6       :1;                                       /* Transmit Buffer Priority Bit 6 */
    uint8 PRIO7       :1;                                       /* Transmit Buffer Priority Bit 7 */
  } Bits;
} CANTXTBPRSTR;



/*** CANTXTSR - MSCAN Transmit Time Stamp Register; baseaddr + (0x3e~0x3f) ***/
typedef union {
  uint16 Word;
   /* Overlapped registers: */
  struct {
    /*** CANTXTSRH - MSCAN Transmit Time Stamp Register High; baseaddr + 0x3e ***/
    union {
      uint8 Byte;
      struct {
        uint8 TSR8        :1;                                       /* Time Stamp Bit 8 */
        uint8 TSR9        :1;                                       /* Time Stamp Bit 9 */
        uint8 TSR10       :1;                                       /* Time Stamp Bit 10 */
        uint8 TSR11       :1;                                       /* Time Stamp Bit 11 */
        uint8 TSR12       :1;                                       /* Time Stamp Bit 12 */
        uint8 TSR13       :1;                                       /* Time Stamp Bit 13 */
        uint8 TSR14       :1;                                       /* Time Stamp Bit 14 */
        uint8 TSR15       :1;                                       /* Time Stamp Bit 15 */
      } Bits;
    } CANTXTSRHSTR;
    

    /*** CANTXTSRL - MSCAN Transmit Time Stamp Register Low; baseaddr + 0x3f ***/
    union {
      uint8 Byte;
      struct {
        uint8 TSR0        :1;                                       /* Time Stamp Bit 0 */
        uint8 TSR1        :1;                                       /* Time Stamp Bit 1 */
        uint8 TSR2        :1;                                       /* Time Stamp Bit 2 */
        uint8 TSR3        :1;                                       /* Time Stamp Bit 3 */
        uint8 TSR4        :1;                                       /* Time Stamp Bit 4 */
        uint8 TSR5        :1;                                       /* Time Stamp Bit 5 */
        uint8 TSR6        :1;                                       /* Time Stamp Bit 6 */
        uint8 TSR7        :1;                                       /* Time Stamp Bit 7 */
      } Bits;
    } CANTXTSRLSTR;
  } Overlap_STR;

  struct {
    uint16 TSR0        :1;                                       /* Time Stamp Bit 0 */
    uint16 TSR1        :1;                                       /* Time Stamp Bit 1 */
    uint16 TSR2        :1;                                       /* Time Stamp Bit 2 */
    uint16 TSR3        :1;                                       /* Time Stamp Bit 3 */
    uint16 TSR4        :1;                                       /* Time Stamp Bit 4 */
    uint16 TSR5        :1;                                       /* Time Stamp Bit 5 */
    uint16 TSR6        :1;                                       /* Time Stamp Bit 6 */
    uint16 TSR7        :1;                                       /* Time Stamp Bit 7 */
    uint16 TSR8        :1;                                       /* Time Stamp Bit 8 */
    uint16 TSR9        :1;                                       /* Time Stamp Bit 9 */
    uint16 TSR10       :1;                                       /* Time Stamp Bit 10 */
    uint16 TSR11       :1;                                       /* Time Stamp Bit 11 */
    uint16 TSR12       :1;                                       /* Time Stamp Bit 12 */
    uint16 TSR13       :1;                                       /* Time Stamp Bit 13 */
    uint16 TSR14       :1;                                       /* Time Stamp Bit 14 */
    uint16 TSR15       :1;                                       /* Time Stamp Bit 15 */
  } Bits;
} CANTXTSRSTR;


/***********************************************
				CAN控制器寄存器汇总
 ***********************************************/
typedef   struct
{
	volatile CANCTL0STR		CANCTL0;/*MSCAN Control 0 Register,                 baseaddr + 0x00u*/
	volatile CANCTL1STR		CANCTL1;/*MSCAN Control 1 Register,                 baseaddr + 0x01u*/
	volatile CANBTR0STR		CANBTR0;/*MSCAN Bus Timing Register 0,              baseaddr + 0x02u*/	
	volatile CANBTR1STR		CANBTR1;/*MSCAN Bus Timing Register 1;              baseaddr + 0x03u*/	
	volatile CANRFLGSTR		CANRFLG;/*MSCAN Receiver Flag Register;             baseaddr + 0x04u*/
	volatile CANRIERSTR		CANRIER;/*MSCAN Receiver Interrupt Enable Register; baseaddr + 0x05u */
	volatile CANTFLGSTR		CANTFLG;/*MSCAN Transmitter Flag Register;          baseaddr + 0x06u*/
	volatile CANTIERSTR		CANTIER;/*MSCAN Transmitter Interrupt Enable Register,	baseaddr + 0x07u*/
	volatile CANTARQSTR		CANTARQ;/*MSCAN Transmitter Message Abort Request;  	baseaddr + 0x08u*/
	volatile CANTAAKSTR		CANTAAK;/*MSCAN Transmitter Message Abort Acknowledge; 	baseaddr + 0x09u*/
	volatile CANTBSELSTR	CANTBSEL;/*MSCAN Transmit Buffer Selection;  			baseaddr + 0x0Au*/
	volatile CANIDACSTR		CANIDAC; /*MSCAN Identifier Acceptance Control Register; baseaddr + 0x0Bu*/
	volatile uint8     		Reserved1;/*MSCAN Reserved Register,				  		baseaddr + 0x0Cu*/
	volatile CANMISCSTR		CANMISC; /*MSCAN Miscellaneous Register; 			  	baseaddr + 0x0Du*/
	volatile CANRXERRSTR	CANRXERR;/*MSCAN Receive Error Counter Register; 		baseaddr + 0x0Eu*/
	volatile CANTXERRSTR	CANTXERR;/*MSCAN Transmit Error Counter Register; 	  	baseaddr + 0x0Fu*/

	volatile CANIDAR0STR  	CANIDAR0;/*MSCAN Identifier Acceptance Register 0; 		baseaddr + 0x10u*/  
	volatile CANIDAR1STR  	CANIDAR1;/*MSCAN Identifier Acceptance Register 1; 		baseaddr + 0x11u*/
	volatile CANIDAR2STR	CANIDAR2;/*MSCAN Identifier Acceptance Register 2;       baseaddr + 0x12u*/
	volatile CANIDAR3STR	CANIDAR3;/*MSCAN Identifier Acceptance Register 3; 		baseaddr + 0x13u*/

	volatile CANIDMR0STR	CANIDMR0;/*MSCAN Identifier Mask Register 0; 			baseaddr + 0x14u*/
	volatile CANIDMR1STR	CANIDMR1;/*MSCAN Identifier Mask Register 1; 			baseaddr + 0x15u*/
	volatile CANIDMR2STR  	CANIDMR2;/*MSCAN Identifier Mask Register 2; 			baseaddr + 0x16u*/
	volatile CANIDMR3STR	CANIDMR3;/*MSCAN Identifier Mask Register 3; 			baseaddr + 0x17u*/

	volatile CANIDAR4STR	CANIDAR4;/*MSCAN Identifier Acceptance Register 4;        baseaddr + 0x18u*/
	volatile CANIDAR5STR	CANIDAR5;/*MSCAN Identifier Acceptance Register 5; 		baseaddr + 0x19u*/
	volatile CANIDAR6STR	CANIDAR6;/*MSCAN Identifier Acceptance Register 6; 		baseaddr + 0x1Au*/		
	volatile CANIDAR7STR	CANIDAR7;/*MSCAN Identifier Acceptance Register 7; 		baseaddr + 0x1Bu*/

	volatile CANIDMR4STR	CANIDMR4;/*MSCAN Identifier Mask Register 4; 			baseaddr + 0x1Cu*/
	volatile CANIDMR5STR	CANIDMR5;/*MSCAN Identifier Mask Register 5; 			baseaddr + 0x1Du*/
	volatile CANIDMR6STR	CANIDMR6;/*MSCAN Identifier Mask Register 6; 			baseaddr + 0x1Eu*/
	volatile CANIDMR7STR	CANIDMR7;/*MSCAN Identifier Mask Register 7;            baseaddr + 0x1Fu*/

	volatile CANRXIDR0STR	CANRXIDR0;/*MSCAN Receive Identifier Register 0; 		baseaddr + 0x20u*/
	volatile CANRXIDR1STR	CANRXIDR1;/*MSCAN Receive Identifier Register 1; 		baseaddr + 0x21u*/
	volatile CANRXIDR2STR	CANRXIDR2;/*MSCAN Receive Identifier Register 2; 	  	baseaddr + 0x22u*/
	volatile CANRXIDR3STR 	CANRXIDR3;/*MSCAN Receive Identifier Register 3; 	  	baseaddr + 0x23u*/

	volatile CANRXDSR0STR 	CANRXDSR0; /*MSCAN Receive Data Segment Register 0; 	baseaddr + 0x24u*/	
	volatile CANRXDSR1STR 	CANRXDSR1; /*MSCAN Receive Data Segment Register 1; 	baseaddr + 0x25u*/
	volatile CANRXDSR2STR 	CANRXDSR2; /*MSCAN Receive Data Segment Register 2; 	baseaddr + 0x26u*/
	volatile CANRXDSR3STR 	CANRXDSR3; /*MSCAN Receive Data Segment Register 3; 	baseaddr + 0x27u*/
	volatile CANRXDSR4STR 	CANRXDSR4; /*MSCAN Receive Data Segment Register 4; 	baseaddr + 0x28u*/
	volatile CANRXDSR5STR	CANRXDSR5; /*MSCAN Receive Data Segment Register 5; 	baseaddr + 0x29u*/
	volatile CANRXDSR6STR	CANRXDSR6; /*MSCAN Receive Data Segment Register 6; 	baseaddr + 0x2au*/
	volatile CANRXDSR7STR 	CANRXDSR7; /*MSCAN Receive Data Segment Register 7; 	baseaddr + 0x2b*/	

	volatile CANRXDLRSTR	CANRXDLR;	/*MSCAN Receive Data Length Register; 	 baseaddr + 0x2c*/

	volatile uint8     		Reserved2 ;	/*MSCAN Reserved Register,		         baseaddr + 0x2d*/	
	volatile CANRXTSRSTR	CANRXTSR;   /*MSCAN Receive Time Stamp Register; 	 baseaddr + (0x2e~0x2f)*/

	volatile CANTXIDR0STR 	CANTXIDR0; /*MSCAN Transmit Identifier Register 0;   baseaddr + 0x30*/
	volatile CANTXIDR1STR	CANTXIDR1; /*MSCAN Transmit Identifier Register 1;   baseaddr + 0x31*/
	volatile CANTXIDR2STR	CANTXIDR2; /*MSCAN Transmit Identifier Register 2;	 baseaddr + 0x32*/
	volatile CANTXIDR3STR	CANTXIDR3; /*MSCAN Transmit Identifier Register 3;	 baseaddr + 0x33*/	

	volatile CANTXDSR0STR	CANTXDSR0; /*MSCAN Transmit Data Segment Register 0; baseaddr + 0x34*/
	volatile CANTXDSR1STR	CANTXDSR1; /*MSCAN Transmit Data Segment Register 1; baseaddr + 0x35*/
	volatile CANTXDSR2STR 	CANTXDSR2; /*MSCAN Transmit Data Segment Register 2; baseaddr + 0x36*/
	volatile CANTXDSR3STR	CANTXDSR3; /*MSCAN Transmit Data Segment Register 3; baseaddr + 0x37*/	
	volatile CANTXDSR4STR	CANTXDSR4; /*MSCAN Transmit Data Segment Register 4; baseaddr + 0x38*/
	volatile CANTXDSR5STR	CANTXDSR5; /*MSCAN Transmit Data Segment Register 5; baseaddr + 0x39*/
	volatile CANTXDSR6STR	CANTXDSR6; /*MSCAN Transmit Data Segment Register 6; baseaddr + 0x3a*/
	volatile CANTXDSR7STR 	CANTXDSR7; /*MSCAN Transmit Data Segment Register 7; baseaddr + 0x3b*/
	volatile CANTXDLRSTR	CANTXDLR;  /*MSCAN Transmit Data Length Register;    baseaddr + 0x3c*/
	volatile CANTXTBPRSTR	CANTXTBPR; /*MSCAN Transmit Buffer Priority; 		 baseaddr + 0x3d*/
	volatile CANTXTSRSTR	CANTXTSR;  /*MSCAN Transmit Time Stamp Register; 	 baseaddr + (0x3e~0x3f)*/	
}Can_RegType;



#endif

