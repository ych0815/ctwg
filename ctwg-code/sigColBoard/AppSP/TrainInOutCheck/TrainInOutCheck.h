/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : TrainInOutCheck.h
* 功能描述  : 车辆入/出检测模块管理头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef TRAININOUTCHECK_H
#define TRAININOUTCHECK_H

/**********************************
 * 头文件
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"


#define         PIN_TRAIN_IN1           PORT_PIN_PD7
#define         PIN_TRAIN_IN2           PORT_PIN_PC0
#define         PIN_TRAIN_OUT1          PORT_PIN_PC1
#define         PIN_TRAIN_OUT2          PORT_PIN_PC2


/**********************************
 * 全局变量外部声明
 * ********************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern BOOLEAN g_trainInOut_info;    /*车辆入/出库信息，TRUE表示车辆入库 FALSE表示车辆出库*/

#pragma DATA_SEG DEFAULT

/**********************************
 * 函数外部声明
 * ********************************/
void TrainInOutCheck_Init(void);
void trainInOutCheck (BOOLEAN *state);


#endif
