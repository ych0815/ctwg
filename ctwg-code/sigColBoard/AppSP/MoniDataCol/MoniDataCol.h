/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : MoniDataCol.h
* 功能描述  : 监测数据采集与散热控制模块管理头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef MONIDATACOL_H
#define MONIDATACOL_H

/**********************************
 * 头文件
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"

/**********************************
 * 宏定义
 * ********************************/
#define         HIGH_TEMP_LIMIT         50u         /**brief 散热控制临界温度值 */
#define         PIN_SR_FAN1             PORT_PIN_PC5 
#define         PIN_SR_FAN2             PORT_PIN_PC6 

/**********************************
 * 全局变量外部声明
 * ********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern BOOLEAN g_fanOpenSta_info;	  /*轨旁控制箱散热风扇开启控制*/
//extern BOOLEAN g_DC5VErrSta_info;	  /*DC5V电源故障状态*/
extern BOOLEAN g_DC12VErrSta_info;	  /*DC12V电源故障状态*/
extern BOOLEAN g_DC24VErrSta_info;	  /*DC24V电源故障状态*/
extern BOOLEAN g_tempErrSta_info;     /*温度传感器故障状态*/
extern INT8S   g_temp_info;		  	  /*环境温度信息*/
extern uint16  g_DC5VVol_info;               /*DC5V电源电压(单位:0.01V)*/

#pragma DATA_SEG DEFAULT

/**********************************
 * 函数外部声明
 * ********************************/
void MoniDataCol_Init(void);
INT8S getDCPowerErrState(BOOLEAN * __far DC12V_state,BOOLEAN * __far DC24V_state);
INT8S getFanOpenState(INT8S temp,BOOLEAN * __far state);
INT8S setFanOpenOrClose(BOOLEAN state);

#endif
