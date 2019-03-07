/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateShow.h
* ��������  : ״̬��ʾģ�����ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/9        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef STATESHOW_H
#define STATESHOW_H

/**********************************
 * ͷ�ļ�
 * ********************************/
#include "os_cpu.h"
#include "Port_Define.h"
#include "Port.h"


/**********************************
 * �궨��
 * ********************************/
#define     STA_NORMAL                          1       /*״̬����*/
#define     STA_ERROR                           2       /*״̬����*/

#define     STA_EXIST_WATER                     1       /*��ˮ*/
#define     STA_NOT_EXIST_WATER                 2       /*��ˮ*/

#define     STA_CLOSE_DOOR                      1       /*����*/
#define     STA_OPEN_DOOR                       2       /*����*/
#define     STA_DOOR_ERROR                      3       /*�Ź���*/

#define     STA_NOT_EXIST                       0       /*��Ч���*/
#define     STA_ANYONE_BOX_OPEN_DOOR            1       /*��һ���忪��*/
#define     STA_ALL_BOX_CLOSE_DOOR              2       /*�����������*/
#define     STA_ANYONE_BOX_ERROR                3       /*��һ�������*/

#define     STA_FAN_NORMAL                      0       /*��������*/
#define     STA_FAN_ERROR                       1       /*���ȹ���*/

#define     STA_FAN_CLOSE                       0       /*���ȹر�*/
#define     STA_FAN_OPEN                        1       /*���ȿ���*/

#define     STA_ANYONE_FAN_OPEN                 1       /*��һ���ȿ���*/
#define     STA_ALL_FAN_CLOSE                   2       /*���з��ȹر�*/
#define     STA_ANYONE_FAN_ERROR                3       /*��һ�������*/

/**********************************
 * ���ݽṹ����
 * ********************************/
/**\brief ״ָ̬ʾ��ö������ */
typedef enum
{
    APP_LED_STATE_OFF       = 0,    /* ָʾ�Ƴ��� */
    APP_LED_STATE_LIGHT     = 1,    /* ָʾ�Ƴ��� */
    APP_LED_STATE_FLASH     = 2     /* ָʾ����˸ */
}APP_LED_STATE;

/**\brief ״ָ̬ʾģ��ṹ������*/
typedef struct
{
    /**\brief ���ź� */
    Port_PinType PortNumberOfPortPins;

    /**\brief ״ָ̬ʾ��״̬ */
    APP_LED_STATE ledSta;

    /**\brief ״ָ̬ʾ�ƴ�����˸״̬ʱ�洢�ϴεĵ�ƽֵ */
    Port_PinLevelValueType lastPinLevelVal;
}APP_STATE_SHOW_STRU;


/**********************************
 * ȫ�ֱ����ⲿ����
 * ********************************/
extern APP_STATE_SHOW_STRU appStaShowStru[30];


/**********************************
 * �����ⲿ����
 * ********************************/
extern void app_stateShow_Init(void);
extern void app_set_led_state(APP_STATE_SHOW_STRU *appStaShowStruct);
extern void app_stateShow_MainFunction(void);

#endif
