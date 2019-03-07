#if 0
/***********************************************************************************************//*!
 * \file
 * \brief �����������.h�ļ�
 * \version 0.2.0
 * \date 2014.02.17
 *
 * ������ɾ�̬ע��Ͷ�̬ע���û�������ɽ���ִ���û����
 *
 \verbatim
  --------------------------Copyright (c)�ɶ��˴�Ƽ��ɷ����޹�˾---------------------------------
 File name: cmd.h
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

#ifndef MDE_CMD_H
#define MDE_CMD_H


/*=================================================================================================
*----ͷ�ļ�����
=================================================================================================*/
#include "os_cpu.h"

/*=================================================================================================
*----�궨��
=================================================================================================*/

#define MDE_CMD_STATE_NONE  0
#define MDE_CMD_STATE_CHAR  1
#define MDE_CMD_STATE_END   2
#define MDE_CMD_STATE_ERR   3

#define MDE_CMD_ERRNO_NOERR 0x00  //û�д���
#define MDE_CMD_ERRNO_NOMEM 0x01  //û���㹻���ڴ�ռ�
#define MDE_CMD_ERRNO_EPMT  0x02  //��������
#define MDE_CMD_ERRNO_ECMD  0xff  //�����ִ���

#define MDE_CMD_ARG_MAX     10    //����������������

/* ������BUF��С */
#define MDE_CMD_BUF_SIZE    128


/* VT100�����ַ� */
#define MDE_CMD_VT100_CHR_BASE  0x1B
#define MDE_CMD_VT100_CHR_EXT   0x5B

/* VT100������������ */
#define MDE_CMD_VT100_ERR       0       //����
#define MDE_CMD_VT100_TIMEOUT   1       //��ʱ
#define MDE_CMD_VT100_NONE      2       //û��VT100����
#define MDE_CMD_VT100_WORK      3       //���ڽ���VT100����
#define MDE_CMD_VT100_UP        4       //����


/* VT100����״̬ */
#define MDE_CMD_VT100_ST0       0
#define MDE_CMD_VT100_ST1       1
#define MDE_CMD_VT100_ST2       2




/*=================================================================================================
*----������������
=================================================================================================*/ 

typedef struct
{
    const char *name_p;
    const char *help_p;
    INT16U (*cmd_fun)(INT16U argc, char **argv);
} mde_cmd_ccb_t;




/*=================================================================================================
*----��������
=================================================================================================*/ 

/***************************************************************************//*!
 * \brief   �����д�������
 *
 * �������,�������,�����س�����Ϊһ������
 *
 * \return  ��ȷ����0
 *****************************************************************************/
INT16U mde_cmd_echo(void);




/***************************************************************************//*!
 * \brief   �Ƚ��ַ�������
 *
 * �Ƚ��ַ���
 *
 * \param   n1  �ַ���1
 * \param   n2  �ַ���2
 * \return  0  �ַ��������
            1  �ַ������
 *****************************************************************************/
INT16U mde_cmd_compare(const char *n1, const char *n2);




/***************************************************************************//*!
 * \brief   �ַ������г��ȼ��㺯��
 *
 * �����ַ������г���
 *
 * \param   str_p  �ַ���
 * \return  �ַ������г���
 *****************************************************************************/
INT16U mde_cmd_linlen(const char *str_p);




/***************************************************************************//*!
 * \brief   �ַ������ȼ��㺯��
 *
 * �����ַ�������
 *
 * \param   str_p  �ַ���
 * \return  �ַ�������
 *****************************************************************************/
INT16U mde_cmd_strlen(const char *str_p);




/***************************************************************************//*!
 * \brief   ������ʾ����������
 *
 * ��ʾ������ʾ��
 *
 * \return ��ȷ����0
 *****************************************************************************/
INT16U mde_cmd_prompt(void);




/***************************************************************************//*!
 * \brief   ����ע�ắ��
 *
 * �豸����ʼ��
 *
 * \param   name_p  ָ���������ַ���
 * \param   help_p  ָ����������ַ���
 * \param   cmd_fun ����ִ�к���
 * \return  MDE_CMD_ERRNO_NOERR  û�д���
 *****************************************************************************/
INT16U mde_cmd_register( const char *name_p,
                         	  const char *help_p,
                         	  INT16U (*cmd_fun)(INT16U argc, char **argv)
                       );




/***************************************************************************//*!
 * \brief   �����������
 *
 * ���������ַ���, ִ����Ӧ����
 *
 * \param   buf_p  �����л���
 * \param   cmd_return_p �����ֵ
 * \return  MDE_CMD_ERRNO_NOERR  û�д���
 *****************************************************************************/
INT16U mde_cmd_parse(char *buf_p, INT16U *return_p);




/***************************************************************************//*!
 * \brief   VT100�����������
 *
 * ����VT100����
 *
 * \param   chr  �ַ�
 * \param   timeout ��ʱʱ��Ƭ
 * \return  ��������
 *****************************************************************************/
INT16U mde_cmd_Vt100Parse(char *chr_p, INT16U timeout);




/***************************************************************************//*!
 * \brief   �������������
 *
 * ������������
 *
 * \param   argc    �����������
 * \param   argv    ��������ַ�������
 * \return  
 *****************************************************************************/
INT16U mde_cmd_help(INT16U argc, char **argv);


#endif /* #ifndef MDE_CMD_H */
#endif