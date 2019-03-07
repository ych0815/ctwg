/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : ComM_CfgType.h
* ��������  : ͨѶ����ģ���������Ͷ���ͷ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COMM_CFGTYPE_H_
#define  _COMM_CFGTYPE_H_

#include "ComM_Cfg.h"
/**********************************
            ��̬�����������Ͷ���
 **********************************/
typedef  struct
{
	uint8   LowValue;      /*��������*/
	uint8   HightValue;    /*��������*/
	uint8   StepValue;     /*��Ӧ����*/
}ComM_StepCfgType;

/*�������е���������ƽ���㷨���������������*/
typedef  struct
{
    uint8   DevId;         /*�豸Id��*/
    boolean Direct;        /*=FALSE;ƽ��ֵ���¼�;=TRUE:ƽ��ֵ���ϼ�*/
    uint8   NumOfSteps;    /*�豸��Ӧ�������*/
    const  ComM_StepCfgType *pDevStepCfg;
    uint32  FaultTimeOut;  /*ͨѶ���ϳ�ʱʱ��*/  
}ComM_DevCfgType;

/*����������ƽ���㷨���������������*/
typedef  struct
{
    uint8   GroupId;         			/*������ID��*/
    uint8   ValueOfBalance;  			/*ƽ����ƽ��ֵ*/
    uint8   BalanceLowLimit; 			/*ƽ����ƽ����ֵ*/
    uint8   BalanceHiLimit;				/*ƽ����ƽ����ֵ*/
	uint8   TrustBusAtPowerOn;			/*����Ĭ����������*/
	uint8   NumOfControllerCfg;         /*�������а����Ŀ���������*/
    const   ComM_DevCfgType   *pControllerCfg;	/*���������������������ʼ��ַ*/
}ComM_GroupCfgType;

/*ģ��֧�ֵ�������������������*/
typedef struct
{
   uint8 NumOfDevice;     		/*ģ��֧�ֵĿ���������*/
   const ComM_DevCfgType   *pDevCfg;
   uint8 NumOfComMGroup;  		/*ģ��֧�ֵ�����������*/
   const ComM_GroupCfgType *pGroupCfg;
}ComM_CfgType;

#endif

