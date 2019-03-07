/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名        : Compile.h
* 功能描述      : 基础软件平台宏定义头文件(.h)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2015/10/27       chenms             重构
**------------------------------------------------------------------------------------------------*/
#ifndef  _STD_TYPE_H_
#define  _STD_TYPE_H_

/***********************************/
#include "Platform_Types.h"
#include "Compile.h"
#include "ComStack_Types.h"

/***********************************/
#define E_NOT_OK		0x00u
#define E_OK			0x01u
#define E_TIMEOUT		0x0Au


#define STD_LOW			0x00u
#define STD_HIGH		0x01u

#define STD_IDLE		0x00u   /* Logical state idle  */
#define STD_ACTIVE		0x01u   /* Logical state   active */

#define	STD_OFF		  	0x00u
#define	STD_ON		  	0x01u

#ifndef	FALSE
#define	FALSE			0u
#endif

#ifndef	TRUE
#define	TRUE			1u
#endif

#define NULL_PTR    ((void *)0)

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/*
 * This type can be used as standard API return type which is shared between the 
 * RTE and the BSW modules.
 * 0x02-0x3F used for user specific errors, 0x40-0xFF used for RTE 
 */ 
typedef uint8 Std_ReturnType;





#endif