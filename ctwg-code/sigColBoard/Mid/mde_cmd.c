#if  0
/***********************************************************************************************//*!
 * \file
 * \brief 命令解析程序
 * \version 0.2.0
 * \date 2014.02.17
 *
 * 本程序可静态注册和动态注册用户命令，并可解析执行用户命令。
 *
 \verbatim
  --------------------------Copyright (c)成都运达科技股份有限公司---------------------------------
 File name: cmd.c
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

#define MDE_CMD_C

/*=================================================================================================
*----头文件包含
=================================================================================================*/
#include "drv_sci.h"
#include "mde.h"




/*=================================================================================================
*----全局变量声明
=================================================================================================*/ 
const char mde_cmd_help_str[] =
"帮助命令. \r\n"
"格式: help [command] \r\n"
"无参数     显示命令列表; \r\n"
"[command]  显示命令的详细帮助信息. \r\n";

/* 命令列表 */
mde_cmd_ccb_t mde_cmd_tab[] =
{
    {"help", mde_cmd_help_str, mde_cmd_help},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL},
    {NULL,   NULL,             NULL}
};

char *mde_cmd_arg_p[MDE_CMD_ARG_MAX];


/***************************************************************************//*!
 * \brief   比较字符串函数
 *
 * 比较字符串
 *
 * \param   n1  字符串1
 * \param   n2  字符串2
 * \return  FALSE  字符串不相等
            TRUE   字符串相等
 *****************************************************************************/
INT16U mde_cmd_compare(const char *n1, const char *n2)
{
    if ((n1 == NULL) || (n2 == NULL))
    {
        return 0;
    }
    while (*n1 || *n2)
    {
        if (*n1++ != *n2++)
        {
            return 0;
        }
    }
    return 1;
}


/***************************************************************************//*!
 * \brief   字符串首行字符长度计算函数
 *
 * 计算字符串首行长度
 *
 * \param   str_p  字符串
 * \return  字符串首行长度
 *****************************************************************************/
INT16U mde_cmd_linlen(const char *str_p)
{
    INT16U len = 0;
    
    if (str_p == NULL)
    {
        return 0;
    }
    
    while ((*str_p != '\r') && (*str_p != '\n') && (*str_p != 0))
    {
        str_p++;
        len++;
    }
    return len;
}


/***************************************************************************//*!
 * \brief   字符串字符长度计算函数
 *
 * 计算字符串字符长度
 *
 * \param   str_p  字符串
 * \return  字符串长度
 *****************************************************************************/
INT16U mde_cmd_strlen(const char *str_p)
{
    INT16U len = 0;
    
    if (str_p == NULL)
    {
        return 0;
    }
    
    while(*str_p)
    {
        str_p++;
        len++;
    }
    
    return len;
}




/***************************************************************************//*!
 * \brief   命令提示符处理函数
 *
 * 显示命令提示符
 *
 * \return 正确返回0
 *****************************************************************************/
INT16U mde_cmd_prompt(void)
{
    INT16U len = 0;

    
    return Drv_Sci_Write("YUNDA>", len, 10);
}




/***************************************************************************//*!
 * \brief   命令行处理程序
 *
 * 命令回显,命令解析,遇到回车键即为一个命令
 *
 * \return  正确返回0
 *****************************************************************************/
INT16U mde_cmd_echo(void)
{
    static char RxBuf[MDE_CMD_BUF_SIZE] = {0, 0};    //接收命令缓冲存储区
    static char ParseBuf[MDE_CMD_BUF_SIZE] = {0, 0}; //解析命令缓冲存储区
    static INT8U CmdEnd = 0;
    static INT8U buf_i = 0;                //命令缓冲存储工作指针
    static INT8U dev_state = 0;            //设备打开状态
    INT16U Vt100Cmd;
    INT16U error;
    INT16U cmd_return;
    INT16U errno;
    char chr;
    
    
    if (dev_state == 0)
    {
        mde_cmd_prompt();
        dev_state = 1;
    }
    
    Vt100Cmd = mde_cmd_Vt100Parse(&chr, 10);
    
    switch(Vt100Cmd)
    {
        case MDE_CMD_VT100_ERR:        //错误
            break;
            
        case MDE_CMD_VT100_TIMEOUT:    //超时
            break;
            
        case MDE_CMD_VT100_NONE:       //没有VT100命令
            if ((chr == 0x0A) || (chr == 0x0D))
            {//回车换行
                CmdEnd = 1;
                
                RxBuf[buf_i] = 0;
                
                errno = Drv_Sci_Write("\r\n", 0, 10);
                
                strcpy(ParseBuf, RxBuf);
                
                error = mde_cmd_parse(ParseBuf, &cmd_return);  /* 调用命令解析 */
                
                if(error == MDE_CMD_ERRNO_ECMD)
                {
                    errno = Drv_Sci_Write("Invalid Command! \r\n", 0, 10);
                }
            
                errno = mde_cmd_prompt();
                buf_i = 0;
            }
            else if ((INT8U)chr == 0x08)
            {//退格
                if (buf_i != 0)
                {
                    buf_i--;
                    errno = Drv_Sci_Write("\b \b", 0, 10);
                }
            }
            else if(((INT8U)chr >= 0x20) && ((INT8U)chr <= 0x7F))
            {//ASCII码中可显示的字符
                CmdEnd = 0;
                if (buf_i < (MDE_CMD_BUF_SIZE-1))
                {
                    RxBuf[buf_i] = chr;
                    buf_i++;
                    errno = Drv_Sci_Write(&chr, 1, 10);
                }
            }
            break;
            
        case MDE_CMD_VT100_WORK:       //正在解析VT100命令
            ;
            break;
            
        case MDE_CMD_VT100_UP:         //向上
            if (CmdEnd)
            {
                CmdEnd = 0;
                errno = Drv_Sci_Write(RxBuf, 0, 10);
                buf_i = mde_cmd_strlen(RxBuf);
            }
            break;
            
        default:
            ;
    }
    
    
    
    
    return 0;
}




/***************************************************************************//*!
 * \brief   命令注册函数
 *
 * 设备表初始化
 *
 * \param   name_p  指向命令名字符串
 * \param   help_p  指向命令帮助字符串
 * \param   mde_cmd_fun 命令执行函数
 * \return  MDE_CMD_ERRNO_NOERR  没有错误
 *****************************************************************************/
INT16U mde_cmd_register( const char *name_p,
                         const char *help_p,
                         INT16U (*cmd_fun)(INT16U argc, char **argv)
                       )
{
    INT16U i;
    INT16U error;
    
    if (NULL == name_p)
    {
        return MDE_CMD_ERRNO_EPMT;
    }
    
    error = MDE_CMD_ERRNO_NOMEM;
    for (i=0; i<(sizeof(mde_cmd_tab)/sizeof(mde_cmd_ccb_t)); i++)
    {
        if (NULL == mde_cmd_tab[i].name_p)
        {//将新命令加入到命令列表末尾
            mde_cmd_tab[i].name_p  = name_p;
            mde_cmd_tab[i].help_p  = help_p;
            mde_cmd_tab[i].cmd_fun = cmd_fun;
            error = MDE_CMD_ERRNO_NOERR;
            break;
        }
        else if (mde_cmd_compare(name_p, mde_cmd_tab[i].name_p))
        {//如果需注册的命令名字在命令列表中已经存在, 则提示错误
            error = MDE_CMD_ERRNO_ECMD;
            break;
        }
    }
    return error;
}


/***************************************************************************//*!
 * \brief   命令解析函数
 *
 * 解析命令字符串, 执行相应命令
 *
 * \param   buf_p  命令行缓存
 * \param   cmd_return_p 命令返回值
 * \return  MDE_CMD_ERRNO_NOERR  没有错误
 *****************************************************************************/
INT16U mde_cmd_parse(char *buf_p, INT16U *return_p)
{
    INT16U error;
    INT16U state=MDE_CMD_STATE_NONE;
    INT16U arg_i;
    INT16U i;
    INT16U len;
    
    
    if (buf_p == NULL)
    {
        return MDE_CMD_ERRNO_EPMT;
    }
    
    arg_i = 0;
    len = mde_cmd_strlen(buf_p) + 1;
    
    for (i=0; i<len; i++)
    {
        switch(state)
        {
            case MDE_CMD_STATE_NONE:
                if (buf_p[i] == ' ')
                {
                    buf_p[i] = 0;
                }
                else if (buf_p[i] == 0)
                {
                    state = MDE_CMD_STATE_END;
                }
                else
                {
                    if (arg_i < MDE_CMD_ARG_MAX)
                    {
                        mde_cmd_arg_p[arg_i++] = &buf_p[i];
                        state = MDE_CMD_STATE_CHAR;
                    }
                    else
                    {
                        state = MDE_CMD_STATE_ERR;
                    }
                }
                break;
            case MDE_CMD_STATE_CHAR:
                if (buf_p[i] == ' ')
                {
                    buf_p[i] = 0;
                    state = MDE_CMD_STATE_NONE;
                }
                else if (buf_p[i] == 0)
                {
                    state = MDE_CMD_STATE_END;
                }
                break;
            default:
                state = MDE_CMD_STATE_ERR;
        }
        if ((state == MDE_CMD_STATE_END) || (state == MDE_CMD_STATE_ERR))
        {
            break;
        }
    }
    
    if (MDE_CMD_STATE_END != state)
    {
        return MDE_CMD_ERRNO_ECMD;
    }
    
    if (arg_i < 1)
    {
        return MDE_CMD_ERRNO_NOERR;
    }
    
    error = MDE_CMD_ERRNO_ECMD;
    for (i=0; i<(sizeof(mde_cmd_tab)/sizeof(mde_cmd_ccb_t)); i++)
    {
        if (mde_cmd_compare(mde_cmd_arg_p[0], mde_cmd_tab[i].name_p))
        {
            if (NULL != mde_cmd_tab[i].cmd_fun)
            {
                *return_p = (mde_cmd_tab[i].cmd_fun)(arg_i, mde_cmd_arg_p);
                error = MDE_CMD_ERRNO_NOERR;
            }
            break;
        }
    }
    
    
    return error;
}




/***************************************************************************//*!
 * \brief   VT100命令解析函数
 *
 * 解析VT100命令
 *
 * \param   chr  字符
 * \param   timeout 超时时间片
 * \return  控制命令
 *****************************************************************************/
INT16U mde_cmd_Vt100Parse(char *chr_p, INT16U timeout)
{
    char   rxch;
    INT16U errno;
    INT16U ReturnNum = MDE_CMD_VT100_ERR;
    static INT8U state = MDE_CMD_VT100_ST0;
    static char buf[10];
    static INT16U BufOut = 0;
    static INT16U StrLen = 0;
    
    
    switch(state)
    {
         case MDE_CMD_VT100_ST0:
            if (StrLen)
            {
                *chr_p = buf[BufOut++];
                if (BufOut == StrLen)
                {
                    BufOut = 0;
                    StrLen = 0;
                }
                ReturnNum = MDE_CMD_VT100_NONE;
            }
            else
            {
                errno = Drv_Sci_Read( &rxch, 1u,timeout);
                if (errno)
                {
                    ReturnNum = MDE_CMD_VT100_TIMEOUT;
                }
                else
                {
                    if (rxch == MDE_CMD_VT100_CHR_BASE)
                    {
                        buf[StrLen++] = rxch;
                        state = MDE_CMD_VT100_ST1;
                        ReturnNum = MDE_CMD_VT100_WORK;
                    }
                    else
                    {
                        *chr_p = rxch;
                        ReturnNum = MDE_CMD_VT100_NONE;
                    }
                }
            }
            break;
            
         case MDE_CMD_VT100_ST1:
            errno = Drv_Sci_Read( &rxch, 1u, timeout);
            if (errno)
            {
                ReturnNum = MDE_CMD_VT100_TIMEOUT;
            }
            else
            {
                buf[StrLen++] = rxch;
                if (rxch == MDE_CMD_VT100_CHR_EXT)
                {
                    
                    state = MDE_CMD_VT100_ST2;
                    ReturnNum = MDE_CMD_VT100_WORK;
                }
                else
                {
                    state = MDE_CMD_VT100_ST0;
                    ReturnNum = MDE_CMD_VT100_WORK;
                }
            }
            break;
            
         case MDE_CMD_VT100_ST2:
            errno = Drv_Sci_Read( &rxch, 1u, timeout);
            if (errno)
            {
                ReturnNum = MDE_CMD_VT100_TIMEOUT;
            }
            else
            {
                buf[StrLen++] = rxch;
                state = MDE_CMD_VT100_ST0;
                if (rxch == 'A')
                {
                    BufOut = 0;
                    StrLen = 0;
                    ReturnNum = MDE_CMD_VT100_UP;
                }
                else
                {
                    ReturnNum = MDE_CMD_VT100_WORK;
                }
            }
            break;
            
         default:
            state = MDE_CMD_VT100_ST1;
            ReturnNum = MDE_CMD_VT100_ERR;
    }
    
    return ReturnNum;
}




/***************************************************************************//*!
 * \brief   帮助命令处理函数
 *
 * 处理帮助命令
 *
 * \param   argc    命令及参数数量
 * \param   argv    命令及参数字符串数组
 * \return  
 *****************************************************************************/
INT16U mde_cmd_help(INT16U argc, char **argv)
{
    INT16U i,j;
    INT16U comperr = 0;
    INT16U len,lenmax,spacelen;
    
    
    switch(argc)
    {
        case 1:
            lenmax = 0;
            for (i=0; i<(sizeof(mde_cmd_tab)/sizeof(mde_cmd_ccb_t)); i++)
            {
                len = mde_cmd_strlen(mde_cmd_tab[i].name_p);
                if (len == 0)
                {
                    break;
                }
                else if(lenmax < len)
                {
                    lenmax = len;
                }
            }
            
            lenmax += 2;
            
            for (i=0; i<(sizeof(mde_cmd_tab)/sizeof(mde_cmd_ccb_t)); i++)
            {
                if ((mde_cmd_tab[i].name_p != NULL) && (mde_cmd_tab[i].help_p != NULL))
                {
                    (void)Drv_Sci_Write((char *)mde_cmd_tab[i].name_p, 0, 10);
                    spacelen = lenmax - mde_cmd_strlen(mde_cmd_tab[i].name_p);
                    for (j=0; j<spacelen; j++)
                    {
                        (void)Drv_Sci_Write(" ", 0, 10);
                    }
                    len = mde_cmd_linlen(mde_cmd_tab[i].help_p);
                    (void)Drv_Sci_Write((char *)mde_cmd_tab[i].help_p, len, 10);
                    (void)Drv_Sci_Write("\r\n", 0, 10);
                }
            }
            break;
        case 2:
	        comperr = 1;
            for (i=0; i<(sizeof(mde_cmd_tab)/sizeof(mde_cmd_ccb_t)); i++)
            {
                if (mde_cmd_compare(mde_cmd_tab[i].name_p, argv[1]) && (mde_cmd_tab[i].help_p != NULL))
                {
                    (void)Drv_Sci_Write((char *)mde_cmd_tab[i].name_p, 0, 10);
                    (void)Drv_Sci_Write("\r\n", 0, 10);
                    (void)Drv_Sci_Write((char *)mde_cmd_tab[i].help_p, 0, 10);
		            comperr = 0;
                }
            }
            if (comperr)
	        {
                (void)Drv_Sci_Write("没有这个命令的帮助信息! \r\n", 0, 10);
	        }
            break;
        default:
            (void)Drv_Sci_Write("命令参数错误! \r\n", 0, 10);
            return 1;
    }
    return 0;
}


#undef MDE_CMD_C
#endif
