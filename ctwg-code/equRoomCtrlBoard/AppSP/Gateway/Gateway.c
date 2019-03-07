/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Gateway.c
* 功能描述  : 网关模块源文件(Gateway.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/22       sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "Bsw.h"
#include "Osal.h"

#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
BOARD_INFO equRoomCtrlBoardInfo,sigColBoardInfo,XZCtrlBoardInfo[3];/*5张板卡板卡信息*/
uint16 g_trainSpeed_info;
uint32 g_osTime_info;
COL_MODULE_STA col_module_sta_info[11];
CTRL_CMD ctrl_cmd_info;
FUN_STRU fun_stru1,fun_stru2;
int8 g_envTemp_info;
uint16 g_DC5VVol_info;
FUN_STRU gpkzx_sta_info_byte6,gpkzx_sta_info_byte25,gpkzx_sta_info_byte26,gpkzx_sta_info_byte27;
FUN_STRU XZCtrlBoardErrInfo[3];//线阵控制板故障信息

COL_MODULE_STA_ERR_INFO col_module_sta_err_info_val[11];
#pragma DATA_SEG DEFAULT


/************************************************************
* 函数名称:Gateway_Init
* 函数描述:GateWay模块初始化函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
void Gateway_Init(void)
{
    equRoomCtrlBoardInfo.word1.bytes.hardwareMainVer        = HARDWARE_MAIN_VERSION;
    equRoomCtrlBoardInfo.word1.bytes.hardwareMinorVer       = HARDWARE_MINOR_VERSION;

    equRoomCtrlBoardInfo.word2.bytes.softwareMainVer        = SOFTWARE_MAIN_VERSION;
    equRoomCtrlBoardInfo.word2.bytes.softwareMinorVer       = SOFTWARE_MINOR_VERSION;

    equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta         = STA_NORMAL;    /*正常*/
    equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta         = STA_NORMAL;    /*正常*/
}

/************************************************************
* 函数名称:GateWay_MainFunction
* 函数描述:GateWay模块后台主循环函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :该函数被周期任务调用
*************************************************************/
static void Gateway_Function(void)
{
    gpkzx_sta_info_byte6.Byte.bits.bit7_6 = fun_stru1.Byte.bits.bit7_6;/*车辆入/出库状态*/
    gpkzx_sta_info_byte6.Byte.bits.bit5_4 = fun_stru1.Byte.bits.bit5_4;/*线阵相机触发信号*/
    gpkzx_sta_info_byte6.Byte.bits.bit3_2 = fun_stru2.Byte.bits.bit7_6;/*轨旁控制箱散热风扇开启控制*/
    gpkzx_sta_info_byte6.Byte.bits.bit1_0 = ctrl_cmd_info.Byte0.bits.localOrRemote;/*本地/远程*/

    gpkzx_sta_info_byte25.Byte.bits.bit7_6 = equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta;/*设备间主控板CAN1故障状态*/
    gpkzx_sta_info_byte25.Byte.bits.bit5_4 = equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta;/*设备间主控板CAN2故障状态*/

    gpkzx_sta_info_byte25.Byte.bits.bit1_0 = sigColBoardInfo.Byte5.bits.boardCan1ErrSta;/*信号采集板CAN1故障状态*/

    gpkzx_sta_info_byte26.Byte.bits.bit7_6 = sigColBoardInfo.Byte5.bits.boardCan1ErrSta;/*信号采集板CAN2故障状态*/
    gpkzx_sta_info_byte26.Byte.bits.bit5_4 = fun_stru2.Byte.bits.bit5_4;/*温度传感器故障状态*/
    gpkzx_sta_info_byte26.Byte.bits.bit3_2 = fun_stru2.Byte.bits.bit3_2;/*DC12V电源故障状态*/
    gpkzx_sta_info_byte26.Byte.bits.bit1_0 = fun_stru2.Byte.bits.bit1_0;/*DC24V电脑故障状态*/

    gpkzx_sta_info_byte27.Byte.bits.bit7_6 = fun_stru1.Byte.bits.bit3_2;/*测速传感器1故障状态*/
    gpkzx_sta_info_byte27.Byte.bits.bit5_4 = fun_stru1.Byte.bits.bit1_0;/*测速传感器2故障状态*/
    gpkzx_sta_info_byte27.Byte.bits.bit3_2 = 0;/*预留*/
    gpkzx_sta_info_byte27.Byte.bits.bit1_0 = 0;/*预留*/
    
    XZCtrlBoardErrInfo[0].Byte.bits.bit5_4 = XZCtrlBoardInfo[0].Byte5.bits.boardCan1ErrSta;/*线阵控制板1CAN1故障*/
    XZCtrlBoardErrInfo[0].Byte.bits.bit3_2 = XZCtrlBoardInfo[0].Byte5.bits.boardCan2ErrSta;/*线阵控制板1CAN2故障*/
    XZCtrlBoardErrInfo[0].Byte.bits.bit1_0 = 0;/*预留*/

    XZCtrlBoardErrInfo[1].Byte.bits.bit5_4 = XZCtrlBoardInfo[1].Byte5.bits.boardCan1ErrSta;/*线阵控制板1CAN1故障*/
    XZCtrlBoardErrInfo[1].Byte.bits.bit3_2 = XZCtrlBoardInfo[1].Byte5.bits.boardCan2ErrSta;/*线阵控制板1CAN2故障*/
    XZCtrlBoardErrInfo[1].Byte.bits.bit1_0 = 0;/*预留*/

    XZCtrlBoardErrInfo[2].Byte.bits.bit5_4 = XZCtrlBoardInfo[2].Byte5.bits.boardCan1ErrSta;/*线阵控制板1CAN1故障*/
    XZCtrlBoardErrInfo[2].Byte.bits.bit3_2 = XZCtrlBoardInfo[2].Byte5.bits.boardCan2ErrSta;/*线阵控制板1CAN2故障*/
    XZCtrlBoardErrInfo[2].Byte.bits.bit1_0 = 0;/*预留*/

}

/************************************************************
* 函数名称:Gateway_MainFunction
* 函数描述:网关模块后台主循环函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :该函数被周期任务调用
*************************************************************/
void Gateway_MainFunction(void)
{
    static uint32 oldTicks = 0u;
    uint32 elapseticks = 0u;
    uint8 buffer[191];
    uint16 len = 191;
    uint8 i=0;
    static uint8 tmpCnt = 0; 

    Gateway_Function();/*对部分变量进行赋值*/

    OSAL_ENTER_CRITICAL();
    elapseticks = (uint32)(OSALTimeGet() - oldTicks);
    OSAL_EXIT_CRITICAL();

    /*周期为500时钟节拍 执行操作函数*/
    if(elapseticks >= 500)
    {
        OSAL_ENTER_CRITICAL();
		oldTicks = 	OSALTimeGet();
		OSAL_EXIT_CRITICAL();

        buffer[0]  = 0xAA;
        buffer[1]  = 0xBB;
        buffer[2]  = BYTE_HIGH_UINT16(len);
        buffer[3]  = BYTE_LOW_UINT16(len);
        buffer[4]  = 0x01;
        buffer[5]  = tmpCnt++;
        buffer[6]  = gpkzx_sta_info_byte6.Byte.val;
        buffer[7]  = BYTE_HIGH_UINT16(g_trainSpeed_info);
        buffer[8]  = BYTE_LOW_UINT16(g_trainSpeed_info);
        buffer[9]  = BYTE_HIGH_UINT32(g_osTime_info);
        buffer[10] = BYTE_MIN_HIGH_UINT32(g_osTime_info);
        buffer[11] = BYTE_MIN_LOW_UINT32(g_osTime_info);
        buffer[12] = BYTE_LOW_UINT32(g_osTime_info);
        buffer[13] = g_envTemp_info;
        buffer[14] = BYTE_HIGH_UINT16(g_DC5VVol_info);
        buffer[15] = BYTE_LOW_UINT16(g_DC5VVol_info);
        buffer[16] = equRoomCtrlBoardInfo.word2.bytes.softwareMainVer;
        buffer[17] = equRoomCtrlBoardInfo.word2.bytes.softwareMinorVer;
        buffer[18] = equRoomCtrlBoardInfo.word1.bytes.hardwareMainVer;
        buffer[19] = equRoomCtrlBoardInfo.word1.bytes.hardwareMinorVer;
        buffer[20] = sigColBoardInfo.hearBeatCnt;
        buffer[21] = sigColBoardInfo.word2.bytes.softwareMainVer;
        buffer[22] = sigColBoardInfo.word2.bytes.softwareMinorVer;
        buffer[23] = sigColBoardInfo.word1.bytes.hardwareMainVer;
        buffer[24] = sigColBoardInfo.word1.bytes.hardwareMinorVer;
        buffer[25] = gpkzx_sta_info_byte25.Byte.val;
        buffer[26] = gpkzx_sta_info_byte26.Byte.val;
        buffer[27] = gpkzx_sta_info_byte27.Byte.val;
        buffer[28] = 3;/*采集模块控制板数量*/
        buffer[29] = XZCtrlBoardInfo[0].hearBeatCnt;
        buffer[30] = XZCtrlBoardInfo[0].word2.bytes.softwareMainVer;
        buffer[31] = XZCtrlBoardInfo[0].word2.bytes.softwareMinorVer;
        buffer[32] = XZCtrlBoardInfo[0].word1.bytes.hardwareMainVer;
        buffer[33] = XZCtrlBoardInfo[0].word1.bytes.hardwareMinorVer;
        buffer[34] = XZCtrlBoardErrInfo[0].Byte.val;
        buffer[35] = XZCtrlBoardInfo[1].hearBeatCnt;
        buffer[36] = XZCtrlBoardInfo[1].word2.bytes.softwareMainVer;
        buffer[37] = XZCtrlBoardInfo[1].word2.bytes.softwareMinorVer;
        buffer[38] = XZCtrlBoardInfo[1].word1.bytes.hardwareMainVer;
        buffer[39] = XZCtrlBoardInfo[1].word1.bytes.hardwareMinorVer;
        buffer[40] = XZCtrlBoardErrInfo[1].Byte.val;
        buffer[41] = XZCtrlBoardInfo[2].hearBeatCnt;
        buffer[42] = XZCtrlBoardInfo[2].word2.bytes.softwareMainVer;
        buffer[43] = XZCtrlBoardInfo[2].word2.bytes.softwareMinorVer;
        buffer[44] = XZCtrlBoardInfo[2].word1.bytes.hardwareMainVer;
        buffer[45] = XZCtrlBoardInfo[2].word1.bytes.hardwareMinorVer;
        buffer[46] = XZCtrlBoardErrInfo[2].Byte.val;
        buffer[47] = 11;/*采集模块数量*/

        for(i=0;i<11;i++)
        {
            buffer[48+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte0.val;
            buffer[49+13*i] = col_module_sta_err_info_val[i]._col_module_sta.moduleNum;
            buffer[50+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte2.val;
            buffer[51+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte3.val;
            buffer[52+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte4.val;
            buffer[53+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte5.val;
            buffer[54+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte6.val;
            buffer[55+13*i] = col_module_sta_err_info_val[i]._col_module_sta.Byte7.val;
            buffer[56+13*i] = col_module_sta_err_info_val[i].Byte8.val;
            buffer[57+13*i] = col_module_sta_err_info_val[i].Byte9.val;
            buffer[58+13*i] = col_module_sta_err_info_val[i].Byte10.val;
            buffer[59+13*i] = col_module_sta_err_info_val[i].Byte11.val;
            buffer[60+13*i] = col_module_sta_err_info_val[i].Byte12.val;
        }

        for(i=0;i<190;i++)
            buffer[190] += buffer[i];

        UDP_Send(buffer,len,0xC0A8001E,5000);  //向192.168.0.30 发送UDP数据报文
    }
}