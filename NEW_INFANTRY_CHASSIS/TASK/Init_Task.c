#include "Init_Task.h"
#include "cmsis_os.h"
#include "cmsis_armcc.h"

#include "can1_receive.h"
#include "can2_receive.h"

/************************* Task ************************/
#include "chassis_app.h"
#include "Task_Safe.h"

/* ************************freertos******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

//#include "shoot_Task.h"

extern osThreadId Init_TASKHandle;

osThreadId Safe_TASKHandle;

static TaskHandle_t *FireTask_Handler;
static TaskHandle_t *AppTask_Handler;

void Init_Task(void const * argument)
{
    taskENTER_CRITICAL(); //Ϊ�˱�֤��PORTA�Ĵ����ķ��ʲ����жϣ������ʲ��������ٽ����������ٽ���
	
		//CAN�˲�����ʼ��
		CAN1_filter_config();
		CAN2_filter_config();
	
		//������ȫ����
		osThreadDef(Safe_TASK, Safe_Task, osPriorityNormal, 0, 128);
		Safe_TASKHandle = osThreadCreate(osThread(Safe_TASK), NULL);
    
		chassis_app_init(); // ����app��ʼ��
		AppTask_Handler = get_chassis_task_handle();

		#ifdef FIRE_WORK  //����
				shoot_app_init();
				FireTask_Handler = get_shoot_task_handle();
		#endif
		
    vTaskDelete(Init_TASKHandle); //ɾ����ʼ����
	  taskEXIT_CRITICAL();            //�˳��ٽ���

}

/**
  * @brief      ʧ�ش���   
  * @param[in]  none
  * @retval     none
  * @attention
  */
void out_of_control(void)
{
    //���������
	  vTaskSuspend(*AppTask_Handler);
	  vTaskSuspend(*FireTask_Handler);

    //���ʧ�ر�����������
//    vTaskResume(OutOf_Control_THandle);
}

/**
  * @brief      ���� | ���ʧ��  
  * @param[in]  none
  * @retval     none
  * @attention
  */
void normal_control(void)
{
    //�������
    vTaskResume(*AppTask_Handler);
	  vTaskResume(*FireTask_Handler);

    //ʧ�ر������������������
//    vTaskSuspend(OutOf_Control_THandle);
}


