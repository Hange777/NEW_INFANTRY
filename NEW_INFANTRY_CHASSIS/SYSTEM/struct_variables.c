 /*code is far away from bug with the animal protecting
  *  ��������������
  *�����ߩ��������ߩ�
  *������������������ ��
  *������������������
  *�����ש������ס���
  *������������������
  *���������ߡ�������
  *������������������
  *������������������
  *�����������������ޱ���
  *��������������������BUG��
  *����������������������
  *���������������������ǩ�
  *������������������������
  *���������������ש�����
  *���������ϩϡ����ϩ�
  *���������ߩ������ߩ� 
  *������
  */


#include "struct_variables.h"
#include "can1_receive.h"
#include "can2_receive.h"

static infantry_state_e infantry_state;

/**
  * @brief      ���ò���ģʽ��ֹͣ��ң�ء����̣�
  * @param[in]  ����ģʽ
  * @retval     none
  * @attention  
  */
void system_state_set(infantry_state_e state)
{
    infantry_state = state;
}

/**
  * @brief      ���ز���ģʽ��ֹͣ��ң�ء����̣�
  * @param[in]  none
  * @retval     ����ģʽ
  * @attention  
  */
infantry_state_e system_state_return(void)
{
    return infantry_state;
}

