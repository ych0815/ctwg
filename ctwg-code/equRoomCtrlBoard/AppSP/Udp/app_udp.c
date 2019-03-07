#include "Bsw.h"

#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
uint8 ctrlHost_heartbeatCnt;/*控制主机生命信号*/
uint8 ctrlHost_SoftwareMainVer;/*控制主机软件主版本*/
uint8 ctrlHost_SoftwareMinorVer;/*控制主机软件次版本*/

#pragma DATA_SEG DEFAULT


/************************************************************
* 函数名称:UDP_MainFunction
* 函数描述:UDP模块后台主循环函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :该函数被周期任务调用
*************************************************************/
void UDP_MainFunction(void)
{
    Gateway_MainFunction(); 
}


/************************************************************
* 函数名称:UDP_Received
* 函数描述:UDP接收函数
* 输入参数:无
* 输出参数:无
* 输入/输出参数:无
* 可重入性:
* 返回值  :
* 备注	  :
*************************************************************/
void UDP_Received(uint8 *data,uint16 size)
{
    uint16 fraTitle,fraLen,infoType,i;
    uint8 checkSum = 0;
    FUN_STRU fun_stru_tmp;

    fraTitle = (uint16)(((uint16)data[0]<<8)|(uint16)data[1]);
    fraLen = (uint16)(((uint16)data[2]<<8)|(uint16)data[3]);
    infoType = data[4];

    if(fraTitle != 0xCCDD)
    {
        return;
    }
    
    for(i=0;i<(fraLen-1);i++)
        checkSum += data[i]; 

    if(checkSum != data[fraLen-1])
    {
        return;
    }

    switch (infoType)
    {
        case 0x01:  /*控制主机信息报文*/
        {
            ctrlHost_heartbeatCnt       = data[5];
            ctrlHost_SoftwareMainVer    = data[6];
            ctrlHost_SoftwareMinorVer   = data[7];
        }
            break;

        case 0x02:  /*控制主机命令报文*/
        {
            if(ctrl_cmd_info.Byte0.bits.localOrRemote = CMD_LOCAL)
            {
                fun_stru_tmp.Byte.val                       = data[5];
                ctrl_cmd_info.Byte0.bits.runOrService       = fun_stru_tmp.Byte.bits.bit7_6;
                ctrl_cmd_info.Byte0.bits.doorOpenOrClose    = fun_stru_tmp.Byte.bits.bit3_2;
                ctrl_cmd_info.Byte0.bits.ccOpenOrClose      = fun_stru_tmp.Byte.bits.bit1_0;

                ctrl_cmd_info.Byte1.val                     = data[6];
                ctrl_cmd_info.Byte2.val                     = data[7];                
            }

        }
            break;
    
        default:
            break;
    }


}