/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : MeaVel.h
* 功能描述  : 测速模块管理头文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/7        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef _MEAVEL_H
#define _MEAVEL_H

#include "drv_ect.h"
#include "Osal.h"

/**\brief 测速磁钢之间的距离 */
#define     MEAVEL_LENGTH           250u


/**\brief 单个测速模块结构体 */
typedef struct
{
    boolean errState;   /**\brief 模块故障状态：TRUE为故障  FALSE为正常 */
    boolean flag[2];    /**\brief True表示进入中断，false表示未进入中断 flag[0]表示第一路标志位 flag[1]表示第二路标志位 */
    INT16U timeCnt[2];  /**\brief 计数值 */
    boolean timeOut;    /**\brief 超时标志 */
    INT8U errorCnt;     /**\brief 测速模块错误计数器 */
    INT32U curTicks;    /**\brief 当前节拍数 */
    INT16U trainVel;    /**\brief 车速值 单位：km/h */
}T_MeaVel;

/**\brief 车速信息结构体 */
typedef struct
{
    boolean IsFinish;   /*\brief 车速信息是否获取标志位 */ 
    INT16U value;       /*\brief 车速值 */
}T_TrainVel;


/************************
 * 全局变量外部声明
 * ************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern T_MeaVel g_meavel_info[2];
extern T_TrainVel  g_trainVeal_info;	  /*车速信息，由2个测速模块仲裁出的，单位:km/h*/

#pragma DATA_SEG DEFAULT


/************************
 * 函数外部声明
 * ************************/
extern void MeaVel_Init(void);
extern void MeaVel_ReInit(void);
extern void MeaVel_MainFunction(void);
extern void trainVelMeaMd1_STA_INT(void);
extern void trainVelMeaMd1_END_INT(void);
extern void trainVelMeaMd2_STA_INT(void);
extern void trainVelMeaMd2_END_INT(void);



#endif
