#include "chassis_task.h"
#include "chassis_app.h"

#include "can1_receive.h"

chassis_control_t Chassis_Control;
static void Chassis_Init(chassis_control_t *Chassis_Control);

void Task_Chassis(void const * argument)
{
  uint32_t currentTime;	
	
	Chassis_Init(&Chassis_Control);
	//vTaskDelay(5);
	
	while(1)
	{
    currentTime = xTaskGetTickCount();//��ǰϵͳʱ��
		
		Chassis_Work(&Chassis_Control);
		
		taskENTER_CRITICAL();  //�����ٽ���
//		Chassis_TO_Gimbal(&Chassis_Control);
//		can1_chassis_setmsg(Chassis_Control.Chassis_Motor[0].give_current,
//                            Chassis_Control.Chassis_Motor[1].give_current,
//                            Chassis_Control.Chassis_Motor[2].give_current,
//                            Chassis_Control.Chassis_Motor[3].give_current);

		taskEXIT_CRITICAL();   //�˳��ٽ���
		
		vTaskDelayUntil(&currentTime, 2);//������ʱ//vTaskDelay(2)
	}
}
/**
  * @brief          �������ݳ�ʼ��
  * @param[in]      *chassis_move_init_f���������ṹ��
  * @retval         none
  */
static void Chassis_Init(chassis_control_t *chassis_data_init_f)
{
	uint8_t i;
	
	chassis_data_init_f->Chassis_RC = get_remote_control_point();  //��ȡң�ص�ָ��
	
	for(i = 0; i < 4; i++)
	{
		chassis_data_init_f->Chassis_Motor[i].chassis_motor_measure = get_chassis_motor_measure_point(i); //��ȡ�����ĸ������ָ��
	}

	//��ȡ�������ݵ�ָ��
//	chassis_data_init_f->super_cap_c = get_supercap_control_point();
	
	//��ȡ����ģʽ��ָ��
//	chassis_beh = get_chassis_behaviour_point();
	
	//��ʼ����ͨ�˲�  ��Ҫ���ֵ,������ң�غͼ��̵�ֵ���˲�
//	 first_order_filter_init(&(chassis_data_init_f->LowFilt_chassis_vx), CHASSIS_FIRST_ORDER_FILTER_K);
//   first_order_filter_init(&(chassis_data_init_f->LowFilt_chassis_vy), CHASSIS_FIRST_ORDER_FILTER_K);
	
	/*--------------------��ʼ������pid--------------------*/
	{
		/*����pid��ʼ��*/
//		pid_init(&chassis_data_init_f->Chassis_Speed_Pid[0],CHASSIS_RF_MOTOR_KP,CHASSIS_RF_MOTOR_KI,CHASSIS_RF_MOTOR_KD);
//		pid_init(&chassis_data_init_f->Chassis_Speed_Pid[1],CHASSIS_LF_MOTOR_KP,CHASSIS_LF_MOTOR_KI,CHASSIS_LF_MOTOR_KD);
//		pid_init(&chassis_data_init_f->Chassis_Speed_Pid[2],CHASSIS_RB_MOTOR_KP,CHASSIS_RB_MOTOR_KI,CHASSIS_RB_MOTOR_KD);
//		pid_init(&chassis_data_init_f->Chassis_Speed_Pid[3],CHASSIS_LB_MOTOR_KP,CHASSIS_LB_MOTOR_KI,CHASSIS_LB_MOTOR_KD);
//		
//		//����λ�û�pid
//		pid_init(&chassis_data_init_f->Chassis_Location_Pid,CHASSIS_LOCATION_KP,CHASSIS_LOCATION_KI,CHASSIS_LOCATION_KD);
//		//������ת����pid
//		pid_init(&chassis_data_init_f->Chassis_Spin_Pid,CHASSIS_SPIN_FOLLOW_KP,CHASSIS_SPIN_FOLLOW_KI,CHASSIS_SPIN_FOLLOW_KD);
//		chassis_data_init_f->Chassis_Spin_Pid.errorabsmin = 0.5f;
//		chassis_data_init_f->Chassis_Spin_Pid.errorabsmax = 180.0f;
//		chassis_data_init_f->Chassis_Spin_Pid.deadband = 0.0f;
//		
//		//��������
//		pid_init(&chassis_data_init_f->Chassis_Power_Pid,10.0f,1.0f,20.5f);
//		chassis_data_init_f->Chassis_Power_Pid.errorabsmin = 0.0f;
//        chassis_data_init_f->Chassis_Power_Pid.errorabsmax = 5.0f;
	}
	
	//���̿���ʱ��Ҫ�������������ڻ�ȡָ���Ժ�
//	Chassis_Take_Off(1);     //�д���д
	
}
