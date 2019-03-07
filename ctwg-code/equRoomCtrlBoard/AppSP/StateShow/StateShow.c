/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : StateShow.c
* 功能描述  : 状态显示模块管理源文件
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/

#include "Bsw.h"
#include "Osal.h"

APP_STATE_SHOW_STRU appStaShowStru[30] = 
{
	/*状态指示灯 LED1~5*/
	{PORT_PIN_PAD1 , APP_LED_STATE_FLASH , PORT_PIN_LEVEL_LOW},/*运行灯*/
	{PORT_PIN_PAD2 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*工作模式*/
	{PORT_PIN_PAD3 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC24V电源*/
	{PORT_PIN_PAD4 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC12V电源*/
	{PORT_PIN_PAD5 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*DC5V电源*/

	/*状态指示灯 LED6~10*/
	{PORT_PIN_PAD6 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CAN1通讯*/
	{PORT_PIN_PAD7 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CAN2通讯*/
	{PORT_PIN_PAD8 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*以太网通讯*/
	{PORT_PIN_PAD9 , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*入库/出库*/
	{PORT_PIN_PAD10, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*水位报警*/
	
	/*状态指示灯 LED11~15*/
	{PORT_PIN_PAD11, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*线阵触发*/
	{PORT_PIN_PAD12, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*面阵触发*/
	{PORT_PIN_PAD13, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*沉箱开/关门*/
	{PORT_PIN_PAD14, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*ZXB侧箱开/关门*/
	{PORT_PIN_PAD15, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*CT侧箱开/关门*/

	/*状态指示灯 LED16~20*/
	{PORT_PIN_PAD16, APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*闸瓦开/关门*/
	{PORT_PIN_PP0  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*闸片开/关门*/
	{PORT_PIN_PP1  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*齿轮箱开/关门*/
	{PORT_PIN_PP2  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*除尘开/关*/
	{PORT_PIN_PP3  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*散热开/关*/
	
	/*状态指示灯 LED21~25*/
	{PORT_PIN_PP4  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*加热开/关*/
	{PORT_PIN_PP5  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*公共信号板*/
	{PORT_PIN_PP6  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*沉箱控制板*/
	{PORT_PIN_PP7  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*侧箱控制板*/
	{PORT_PIN_PH2  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*车顶控制板*/
	
	/*状态指示灯 LED26~30*/
	{PORT_PIN_PH3  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*面阵控制板1*/
	{PORT_PIN_PH4  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*面阵控制板2*/
	{PORT_PIN_PH5  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*预留*/
	{PORT_PIN_PH6  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW},/*预留*/
	{PORT_PIN_PH7  , APP_LED_STATE_OFF , PORT_PIN_LEVEL_LOW} /*预留*/
};

/***************************************************************************//*!
 * \brief   状态显示模块初始化
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void app_stateShow_Init(void)
{

}


/***************************************************************************//*!
 * \brief   设置状态指示灯状态
 *
 * \param   APP_STATE_SHOW_STRU 状态指示模块结构变量
 *
 * \return  无
 *
 *****************************************************************************/
void app_set_led_state(APP_STATE_SHOW_STRU *appStaShowStruct)
{
    uint8 portPin,ledSta;
    
    portPin = appStaShowStruct->PortNumberOfPortPins;/*led引脚号*/
    ledSta  = appStaShowStruct->ledSta; /*led状态*/        

    switch (ledSta)
    {
        case APP_LED_STATE_OFF:     /* 常灭 */
            Port_WritePinValue(portPin,PORT_PIN_LEVEL_HIGH);
            break;

        case APP_LED_STATE_LIGHT:   /* 常亮 */
            Port_WritePinValue(portPin,PORT_PIN_LEVEL_LOW);
            break;

        case APP_LED_STATE_FLASH:   /* 闪烁 */  
            appStaShowStruct->lastPinLevelVal = !appStaShowStruct->lastPinLevelVal;
            Port_WritePinValue(portPin,appStaShowStruct->lastPinLevelVal);
            break;
    
        default:
            break;
    }
}

/***************************************************************************//*!
 * \brief   状态显示模块后台主循环
 *
 * \param   无
 *
 * \return  无
 *
 *****************************************************************************/
void app_stateShow_MainFunction(void)
{
	static uint32 oldTicks = 0u;
	static uint8 board_last_heartbeatCnt[4],ctrlHost_last_heartbeatCnt;
    uint32 elapseticks = 0u;
    uint8 i = 0;/*累加变量*/
	uint16 tmp[30];/*用于存储30个指示灯的对应的各种情况*/

	OSAL_ENTER_CRITICAL();
	tmp[1] = ctrl_cmd_info.Byte0.bits.runOrService;/*2 运行模式*/
	tmp[2] = fun_stru2.Byte.bits.bit1_0;/*3 DC24V电源*/
	tmp[3] = fun_stru2.Byte.bits.bit3_2;/*4 DC12V电源*/
	tmp[4] = g_DC5VVol_info;/*5 DC5V电源*/
	tmp[5] = equRoomCtrlBoardInfo.Byte5.bits.boardCan1ErrSta;/*6 CAN1通讯*/
	tmp[6] = equRoomCtrlBoardInfo.Byte5.bits.boardCan2ErrSta;/*7 CAN2通讯*/
	
	tmp[8] = fun_stru1.Byte.bits.bit7_6;/*9 入库/出库*/
	/*10 水位报警*/
	if((col_module_sta_info[0].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[1].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[2].Byte5.bits.waterAlarm == 1)
	||(col_module_sta_info[3].Byte5.bits.waterAlarm == 1))
	{
		tmp[9] = STA_EXIST_WATER;/*有水*/
	}
	else
	{
		tmp[9] = STA_NOT_EXIST_WATER;/*无水*/
	}
	tmp[10] = fun_stru1.Byte.bits.bit5_4;/*11 线阵触发*/

	/*13 沉箱开/关门*/
	if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[12] = STA_ANYONE_BOX_OPEN_DOOR;/*任一箱体开门*/
	}
	else if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[12] = STA_ALL_BOX_CLOSE_DOOR;/*所有箱体关门*/
	}
	else if((col_module_sta_info[0].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[1].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[2].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[3].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[12] = STA_ANYONE_BOX_ERROR;/*任一箱体故障*/
	}
	else
	{
		tmp[12] = STA_NOT_EXIST;/*无效情况*/
	}
	
	/*14 ZXB侧箱开/关门*/
	if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[13] = STA_ANYONE_BOX_OPEN_DOOR;//任一箱体开门
	}
	else if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[13] = STA_ALL_BOX_CLOSE_DOOR;//所有箱体关门
	}
	else if((col_module_sta_info[4].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[5].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[13] = STA_ANYONE_BOX_ERROR;//任一箱体故障
	}
	else
	{
		tmp[13] = STA_NOT_EXIST;/*无效情况*/
	}

	/*15 CT侧箱开/关门*/
	if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_OPEN_DOOR)
	||(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_OPEN_DOOR))
	{
		tmp[14] = STA_ANYONE_BOX_OPEN_DOOR;//任一箱体开门
	}
	else if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_CLOSE_DOOR)
	&&(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_CLOSE_DOOR))
	{
		tmp[14] = STA_ALL_BOX_CLOSE_DOOR;//所有箱体关门
	}
	else if((col_module_sta_info[6].Byte5.bits.camDoorSta==STA_DOOR_ERROR)
	||(col_module_sta_info[7].Byte5.bits.camDoorSta==STA_DOOR_ERROR))
	{
		tmp[14] = STA_ANYONE_BOX_ERROR;//任一箱体故障
	}
	else
	{
		tmp[14] = STA_NOT_EXIST;/*无效情况*/
	}

	/*19 除尘开/关*/
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
		/*任一除尘风扇故障*/
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
		/*任一除尘风扇开启*/
		tmp[18] = STA_ANYONE_FAN_OPEN;
	}
	else
	{
		/*所有除尘风扇关闭*/
		tmp[18] = STA_ALL_FAN_CLOSE;
	}

	/*20 散热开/关*/
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
		/*任一散热风扇故障*/
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
		/*任一散热风扇开启*/
		tmp[19] = STA_ANYONE_FAN_OPEN;
	}
	else
	{
		/*所有散热风扇关闭*/
		tmp[19] = STA_ALL_FAN_CLOSE;		
	}
	
	
    elapseticks = (uint32)(OSALTimeGet() - oldTicks);
    if(elapseticks >= 2000)
    {
        if(ctrlHost_heartbeatCnt != ctrlHost_last_heartbeatCnt)
        {
			tmp[7] = STA_NORMAL;/*以太网通讯正常*/ 
			ctrlHost_last_heartbeatCnt = ctrlHost_heartbeatCnt;
        }
		else
		{
			tmp[7] = STA_ERROR;/*以太网通讯异常*/
		}
		

		/*22 公共信号板*/
		if(sigColBoardInfo.hearBeatCnt != board_last_heartbeatCnt[0])
		{
			tmp[21] = STA_NORMAL;//正常
			gpkzx_sta_info_byte25.Byte.bits.bit3_2 = STA_NORMAL;
			board_last_heartbeatCnt[0] = sigColBoardInfo.hearBeatCnt;
		}
		else
		{
			tmp[21] = STA_ERROR;//异常
			gpkzx_sta_info_byte25.Byte.bits.bit3_2 = STA_ERROR;
		}

		/*23 沉箱控制板*/
		if(XZCtrlBoardInfo[0].hearBeatCnt != board_last_heartbeatCnt[1])
		{
			tmp[22] = STA_NORMAL;//正常
			XZCtrlBoardErrInfo[0].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[1] = XZCtrlBoardInfo[0].hearBeatCnt;
		}
		else
		{
			tmp[22] = STA_ERROR;//异常
			XZCtrlBoardErrInfo[0].Byte.bits.bit7_6 = STA_ERROR;
		}

		/*24 侧箱控制板*/
		if(XZCtrlBoardInfo[1].hearBeatCnt != board_last_heartbeatCnt[2])
		{
			tmp[23] = STA_NORMAL;//正常
			XZCtrlBoardErrInfo[1].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[2] = XZCtrlBoardInfo[1].hearBeatCnt;
		}
		else
		{
			tmp[23] = STA_ERROR;//异常
			XZCtrlBoardErrInfo[1].Byte.bits.bit7_6 = STA_ERROR;
		}

		/*25 车顶控制板*/
		if(XZCtrlBoardInfo[2].hearBeatCnt != board_last_heartbeatCnt[3])
		{
			tmp[24] = STA_NORMAL;//正常
			XZCtrlBoardErrInfo[2].Byte.bits.bit7_6 = STA_NORMAL;
			board_last_heartbeatCnt[3] = XZCtrlBoardInfo[2].hearBeatCnt;
		}
		else
		{
			tmp[24] = STA_ERROR;//异常
			XZCtrlBoardErrInfo[2].Byte.bits.bit7_6 = STA_ERROR;
		}		
	}
	
	OSAL_EXIT_CRITICAL();

    /*对部分状态进行判断其状态*/
	/*2 工作模式 运行模式:亮/维护模式:灭*/
    if(tmp[1] == STA_NORMAL)
	{
		appStaShowStru[1].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[1].ledSta = APP_LED_STATE_OFF;
	}

	/*3 DC24V电源正常:常亮/故障:常灭*/
	if(tmp[2] == STA_NORMAL)
	{
		appStaShowStru[2].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[2].ledSta = APP_LED_STATE_OFF;
	}

	/*4 DC12V电源正常:常亮/故障:常灭*/
	if(tmp[3] == STA_NORMAL)
	{
		appStaShowStru[3].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[3].ledSta = APP_LED_STATE_OFF;
	}

	/*5 DC5V电源正常:常亮/故障:常灭*/
	/*当DC5V电源电压在区间(4.85,5.15)时,判定电源正常，反之判定为电源异常*/
	if((tmp[4]>485)&&(tmp[4]<515))
	{
		appStaShowStru[4].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[4].ledSta = APP_LED_STATE_OFF;
	}

	/*6 CAN1通讯 正常:常亮/故障:常灭*/
	if(tmp[5] == STA_NORMAL)
	{
		appStaShowStru[5].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[5].ledSta = APP_LED_STATE_OFF;
	}
	
	/*7 CAN2通讯 正常:常亮/故障:常灭*/
	if(tmp[6] == STA_NORMAL)
	{
		appStaShowStru[6].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[6].ledSta = APP_LED_STATE_OFF;
	}

	/*8 以太网通讯 正常:常亮/故障:常灭*/
	if(tmp[7] == STA_NORMAL)
	{
		appStaShowStru[7].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[7].ledSta = APP_LED_STATE_OFF;
	}

	/*9 入库/出库 入库：秒闪/出库：亮/故障：灭*/
	if(tmp[8] == 1)
	{
		appStaShowStru[8].ledSta = APP_LED_STATE_FLASH;
	}
	else
	{
		appStaShowStru[8].ledSta = APP_LED_STATE_LIGHT;
	}

	/*10 水位报警 有水：常亮/无水:常灭*/
	if(tmp[9] == STA_EXIST_WATER)
	{
		appStaShowStru[9].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[9].ledSta = APP_LED_STATE_OFF;
	}

	/*11 线阵触发 拍摄触发：常亮/出库：常灭*/
	if((tmp[10]==1)&&(tmp[8]==1))
	{
		appStaShowStru[10].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[10].ledSta = APP_LED_STATE_OFF;
	}

	/*12 面阵触发 预留*/

	/*13 沉箱开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
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

	/*14 ZXB侧箱开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
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

	/*15 CT侧箱开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
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

	/*16 闸瓦开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
	/*暂不做处理*/

	/*17 闸片开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
	/*暂不做处理*/

	/*18 齿轮箱开/关门 开门：秒闪/关门：常亮/任一箱体门控故障：灭*/
	/*暂不做处理*/

	/*19 除尘开/关 开：秒闪/关：常亮/任一风扇故障：灭*/
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
	
	/*20 散热开/关 开：秒闪/关：常亮/任一风扇故障：灭*/
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

	/*21 加热开/关 开：常亮/关：灭*/
	/*暂不做处理*/

	/*22 公共信号板 正常：亮/异常：灭*/
	if(tmp[21] == STA_NORMAL)
	{
		appStaShowStru[21].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[21].ledSta = APP_LED_STATE_OFF;
	}
	
	/*23 沉箱控制板 正常：亮/异常：灭*/
	if(tmp[22] == STA_NORMAL)
	{
		appStaShowStru[22].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[22].ledSta = APP_LED_STATE_OFF;
	}

	/*24 侧箱控制板 正常：亮/异常：灭*/
	if(tmp[23] == STA_NORMAL)
	{
		appStaShowStru[23].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[23].ledSta = APP_LED_STATE_OFF;
	}

	/*25 车顶控制板 正常：亮/异常：灭*/
	if(tmp[24] == STA_NORMAL)
	{
		appStaShowStru[24].ledSta = APP_LED_STATE_LIGHT;
	}
	else
	{
		appStaShowStru[24].ledSta = APP_LED_STATE_OFF;
	}

	/*26 面阵控制板1 正常：亮/异常：灭*/
	/*暂不做处理*/

	/*27 面阵控制板1 正常：亮/异常：灭*/
	/*暂不做处理*/

	/*28 29 30 预留*/
	/*暂不做处理*/


    /*设置指示灯状态*/
    for(i=0;i<30;i++)
        app_set_led_state(&appStaShowStru[i]);
}
