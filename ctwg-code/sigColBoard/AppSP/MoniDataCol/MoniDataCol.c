/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : MoniDataCol.c
* ��������  : ������ݲɼ���ɢ�ȿ���ģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/8        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#include "Bsw.h"


#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
BOOLEAN g_fanOpenSta_info;	  /*���Կ�����ɢ�ȷ��ȿ�������*/
//BOOLEAN g_DC5VErrSta_info;	  /*DC5V��Դ����״̬*/
BOOLEAN g_DC12VErrSta_info;	  /*DC12V��Դ����״̬*/
BOOLEAN g_DC24VErrSta_info;	  /*DC24V��Դ����״̬*/
BOOLEAN g_tempErrSta_info;    /*�¶ȴ���������״̬*/
INT8S	g_temp_info;		  /*�����¶���Ϣ*/
uint16  g_DC5VVol_info;       /*DC5V��Դ��ѹ(��λ:0.01V)*/

#pragma DATA_SEG DEFAULT


/***************************************************************************//*!
 * \brief   ������ݲɼ�ģ���ʼ��
 *
 * \param   ��
 *
 * \return  ��
 *
 *****************************************************************************/
void MoniDataCol_Init(void)
{
    char iRet;

    /*��ʼ����ر���*/
    g_fanOpenSta_info   = FALSE;
//    g_DC5VErrSta_info   = FALSE;
    g_DC12VErrSta_info  = FALSE;
    g_DC24VErrSta_info  = FALSE;
    g_tempErrSta_info   = FALSE; 
    g_temp_info         = 0;

    OSAL_ENTER_CRITICAL();
    iRet = drv_tmp1075_init(BSP_TMP1075_SLAVE_ADDR);
    OSAL_EXIT_CRITICAL();
    
    if(iRet==0)
    {
        g_tempErrSta_info = FALSE;
        Drv_Sci_Write("\r\ntmp1075 init successed",0,0);
    } 
    else
    {
        g_tempErrSta_info = TRUE;
        Drv_Sci_Write("\r\ntmp1075 init failed",0,0); 
    }
}


/***************************************************************************//*!
 * \brief   ��ȡDC5V��12V��24V��Դ����״̬
 *
 * \param   DC5V_state   DC5V��Դ����״ָ̬��
 *          DC12V_state  DC5V��Դ����״ָ̬��
 *          DC24V_state  DC5V��Դ����״ָ̬��
 *
 * \return  0  ��ʾ�ɹ�
 *          -1 ��ʾʧ��
 *
 *****************************************************************************/
INT8S getDCPowerErrState(BOOLEAN * __far DC12V_state,BOOLEAN * __far DC24V_state)
{
    BOOLEAN sta_12V,sta_24V;

    /*��ȡDC5V��Դ״̬*/
    //Port_ReadPinValue(PORT_PIN_PB2,&sta_5V);
    /*��ȡDC12V��Դ״̬*/
    Port_ReadPinValue(PORT_PIN_PB0,&sta_12V);
    /*��ȡDC24V��Դ״̬*/
    Port_ReadPinValue(PORT_PIN_PC7,&sta_24V);

    if(sta_12V==TRUE)
    {
        *DC12V_state = FALSE;
    }
    else
    {
        *DC12V_state = TRUE;
    }

    if(sta_24V==TRUE)
    {
        *DC24V_state = FALSE;
    }
    else
    {
        *DC24V_state = TRUE;
    }   

}

/***************************************************************************//*!
 * \brief   ��ȡ���Կ�����ɢ�ȷ��ȿ���״̬
 *
 * \param   state   ���Կ�����ɢ�ȷ��ȿ���״̬
 *
 * \return  0  ��ʾ�ɹ�
 *          -1 ��ʾʧ��
 *
 *****************************************************************************/
INT8S getFanOpenState(INT8S temp,BOOLEAN * __far state)
{
    if(temp > HIGH_TEMP_LIMIT)
    {
        /*�������Ƚ���ɢ�ȿ���*/
        *state = TRUE;
    }
    else
    {
        *state = FALSE;
    }

    return 0;  
}

/***************************************************************************//*!
 * \brief   ���ݷ��ȿ���״̬����ɢ�ȷ��ȿ�����ر�
 *
 * \param   state   ���Կ�����ɢ�ȷ��ȿ���״̬
 *
 * \return  0  ��ʾ�ɹ�
 *          -1 ��ʾʧ��
 *
 *****************************************************************************/
INT8S setFanOpenOrClose(BOOLEAN state)
{
    if(state)
    {
        /*�������_��ƽ,��������*/
        Port_WritePinValue(PIN_SR_FAN1,PORT_PIN_LEVEL_HIGH);
        Port_WritePinValue(PIN_SR_FAN2,PORT_PIN_LEVEL_HIGH);
    }
    else
    {
        /*�������_��ƽ���رշ���*/
        Port_WritePinValue(PIN_SR_FAN1,PORT_PIN_LEVEL_LOW);
        Port_WritePinValue(PIN_SR_FAN2,PORT_PIN_LEVEL_LOW);
    }

    return 0;
}


