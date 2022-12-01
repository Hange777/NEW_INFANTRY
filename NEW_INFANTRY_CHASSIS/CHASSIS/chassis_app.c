#include "chassis_app.h"
#include "chassis_task.h"
#include "rc.h"
#include "Task_Safe.h"
osThreadId TASK_CHASSISHandle;

/**
  * @brief          底盘主要任务控制函数
  * @param[in]      *chassis_control_f：底盘主结构体
  * @retval         none
  */
void Chassis_Work(chassis_control_t *Chassis_Control_f)
{
	//计算底盘与云台的差角
//	Chassis_Control_f->Chassis_Gimbal_Diference_Angle = Chassis_Control_f->Gimbal_Yaw_Data->chassis_gimbal_angel;
//	//底盘数据更新  没写
//	Chassis_Data_Updata(Chassis_Control_f);
//	
//	//遥控模式的选择
//	Chassis_Mode_Choose(Chassis_Control_f);
//	
//	//底盘PID计算
//	Chassis_Pid_Calc(Chassis_Control_f);
	
}





void chassis_app_init()
{
	//遥控器初始化
	remote_control_init();
	
	//裁判系统
//	referee_system_init();
	
//	rc_lost_time = chassis_rc_lost_time;
	
	//创建底盘任务
	osThreadDef(CHASSIS_TASK, Task_Chassis, osPriorityHigh, 0, 256);
  TASK_CHASSISHandle = osThreadCreate(osThread(CHASSIS_TASK), NULL);

	//创建UI任务
//	osThreadDef(UI_TASK, UI_Task, osPriorityLow, 0, 256);
//  UI_TASKHandle = osThreadCreate(osThread(UI_TASK), NULL);
	
}
/**
	* @brief		底盘任务函数句柄
	* @param		none
	*	@retval		返回底盘任务函数句柄
  */
TaskHandle_t *get_chassis_task_handle(void)
{
    return &TASK_CHASSISHandle;
}
