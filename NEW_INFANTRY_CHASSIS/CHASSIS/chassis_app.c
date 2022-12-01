#include "chassis_app.h"
#include "chassis_task.h"
#include "rc.h"
#include "Task_Safe.h"
osThreadId TASK_CHASSISHandle;

/**
  * @brief          ������Ҫ������ƺ���
  * @param[in]      *chassis_control_f���������ṹ��
  * @retval         none
  */
void Chassis_Work(chassis_control_t *Chassis_Control_f)
{
	//�����������̨�Ĳ��
//	Chassis_Control_f->Chassis_Gimbal_Diference_Angle = Chassis_Control_f->Gimbal_Yaw_Data->chassis_gimbal_angel;
//	//�������ݸ���  ûд
//	Chassis_Data_Updata(Chassis_Control_f);
//	
//	//ң��ģʽ��ѡ��
//	Chassis_Mode_Choose(Chassis_Control_f);
//	
//	//����PID����
//	Chassis_Pid_Calc(Chassis_Control_f);
	
}





void chassis_app_init()
{
	//ң������ʼ��
	remote_control_init();
	
	//����ϵͳ
//	referee_system_init();
	
//	rc_lost_time = chassis_rc_lost_time;
	
	//������������
	osThreadDef(CHASSIS_TASK, Task_Chassis, osPriorityHigh, 0, 256);
  TASK_CHASSISHandle = osThreadCreate(osThread(CHASSIS_TASK), NULL);

	//����UI����
//	osThreadDef(UI_TASK, UI_Task, osPriorityLow, 0, 256);
//  UI_TASKHandle = osThreadCreate(osThread(UI_TASK), NULL);
	
}
/**
	* @brief		�������������
	* @param		none
	*	@retval		���ص������������
  */
TaskHandle_t *get_chassis_task_handle(void)
{
    return &TASK_CHASSISHandle;
}
