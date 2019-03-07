#include "Bsw.h"

#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
uint8 ctrlHost_heartbeatCnt;/*�������������ź�*/
uint8 ctrlHost_SoftwareMainVer;/*��������������汾*/
uint8 ctrlHost_SoftwareMinorVer;/*������������ΰ汾*/

#pragma DATA_SEG DEFAULT


/************************************************************
* ��������:UDP_MainFunction
* ��������:UDPģ���̨��ѭ������
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ����ֵ  :
* ��ע	  :�ú����������������
*************************************************************/
void UDP_MainFunction(void)
{
    Gateway_MainFunction(); 
}


/************************************************************
* ��������:UDP_Received
* ��������:UDP���պ���
* �������:��
* �������:��
* ����/�������:��
* ��������:
* ����ֵ  :
* ��ע	  :
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
        case 0x01:  /*����������Ϣ����*/
        {
            ctrlHost_heartbeatCnt       = data[5];
            ctrlHost_SoftwareMainVer    = data[6];
            ctrlHost_SoftwareMinorVer   = data[7];
        }
            break;

        case 0x02:  /*�������������*/
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