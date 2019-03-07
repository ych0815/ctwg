/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Com_Protocol.h
* ��������  : ͨѶģ��Э�����ͷ�ļ�(Com_Protocol.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2017/5/25       chenms            	  New
**------------------------------------------------------------------------------------------------*/
#ifndef  _COM_PROTOCOL_H_
#define  _COM_PROTOCOL_H_


/**************************************
              	ͷ�ļ�
 **************************************/
#include "Com_Cfg.h"
#include "Com_CfgType.h"

/**************************************
             	CAN�������Ͷ���
 **************************************/
/*��չ֡ID���ݽṹ*/
typedef union
{
	uint32	ExtId;
	struct
	{
		uint8 FrameType :5; 	/*ID28~ID24:֡���� */
		uint8 Reserve0  :3; 	/*ID31~ID29:����   */
		uint8 DestAddr  :5; 	/*ID20~ID16:Ŀ�ĵ�ַ*/
		uint8 Reserve1  :3; 	/*ID23~ID21:����   */
		uint8 SourceAddr:5; 	/*ID12~ID8 :Դ��ַ */
		uint8 Reserve2  :3; 	/*ID15~ID13:����   */
		uint8 heatbeatCount:8; 	/*ID7~ID0  :��������,ȡֵ��Χ:0~255*/
	}bit;
}Com_ProtocolIdType;

/*�忨��Ϣ���ݽṹ*/
typedef struct board_info
{
	uint8 hearBeatCnt; 					/**brief �����ź� 0~255 */
	union
	{
		uint16 hardwareVer;				/**brief Ӳ���汾*/
		struct
		{
			uint8 hardwareMainVer; 		/**brief Ӳ�����汾�� */
			uint8 hardwareMinorVer; 	/**brief Ӳ���ΰ汾�� */			
		}bytes;	
	}word1;

	union
	{
		uint16 softwareVer;				/**brief ����汾*/
		struct
		{
			uint8 softwareMainVer; 		/**brief ������汾�� */
			uint8 softwareMinorVer;     /**brief ����ΰ汾�� */			
		}bytes;
	}word2;
	
	union
	{
		uint8 val;
		struct
		{
			uint8 reserve1			:2;		/**brief Ԥ�� */
			uint8 reserve0			:2;		/**brief Ԥ�� */
			uint8 boardCan2ErrSta	:2;		/**brief �忨CAN2����״̬ 1��ʾ���� 2��ʾ����*/
			uint8 boardCan1ErrSta	:2;		/**brief �忨CAN1����״̬ 1��ʾ���� 2��ʾ����*/
		}bits;
	}Byte5;
}BOARD_INFO;

/*�ɼ�ģ��״̬���ݽṹ*/
typedef struct col_module_sta
{
	union 
	{
		uint8 val;
		struct 
		{
			uint8 moduleWorkSta		:4;		/**brief �ɼ�ģ�鹤��״̬*/
			uint8 moduleType		:4;		/**brief �ɼ�ģ������ */
		}bits;
	}Byte0;


	uint8 moduleNum;				/**brief �ɼ�ģ���� */

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2LightErrSta	:1;		/*brief ���2��Դ����״̬ */
			uint8 cam2LightCtrl		:1;		/*brief ���2��Դ�������� */
			uint8 cam1CamErrSta 	:1;		/*brief ���1�������״̬(Ԥ��) */
			uint8 cam1CamCtrl 		:1;		/*brief ���1����������� */
			uint8 cam1LightErrSta 	:1;		/*brief ���1��Դ����״̬ */
			uint8 cam1LightCtrl 	:1;		/*brief ���1��Դ�������� */
			uint8 moduleWorkModel 	:2;		/*brief �ɼ�ģ�鹤��״̬ */
		}bits;
	}Byte2;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam1CCFanErrSta 	:1;		/*brief ���1�������ȹ���״̬ */
			uint8 cam1CCFanOpenCtrl :1;		/*brief ���1�������ȿ������� */
			uint8 cam3CamErrSta 	:1;		/*brief ���3�������״̬(Ԥ��) */
			uint8 cam3CamCtrl 		:1;		/*brief ���3����������� */
			uint8 cam3LightErrSta 	:1;		/*brief ���3��Դ����״̬ */
			uint8 cam3LightCtrl 	:1;		/*brief ���3��Դ�������� */
			uint8 cam2CamErrSta 	:1;		/*brief ���2�������״̬(Ԥ��) */
			uint8 cam2CamCtrl 		:1;		/*brief ���2����������� */		
		}bits;
	}Byte3;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2SRFanOpenCtrl :1; 	/*brief ���2ɢ�ȷ��ȿ������� */
			uint8 cam1SRFan2ErrSta 	:1;		/*brief ���1ɢ�ȷ���2����״̬ */
			uint8 cam1SRFan1ErrSta 	:1;		/*brief ���1ɢ�ȷ���1����״̬ */
			uint8 cam1SRFanOpenCtrl :1; 	/*brief ���1ɢ�ȷ��ȿ������� */
			uint8 cam3CCFanErrSta 	:1;		/*brief ���3�������ȹ���״̬ */
			uint8 cam3CCFanOpenCtrl :1;		/*brief ���3�������ȿ������� */
			uint8 cam2CCFanErrSta 	:1;		/*brief ���2�������ȹ���״̬ */
			uint8 cam2CCFanOpenCtrl :1;		/*brief ���2�������ȿ������� */	
		}bits;
	}Byte4;

	union
	{
		uint8 val;
		struct
		{
			uint8 camDoorSta		:2;		/*brief ������״̬ */
			uint8 waterAlarm		:1;		/*brief ˮλ���� */
			uint8 cam3SRFan2ErrSta 	:1;		/*brief ���3ɢ�ȷ���2����״̬ */
			uint8 cam3SRFan1ErrSta 	:1;		/*brief ���3ɢ�ȷ���1����״̬ */
			uint8 cam3SRFanOpenCtrl :1; 	/*brief ���3ɢ�ȷ��ȿ������� */
			uint8 cam2SRFan2ErrSta 	:1;		/*brief ���2ɢ�ȷ���2����״̬ */
			uint8 cam2SRFan1ErrSta 	:1;		/*brief ���2ɢ�ȷ���1����״̬ */		
		}bits;
	}Byte5;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:1;		/*brief Ԥ�� */
			uint8 reserve1			:1;		/*brief Ԥ�� */
			uint8 reserve0			:1;		/*brief Ԥ�� */
			uint8 boxSRFanOpenCtrl	:1;		/*brief ����ɢ�ȷ��ȿ������� */
			uint8 heaterErrSta		:1;		/*brief	����������״̬(Ԥ��) */
			uint8 heaterSupSta		:1;		/*brief ����������״̬(Ԥ��)*/
			uint8 camDoorCloseCtrl 	:1;		/*brief	�����Źرտ��� */
			uint8 camDoorOpenCtrl	:1;		/*brief �����ſ������� */		
		}bits;
	}Byte6;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve3; 				/*brief Ԥ�� */
		}bits;
	}Byte7;	
}COL_MODULE_STA;

/*�豸�����������ָ�����ݽṹ*/
typedef struct ctrl_cmd
{
	union
	{
		uint8 val;
		struct
		{
			uint8 ccOpenOrClose		:2;		/*������/��ָ��*/
			uint8 doorOpenOrClose 	:2;		/*����/����ָ��*/
			uint8 localOrRemote		:2;		/*����/Զ��ָ��*/
			uint8 runOrService 		:2;		/*����/ά��ָ��*/
		}bits;
	}Byte0;
	
	union
	{
		uint8 val;
		struct
		{
			uint8 mzOpenOrClose		:2;		/*����/��ָ��*/
			uint8 xzOpenOrClose		:2;		/*����/��ָ��*/
			uint8 heatOpenOrClose	:2;		/*���ȿ�/��ָ��(Ԥ��)*/
			uint8 srOpenOrClose		:2;		/*ɢ�ȿ�/��ָ��*/
		}bits;
	}Byte1;
		
	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:2;		/*Ԥ��*/
			uint8 reserve1			:2;		/*Ԥ��*/
			uint8 reserve0			:2;		/*Ԥ��*/
			uint8 simuOpenOrClose	:2;		/*ģ�⿪/��ָ��*/
		}bits;
	}Byte2;

}CTRL_CMD;

/*�������ݽṹ*/
typedef struct fun_stru
{
	union
	{
		uint8 val;
		struct
		{
			uint8 bit1_0 :2;
			uint8 bit3_2 :2;
			uint8 bit5_4 :2;
			uint8 bit7_6 :2;
		}bits;
	}Byte;
}FUN_STRU;

/**************************************
             	ETH�������Ͷ���
 **************************************/
typedef struct ctrl_board_info
{
	uint8 board_heartBeat;				/*�ɼ�ģ����ư������ź�*/
	uint16 board_softwareVer;			/*�ɼ�ģ����ư�����汾*/
	uint16 board_hardwareVer;			/*�ɼ�ģ����ư�Ӳ���汾*/

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve0 			:2;	/*Ԥ��*/
			uint8 board_Can2ErrSta 	:2;	/*�ɼ�ģ����ư�CAN2����״̬*/
			uint8 board_Can1ErrSta 	:2; /*�ɼ�ģ����ư�CAN2����״̬*/
			uint8 board_ErrSta		:2;	/*�ɼ�ģ����ư����״̬*/
		}bits;
	}Byte3; 
}CTRL_BOARD_INFO;


typedef struct col_module_sta_err_info
{
	COL_MODULE_STA _col_module_sta;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2LightErrSta	:2;		/*brief ���2��Դ����״̬ */
			uint8 cam2CamErrSta 	:2;		/*brief ���2�������״̬(Ԥ��) */
			uint8 cam1LightErrSta	:2;		/*brief ���1��Դ����״̬ */
			uint8 cam1CamErrSta 	:2;		/*brief ���1�������״̬(Ԥ��) */
		}bits;	
	}Byte8;

	union
	{
		uint8 val;
		struct
		{
			uint8 cam2CCFanErrSta 	:2;		/*brief ���2�������ȹ���״̬ */
			uint8 cam1CCFanErrSta 	:2;		/*brief ���1�������ȹ���״̬ */
			uint8 cam3LightErrSta	:2;		/*brief ���3��Դ����״̬ */
			uint8 cam3CamErrSta 	:2;		/*brief ���3�������״̬(Ԥ��) */
		}bits;	
	}Byte9;

    union
	{
		uint8 val;
		struct
		{
			uint8 cam2SRFan1ErrSta 	:2;		/*brief ���2ɢ�ȷ���1����״̬ */
			uint8 cam1SRFan2ErrSta 	:2;		/*brief ���1ɢ�ȷ���2����״̬ */
			uint8 cam1SRFan1ErrSta 	:2;		/*brief ���1ɢ�ȷ���2����״̬ */
			uint8 cam3CCFanErrSta 	:2;		/*brief ���2�������ȹ���״̬ */
		}bits;	
	}Byte10;

	union
	{
		uint8 val;
		struct
		{
			uint8 camDoorErrSta		:2;		/*brief �����Ź���״̬ */
			uint8 cam3SRFan2ErrSta 	:2;		/*brief ���3ɢ�ȷ���2����״̬ */
			uint8 cam3SRFan1ErrSta 	:2;		/*brief ���3ɢ�ȷ���1����״̬ */ 
			uint8 cam2SRFan2ErrSta 	:2;		/*brief ���2ɢ�ȷ���2����״̬ */
		}bits;	
	}Byte11;

	union
	{
		uint8 val;
		struct
		{
			uint8 reserve2			:2; 	/*brief Ԥ�� */
			uint8 reserve1			:2; 	/*brief Ԥ�� */
			uint8 reserve0			:2; 	/*brief Ԥ�� */
			uint8 waterAlarm		:2;		/*brief ˮλ���� */ 
		}bits;	
	}Byte12;			
}COL_MODULE_STA_ERR_INFO;

/**************************************
             	�궨��
 **************************************/
/**************************FRAME TYPE**************************/ 
#define FRAME_TYPE_SIGCOLBOARD_COl            1   /*�źŲɼ���ɼ�����*/
#define FRAME_TYPE_EQU_ROOM_CTRL_BORAD_CRL 	  2   /*�豸����������Ʊ���*/
#define FRAME_TYPE_COL_MODULE_STA             3   /*�ɼ�ģ��״̬����*/
#define	FRAME_TYPE_GPKZX_STATEMONI            4   /*���Կ�����״̬��ⱨ��*/
#define FRAME_TYPE_BOARD_INFO		          5	  /*�忨��Ϣ����*/ 

/**************************ADDR**************************/
#define ADDR_EQUIPMENT_ROOM_HOST_CTRL_BOARD   1   /*�豸�����ذ��ַ*/
#define ADDR_SIGNAL_COLLECT_BOARD             2   /*�źŲɼ����ַ*/
#define ADDR_BOTTOM_MODULE_CTRL_BOARD         3   /*������ư��ַ*/
#define ADDR_SIDE_MODULE_CTRL_BOARD           4   /*������ư��ַ*/
#define ADDR_TOP_MODULE_CTRL_BOARD            5   /*�������ư��ַ*/
#define ADDR_BROADCAST                        31  /*�㲥��ַ*/

/**************************BOARD INFO**************************/
#define HARDWARE_MAIN_VERSION				  0	  /*Ӳ�����汾��*/
#define HARDWARE_MINOR_VERSION  			  1   /*Ӳ���ΰ汾��*/

#define SOFTWARE_MAIN_VERSION				  0	  /*������汾��*/
#define SOFTWARE_MINOR_VERSION  			  1   /*����ΰ汾��*/
/**************************************
             	��������
 **************************************/
extern	Std_ReturnType Com_ReceSigColBoardCol(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceColModuleSta(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceBoardInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_ReceGPKZXStaMoni(const PduInfoType *pPduInfo);

extern	Std_ReturnType Com_TransmitEquRoomCtrlBoardCtrlInfo(const PduInfoType *pPduInfo);
extern	Std_ReturnType Com_TransmitBoardInfo(const PduInfoType *pPduInfo);
#endif

