#ifndef __CHASSIS_APP_H
#define __CHASSIS_APP_H

/* ************************FreeRTOS******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "cmsis_os.h"

#include "struct_variables.h"
void Chassis_Work(chassis_control_t *Chassis_Control_f);
TaskHandle_t *get_chassis_task_handle(void);
void chassis_app_init(void);


#endif

