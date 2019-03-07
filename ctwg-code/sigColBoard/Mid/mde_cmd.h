#if 0
/***********************************************************************************************//*!
 * \file
 * \brief 命令解析程序.h文件
 * \version 0.2.0
 * \date 2014.02.17
 *
 * 本程序可静态注册和动态注册用户命令，并可解析执行用户命令。
 *
 \verbatim
  --------------------------Copyright (c)成都运达科技股份有限公司---------------------------------
 File name: cmd.h
              +----- (NEW | MODify | ADD | DELete)
              |
  ver         |   date(yy/mm/dd)  name               descant
 ----------+----+---------------+-----------+-----------------------------------------------------
  0.1.0      NEW  2012/08/10      段云波      初始版本
  0.1.1      MOD  2013/01/24      段云波      删除测试用命令
  0.2.0      MOD  2014/02/17      段云波      基于dspic6012A的串口驱动程序做适应性修订
  0.3.0      MOD  2014/03/25      段云波      增加重复执行上一次命令的功能
 -------------------------------------------------------------------------------------------------
 \endverbatim
 **************************************************************************************************/

#ifndef MDE_CMD_H
#define MDE_CMD_H


/*=================================================================================================
*----头文件包含
=================================================================================================*/
#include "os_cpu.h"

/*=================================================================================================
*----宏定义
=================================================================================================*/

#define MDE_CMD_STATE_NONE  0
#define MDE_CMD_STATE_CHAR  1
#define MDE_CMD_STATE_END   2
#define MDE_CMD_STATE_ERR   3

#define MDE_CMD_ERRNO_NOERR 0x00  //没有错误
#define MDE_CMD_ERRNO_NOMEM 0x01  //没有足够的内存空间
#define MDE_CMD_ERRNO_EPMT  0x02  //参数错误
#define MDE_CMD_ERRNO_ECMD  0xff  //命令字错误

#define MDE_CMD_ARG_MAX     10    //命令行最多参数个数

/* 命令行BUF大小 */
#define MDE_CMD_BUF_SIZE    128


/* VT100特殊字符 */
#define MDE_CMD_VT100_CHR_BASE  0x1B
#define MDE_CMD_VT100_CHR_EXT   0x5B

/* VT100解析返回命令 */
#define MDE_CMD_VT100_ERR       0       //错误
#define MDE_CMD_VT100_TIMEOUT   1       //超时
#define MDE_CMD_VT100_NONE      2       //没有VT100命令
#define MDE_CMD_VT100_WORK      3       //正在解析VT100命令
#define MDE_CMD_VT100_UP        4       //向上


/* VT100解析状态 */
#define MDE_CMD_VT100_ST0       0
#define MDE_CMD_VT100_ST1       1
#define MDE_CMD_VT100_ST2       2




/*=================================================================================================
*----数据类型声明
=================================================================================================*/ 

typedef struct
{
    const char *name_p;
    const char *help_p;
    INT16U (*cmd_fun)(INT16U argc, char **argv);
} mde_cmd_ccb_t;




/*=================================================================================================
*----函数声明
=================================================================================================*/ 

/***************************************************************************//*!
 * \brief   命令行处理程序
 *
 * 命令回显,命令解析,遇到回车键即为一个命令
 *
 * \return  正确返回0
 *****************************************************************************/
INT16U mde_cmd_echo(void);




/***************************************************************************//*!
 * \brief   比较字符串函数
 *
 * 比较字符串
 *
 * \param   n1  字符串1
 * \param   n2  字符串2
 * \return  0  字符串不相等
            1  字符串相等
 *****************************************************************************/
INT16U mde_cmd_compare(const char *n1, const char *n2);




/***************************************************************************//*!
 * \brief   字符串首行长度计算函数
 *
 * 计算字符串首行长度
 *
 * \param   str_p  字符串
 * \return  字符串首行长度
 *****************************************************************************/
INT16U mde_cmd_linlen(const char *str_p);




/***************************************************************************//*!
 * \brief   字符串长度计算函数
 *
 * 计算字符串长度
 *
 * \param   str_p  字符串
 * \return  字符串长度
 *****************************************************************************/
INT16U mde_cmd_strlen(const char *str_p);




/***************************************************************************//*!
 * \brief   命令提示符处理函数
 *
 * 显示命令提示符
 *
 * \return 正确返回0
 *****************************************************************************/
INT16U mde_cmd_prompt(void);




/***************************************************************************//*!
 * \brief   命令注册函数
 *
 * 设备表初始化
 *
 * \param   name_p  指向命令名字符串
 * \param   help_p  指向命令帮助字符串
 * \param   cmd_fun 命令执行函数
 * \return  MDE_CMD_ERRNO_NOERR  没有错误
 *****************************************************************************/
INT16U mde_cmd_register( const char *name_p,
                         	  const char *help_p,
                         	  INT16U (*cmd_fun)(INT16U argc, char **argv)
                       );




/***************************************************************************//*!
 * \brief   命令解析函数
 *
 * 解析命令字符串, 执行相应命令
 *
 * \param   buf_p  命令行缓存
 * \param   cmd_return_p 命令返回值
 * \return  MDE_CMD_ERRNO_NOERR  没有错误
 *****************************************************************************/
INT16U mde_cmd_parse(char *buf_p, INT16U *return_p);




/***************************************************************************//*!
 * \brief   VT100命令解析函数
 *
 * 解析VT100命令
 *
 * \param   chr  字符
 * \param   timeout 超时时间片
 * \return  控制命令
 *****************************************************************************/
INT16U mde_cmd_Vt100Parse(char *chr_p, INT16U timeout);




/***************************************************************************//*!
 * \brief   帮助命令处理函数
 *
 * 处理帮助命令
 *
 * \param   argc    命令及参数数量
 * \param   argv    命令及参数字符串数组
 * \return  
 *****************************************************************************/
INT16U mde_cmd_help(INT16U argc, char **argv);


#endif /* #ifndef MDE_CMD_H */
#endif
