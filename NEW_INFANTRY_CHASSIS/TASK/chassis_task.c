#include "chassis_task.h"
#include "chassis_behaviour.h"
#include "pid.h"
#include "can1_receive.h"
#include "string.h"
#include "filter.h"

chassis_control_t Chassis_Control;

static void Chassis_Init(chassis_control_t *Chassis_Control);
static void Chassis_Work(chassis_control_t *Chassis_Control_f);
static void Chassis_pid_calculate(chassis_control_t *Chassis_pid_calculate_f);
void Task_Chassis(void const *argument)
{
	uint32_t currentTime;

	Chassis_Init(&Chassis_Control);
	// vTaskDelay(5);

	while (1)
	{
		currentTime = xTaskGetTickCount(); //��ǰϵͳʱ��

		taskENTER_CRITICAL(); //�����ٽ���

		Chassis_Work(&Chassis_Control);

		//		Chassis_TO_Gimbal(&Chassis_Control);
		//		can1_chassis_setmsg(Chassis_Control.Chassis_Motor[0].give_current,
		//                            Chassis_Control.Chassis_Motor[1].give_current,
		//                            Chassis_Control.Chassis_Motor[2].give_current,
		//                            Chassis_Control.Chassis_Motor[3].give_current);

		taskEXIT_CRITICAL(); //�˳��ٽ���

		vTaskDelayUntil(&currentTime, 2); //������ʱ//vTaskDelay(2)
	}
}
/**
 * @brief          �������ݳ�ʼ��
 * @param[in]      *chassis_move_init_f���������ṹ��
 * @retval         none
 */
static void Chassis_Init(chassis_control_t *chassis_data_init_f)
{
	memset(chassis_data_init_f, 0, sizeof(chassis_control_t));
	//��ȡң�ص�ָ��
	chassis_data_init_f->Chassis_RC = get_remote_control_point();

	//��ȡ�����ĸ������ָ��
	chassis_data_init_f->Chassis_Motor[0].chassis_motor_measure = get_chassis_motor_measure_point(0);
	chassis_data_init_f->Chassis_Motor[1].chassis_motor_measure = get_chassis_motor_measure_point(0);
	chassis_data_init_f->Chassis_Motor[2].chassis_motor_measure = get_chassis_motor_measure_point(0);
	chassis_data_init_f->Chassis_Motor[3].chassis_motor_measure = get_chassis_motor_measure_point(0);

	//��ȡ�������ݵ�ָ��
	chassis_data_init_f->super_cap_c = get_supercap_control_point();

	//��ȡ����ģʽ��ָ��
	chassis_data_init_f->behaviour = get_chassis_behaviour_point();

	//��ȡ����״̬��ָ��
	chassis_data_init_f->state = get_chassis_state_point();

	//��ʼ����ͨ�˲�  ��Ҫ���ֵ,������ң�غͼ��̵�ֵ���˲�
	first_order_filter_init(&(chassis_data_init_f->LowFilt_chassis_vx), CHASSIS_FIRST_ORDER_FILTER_K);
	first_order_filter_init(&(chassis_data_init_f->LowFilt_chassis_vy), CHASSIS_FIRST_ORDER_FILTER_K);

	/*--------------------��ʼ������pid--------------------*/

	/*����pid��ʼ��*/
	PidInit(&chassis_data_init_f->Chassis_Speed_Pid[0], CHASSIS_RF_MOTOR_KP, CHASSIS_RF_MOTOR_KI, CHASSIS_RF_MOTOR_KD, Output_Limit);
	PidInit(&chassis_data_init_f->Chassis_Speed_Pid[1], CHASSIS_LF_MOTOR_KP, CHASSIS_LF_MOTOR_KI, CHASSIS_LF_MOTOR_KD, Output_Limit);
	PidInit(&chassis_data_init_f->Chassis_Speed_Pid[2], CHASSIS_RB_MOTOR_KP, CHASSIS_RB_MOTOR_KI, CHASSIS_RB_MOTOR_KD, Output_Limit);
	PidInit(&chassis_data_init_f->Chassis_Speed_Pid[3], CHASSIS_LB_MOTOR_KP, CHASSIS_LB_MOTOR_KI, CHASSIS_LB_MOTOR_KD, Output_Limit);
	PidInitMode(&chassis_data_init_f->Chassis_Speed_Pid[0], Output_Limit, 30000, 0);
	PidInitMode(&chassis_data_init_f->Chassis_Speed_Pid[1], Output_Limit, 30000, 0);
	PidInitMode(&chassis_data_init_f->Chassis_Speed_Pid[2], Output_Limit, 30000, 0);
	PidInitMode(&chassis_data_init_f->Chassis_Speed_Pid[3], Output_Limit, 30000, 0);

	//����λ�û�pid
	PidInit(&chassis_data_init_f->Chassis_Location_Pid, CHASSIS_LOCATION_KP, CHASSIS_LOCATION_KI, CHASSIS_LOCATION_KD, NONE);
	//������ת����pid
	PidInit(&chassis_data_init_f->chassis_rotate_pid, CHASSIS_SPIN_FOLLOW_KP, CHASSIS_SPIN_FOLLOW_KI, CHASSIS_SPIN_FOLLOW_KD, Deadzone | ChangingIntegrationRate | Integral_Limit);
	PidInitMode(&chassis_data_init_f->chassis_rotate_pid, Deadzone, 0.0f, 0);
	PidInitMode(&chassis_data_init_f->chassis_rotate_pid, ChangingIntegrationRate, 180.0f, 0.5f);
	PidInitMode(&chassis_data_init_f->chassis_rotate_pid, Integral_Limit, 1000, 0);

	chassis_data_init_f->chassis_speed_gain = 1;
}

void Chassis_pid_calculate(chassis_control_t *Chassis_pid_calculate_f)
{
	motor_speed_control(&Chassis_pid_calculate_f->Chassis_Speed_Pid[0], Chassis_pid_calculate_f->Chassis_Motor[0].Speed_Set, Chassis_pid_calculate_f->Chassis_Motor[0].chassis_motor_measure->speed);
	motor_speed_control(&Chassis_pid_calculate_f->Chassis_Speed_Pid[1], Chassis_pid_calculate_f->Chassis_Motor[1].Speed_Set, Chassis_pid_calculate_f->Chassis_Motor[1].chassis_motor_measure->speed);
	motor_speed_control(&Chassis_pid_calculate_f->Chassis_Speed_Pid[2], Chassis_pid_calculate_f->Chassis_Motor[2].Speed_Set, Chassis_pid_calculate_f->Chassis_Motor[2].chassis_motor_measure->speed);
	motor_speed_control(&Chassis_pid_calculate_f->Chassis_Speed_Pid[3], Chassis_pid_calculate_f->Chassis_Motor[3].Speed_Set, Chassis_pid_calculate_f->Chassis_Motor[3].chassis_motor_measure->speed);
}

void Chassis_Work(chassis_control_t *Chassis_Control_f)
{
	//ѡ�����ģʽ
	chassis_behaviour_choose(Chassis_Control_f);

	//���ݵ���ģʽ����x��y��yawֵ
	chassis_behaviour_react(Chassis_Control_f);

	//�˶��ֽ�
	chassis_motion_decomposition(Chassis_Control_f);

	// pid����
	Chassis_pid_calculate(Chassis_Control_f);
}
