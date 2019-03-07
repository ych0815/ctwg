/********************************************************************************//*！
*\file
*\brief      sci寄存器配置程序
*\version    1.0.0
*\date       2015\12\22
*\author     zdj
*
*sci寄存器配置程序
*
\verbatim
------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
                 
                 +------(NEW | MODify |ADD |DELete)------+
                 |
version          |    date(yyyy/mm/dd)  name        brief

---------------------+----------------+---------------------------------------------
 1.0.0         NEW       2015/12/22     zdj         create
------------------------------------------------------------------------------------
\endverbatim
************************************************************************************/

#include "Sci.h"
                 
/*==================================================================================
*---------函数定义
===================================================================================*/

/********************************************************************************//*！
*\brief      SCI波特率设置函数
*
*波特率设置
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    无返回值
*
**********************************************************************************/
void sci_sbr_config(uint8 config,uint16 sbr,uint8 channel) 
{
  switch(channel) 
  {
    case 10: 
      	SCI0SR2_AMAP = 0;     /*AMAP为0时，可读写SCIBDL/H寄存器*/
      	SCI0BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI0BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 1: 
      	SCI1SR2_AMAP = 0;
      	SCI1BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI1BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 2: 
      	SCI2SR2_AMAP = 0;
      	SCI2BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI2BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 3: 
      	SCI3SR2_AMAP = 0;
      	SCI3BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI3BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 4: 
      	SCI4SR2_AMAP = 0;
      	SCI4BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI4BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 5: 
      	SCI5SR2_AMAP = 0;
     	SCI5BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI5BDH = config | ((uint8)(sbr >> 8)); 
	    break;

    case 6: 
      	SCI6SR2_AMAP = 0;
      	SCI6BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI6BDH = config | ((uint8)(sbr >> 8)); 
	    break;

    case 7: 
      	SCI7SR2_AMAP = 0;
      	SCI7BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI7BDH = config | ((uint8)(sbr >> 8));
	    break;

    default:							/*默认为UART0*/
      	SCI0SR2_AMAP = 0;
      	SCI0BDL = (uint8)(sbr & 0xff);  /*波特率配置*/
    	SCI0BDH = config | ((uint8)(sbr >> 8));  
	    break;
  }
}

/********************************************************************************//*！
*\brief      SCI中断、模式配置函数
*
*SCI中断配置，模式设置
*
*\param    config1        模式配置参数
*\param    config2        中断配置参数
*\param    channel        sci序号选择
*
*return    无返回值
*
*********************************************************************************/
void sci_config(uint8 config1,uint8 config2,uint8 channel) 
{ 
  switch(channel) 
  {
    case 10: 
      	SCI0SR2_AMAP = 0;   /*AMAP为0时，可读写SCICR1寄存器*/
    	SCI0CR1 = config1;  /*模式配置*/
	    SCI0CR2 = config2;  /*中断使能配置*/
	    break;

    case 1: 
    	SCI1SR2_AMAP = 0;
    	SCI1CR1 = config1;
	    SCI1CR2 = config2;  /*中断使能配置*/
	    break;

    case 2: 
      	SCI2SR2_AMAP = 0;
    	SCI2CR1 = config1;
	    SCI2CR2 = config2;  /*中断使能配置*/
	    break;

    case 3: 
    	SCI3SR2_AMAP = 0;
    	SCI3CR1 = config1;
	    SCI3CR2 = config2;  /*中断使能配置*/
	    break;

    case 4: 
    	SCI4SR2_AMAP = 0;
    	SCI4CR1 = config1;
	    SCI4CR2 = config2;  /*中断使能配置*/
	    break;

    case 5: 
    	SCI5SR2_AMAP = 1;
    	SCI5CR1 = config1;
	    SCI5CR2 = config2;  /*中断使能配置*/
	    break;

    case 6: 
    	SCI6SR2_AMAP = 0;
    	SCI6CR1 = config1;
	    SCI6CR2 = config2;  /*中断使能配置*/
	    break;

    case 7: 
    	SCI7SR2_AMAP = 0;
    	SCI7CR1 = config1;
	    SCI7CR2 = config2;  /*中断使能配置*/
	    break;

    default:
    	SCI0SR2_AMAP = 0;
    	SCI0CR1 = config1;
	    SCI0CR2 = config2;  /*中断使能配置*/
	    break;
  }
}

/********************************************************************************//*！
*\brief      SCI写寄存器函数
*
*向寄存器中写数据
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    无返回值
*
*********************************************************************************/
void sci_put_reg(uint8 data,uint8 channel) 
{
   uint8 i = 0;
   switch(channel) 
   {
      case 10: 
	       SCI0DRL = data;  /*发送数据*/
	       break;

      case 1: 
    	   SCI1DRL = data;  /*发送数据*/
	       break;

      case 2: 
           SCI2DRL = data;  /*发送数据*/
	       break;

      case 3: 
      	   SCI3DRL = data;  /*发送数据*/
	       break;

      case 4: 
      	   SCI4DRL = data;  /*发送数据*/
	       break;
		   
      case 5: 
      	   SCI5DRL = data;  /*发送数据*/
	       break;

      case 6: 
      	   SCI6DRL = data;  /*发送数据*/
	       break;

      case 7: 
      	   SCI7DRL = data;  /*发送数据*/
	       break;

      default:
      	   SCI0DRL = data;  /*发送数据*/
	       break;
    }
}

/********************************************************************************//*！
*\brief      SCI读寄存器函数
*
*从寄存器中读数据
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    无返回值
*
*********************************************************************************/    
uint8 sci_get_reg(uint8 channel) 
{
   uint8  data = 0u;
	
   switch(channel) 
   {
      case 10: 
	      data = (SCI0DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 1: 
 	      data = (SCI1DRL & 0xff);/*接收数据*/
	  	  break;
		  
     case 2: 
 	      data = (SCI2DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 3: 
 	      data = (SCI3DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 4: 
 	      data = (SCI4DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 5: 
	      data = (SCI5DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 6: 
	      data = (SCI6DRL & 0xff);/*接收数据*/
	  	  break;
		  
      case 7: 
	      data = (SCI7DRL & 0xff);/*接收数据*/
	  	  break;
		  
      default:
	      data = (SCI0DRL & 0xff);/*接收数据*/
	  	  break;
    }
    return(0);
}  

#if 0
/********************************************************************************//*！
*\brief      SCI接收寄存器准备就绪函数
*
*从寄存器中读数据
*
*\param    btr_config     配置参数
*\param    sbr            波特率
*\param    channel        sci序号选择
*
*return    无返回值
*
*********************************************************************************/    
char sci_data_ready(uint8 channel) 
{
   switch(channel) 
   {
      case 10: 
      {
	      return (SCI0SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 1: 
      { 
    	  return (SCI1SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 2: 
      { 
        return (SCI2SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 3: 
      { 
      	return (SCI3SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 4: 
      { 
      	return (SCI4SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 5: 
      { 
      	return (SCI5SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 6: 
      { 
      	return (SCI6SR1_RDRF);  /*数据是否已经准备好*/
      }
      case 7: 
      { 
      	return (SCI7SR1_RDRF);  /*数据是否已经准备好*/
      }
      default:
      { 
      	return (SCI0SR1_RDRF);  /*数据是否已经准备好*/
      }
    }
}  
#endif

