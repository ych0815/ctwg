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


/**********************************
 * 宏定义
 * ********************************/
#define     STA_NORMAL                          1       /*状态正常*/
#define     STA_ERROR                           2       /*状态故障*/

#define     STA_EXIST_WATER                     1       /*有水*/
#define     STA_NOT_EXIST_WATER                 2       /*无水*/

#define     STA_CLOSE_DOOR                      1       /*关门*/
#define     STA_OPEN_DOOR                       2       /*开门*/
#define     STA_DOOR_ERROR                      3       /*门故障*/

#define     STA_NOT_EXIST                       0       /*无效情况*/
#define     STA_ANYONE_BOX_OPEN_DOOR            1       /*任一箱体开门*/
#define     STA_ALL_BOX_CLOSE_DOOR              2       /*所有箱体关门*/
#define     STA_ANYONE_BOX_ERROR                3       /*任一箱体故障*/

#define     STA_FAN_NORMAL                      0       /*风扇正常*/
#define     STA_FAN_ERROR                       1       /*风扇故障*/

#define     STA_FAN_CLOSE                       0       /*风扇关闭*/
#define     STA_FAN_OPEN                        1       /*风扇开启*/

#define     STA_ANYONE_FAN_OPEN                 1       /*任一风扇开启*/
#define     STA_ALL_FAN_CLOSE                   2       /*所有风扇关闭*/
#define     STA_ANYONE_FAN_ERROR                3       /*任一箱体故障*/

/**********************************
 * 数据结构定义
 * ********************************/
/**\brief 状态指示灯枚举类型 */
typedef enum
{
    APP_LED_STATE_OFF       = 0,    /* 指示灯常灭 */
    APP_LED_STATE_LIGHT     = 1,    /* 指示灯常亮 */
    APP_LED_STATE_FLASH     = 2     /* 指示灯闪烁 */
}APP_LED_STATE;

/**\brief 状态指示模块结构体类型*/
typedef struct
{
    /**\brief 引脚号 */
    Port_PinType PortNumberOfPortPins;

    /**\brief 状态指示灯状态 */
    APP_LED_STATE ledSta;

    /**\brief 状态指示灯处于闪烁状态时存储上次的电平值 */
    Port_PinLevelValueType lastPinLevelVal;
}APP_STATE_SHOW_STRU;


/**********************************
 * 全局变量外部声明
 * ********************************/
extern APP_STATE_SHOW_STRU appStaShowStru[30];


/**********************************
 * 函数外部声明
 * ********************************/
extern void app_stateShow_Init(void);
extern void app_set_led_state(APP_STATE_SHOW_STRU *appStaShowStruct);
extern void app_stateShow_MainFunction(void);

#endif
