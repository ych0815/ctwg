/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���        : Compile.h
* ��������      : ͨѶջ�������Ͷ���ͷ�ļ�(.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2015/10/27       chenms             �ع�
**------------------------------------------------------------------------------------------------*/

#ifndef _COMSTACK_TYPES_H_
#define _COMSTACK_TYPES_H_

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"


/*=======[M A C R O S]========================================================*/
#define  CAN_CONTROLLER_0	(0u)	/* ECU��[Ƭ��]������0 */
#define  CAN_CONTROLLER_1	(1u)	/* ECU��[Ƭ��]������1 */
#define  CAN_CONTROLLER_2	(2u)	/* ECU��[Ƭ��]������2 */
#define  CAN_CONTROLLER_3	(3u)	/* ECU��[Ƭ��]������3 */
#define  CAN_CONTROLLER_4	(4u)	/* ECU��[Ƭ��]������4 */
#define  CAN_CONTROLLER_5	(5u)	/* ECU��[Ƭ��]������5 */


/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef uint32   PduIdType;    	 /*pdu Id*/

typedef uint8    PduLengthType; /*pdu length*/

typedef struct  
{
   	PduIdType     PduId;
   	PduLengthType PduLength;
   	uint8         PduData[8];
}PduInfoType;

#endif /* end of COMSTACK_TYPES_H */

/*=======[E N D   O F   F I L E]==============================================*/
