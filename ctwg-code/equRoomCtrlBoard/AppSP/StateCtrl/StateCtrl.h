/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : StateCtrl.h
* 功能描述  : 状态控制模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/28        sunj            	  New
**------------------------------------------------------------------------------------------------*/


#define         CMD_RUN                     1       /*运行指令*/
#define         CMD_SERVICE                 2       /*维护指令*/

#define         CMD_LOCAL                   1       /*本地指令*/
#define         CMD_REMOTE                  2       /*远程指令*/

#define         CMD_OPEN_DOOR               1       /*开门指令*/
#define         CMD_CLOSE_DOOR              2       /*关门指令*/

#define         CMD_OPEN_CC                 1       /*打开除尘风扇指令*/
#define         CMD_CLOSE_CC                2       /*关闭除尘风扇指令*/

#define         CMD_OPEN_SR                 1       /*打开散热风扇指令*/
#define         CMD_CLOSE_SR                2       /*关闭散热风扇指令*/

#define         CMD_OPEN_HEAT               1       /*加热开指令*/
#define         CMD_CLOSE_HEAT              2       /*加热关指令*/

#define         CMD_OPEN_XZ                 1       /*线阵触发开指令*/
#define         CMD_CLOSE_XZ                2       /*线阵触发关指令*/

#define         CMD_OPEN_MZ                 1       /*面阵触发开指令*/
#define         CMD_CLOSE_MZ                2       /*面阵触发关指令*/

#define         CMD_OPEN_SIMU_TEST          1       /*模拟测试触发开指令*/
#define         CMD_CLOSE_SIMU_TEST         2       /*模拟测试触发关指令*/



/********************************************
 * 函数声明
 *******************************************/
extern void app_stateCtrl_MainFunction(void);