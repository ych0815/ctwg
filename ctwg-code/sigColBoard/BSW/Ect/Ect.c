/****************************************Copyright (c)**********************************************
**                                   成都运达科技股份公司
* 文件名    : Ect.c
* 功能描述  : 9s12xep100-Ect驱源文件(Ect.c)
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* 版本       |    日期         姓名               版本描述
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/1/3         sunj                New
**------------------------------------------------------------------------------------------------*/
#include "Ect.h"
#include "cpu.h"
#include "mc9s12xep100.h"



/********************************************************************************//*！
*\brief     ECT 通道输入捕捉/输出比较选择配置函数
*
*
*\param    channel        通道号，取值范围为0~7
*\param    type           输入捕捉/输出比较选择
*
*return    无返回值
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
            {   //输入捕捉选择
                ECT_TIOS &= (~0x80>>(7-channel));
            }
            else
            {   //输出比较选择
                ECT_TIOS |= (0x80>>(7-channel));
            }
        break;

        default:

        break;
    }
}

/********************************************************************************//*！
*\brief     ECT 通道输入捕捉边沿检测配置函数
*
*
*\param    channel        通道号，取值范围为0~7
*\param    type           边沿检测配置 
                          0 = 捕捉禁止    
                          1 = 仅捕捉上升沿    
                          2 = 仅捕捉下降沿     
                          3 = 上升、下降沿均捕捉
*
*return    无返回值
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
                /*设置通道0捕捉禁止*/
                ECT_TCTL4 &= (~0x02);                     
                ECT_TCTL4 &= (~0x01);
            }
            else if(edgModel==1)
            {
                /*设置通道0仅捕捉上升沿*/
                ECT_TCTL4 &= (~0x02);                     
                ECT_TCTL4 |= 0x01;
            }
            else if(edgModel==2)
            {
                /*设置通道0仅捕捉下降沿*/
                ECT_TCTL4 |= 0x02;                        
                ECT_TCTL4 &= (~0x01);                      
            }
            else if(edgModel==3)
            {
                /*设置通道0上升、下降沿均捕捉*/
                ECT_TCTL4 |= 0x02;                        
                ECT_TCTL4 |= 0x01;
            }            
        }
        break;

        case 1:
        {
            if(edgModel==0)
            {
                /*设置通道1捕捉禁止*/
                ECT_TCTL4 &= (~0x08);                     
                ECT_TCTL4 &= (~0x04);
            }
            else if(edgModel==1)
            {
                /*设置通道1仅捕捉上升沿*/
                ECT_TCTL4 &= (~0x08);                     
                ECT_TCTL4 |= 0x04;
            }
            else if(edgModel==2)
            { 
                /*设置通道1仅捕捉下降沿*/
                ECT_TCTL4 |= 0x08;                       
                ECT_TCTL4 &= (~0x04);                      
            }
            else if(edgModel==3)
            {
                /*设置通道1上升、下降沿均捕捉*/
                ECT_TCTL4 |= 0x08;                        
                ECT_TCTL4 |= 0x04;
            }            
        }
        break;

        case 2:
        {
            if(edgModel==0)
            {
                /*设置通道2捕捉禁止*/
                ECT_TCTL4 &= (~0x20);                     
                ECT_TCTL4 &= (~0x10);
            }
            else if(edgModel==1)
            {
                /*设置通道2仅捕捉上升沿*/
                ECT_TCTL4 &= (~0x20);                     
                ECT_TCTL4 |= 0x10;
            }
            else if(edgModel==2)
            {
                /*设置通道2仅捕捉下降沿*/
                ECT_TCTL4 |= 0x20;                        
                ECT_TCTL4 &= (~0x10);                      
            }
            else if(edgModel==3)
            {
                /*设置通道2上升、下降沿均捕捉*/
                ECT_TCTL4 |= 0x20;                        
                ECT_TCTL4 |= 0x10;
            }            
        }
        break;

        case 3:
        {
            if(edgModel==0)
            {
                /*设置通道3捕捉禁止*/
                ECT_TCTL4 &= (~0x80);                     
                ECT_TCTL4 &= (~0x40);
            }
            else if(edgModel==1)
            {
                /*设置通道3仅捕捉上升沿*/
                ECT_TCTL4 &= (~0x80);                     
                ECT_TCTL4 |= 0x40;
            }
            else if(edgModel==2)
            { 
                /*设置通道3仅捕捉下降沿*/
                ECT_TCTL4 |= 0x80;                       
                ECT_TCTL4 &= (~0x40);                      
            }
            else if(edgModel==3)
            {
                /*设置通道3上升、下降沿均捕捉*/
                ECT_TCTL4 |= 0x80;                        
                ECT_TCTL4 |= 0x40;
            }            
        }
        break;

        case 4:
        {
            if(edgModel==0)
            {
                /*设置通道4捕捉禁止*/
                ECT_TCTL3 &= (~0x02);                     
                ECT_TCTL3 &= (~0x01);
            }
            else if(edgModel==1)
            {
                /*设置通道4仅捕捉上升沿*/
                ECT_TCTL3 &= (~0x02);                     
                ECT_TCTL3 |= 0x01;
            }
            else if(edgModel==2)
            {
                /*设置通道4仅捕捉下降沿*/
                ECT_TCTL3 |= 0x02;                        
                ECT_TCTL3 &= (~0x01);                      
            }
            else if(edgModel==3)
            {
                /*设置通道4上升、下降沿均捕捉*/
                ECT_TCTL3 |= 0x02;                        
                ECT_TCTL3 |= 0x01;
            }            
        }
        break;

        case 5:
        {
            if(edgModel==0)
            {
                /*设置通道5捕捉禁止*/
                ECT_TCTL3 &= (~0x08);                     
                ECT_TCTL3 &= (~0x04);
            }
            else if(edgModel==1)
            {
                /*设置通道5仅捕捉上升沿*/
                ECT_TCTL3 &= (~0x08);                     
                ECT_TCTL3 |= 0x04;
            }
            else if(edgModel==2)
            { 
                /*设置通道5仅捕捉下降沿*/
                ECT_TCTL3 |= 0x08;                       
                ECT_TCTL3 &= (~0x04);                      
            }
            else if(edgModel==3)
            {
                /*设置通道5上升、下降沿均捕捉*/
                ECT_TCTL3 |= 0x08;                        
                ECT_TCTL3 |= 0x04;
            }            
        }
        break;

        case 6:
        {
            if(edgModel==0)
            {
                /*设置通道6捕捉禁止*/
                ECT_TCTL3 &= (~0x20);                     
                ECT_TCTL3 &= (~0x10);
            }
            else if(edgModel==1)
            {
                /*设置通道6仅捕捉上升沿*/
                ECT_TCTL3 &= (~0x20);                     
                ECT_TCTL3 |= 0x10;
            }
            else if(edgModel==2)
            {
                /*设置通道6仅捕捉下降沿*/
                ECT_TCTL3 |= 0x20;                        
                ECT_TCTL3 &= (~0x10);                      
            }
            else if(edgModel==3)
            {
                /*设置通道6上升、下降沿均捕捉*/
                ECT_TCTL3 |= 0x20;                        
                ECT_TCTL3 |= 0x10;
            }            
        }
        break;

        case 7:
        {
            if(edgModel==0)
            {
                /*设置通道7捕捉禁止*/
                ECT_TCTL3 &= (~0x80);                     
                ECT_TCTL3 &= (~0x40);
            }
            else if(edgModel==1)
            {
                /*设置通道7仅捕捉上升沿*/
                ECT_TCTL3 &= (~0x80);                     
                ECT_TCTL3 |= 0x40;
            }
            else if(edgModel==2)
            { 
                /*设置通道7仅捕捉下降沿*/
                ECT_TCTL3 |= 0x80;                       
                ECT_TCTL3 &= (~0x40);                      
            }
            else if(edgModel==3)
            {
                /*设置通道7上升、下降沿均捕捉*/
                ECT_TCTL3 |= 0x80;                        
                ECT_TCTL3 |= 0x40;
            }            
        }
        break;

        default:

        break;
    }
}

/********************************************************************************//*！
*\brief     ECT 通道 中断使能配置函数
*
*
*\param    channel        通道号，取值范围为0~7
*\param    enable         中断使能   TRUE=中断使能    FALSE=中断禁止
*
*return    无返回值
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
