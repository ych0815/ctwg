/********************************************************************************//*��
*\file
*\brief      sci�Ĵ������ó���
*\version    1.0.0
*\date       2015\12\22
*\author     zdj
*
*sci�Ĵ������ó���
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
*---------��������
===================================================================================*/

/********************************************************************************//*��
*\brief      SCI���������ú���
*
*����������
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    �޷���ֵ
*
**********************************************************************************/
void sci_sbr_config(uint8 config,uint16 sbr,uint8 channel) 
{
  switch(channel) 
  {
    case 10: 
      	SCI0SR2_AMAP = 0;     /*AMAPΪ0ʱ���ɶ�дSCIBDL/H�Ĵ���*/
      	SCI0BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI0BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 1: 
      	SCI1SR2_AMAP = 0;
      	SCI1BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI1BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 2: 
      	SCI2SR2_AMAP = 0;
      	SCI2BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI2BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 3: 
      	SCI3SR2_AMAP = 0;
      	SCI3BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI3BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 4: 
      	SCI4SR2_AMAP = 0;
      	SCI4BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI4BDH = config | ((uint8)(sbr >> 8));
	    break;

    case 5: 
      	SCI5SR2_AMAP = 0;
     	SCI5BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI5BDH = config | ((uint8)(sbr >> 8)); 
	    break;

    case 6: 
      	SCI6SR2_AMAP = 0;
      	SCI6BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI6BDH = config | ((uint8)(sbr >> 8)); 
	    break;

    case 7: 
      	SCI7SR2_AMAP = 0;
      	SCI7BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI7BDH = config | ((uint8)(sbr >> 8));
	    break;

    default:							/*Ĭ��ΪUART0*/
      	SCI0SR2_AMAP = 0;
      	SCI0BDL = (uint8)(sbr & 0xff);  /*����������*/
    	SCI0BDH = config | ((uint8)(sbr >> 8));  
	    break;
  }
}

/********************************************************************************//*��
*\brief      SCI�жϡ�ģʽ���ú���
*
*SCI�ж����ã�ģʽ����
*
*\param    config1        ģʽ���ò���
*\param    config2        �ж����ò���
*\param    channel        sci���ѡ��
*
*return    �޷���ֵ
*
*********************************************************************************/
void sci_config(uint8 config1,uint8 config2,uint8 channel) 
{ 
  switch(channel) 
  {
    case 10: 
      	SCI0SR2_AMAP = 0;   /*AMAPΪ0ʱ���ɶ�дSCICR1�Ĵ���*/
    	SCI0CR1 = config1;  /*ģʽ����*/
	    SCI0CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 1: 
    	SCI1SR2_AMAP = 0;
    	SCI1CR1 = config1;
	    SCI1CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 2: 
      	SCI2SR2_AMAP = 0;
    	SCI2CR1 = config1;
	    SCI2CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 3: 
    	SCI3SR2_AMAP = 0;
    	SCI3CR1 = config1;
	    SCI3CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 4: 
    	SCI4SR2_AMAP = 0;
    	SCI4CR1 = config1;
	    SCI4CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 5: 
    	SCI5SR2_AMAP = 1;
    	SCI5CR1 = config1;
	    SCI5CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 6: 
    	SCI6SR2_AMAP = 0;
    	SCI6CR1 = config1;
	    SCI6CR2 = config2;  /*�ж�ʹ������*/
	    break;

    case 7: 
    	SCI7SR2_AMAP = 0;
    	SCI7CR1 = config1;
	    SCI7CR2 = config2;  /*�ж�ʹ������*/
	    break;

    default:
    	SCI0SR2_AMAP = 0;
    	SCI0CR1 = config1;
	    SCI0CR2 = config2;  /*�ж�ʹ������*/
	    break;
  }
}

/********************************************************************************//*��
*\brief      SCIд�Ĵ�������
*
*��Ĵ�����д����
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    �޷���ֵ
*
*********************************************************************************/
void sci_put_reg(uint8 data,uint8 channel) 
{
   uint8 i = 0;
   switch(channel) 
   {
      case 10: 
	       SCI0DRL = data;  /*��������*/
	       break;

      case 1: 
    	   SCI1DRL = data;  /*��������*/
	       break;

      case 2: 
           SCI2DRL = data;  /*��������*/
	       break;

      case 3: 
      	   SCI3DRL = data;  /*��������*/
	       break;

      case 4: 
      	   SCI4DRL = data;  /*��������*/
	       break;
		   
      case 5: 
      	   SCI5DRL = data;  /*��������*/
	       break;

      case 6: 
      	   SCI6DRL = data;  /*��������*/
	       break;

      case 7: 
      	   SCI7DRL = data;  /*��������*/
	       break;

      default:
      	   SCI0DRL = data;  /*��������*/
	       break;
    }
}

/********************************************************************************//*��
*\brief      SCI���Ĵ�������
*
*�ӼĴ����ж�����
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    �޷���ֵ
*
*********************************************************************************/    
uint8 sci_get_reg(uint8 channel) 
{
   uint8  data = 0u;
	
   switch(channel) 
   {
      case 10: 
	      data = (SCI0DRL & 0xff);/*��������*/
	  	  break;
		  
      case 1: 
 	      data = (SCI1DRL & 0xff);/*��������*/
	  	  break;
		  
     case 2: 
 	      data = (SCI2DRL & 0xff);/*��������*/
	  	  break;
		  
      case 3: 
 	      data = (SCI3DRL & 0xff);/*��������*/
	  	  break;
		  
      case 4: 
 	      data = (SCI4DRL & 0xff);/*��������*/
	  	  break;
		  
      case 5: 
	      data = (SCI5DRL & 0xff);/*��������*/
	  	  break;
		  
      case 6: 
	      data = (SCI6DRL & 0xff);/*��������*/
	  	  break;
		  
      case 7: 
	      data = (SCI7DRL & 0xff);/*��������*/
	  	  break;
		  
      default:
	      data = (SCI0DRL & 0xff);/*��������*/
	  	  break;
    }
    return(0);
}  

#if 0
/********************************************************************************//*��
*\brief      SCI���ռĴ���׼����������
*
*�ӼĴ����ж�����
*
*\param    btr_config     ���ò���
*\param    sbr            ������
*\param    channel        sci���ѡ��
*
*return    �޷���ֵ
*
*********************************************************************************/    
char sci_data_ready(uint8 channel) 
{
   switch(channel) 
   {
      case 10: 
      {
	      return (SCI0SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 1: 
      { 
    	  return (SCI1SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 2: 
      { 
        return (SCI2SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 3: 
      { 
      	return (SCI3SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 4: 
      { 
      	return (SCI4SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 5: 
      { 
      	return (SCI5SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 6: 
      { 
      	return (SCI6SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      case 7: 
      { 
      	return (SCI7SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
      default:
      { 
      	return (SCI0SR1_RDRF);  /*�����Ƿ��Ѿ�׼����*/
      }
    }
}  
#endif

