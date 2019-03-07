/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : Ect.c
* ��������  : 9s12xep100-Ect��Դ�ļ�(Ect.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj                New
**------------------------------------------------------------------------------------------------*/
#include "Ect.h"
#include "cpu.h"
#include "mc9s12xep100.h"



/********************************************************************************//*��
*\brief     ECT ͨ�����벶׽/����Ƚ�ѡ�����ú���
*
*
*\param    channel        ͨ���ţ�ȡֵ��ΧΪ0~7
*\param    type           ���벶׽/����Ƚ�ѡ��
*
*return    �޷���ֵ
*
*********************************************************************************/
void Ect_IC_OC_Sel_Channel_Config(uint8 channel, Ect_ICOC_Type type)
{
    switch(channel)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if(type==Ect_IC_Type)
            {   //���벶׽ѡ��
                ECT_TIOS &= (~0x80>>(7-channel));
            }
            else
            {   //����Ƚ�ѡ��
                ECT_TIOS |= (0x80>>(7-channel));
            }
        break;

        default:

        break;
    }
}

/********************************************************************************//*��
*\brief     ECT ͨ�����벶׽���ؼ�����ú���
*
*
*\param    channel        ͨ���ţ�ȡֵ��ΧΪ0~7
*\param    type           ���ؼ������ 
                          0 = ��׽��ֹ    
                          1 = ����׽������    
                          2 = ����׽�½���     
                          3 = �������½��ؾ���׽
*
*return    �޷���ֵ
*
*********************************************************************************/
void Ect_IC_Edg_Channel_Config(uint8 channel,uint8 edgModel)
{
    switch(channel)
    {
        case 0:
        {
            if(edgModel==0)
            {
                /*����ͨ��0��׽��ֹ*/
                ECT_TCTL4 &= (~0x02);                     
                ECT_TCTL4 &= (~0x01);
            }
            else if(edgModel==1)
            {
                /*����ͨ��0����׽������*/
                ECT_TCTL4 &= (~0x02);                     
                ECT_TCTL4 |= 0x01;
            }
            else if(edgModel==2)
            {
                /*����ͨ��0����׽�½���*/
                ECT_TCTL4 |= 0x02;                        
                ECT_TCTL4 &= (~0x01);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��0�������½��ؾ���׽*/
                ECT_TCTL4 |= 0x02;                        
                ECT_TCTL4 |= 0x01;
            }            
        }
        break;

        case 1:
        {
            if(edgModel==0)
            {
                /*����ͨ��1��׽��ֹ*/
                ECT_TCTL4 &= (~0x08);                     
                ECT_TCTL4 &= (~0x04);
            }
            else if(edgModel==1)
            {
                /*����ͨ��1����׽������*/
                ECT_TCTL4 &= (~0x08);                     
                ECT_TCTL4 |= 0x04;
            }
            else if(edgModel==2)
            { 
                /*����ͨ��1����׽�½���*/
                ECT_TCTL4 |= 0x08;                       
                ECT_TCTL4 &= (~0x04);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��1�������½��ؾ���׽*/
                ECT_TCTL4 |= 0x08;                        
                ECT_TCTL4 |= 0x04;
            }            
        }
        break;

        case 2:
        {
            if(edgModel==0)
            {
                /*����ͨ��2��׽��ֹ*/
                ECT_TCTL4 &= (~0x20);                     
                ECT_TCTL4 &= (~0x10);
            }
            else if(edgModel==1)
            {
                /*����ͨ��2����׽������*/
                ECT_TCTL4 &= (~0x20);                     
                ECT_TCTL4 |= 0x10;
            }
            else if(edgModel==2)
            {
                /*����ͨ��2����׽�½���*/
                ECT_TCTL4 |= 0x20;                        
                ECT_TCTL4 &= (~0x10);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��2�������½��ؾ���׽*/
                ECT_TCTL4 |= 0x20;                        
                ECT_TCTL4 |= 0x10;
            }            
        }
        break;

        case 3:
        {
            if(edgModel==0)
            {
                /*����ͨ��3��׽��ֹ*/
                ECT_TCTL4 &= (~0x80);                     
                ECT_TCTL4 &= (~0x40);
            }
            else if(edgModel==1)
            {
                /*����ͨ��3����׽������*/
                ECT_TCTL4 &= (~0x80);                     
                ECT_TCTL4 |= 0x40;
            }
            else if(edgModel==2)
            { 
                /*����ͨ��3����׽�½���*/
                ECT_TCTL4 |= 0x80;                       
                ECT_TCTL4 &= (~0x40);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��3�������½��ؾ���׽*/
                ECT_TCTL4 |= 0x80;                        
                ECT_TCTL4 |= 0x40;
            }            
        }
        break;

        case 4:
        {
            if(edgModel==0)
            {
                /*����ͨ��4��׽��ֹ*/
                ECT_TCTL3 &= (~0x02);                     
                ECT_TCTL3 &= (~0x01);
            }
            else if(edgModel==1)
            {
                /*����ͨ��4����׽������*/
                ECT_TCTL3 &= (~0x02);                     
                ECT_TCTL3 |= 0x01;
            }
            else if(edgModel==2)
            {
                /*����ͨ��4����׽�½���*/
                ECT_TCTL3 |= 0x02;                        
                ECT_TCTL3 &= (~0x01);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��4�������½��ؾ���׽*/
                ECT_TCTL3 |= 0x02;                        
                ECT_TCTL3 |= 0x01;
            }            
        }
        break;

        case 5:
        {
            if(edgModel==0)
            {
                /*����ͨ��5��׽��ֹ*/
                ECT_TCTL3 &= (~0x08);                     
                ECT_TCTL3 &= (~0x04);
            }
            else if(edgModel==1)
            {
                /*����ͨ��5����׽������*/
                ECT_TCTL3 &= (~0x08);                     
                ECT_TCTL3 |= 0x04;
            }
            else if(edgModel==2)
            { 
                /*����ͨ��5����׽�½���*/
                ECT_TCTL3 |= 0x08;                       
                ECT_TCTL3 &= (~0x04);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��5�������½��ؾ���׽*/
                ECT_TCTL3 |= 0x08;                        
                ECT_TCTL3 |= 0x04;
            }            
        }
        break;

        case 6:
        {
            if(edgModel==0)
            {
                /*����ͨ��6��׽��ֹ*/
                ECT_TCTL3 &= (~0x20);                     
                ECT_TCTL3 &= (~0x10);
            }
            else if(edgModel==1)
            {
                /*����ͨ��6����׽������*/
                ECT_TCTL3 &= (~0x20);                     
                ECT_TCTL3 |= 0x10;
            }
            else if(edgModel==2)
            {
                /*����ͨ��6����׽�½���*/
                ECT_TCTL3 |= 0x20;                        
                ECT_TCTL3 &= (~0x10);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��6�������½��ؾ���׽*/
                ECT_TCTL3 |= 0x20;                        
                ECT_TCTL3 |= 0x10;
            }            
        }
        break;

        case 7:
        {
            if(edgModel==0)
            {
                /*����ͨ��7��׽��ֹ*/
                ECT_TCTL3 &= (~0x80);                     
                ECT_TCTL3 &= (~0x40);
            }
            else if(edgModel==1)
            {
                /*����ͨ��7����׽������*/
                ECT_TCTL3 &= (~0x80);                     
                ECT_TCTL3 |= 0x40;
            }
            else if(edgModel==2)
            { 
                /*����ͨ��7����׽�½���*/
                ECT_TCTL3 |= 0x80;                       
                ECT_TCTL3 &= (~0x40);                      
            }
            else if(edgModel==3)
            {
                /*����ͨ��7�������½��ؾ���׽*/
                ECT_TCTL3 |= 0x80;                        
                ECT_TCTL3 |= 0x40;
            }            
        }
        break;

        default:

        break;
    }
}

/********************************************************************************//*��
*\brief     ECT ͨ�� �ж�ʹ�����ú���
*
*
*\param    channel        ͨ���ţ�ȡֵ��ΧΪ0~7
*\param    enable         �ж�ʹ��   TRUE=�ж�ʹ��    FALSE=�жϽ�ֹ
*
*return    �޷���ֵ
*
*********************************************************************************/
void Ect_Enable_IC_OC_Interrupt(uint8 channel,boolean enable)
{
    switch(channel)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          if(enable==TRUE)
          {
              ECT_TIE |= (0x80>>(7-channel));
          }
          else
          {
              ECT_TIE &= (~(0x80>>(7-channel)));
          }  
    }
}
