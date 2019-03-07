/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Compile.h
* ��������      : Ӳ��ƽ̨�������Ͷ���ͷ�ļ�(.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2015/10/27       chenms             �ع�
**------------------------------------------------------------------------------------------------*/
#ifndef  _PLATFORM_TYPE_H_
#define  _PLATFORM_TYPE_H_

/***********************************/
typedef unsigned char 			boolean;
typedef signed char				int8;
typedef unsigned char           uint8;
typedef signed short            int16;
typedef unsigned short          uint16;
typedef signed long             int32;
typedef unsigned long           uint32;
typedef long long               int64;
typedef unsigned long long      uint64;

#if 0
/***************************************
      add by chenms for 2oo3LCU
 **************************************/
typedef  union
{
    uint8  Byte;
  	struct 
  	{
    	uint8 Bit0	:1;
    	uint8 Bit1	:1;
    	uint8 Bit2	:1;
    	uint8 Bit3	:1;
    	uint8 Bit4	:1;
    	uint8 Bit5	:1;
    	uint8 Bit6	:1;
    	uint8 Bit7	:1;
  	} Bits;	
}ByteToBit;
#endif
/***********************************/

#endif







