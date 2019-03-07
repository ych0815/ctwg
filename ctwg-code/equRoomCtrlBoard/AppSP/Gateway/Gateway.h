/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Gateway.h
* ��������  : ����ģ��ͷ�ļ�(Gateway.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/22       sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef GATEWAY_H
#define GATEWAY_H

#include "Bsw.h"

#define 	BYTE_HIGH_UINT16(dwTemp)		(*(unsigned char *)(&dwTemp))
#define 	BYTE_LOW_UINT16(dwTemp)		    (*((unsigned char *)(&dwTemp)+1))

#define 	BYTE_HIGH_UINT32(dwTemp)		(*(unsigned char *)(&dwTemp))
#define 	BYTE_MIN_HIGH_UINT32(dwTemp)	(*((unsigned char *)(&dwTemp)+1))
#define 	BYTE_MIN_LOW_UINT32(dwTemp)		(*((unsigned char *)(&dwTemp)+2))
#define 	BYTE_LOW_UINT32(dwTemp)		    (*((unsigned char *)(&dwTemp)+3))


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern BOARD_INFO equRoomCtrlBoardInfo,sigColBoardInfo,XZCtrlBoardInfo[3];
extern uint16 g_trainSpeed_info;
extern uint32 g_osTime_info;
extern COL_MODULE_STA col_module_sta_info[11];
extern CTRL_CMD ctrl_cmd_info;
extern FUN_STRU fun_stru1,fun_stru2;
extern int8 g_envTemp_info;
extern uint16 g_DC5VVol_info;
extern FUN_STRU gpkzx_sta_info_byte6,gpkzx_sta_info_byte25,gpkzx_sta_info_byte26,gpkzx_sta_info_byte27;
extern FUN_STRU XZCtrlBoardErrInfo[3];//������ư������Ϣ

#pragma DATA_SEG DEFAULT

/***************************************************
 * ����˵��
 * ************************************************/
extern void Gateway_Init(void);
extern void Gateway_MainFunction(void);

#endif
