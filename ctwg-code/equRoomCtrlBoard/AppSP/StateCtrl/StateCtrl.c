/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateCtrl.c
* ��������  : ״̬����ģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/28        sunj            	  New
**------------------------------------------------------------------------------------------------*/

#include "Bsw.h"


/***************************************************************************//*!
 * \brief   ״̬����ģ���̨��ѭ������
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void app_stateCtrl_MainFunction(void)
{
    boolean sta[9];

    Port_ReadPinValue(PORT_PIN_PT0,&sta[0]);/*�ɼ����� ����/ά�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT1,&sta[1]);/*�ɼ����� ����/Զ�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT2,&sta[2]);/*�ɼ����� ����/���� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT3,&sta[3]);/*�ɼ����� ������/�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT4,&sta[4]);/*�ɼ����� ɢ�ȿ�/�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT5,&sta[5]);/*�ɼ����� ���ȿ�/�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT6,&sta[6]);/*�ɼ����� ����/�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PT7,&sta[7]);/*�ɼ����� ����/�� ��״̬*/
    Port_ReadPinValue(PORT_PIN_PAD0,&sta[8]);/*�ɼ����� ģ����Դ��� ��״̬*/

    OSAL_ENTER_CRITICAL();
    /*����/Զ��*/
    if(sta[1]==TRUE)
    {
        ctrl_cmd_info.Byte0.bits.localOrRemote = CMD_LOCAL;
        
        /*��������ָʾ��*/
        Port_WritePinValue(PORT_PIN_PK0,PORT_PIN_LEVEL_HIGH);
    }
    else
    {
        ctrl_cmd_info.Byte0.bits.localOrRemote = CMD_REMOTE;
                
        /*Ϩ�𰴼�ָʾ��*/
        Port_WritePinValue(PORT_PIN_PK0,PORT_PIN_LEVEL_LOW);
    }

    if(ctrl_cmd_info.Byte0.bits.localOrRemote == CMD_LOCAL)
    {
        /*����/ά��ָ��*/
        if(sta[0]==TRUE)
        {
            ctrl_cmd_info.Byte0.bits.runOrService = CMD_RUN;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PA1,PORT_PIN_LEVEL_HIGH);
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.runOrService = CMD_SERVICE;
            
            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PA1,PORT_PIN_LEVEL_LOW);            
        }

        /*����/����ָ��*/
        if(sta[2]==FALSE)
        {
            ctrl_cmd_info.Byte0.bits.doorOpenOrClose = CMD_OPEN_DOOR;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK1,PORT_PIN_LEVEL_HIGH);
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.doorOpenOrClose = CMD_CLOSE_DOOR;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK1,PORT_PIN_LEVEL_LOW);
        }

        /*������/��ָ��*/
        if(sta[3]==FALSE)
        {
            ctrl_cmd_info.Byte0.bits.ccOpenOrClose = CMD_OPEN_CC;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK2,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte0.bits.ccOpenOrClose = CMD_CLOSE_CC;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK2,PORT_PIN_LEVEL_LOW);
        }

        /*ɢ�ȿ�/��ָ��*/
        if(sta[4]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.srOpenOrClose = CMD_OPEN_SR;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK3,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.srOpenOrClose = CMD_CLOSE_SR;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK3,PORT_PIN_LEVEL_LOW);
        }

        /*���ȿ�/��ָ�Ԥ����*/
        if(sta[5]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.heatOpenOrClose = CMD_OPEN_HEAT;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK4,PORT_PIN_LEVEL_HIGH);                  
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.heatOpenOrClose = CMD_CLOSE_HEAT;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK4,PORT_PIN_LEVEL_LOW);      
        }

        /*����/��ָ��*/
        if(sta[6]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.xzOpenOrClose = CMD_OPEN_XZ;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK5,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.xzOpenOrClose = CMD_CLOSE_XZ;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK5,PORT_PIN_LEVEL_LOW);            
        }

        /*����/��ָ�Ԥ����*/
        if(sta[7]==FALSE)
        {
            ctrl_cmd_info.Byte1.bits.mzOpenOrClose = CMD_OPEN_MZ;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK6,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte1.bits.mzOpenOrClose = CMD_CLOSE_MZ;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK6,PORT_PIN_LEVEL_LOW);            
        }

        /*ģ����Դ���ָ��*/
        if(sta[8]==FALSE)
        {
            ctrl_cmd_info.Byte2.bits.simuOpenOrClose = CMD_OPEN_SIMU_TEST;

            /*��������ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK7,PORT_PIN_LEVEL_HIGH);            
        }
        else
        {
            ctrl_cmd_info.Byte2.bits.simuOpenOrClose = CMD_CLOSE_SIMU_TEST;

            /*Ϩ�𰴼�ָʾ��*/
            Port_WritePinValue(PORT_PIN_PK7,PORT_PIN_LEVEL_LOW);            
        }        
    }


    OSAL_EXIT_CRITICAL();
}
