#if  0
/***********************************************************************************************//*!
 * \file
 * \brief �����������
 * \version 0.2.0
 * \date 2014.02.17
 *
 * ������ɾ�̬ע��Ͷ�̬ע���û�������ɽ���ִ���û����
 *
 \verbatim
  --------------------------Copyright (c)�ɶ��˴�Ƽ��ɷ����޹�˾---------------------------------
 File name: cmd.c
              +----- (NEW | MODify | ADD | DELete)
              |
  ver         |   date(yy/mm/dd)  name               descant
 ----------+----+---------------+-----------+-----------------------------------------------------
  0.1.0      NEW  2012/08/10      ���Ʋ�      ��ʼ�汾
  0.1.1      MOD  2013/01/24      ���Ʋ�      ɾ������������
  0.2.0      MOD  2014/02/17      ���Ʋ�      ����dspic6012A�Ĵ���������������Ӧ���޶�
  0.3.0      MOD  2014/03/25      ���Ʋ�      �����ظ�ִ����һ������Ĺ���
 -------------------------------------------------------------------------------------------------
 \endverbatim
 **************************************************************************************************/

#define MDE_CMD_C

/*=================================================================================================
*----ͷ�ļ�����
=================================================================================================*/
#include "drv_sci.h"
#include "mde.h"




/*=================================================================================================
*----ȫ�ֱ�������
=================================================================================================*/ 
const char mde_cmd_help_str[] =
"��������. \r\n"
"��ʽ: help [command] \r\n"
"�޲���     ��ʾ�����б�; \r\n"
"[command]  ��ʾ�������ϸ������Ϣ. \r\n";

/* �����б� */
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
 * \brief   �Ƚ��ַ�������
 *
 * �Ƚ��ַ���
 *
 * \param   n1  �ַ���1
 * \param   n2  �ַ���2
 * \return  FALSE  �ַ��������
            TRUE   �ַ������
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
 * \brief   �ַ��������ַ����ȼ��㺯��
 *
 * �����ַ������г���
 *
 * \param   str_p  �ַ���
 * \return  �ַ������г���
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
 * \brief   �ַ����ַ����ȼ��㺯��
 *
 * �����ַ����ַ�����
 *
 * \param   str_p  �ַ���
 * \return  �ַ�������
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
 * \brief   ������ʾ��������
 *
 * ��ʾ������ʾ��
 *
 * \return ��ȷ����0
 *****************************************************************************/
INT16U mde_cmd_prompt(void)
{
    INT16U len = 0;

    
    return Drv_Sci_Write("YUNDA>", len, 10);
}




/***************************************************************************//*!
 * \brief   �����д������
 *
 * �������,�������,�����س�����Ϊһ������
 *
 * \return  ��ȷ����0
 *****************************************************************************/
INT16U mde_cmd_echo(void)
{
    static char RxBuf[MDE_CMD_BUF_SIZE] = {0, 0};    //���������洢��
    static char ParseBuf[MDE_CMD_BUF_SIZE] = {0, 0}; //���������洢��
    static INT8U CmdEnd = 0;
    static INT8U buf_i = 0;                //�����洢����ָ��
    static INT8U dev_state = 0;            //�豸��״̬
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
        case MDE_CMD_VT100_ERR:        //����
            break;
            
        case MDE_CMD_VT100_TIMEOUT:    //��ʱ
            break;
            
        case MDE_CMD_VT100_NONE:       //û��VT100����
            if ((chr == 0x0A) || (chr == 0x0D))
            {//�س�����
                CmdEnd = 1;
                
                RxBuf[buf_i] = 0;
                
                errno = Drv_Sci_Write("\r\n", 0, 10);
                
                strcpy(ParseBuf, RxBuf);
                
                error = mde_cmd_parse(ParseBuf, &cmd_return);  /* ����������� */
                
                if(error == MDE_CMD_ERRNO_ECMD)
                {
                    errno = Drv_Sci_Write("Invalid Command! \r\n", 0, 10);
                }
            
                errno = mde_cmd_prompt();
                buf_i = 0;
            }
            else if ((INT8U)chr == 0x08)
            {//�˸�
                if (buf_i != 0)
                {
                    buf_i--;
                    errno = Drv_Sci_Write("\b \b", 0, 10);
                }
            }
            else if(((INT8U)chr >= 0x20) && ((INT8U)chr <= 0x7F))
            {//ASCII���п���ʾ���ַ�
                CmdEnd = 0;
                if (buf_i < (MDE_CMD_BUF_SIZE-1))
                {
                    RxBuf[buf_i] = chr;
                    buf_i++;
                    errno = Drv_Sci_Write(&chr, 1, 10);
                }
            }
            break;
            
        case MDE_CMD_VT100_WORK:       //���ڽ���VT100����
            ;
            break;
            
        case MDE_CMD_VT100_UP:         //����
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
 * \brief   ����ע�ắ��
 *
 * �豸���ʼ��
 *
 * \param   name_p  ָ���������ַ���
 * \param   help_p  ָ����������ַ���
 * \param   mde_cmd_fun ����ִ�к���
 * \return  MDE_CMD_ERRNO_NOERR  û�д���
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
        {//����������뵽�����б�ĩβ
            mde_cmd_tab[i].name_p  = name_p;
            mde_cmd_tab[i].help_p  = help_p;
            mde_cmd_tab[i].cmd_fun = cmd_fun;
            error = MDE_CMD_ERRNO_NOERR;
            break;
        }
        else if (mde_cmd_compare(name_p, mde_cmd_tab[i].name_p))
        {//�����ע������������������б����Ѿ�����, ����ʾ����
            error = MDE_CMD_ERRNO_ECMD;
            break;
        }
    }
    return error;
}


/***************************************************************************//*!
 * \brief   �����������
 *
 * ���������ַ���, ִ����Ӧ����
 *
 * \param   buf_p  �����л���
 * \param   cmd_return_p �����ֵ
 * \return  MDE_CMD_ERRNO_NOERR  û�д���
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
 * \brief   VT100�����������
 *
 * ����VT100����
 *
 * \param   chr  �ַ�
 * \param   timeout ��ʱʱ��Ƭ
 * \return  ��������
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
 * \brief   �����������
 *
 * �����������
 *
 * \param   argc    �����������
 * \param   argv    ��������ַ�������
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
                (void)Drv_Sci_Write("û���������İ�����Ϣ! \r\n", 0, 10);
	        }
            break;
        default:
            (void)Drv_Sci_Write("�����������! \r\n", 0, 10);
            return 1;
    }
    return 0;
}


#undef MDE_CMD_C
#endif
