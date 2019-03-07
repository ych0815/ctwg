/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : ComM_Cfg.c
* ��������  : ͨѶ����ģ������Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/8       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#include "ComM_Cfg.h"
#include "ComM_CfgType.h"

const  ComM_StepCfgType   ComM_StepAddCfg[3] = 
{
  {0,   10,   10},   /*��������,��������,��Ӧ����*/
  {11,  30,   2 },
  {31,  100,  1 }
};

const  ComM_StepCfgType   ComM_StepSubCfg[3] = 
{
  {0,   70,    1},   /*��������,��������,��Ӧ����*/
  {71,  90,    2},
  {91,  100,  10}
};

const  ComM_DevCfgType    ComM_DevCfg[2] = 
{
  {CAN_CONTROLLER_0, TRUE,  3, &ComM_StepAddCfg[0], 2000ul},
  {CAN_CONTROLLER_1, FALSE, 3, &ComM_StepSubCfg[0], 2000ul}
};

/*�����������ñ�����CanIfģ��������һ��(GroupId��ControllerId)*/
const  ComM_GroupCfgType ComM_GroupCfg[1] = 
{
	{
		0u,  				/*������ID��*/
		50u, 				/*ƽ����ƽ��ֵ*/
		1u,					/*ƽ����ƽ����ֵ*/
		99,     			/*ƽ����ƽ����ֵ*/ 
		CAN_CONTROLLER_0,	/*�����鿪��Ĭ����������*/
		2u,					/*�������а����Ŀ���������*/				
		&ComM_DevCfg[0]    	/*���������������������ʼ��ַ*/
	}
};

const ComM_CfgType   ComM_Cfg = 
{
	2u,						/*ģ��֧�ֵĿ���������*/
	&ComM_DevCfg[0],
	1u,						/*ģ��֧�ֵ�����������*/
	&ComM_GroupCfg[0]
};










