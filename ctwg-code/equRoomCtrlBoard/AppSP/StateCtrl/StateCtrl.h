/****************************************Copyright (c)**********************************************
**                                   �ɶ��˴�Ƽ��ɷݹ�˾
* �ļ���    : StateCtrl.h
* ��������  : ״̬����ģ�����Դ�ļ�
*
*            +----- (NEW | MODify | ADD | DELete)
*            |
* �汾       |    ����         ����               �汾����
*----------+---+------------+------------------+----------------------------------------------------
* 1.0.0       2019/2/28        sunj            	  New
**------------------------------------------------------------------------------------------------*/


#define         CMD_RUN                     1       /*����ָ��*/
#define         CMD_SERVICE                 2       /*ά��ָ��*/

#define         CMD_LOCAL                   1       /*����ָ��*/
#define         CMD_REMOTE                  2       /*Զ��ָ��*/

#define         CMD_OPEN_DOOR               1       /*����ָ��*/
#define         CMD_CLOSE_DOOR              2       /*����ָ��*/

#define         CMD_OPEN_CC                 1       /*�򿪳�������ָ��*/
#define         CMD_CLOSE_CC                2       /*�رճ�������ָ��*/

#define         CMD_OPEN_SR                 1       /*��ɢ�ȷ���ָ��*/
#define         CMD_CLOSE_SR                2       /*�ر�ɢ�ȷ���ָ��*/

#define         CMD_OPEN_HEAT               1       /*���ȿ�ָ��*/
#define         CMD_CLOSE_HEAT              2       /*���ȹ�ָ��*/

#define         CMD_OPEN_XZ                 1       /*���󴥷���ָ��*/
#define         CMD_CLOSE_XZ                2       /*���󴥷���ָ��*/

#define         CMD_OPEN_MZ                 1       /*���󴥷���ָ��*/
#define         CMD_CLOSE_MZ                2       /*���󴥷���ָ��*/

#define         CMD_OPEN_SIMU_TEST          1       /*ģ����Դ�����ָ��*/
#define         CMD_CLOSE_SIMU_TEST         2       /*ģ����Դ�����ָ��*/



/********************************************
 * ��������
 *******************************************/
extern void app_stateCtrl_MainFunction(void);