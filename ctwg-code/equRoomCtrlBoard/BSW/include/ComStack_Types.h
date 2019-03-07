/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Compile.h
* 功能描述      : 通讯栈数据类型定义头文件(.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2015/10/27       chenms             重构
**------------------------------------------------------------------------------------------------*/

#ifndef _COMSTACK_TYPES_H_
#define _COMSTACK_TYPES_H_

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"


/*=======[M A C R O S]========================================================*/
#define  CAN_CONTROLLER_0	(0u)	/* ECU级[片内]控制器0 */
#define  CAN_CONTROLLER_1	(1u)	/* ECU级[片内]控制器1 */
#define  CAN_CONTROLLER_2	(2u)	/* ECU级[片内]控制器2 */
#define  CAN_CONTROLLER_3	(3u)	/* ECU级[片内]控制器3 */
#define  CAN_CONTROLLER_4	(4u)	/* ECU级[片内]控制器4 */
#define  CAN_CONTROLLER_5	(5u)	/* ECU级[片外]控制器5 */


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
