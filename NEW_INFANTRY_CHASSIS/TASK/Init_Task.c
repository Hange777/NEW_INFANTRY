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
    taskENTER_CRITICAL(); //为了保证对PORTA寄存器的访问不被中断，将访问操作放入临界区。进入临界区
	
		//CAN滤波器初始化
		CAN1_filter_config();
		CAN2_filter_config();
	
		//创建安全任务
		osThreadDef(Safe_TASK, Safe_Task, osPriorityNormal, 0, 128);
		Safe_TASKHandle = osThreadCreate(osThread(Safe_TASK), NULL);
    
		chassis_app_init(); // 底盘app初始化
		AppTask_Handler = get_chassis_task_handle();

		#ifdef FIRE_WORK  //火力
				shoot_app_init();
				FireTask_Handler = get_shoot_task_handle();
		#endif
		
    vTaskDelete(Init_TASKHandle); //删除开始任务
	  taskEXIT_CRITICAL();            //退出临界区

}

/**
  * @brief      失控处理   
  * @param[in]  none
  * @retval     none
  * @attention
  */
void out_of_control(void)
{
    //将任务挂起
	  vTaskSuspend(*AppTask_Handler);
	  vTaskSuspend(*FireTask_Handler);

    //解挂失控保护控制任务
//    vTaskResume(OutOf_Control_THandle);
}

/**
  * @brief      正常 | 解除失控  
  * @param[in]  none
  * @retval     none
  * @attention
  */
void normal_control(void)
{
    //解挂任务
    vTaskResume(*AppTask_Handler);
	  vTaskResume(*FireTask_Handler);

    //失控保护控制任务任务挂起
//    vTaskSuspend(OutOf_Control_THandle);
}


