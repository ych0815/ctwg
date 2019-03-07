/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : StateShow.h
* 功能描述  : 状态显示模块管理头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef STATESHOW_H
#define STATESHOW_H

/**********************************
 * 头文件
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"

#define         RUN_LED         PORT_PIN_PA4
#define         CAN1_LED        PORT_PIN_PA3
#define         CAN2_LED        PORT_PIN_PA2


/**********************************
 * 全局变量外部声明
 * ********************************/


/**********************************
 * 函数外部声明
 * ********************************/
extern void setRunLedState(void);
extern void setCAN1LedState(BOOLEAN errSta);
extern void setCAN2LedState(BOOLEAN errSta);




#endif
