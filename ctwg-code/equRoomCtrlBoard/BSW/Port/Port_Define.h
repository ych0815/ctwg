/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Port_Define.h
* 功能描述      : Port模块引脚ID号+数据/方向寄存器地址定义(.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名         版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/4/25       chenms          NEW
**------------------------------------------------------------------------------------------------*/
#ifndef  _PORT_DEFINE_
#define  _PORT_DEFINE_

/*****************************************************
					Pin脚ID号定义 
 ****************************************************/
/*Port P*/
#define		PORT_PIN_PP0		(0u)
#define		PORT_PIN_PP1		(1u)
#define		PORT_PIN_PP2		(2u)
#define		PORT_PIN_PP3		(3u)
#define		PORT_PIN_PP4		(4u)
#define		PORT_PIN_PP5		(5u)	  
#define		PORT_PIN_PP6		(6u)
#define		PORT_PIN_PP7		(7u)

/*Port AD0*/
#define   	PORT_PIN_PAD0   	(8u)
#define   	PORT_PIN_PAD1   	(9u)
#define   	PORT_PIN_PAD2   	(10u)
#define   	PORT_PIN_PAD3   	(11u)
#define   	PORT_PIN_PAD4   	(12u)
#define   	PORT_PIN_PAD5   	(13u)
#define   	PORT_PIN_PAD6   	(14u)
#define   	PORT_PIN_PAD7   	(15u)
#define   	PORT_PIN_PAD8   	(16u)
#define   	PORT_PIN_PAD9   	(17u)
#define   	PORT_PIN_PAD10   	(18u)
#define   	PORT_PIN_PAD11   	(19u)
#define   	PORT_PIN_PAD12   	(20u)
#define   	PORT_PIN_PAD13   	(21u)
#define   	PORT_PIN_PAD14   	(22u)
#define   	PORT_PIN_PAD15   	(23u)

/*Port AD1*/                                                                   
#define   	PORT_PIN_PAD16   	(24u)
#define   	PORT_PIN_PAD17   	(25u)
#define   	PORT_PIN_PAD18   	(26u)
#define   	PORT_PIN_PAD19   	(27u)
#define   	PORT_PIN_PAD20   	(28u)
#define   	PORT_PIN_PAD21   	(29u)
#define   	PORT_PIN_PAD22   	(30u)
#define   	PORT_PIN_PAD23   	(31u)
#define   	PORT_PIN_PAD24   	(32u)
#define   	PORT_PIN_PAD25   	(33u)
#define   	PORT_PIN_PAD26   	(34u)
#define   	PORT_PIN_PAD27   	(35u)
#define   	PORT_PIN_PAD28   	(36u)
#define   	PORT_PIN_PAD29   	(37u)
#define   	PORT_PIN_PAD30   	(38u)
#define   	PORT_PIN_PAD31   	(39u)

/*Port S  SCI SPI  */
#define   	PORT_PIN_PS0   		(40u)
#define   	PORT_PIN_PS1   		(41u)
#define   	PORT_PIN_PS2   		(42u)
#define   	PORT_PIN_PS3   		(43u)
#define   	PORT_PIN_PS4   		(44u)
#define   	PORT_PIN_PS5   		(45u)
#define  	PORT_PIN_PS6   		(46u)
#define   	PORT_PIN_PS7   		(47u)

/*Port M  SCI */
#define   	PORT_PIN_PM0   		(48u)
#define   	PORT_PIN_PM1   		(49u)
#define   	PORT_PIN_PM2   		(50u)
#define   	PORT_PIN_PM3   		(51u)
#define   	PORT_PIN_PM4   		(52u)
#define   	PORT_PIN_PM5   		(53u)
#define   	PORT_PIN_PM6   		(54u)
#define   	PORT_PIN_PM7   		(55u)

/*Port H  SCI */
#define   	PORT_PIN_PH0   		(56u)
#define   	PORT_PIN_PH1   		(57u)
#define   	PORT_PIN_PH2   		(58u)
#define   	PORT_PIN_PH3   		(59u)
#define   	PORT_PIN_PH4   		(60u)
#define   	PORT_PIN_PH5   		(61u)
#define   	PORT_PIN_PH6   		(62u)
#define   	PORT_PIN_PH7   		(63u)

/*Port J  SCI */
#define   	PORT_PIN_PJ0   		(64u)
#define   	PORT_PIN_PJ1   		(65u)
#define   	PORT_PIN_PJ2   		(66u)
#define   	PORT_PIN_PJ3   		(67u)
#define   	PORT_PIN_PJ4   		(68u)
#define   	PORT_PIN_PJ5   		(69u)
#define   	PORT_PIN_PJ6   		(70u)
#define   	PORT_PIN_PJ7   		(71u)

/*Port L  SCI  */
#define   	PORT_PIN_PL0   		(72u)
#define   	PORT_PIN_PL1   		(73u)
#define   	PORT_PIN_PL2   		(74u)
#define   	PORT_PIN_PL3   		(75u)
#define   	PORT_PIN_PL4   		(76u)
#define   	PORT_PIN_PL5   		(77u)
#define   	PORT_PIN_PL6   		(78u)
#define   	PORT_PIN_PL7   		(79u)

/*Port F  SCI */
#define   	PORT_PIN_PF0   		(80u)
#define   	PORT_PIN_PF1   		(81u)
#define   	PORT_PIN_PF2   		(82u)
#define   	PORT_PIN_PF3   		(83u)
#define   	PORT_PIN_PF4   		(84u)
#define   	PORT_PIN_PF5   		(85u)
#define   	PORT_PIN_PF6   		(86u)
#define   	PORT_PIN_PF7   		(87u)

/*Port A */
#define   	PORT_PIN_PA0   		(88u)
#define   	PORT_PIN_PA1   		(89u)
#define   	PORT_PIN_PA2   		(90u)
#define   	PORT_PIN_PA3   		(91u)
#define   	PORT_PIN_PA4   		(92u)
#define   	PORT_PIN_PA5   		(93u)
#define   	PORT_PIN_PA6   		(94u)
#define   	PORT_PIN_PA7   		(95u)

/*Port B  */
#define   	PORT_PIN_PB0   		(96u)
#define   	PORT_PIN_PB1   		(97u)
#define   	PORT_PIN_PB2   		(98u)
#define   	PORT_PIN_PB3   		(99u)
#define   	PORT_PIN_PB4   		(100u)
#define   	PORT_PIN_PB5   		(101u)
#define   	PORT_PIN_PB6   		(102u)
#define   	PORT_PIN_PB7   		(103u)

/*Port C  */
#define   	PORT_PIN_PC0   		(104u)
#define   	PORT_PIN_PC1   		(105u)
#define   	PORT_PIN_PC2   		(106u)
#define   	PORT_PIN_PC3   		(107u)
#define   	PORT_PIN_PC4   		(108u)
#define   	PORT_PIN_PC5   		(109u)
#define   	PORT_PIN_PC6   		(110u)
#define   	PORT_PIN_PC7   		(111u)

/*Port D  */
#define   	PORT_PIN_PD0   		(112u)
#define   	PORT_PIN_PD1   		(113u)
#define   	PORT_PIN_PD2   		(114u)
#define   	PORT_PIN_PD3   		(115u)
#define   	PORT_PIN_PD4   		(116u)
#define   	PORT_PIN_PD5   		(117u)
#define   	PORT_PIN_PD6   		(118u)
#define   	PORT_PIN_PD7   		(119u)

/*Port E  */
#define   	PORT_PIN_PE0   		(120u)
#define   	PORT_PIN_PE1   		(121u)
#define   	PORT_PIN_PE2   		(122u)
#define   	PORT_PIN_PE3   		(123u)
#define   	PORT_PIN_PE4   		(124u)
#define   	PORT_PIN_PE5   		(125u)
#define   	PORT_PIN_PE6   		(126u)
#define   	PORT_PIN_PE7   		(127u)

/*Port K  */
#define   	PORT_PIN_PK0   		(128u)
#define   	PORT_PIN_PK1   		(129u)
#define   	PORT_PIN_PK2   		(130u)
#define   	PORT_PIN_PK3   		(131u)
#define   	PORT_PIN_PK4   		(132u)
#define   	PORT_PIN_PK5   		(133u)
#define   	PORT_PIN_PK6   		(134u)
#define   	PORT_PIN_PK7   		(135u)

/*Port T  */
#define   	PORT_PIN_PT0   		(136u)
#define   	PORT_PIN_PT1   		(137u)
#define   	PORT_PIN_PT2   		(138u)
#define   	PORT_PIN_PT3   		(139u)
#define   	PORT_PIN_PT4   		(140u)
#define   	PORT_PIN_PT5   		(141u)
#define   	PORT_PIN_PT6   		(142u)
#define   	PORT_PIN_PT7   		(143u)

/*Port R  */
#define   	PORT_PIN_PR0   		(144u)
#define   	PORT_PIN_PR1   		(145u)
#define   	PORT_PIN_PR2   		(146u)
#define   	PORT_PIN_PR3   		(147u)
#define   	PORT_PIN_PR4   		(148u)
#define   	PORT_PIN_PR5   		(149u)
#define   	PORT_PIN_PR6   		(150u)
#define   	PORT_PIN_PR7   		(151u)



/*****************************************************
		芯片端口数据、方向寄存器绝对地址定义
 ****************************************************/
/*DATA registers' address */
#define   	PORT_DATA_A       		(0x0000u)
#define   	PORT_DATA_B       		(0x0001u)
#define   	PORT_DATA_C       		(0x0004u)
#define   	PORT_DATA_D       		(0x0005u)
#define   	PORT_DATA_E       		(0x0008u)
#define   	PORT_DATA_K       		(0x0032u)
#define   	PORT_DATA_T       		(0x0240u)
#define   	PORT_DATA_S       		(0x0248u)
#define   	PORT_DATA_M       		(0x0250u)
#define   	PORT_DATA_P       		(0x0258u)
#define   	PORT_DATA_H       		(0x0260u)
#define   	PORT_DATA_J       		(0x0268u)
#define   	PORT_DATA_AD0_0   		(0x0270u)
#define   	PORT_DATA_AD0_1   		(0x0271u)
#define   	PORT_DATA_AD1_0   		(0x0278u)
#define   	PORT_DATA_AD1_1   		(0x0279u)
#define   	PORT_DATA_R       		(0x0368u)
#define   	PORT_DATA_L       		(0x0370u)
#define   	PORT_DATA_F       		(0x0378u)

/*direction registers' address */
#define   	PORT_DIRECTION_A        (0x0002u)
#define   	PORT_DIRECTION_B        (0x0003u)
#define   	PORT_DIRECTION_C        (0x0006u)
#define   	PORT_DIRECTION_D        (0x0007u)
#define   	PORT_DIRECTION_E        (0x0009u)
#define   	PORT_DIRECTION_K        (0x0033u)
#define   	PORT_DIRECTION_T        (0x0242u)
#define   	PORT_DIRECTION_S        (0x024Au)
#define   	PORT_DIRECTION_M        (0x0252u)
#define   	PORT_DIRECTION_P        (0x025Au)
#define   	PORT_DIRECTION_H        (0x0262u)
#define   	PORT_DIRECTION_J        (0x026Au)
#define   	PORT_DIRECTION_AD0_0   	(0x0272u)
#define   	PORT_DIRECTION_AD0_1   	(0x0273u)
#define   	PORT_DIRECTION_AD1_0   	(0x027Au)
#define   	PORT_DIRECTION_AD1_1   	(0x027Bu)
#define   	PORT_DIRECTION_R        (0x036Au)
#define   	PORT_DIRECTION_L        (0x0372u)
#define   	PORT_DIRECTION_F        (0x037Au)

/*AD0(PAD15~0),AD1(PAD31~16) read enable register */
#define   	PORT_ATD0DIENL      	(0x02CDu) /*AD0:IEN7~IEN0*/
#define   	PORT_ATD0DIENH      	(0x02CCu) /*AD0:IEN15~IEN8*/
#define   	PORT_ATD1DIENL      	(0x008Du) /*AD1:IEN7~IEN0*/ 
#define   	PORT_ATD1DIENH      	(0x008Cu) /*AD1:IEN15~IEN8*/

/*****************************************************
		芯片引脚端口类型定义
 ****************************************************/
#define   	PORT_A       		(0x00u)
#define   	PORT_B       		(0x01u)
#define   	PORT_C       		(0x02u)
#define   	PORT_D       		(0x03u)
#define   	PORT_E       		(0x04u)
#define   	PORT_K       		(0x05u)
#define   	PORT_T       		(0x06u)
#define   	PORT_S       		(0x07u)
#define   	PORT_M       		(0x08u)
#define   	PORT_P       		(0x09u)
#define   	PORT_H       		(0x0Au)
#define   	PORT_J       		(0x0Bu)
#define   	PORT_PAD    		(0x0Cu)
#define   	PORT_R       		(0x0Du)
#define   	PORT_L       		(0x0Eu)
#define   	PORT_F       		(0x0Fu)


#endif

