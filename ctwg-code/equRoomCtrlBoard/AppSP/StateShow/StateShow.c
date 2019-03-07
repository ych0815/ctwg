/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateShow.c
* ��������  : ״̬��ʾģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/

#include "Bsw.h"
#include "Osal.h"

APP_STATE_SHOW_STRU appStaShowStru[30] = 
{
	/*״ָ̬ʾ�� LED1~5*/
	{PORT_PIN_PAD1 , APP_LED_STATE_FLASH , PORT_PIN_LEVEL_LOW},/*���е�*/
	{PORT_PIN_PAD2 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*����ģʽ*/
	{PORT_PIN_PAD3 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC24V��Դ*/
	{PORT_PIN_PAD4 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC12V��Դ*/
	{PORT_PIN_PAD5 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC5V��Դ*/

	/*״ָ̬ʾ�� LED6~10*/
	{PORT_PIN_PAD6 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CAN1ͨѶ*/
	{PORT_PIN_PAD7 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CAN2ͨѶ*/
	{PORT_PIN_PAD8 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*��̫��ͨѶ*/
	{PORT_PIN_PAD9 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*���/����*/
	{PORT_PIN_PAD10, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*ˮλ����*/
	
	/*״ָ̬ʾ�� LED11~15*/
	{PORT_PIN_PAD11, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*���󴥷�*/
	{PORT_PIN_PAD12, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*���󴥷�*/
	{PORT_PIN_PAD13, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*���俪/����*/
	{PORT_PIN_PAD14, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*ZXB���俪/����*/
	{PORT_PIN_PAD15, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CT���俪/����*/

	/*״ָ̬ʾ�� LED16~20*/
	{PORT_PIN_PAD16, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*բ�߿�/����*/
	{PORT_PIN_PP0  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*բƬ��/����*/
	{PORT_PIN_PP1  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*�����俪/����*/
	{PORT_PIN_PP2  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*������/��*/
	{PORT_PIN_PP3  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*ɢ�ȿ�/��*/
	
	/*״ָ̬ʾ�� LED21~25*/
	{PORT_PIN_PP4  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*���ȿ�/��*/
	{PORT_PIN_PP5  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*�����źŰ�*/
	{PORT_PIN_PP6  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*������ư�*/
	{PORT_PIN_PP7  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*������ư�*/
	{PORT_PIN_PH2  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*�������ư�*/
	
	/*״ָ̬ʾ�� LED26~30*/
	{PORT_PIN_PH3  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*������ư�1*/
	{PORT_PIN_PH4  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*������ư�2*/
	{PORT_PIN_PH5  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*Ԥ��*/
	{PORT_PIN_PH6  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*Ԥ��*/
	{PORT_PIN_PH7  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW} /*Ԥ��*/
};

/***************************************************************************//*!
 * \brief   ״̬��ʾģ���ʼ��
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void app_stateShow_Init(void)
{

}


/***************************************************************************//*!
 * \brief   ����״ָ̬ʾ��״̬
 *
 * \param   APP_STATE_SHOW_STRU ״ָ̬ʾģ��ṹ����
 *
 * \return  ��
 *
 *****************************************************************************/
void app_set_led_state(APP_STATE_SHOW_STRU *appStaShowStruct)
{
    uint8 portPin,ledSta;
    
    portPin = appStaShowStruct->PortNumberOfPortPins;/*led���ź�*/
    ledSta  = appStaShowStruct->ledSta; /*led״̬*/        

    switch (ledSta)
    {
        case APP_LED_STATE_OFF:     /* ���� */
            Port_WritePinValue(portPin,PORT_PIN_LEVEL_HIGH);
            break;

        case APP_LED_STATE_LIGHT:   /* ���� */
            Port_WritePinValue(portPin,PORT_PIN_LEVEL_LOW);
            break;

        case APP_LED_STATE_FLASH:   /* ��˸ */  
            appStaShowStruct->lastPinLevelVal = !appStaShowStruct->lastPinLevelVal;
            Port_WritePinValue(portPin,appStaShowStruct->lastPinLevelVal);
            break;
    
        default:
            break;
    }
}

/***************************************************************************//*!
 * \brief   ״̬��ʾģ���̨��ѭ��
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void app_stateShow_MainFunction(void)
{
	static uint32 oldTicks = 0u;
	static uint8 board_last_heartbeatCnt[4],ctrlHost_last_heartbeatCnt;
    uint32 elapseticks = 0u;
    uint8 i = 0;/*�ۼӱ���*/
	uint16 tmp[30];/*���ڴ洢30��ָʾ�ƵĶ�Ӧ�ĸ������*/

	OSAL_ENTER_CRITICAL();
	tmp[1] = ctrl_cmd_info.Byte0.bits.runOrService;/*2 ����ģʽ*/
	tmp[2] = fun_stru2.Byte.bits.bit1_0;/*3 DC24V��Դ*/
	tmp[3] = fun_stru2.Byte.bits.bit3_2;/*4 DC12V��Դ*/
	tmp[4] = g_DC5VVol_info;/*5 DC5V��Դ*/
	tmp[5] = equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta;/*6 CAN1ͨѶ*/
	tmp[6] = equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta;/*7 CAN2ͨѶ*/
	
	tmp[8] = fun_stru1.Byte.bits.bit7_6;/*9 ���/����*/
	/*10 ˮλ����*/
	if((col_module_sta_info[0].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[1].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[2].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[3].Byte5.bits.waterAlarm == 1))
	{
		tmp[9] = STA_EXIST_WATER;/*��ˮ*/
	}
	else
	{
		tmp[9] = STA_NOT_EXIST_WATER;/*��ˮ*/
	}
	tmp[10] = fun_stru1.Byte.bits.bit5_4;/*11 ���󴥷�*/

	/*13 ���俪/����*/
	if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[12] = STA_ANYONE_BOX_OPEN_DOOR;/*��һ���忪��*/
	}
	else if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[12] = STA_ALL_BOX_CLOSE_DOOR;/*�����������*/
	}
	else if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[12] = STA_ANYONE_BOX_ERROR;/*��һ�������*/
	}
	else
	{
		tmp[12] = STA_NOT_EXIST;/*��Ч���*/
	}
	
	/*14 ZXB���俪/����*/
	if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[13] = STA_ANYONE_BOX_OPEN_DOOR;//��һ���忪��
	}
	else if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[13] = STA_ALL_BOX_CLOSE_DOOR;//�����������
	}
	else if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[13] = STA_ANYONE_BOX_ERROR;//��һ�������
	}
	else
	{
		tmp[13] = STA_NOT_EXIST;/*��Ч���*/
	}

	/*15 CT���俪/����*/
	if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[14] = STA_ANYONE_BOX_OPEN_DOOR;//��һ���忪��
	}
	else if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[14] = STA_ALL_BOX_CLOSE_DOOR;//�����������
	}
	else if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[14] = STA_ANYONE_BOX_ERROR;//��һ�������
	}
	else
	{
		tmp[14] = STA_NOT_EXIST;/*��Ч���*/
	}

	/*19 ������/��*/
	if((col_module_sta_info[0].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[0].Byte4.bits.cam2CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[1].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[2].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[3].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[4].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[5].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[6].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[7].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[8].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[9].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR)
	||(col_module_sta_info[10].Byte3.bits.cam1CCFanErrSta==STA_FAN_ERROR))
	{
		/*��һ�������ȹ���*/
		tmp[18] = STA_ANYONE_FAN_ERROR;
	}
	else if((col_module_sta_info[0].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[0].Byte4.bits.cam2CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[1].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[2].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[3].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[4].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[5].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[6].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[7].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[8].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[9].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[10].Byte3.bits.cam1CCFanOpenCtrl == STA_FAN_OPEN)
	)
	{
		/*��һ�������ȿ���*/
		tmp[18] = STA_ANYONE_FAN_OPEN;
	}
	else
	{
		/*���г������ȹر�*/
		tmp[18] = STA_ALL_FAN_CLOSE;
	}

	/*20 ɢ�ȿ�/��*/
	if((col_module_sta_info[0].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[0].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[0].Byte5.bits.cam2SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[0].Byte5.bits.cam2SRFan2ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[1].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[1].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[2].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[2].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[3].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[3].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[4].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[4].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[5].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[5].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[6].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[6].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[7].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[7].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[8].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[8].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[9].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[9].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	||(col_module_sta_info[10].Byte4.bits.cam1SRFan1ErrSta == STA_FAN_ERROR)
	||(col_module_sta_info[10].Byte4.bits.cam1SRFan2ErrSta == STA_FAN_ERROR)	
	)
	{
		/*��һɢ�ȷ��ȹ���*/
		tmp[19] = STA_ANYONE_FAN_ERROR;
	}
	else if((col_module_sta_info[0].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[0].Byte4.bits.cam2SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[1].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[2].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[3].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[4].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[5].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[6].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[7].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[8].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[9].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	||(col_module_sta_info[10].Byte4.bits.cam1SRFanOpenCtrl == STA_FAN_OPEN)
	)
	{
		/*��һɢ�ȷ��ȿ���*/
		tmp[19] = STA_ANYONE_FAN_OPEN;
	}
	else
	{
		/*����ɢ�ȷ��ȹر�*/
		tmp[19] = STA_ALL_FAN_CLOSE;		
	}
	
	
    elapseticks = (uint32)(OSALTimeGet() - oldTicks);
    if(elapseticks >= 2000)
    {
        if(ctrlHost_heartbeatCnt != ctrlHost_last_heartbeatCnt)
        {
			tmp[7] = STA_NORMAL;/*��̫��ͨѶ����*/ 
			ctrlHost_last_heartbeatCnt = ctrlHost_heartbeatCnt;
        }
		else
		{
			tmp[7] = STA_ERROR;/*��̫��ͨѶ�쳣*/
		}
		

		/*22 �����źŰ�*/
		if(sigColBoardInfo.hearBeatCnt != board_last_heartbeatCnt[0])
		{
			tmp[21] = STA_NORMAL;//����
			gpkzx_sta_info_byte25.Byte.bits.bit3_2 = STA_NORMAL;
			board_last_heartbeatCnt[0] = sigColBoardInfo.hearBeatCnt;
		}
		else
		{
			tmp[21] = STA_ERROR;//�쳣
			gpkzx_sta_info_byte25.Byte.bits.bit3_2 = STA_ERROR;
		}

		/*23 ������ư�*/
		if(XZCtrlBoardInfo[0].hearBeatCnt != board_last_heartbeatCnt[1])
		{
			tmp[22] = STA_NORMAL;//����
			XZCtrlBoardErrInfo[0].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[1] = XZCtrlBoardInfo[0].hearBeatCnt;
		}
		else
		{
			tmp[22] = STA_ERROR;//�쳣
			XZCtrlBoardErrInfo[0].Byte.bits.bit7_6 = STA_ERROR;
		}

		/*24 ������ư�*/
		if(XZCtrlBoardInfo[1].hearBeatCnt != board_last_heartbeatCnt[2])
		{
			tmp[23] = STA_NORMAL;//����
			XZCtrlBoardErrInfo[1].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[2] = XZCtrlBoardInfo[1].hearBeatCnt;
		}
		else
		{
			tmp[23] = STA_ERROR;//�쳣
			XZCtrlBoardErrInfo[1].Byte.bits.bit7_6 = STA_ERROR;
		}

		/*25 �������ư�*/
		if(XZCtrlBoardInfo[2].hearBeatCnt != board_last_heartbeatCnt[3])
		{
			tmp[24] = STA_NORMAL;//����
			XZCtrlBoardErrInfo[2].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[3] = XZCtrlBoardInfo[2].hearBeatCnt;
		}
		else
		{
			tmp[24] = STA_ERROR;//�쳣
			XZCtrlBoardErrInfo[2].Byte.bits.bit7_6 = STA_ERROR;
		}		
	}
	
	OSAL_EXIT_CRITICAL();

    /*�Բ���״̬�����ж���״̬*/
	/*2 ����ģʽ ����ģʽ:��/ά��ģʽ:��*/
    if(tmp[1] == STA_NORMAL)
	{
		appStaShowStru[1].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[1].ledSta = APP_LED_STATE_OFF;
	}

	/*3 DC24V��Դ����:����/����:����*/
	if(tmp[2] == STA_NORMAL)
	{
		appStaShowStru[2].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[2].ledSta = APP_LED_STATE_OFF;
	}

	/*4 DC12V��Դ����:����/����:����*/
	if(tmp[3] == STA_NORMAL)
	{
		appStaShowStru[3].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[3].ledSta = APP_LED_STATE_OFF;
	}

	/*5 DC5V��Դ����:����/����:����*/
	/*��DC5V��Դ��ѹ������(4.85,5.15)ʱ,�ж���Դ��������֮�ж�Ϊ��Դ�쳣*/
	if((tmp[4]>485)&&(tmp[4]<515))
	{
		appStaShowStru[4].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[4].ledSta = APP_LED_STATE_OFF;
	}

	/*6 CAN1ͨѶ ����:����/����:����*/
	if(tmp[5] == STA_NORMAL)
	{
		appStaShowStru[5].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[5].ledSta = APP_LED_STATE_OFF;
	}
	
	/*7 CAN2ͨѶ ����:����/����:����*/
	if(tmp[6] == STA_NORMAL)
	{
		appStaShowStru[6].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[6].ledSta = APP_LED_STATE_OFF;
	}

	/*8 ��̫��ͨѶ ����:����/����:����*/
	if(tmp[7] == STA_NORMAL)
	{
		appStaShowStru[7].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[7].ledSta = APP_LED_STATE_OFF;
	}

	/*9 ���/���� ��⣺����/���⣺��/���ϣ���*/
	if(tmp[8] == 1)
	{
		appStaShowStru[8].ledSta = APP_LED_STATE_FLASH;
	}
	else
	{
		appStaShowStru[8].ledSta = APP_LED_STATE_LIGHT;
	}

	/*10 ˮλ���� ��ˮ������/��ˮ:����*/
	if(tmp[9] == STA_EXIST_WATER)
	{
		appStaShowStru[9].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[9].ledSta = APP_LED_STATE_OFF;
	}

	/*11 ���󴥷� ���㴥��������/���⣺����*/
	if((tmp[10]==1)&&(tmp[8]==1))
	{
		appStaShowStru[10].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[10].ledSta = APP_LED_STATE_OFF;
	}

	/*12 ���󴥷� Ԥ��*/

	/*13 ���俪/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	if(tmp[12] == STA_ANYONE_BOX_OPEN_DOOR)
	{
		appStaShowStru[12].ledSta = APP_LED_STATE_FLASH;
	}
	else if(tmp[12] == STA_ALL_BOX_CLOSE_DOOR)
	{
		appStaShowStru[12].ledSta = APP_LED_STATE_LIGHT;
	}
	else 
	{
		appStaShowStru[12].ledSta = APP_LED_STATE_OFF;
	}

	/*14 ZXB���俪/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	if(tmp[13] == STA_ANYONE_BOX_OPEN_DOOR)
	{
		appStaShowStru[13].ledSta = APP_LED_STATE_FLASH;
	}
	else if(tmp[13] == STA_ALL_BOX_CLOSE_DOOR)
	{
		appStaShowStru[13].ledSta = APP_LED_STATE_LIGHT;
	}
	else 
	{
		appStaShowStru[13].ledSta = APP_LED_STATE_OFF;
	}

	/*15 CT���俪/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	if(tmp[14] == STA_ANYONE_BOX_OPEN_DOOR)
	{
		appStaShowStru[14].ledSta = APP_LED_STATE_FLASH;
	}
	else if(tmp[14] == STA_ALL_BOX_CLOSE_DOOR)
	{
		appStaShowStru[14].ledSta = APP_LED_STATE_LIGHT;
	}
	else 
	{
		appStaShowStru[14].ledSta = APP_LED_STATE_OFF;
	}

	/*16 բ�߿�/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	/*�ݲ�������*/

	/*17 բƬ��/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	/*�ݲ�������*/

	/*18 �����俪/���� ���ţ�����/���ţ�����/��һ�����ſع��ϣ���*/
	/*�ݲ�������*/

	/*19 ������/�� ��������/�أ�����/��һ���ȹ��ϣ���*/
    if(tmp[18] == STA_ANYONE_FAN_OPEN)
	{
		appStaShowStru[18].ledSta = APP_LED_STATE_FLASH;
	}
	else if(tmp[18] == STA_ALL_FAN_CLOSE)
	{
		appStaShowStru[18].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[18].ledSta = APP_LED_STATE_OFF;
	}
	
	/*20 ɢ�ȿ�/�� ��������/�أ�����/��һ���ȹ��ϣ���*/
	if(tmp[19] == STA_ANYONE_FAN_OPEN)
	{
		appStaShowStru[19].ledSta = APP_LED_STATE_FLASH;
	}
	else if(tmp[19] == STA_ALL_FAN_CLOSE)
	{
		appStaShowStru[19].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[19].ledSta = APP_LED_STATE_OFF;
	}

	/*21 ���ȿ�/�� ��������/�أ���*/
	/*�ݲ�������*/

	/*22 �����źŰ� ��������/�쳣����*/
	if(tmp[21] == STA_NORMAL)
	{
		appStaShowStru[21].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[21].ledSta = APP_LED_STATE_OFF;
	}
	
	/*23 ������ư� ��������/�쳣����*/
	if(tmp[22] == STA_NORMAL)
	{
		appStaShowStru[22].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[22].ledSta = APP_LED_STATE_OFF;
	}

	/*24 ������ư� ��������/�쳣����*/
	if(tmp[23] == STA_NORMAL)
	{
		appStaShowStru[23].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[23].ledSta = APP_LED_STATE_OFF;
	}

	/*25 �������ư� ��������/�쳣����*/
	if(tmp[24] == STA_NORMAL)
	{
		appStaShowStru[24].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[24].ledSta = APP_LED_STATE_OFF;
	}

	/*26 ������ư�1 ��������/�쳣����*/
	/*�ݲ�������*/

	/*27 ������ư�1 ��������/�쳣����*/
	/*�ݲ�������*/

	/*28 29 30 Ԥ��*/
	/*�ݲ�������*/


    /*����ָʾ��״̬*/
    for(i=0;i<30;i++)
        app_set_led_state(&appStaShowStru[i]);
}
