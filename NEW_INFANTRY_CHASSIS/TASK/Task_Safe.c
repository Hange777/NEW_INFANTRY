/**
  *****************************东莞理工学院ACE实验室 *****************************
  * @file       Task_Safe.c/h
  * @brief      安全任务
  * @note       合并版本
  * @history    
  *
  @verbatim   v1.0
  ==============================================================================
  
  ==============================================================================
  @endverbatim
  *****************************东莞理工学院ACE实验室 *****************************
	*/
#include "Task_Safe.h"


/* ************************freertos******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"



/**
  * @brief      失控保护检测任务
  * @param[in]  *pvParameters
  * @retval     none
  * @attention
  */
void Safe_Task(void const * argument)
{
	  static TickType_t currentTime;

	  currentTime = xTaskGetTickCount(); //获取当前系统时间
	
	  while(1)
	  {

	  	//检测周期
	  	vTaskDelayUntil(&currentTime, 1);//绝对延时//vTaskDelay(2)
			
	  }
}



