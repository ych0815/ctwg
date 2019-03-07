/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : MeaVel.h
* ��������  : ����ģ�����ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/7        sunj            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef _MEAVEL_H
#define _MEAVEL_H

#include "drv_ect.h"
#include "Osal.h"

/**\brief ���ٴŸ�֮��ľ��� */
#define     MEAVEL_LENGTH           250u


/**\brief ��������ģ��ṹ�� */
typedef struct
{
    boolean errState;   /**\brief ģ�����״̬��TRUEΪ����  FALSEΪ���� */
    boolean flag[2];    /**\brief True��ʾ�����жϣ�false��ʾδ�����ж� flag[0]��ʾ��һ·��־λ flag[1]��ʾ�ڶ�·��־λ */
    INT16U timeCnt[2];  /**\brief ����ֵ */
    boolean timeOut;    /**\brief ��ʱ��־ */
    INT8U errorCnt;     /**\brief ����ģ���������� */
    INT32U curTicks;    /**\brief ��ǰ������ */
    INT16U trainVel;    /**\brief ����ֵ ��λ��km/h */
}T_MeaVel;

/**\brief ������Ϣ�ṹ�� */
typedef struct
{
    boolean IsFinish;   /*\brief ������Ϣ�Ƿ��ȡ��־λ */ 
    INT16U value;       /*\brief ����ֵ */
}T_TrainVel;


/************************
 * ȫ�ֱ����ⲿ����
 * ************************/
#pragma DATA_SEG __GPAGE_SEG  LARGER_RAM
extern T_MeaVel g_meavel_info[2];
extern T_TrainVel  g_trainVeal_info;	  /*������Ϣ����2������ģ���ٲó��ģ���λ:km/h*/

#pragma DATA_SEG DEFAULT


/************************
 * �����ⲿ����
 * ************************/
extern void MeaVel_Init(void);
extern void MeaVel_ReInit(void);
extern void MeaVel_MainFunction(void);
extern void trainVelMeaMd1_STA_INT(void);
extern void trainVelMeaMd1_END_INT(void);
extern void trainVelMeaMd2_STA_INT(void);
extern void trainVelMeaMd2_END_INT(void);



#endif
