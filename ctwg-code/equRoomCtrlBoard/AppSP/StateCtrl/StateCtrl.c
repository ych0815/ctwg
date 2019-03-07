/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : StateCtrl.c
* 功能描述  : 状态控制模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/28        sunj            	  New
**------------------------------------------------------------------------------------------------*/

#include "Bsw.h"


/***************************************************************************//*!
 * \brief   状态控制模块后台主循环函数
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void app_stateCtrl_MainFunction(void)
{
    boolean sta[9];

    Port_ReadPinValue(PORT_PIN_PT0,&sta[0]);/*采集按键 运行/维护 的状态*/
    Port_ReadPinValue(PORT_PIN_PT1,&sta[1]);/*采集按键 本地/远程 的状态*/
    Port_ReadPinValue(PORT_PIN_PT2,&sta[2]);/*采集按键 开门/关门 的状态*/
    Port_ReadPinValue(PORT_PIN_PT3,&sta[3]);/*采集按键 除尘开/关 的状态*/
    Port_ReadPinValue(PORT_PIN_PT4,&sta[4]);/*采集按键 散热开/关 的状态*/
    Port_ReadPinValue(PORT_PIN_PT5,&sta[5]);/*采集按键 加热开/关 的状态*/
    Port_ReadPinValue(PORT_PIN_PT6,&sta[6]);/*采集按键 线阵开/关 的状态*/
    Port_ReadPinValue(PORT_PIN_PT7,&sta[7]);/*采集按键 面阵开/关 的状态*/
    Port_ReadPinValue(PORT_PIN_PAD0,&sta[8]);/*采集按键 模拟测试触发 的状态*/

    OSAL_ENTER_CRITICAL();
    /*本地/远程*/
    if(sta[1]==TRUE)
    {
        ctrl_cmd_info.Byte0.bits.localOrRemote = CMD_LOCAL;
        
        /*点亮按键指示灯*/
        Port_WritePinValue(PORT_PIN_PK0,PORT_PIN_LEVEL_HIGH);
    }
    else
    {
        ctrl_cmd_info.Byte0.bits.localOrRemote = CMD_REMOTE;
                
        /*熄灭按键指示灯*/
        Port_WritePinValue(PORT_PIN_PK0,PORT_PIN_LEVEL_LOW);
    }

    if(ctrl_cmd_info.Byte0.bits.localOrRemote == CMD_LOCAL)
    {
        /*运行/维护指令*/
        if(sta[0]==TRUE)
        {
            ctrl_cmd_info.Byte0.bits.runOrService = CMD_RUN;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PA1,PORT_PIN_LEVEL_HIGH);
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.runOrService = CMD_SERVICE;
            
            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PA1,PORT_PIN_LEVEL_LOW);            
        }

        /*开门/关门指令*/
        if(sta[2]==FALSE)
        {
            ctrl_cmd_info.Byte0.bits.doorOpenOrClose = CMD_OPEN_DOOR;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK1,PORT_PIN_LEVEL_HIGH);
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.doorOpenOrClose = CMD_CLOSE_DOOR;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK1,PORT_PIN_LEVEL_LOW);
        }

        /*除尘开/关指令*/
        if(sta[3]==FALSE)
        {
            ctrl_cmd_info.Byte0.bits.ccOpenOrClose = CMD_OPEN_CC;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK2,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.ccOpenOrClose = CMD_CLOSE_CC;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK2,PORT_PIN_LEVEL_LOW);
        }

        /*散热开/关指令*/
        if(sta[4]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.srOpenOrClose = CMD_OPEN_SR;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK3,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.srOpenOrClose = CMD_CLOSE_SR;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK3,PORT_PIN_LEVEL_LOW);
        }

        /*加热开/关指令（预留）*/
        if(sta[5]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.heatOpenOrClose = CMD_OPEN_HEAT;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK4,PORT_PIN_LEVEL_HIGH);                  
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.heatOpenOrClose = CMD_CLOSE_HEAT;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK4,PORT_PIN_LEVEL_LOW);      
        }

        /*线阵开/关指令*/
        if(sta[6]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.xzOpenOrClose = CMD_OPEN_XZ;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK5,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.xzOpenOrClose = CMD_CLOSE_XZ;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK5,PORT_PIN_LEVEL_LOW);            
        }

        /*面阵开/关指令（预留）*/
        if(sta[7]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.mzOpenOrClose = CMD_OPEN_MZ;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK6,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.mzOpenOrClose = CMD_CLOSE_MZ;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK6,PORT_PIN_LEVEL_LOW);            
        }

        /*模拟测试触发指令*/
        if(sta[8]==FALSE)
        {
            ctrl_cmd_info.Byte2.bits.simuOpenOrClose = CMD_OPEN_SIMU_TEST;

            /*点亮按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK7,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte2.bits.simuOpenOrClose = CMD_CLOSE_SIMU_TEST;

            /*熄灭按键指示灯*/
            Port_WritePinValue(PORT_PIN_PK7,PORT_PIN_LEVEL_LOW);            
        }        
    }


    OSAL_EXIT_CRITICAL();
}
