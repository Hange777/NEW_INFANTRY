#ifndef __STRUCT_VARIABLES_H
#define __STRUCT_VARIABLES_H

#include "main.h"
#include "parameter.h"
#include "struct_typedef.h"

/*  ϵͳͷ�ļ� */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stdint.h"

/* ************************FreeRTOS******************** */
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "cmsis_os.h"

/********************CONTROL********************/
#include "rc.h"
//#include "can1_receive.h"
//#include "can2_receive.h"
//#include "capacitor_control.h"
//#include "upper_machine.h"
//#include "visual.h"

/********************ALGORITHM********************/
//#include "fifo_buff.h"
#include "pid.h"
//#include "maths.h"
//#include "rm_motor.h"
#include "filter.h"

/********************REFEREE********************/
//#include "crc.h"
//#include "referee_deal.h"

typedef enum
{
	CHASSIS_ZERO_FORCE = 0, //��������
	CHASSIS_FOLLOW,			//����
	CHASSIS_NO_FOLLOW,		//������
	CHASSIS_ROTATION,		//С����
	CHASSIS_BATTERY,		//��̨ģʽ
} chassis_behaviour_e;

typedef enum
{
	INF_STOP = 0, //ֹͣ
	INF_RC,		  //ң����
	INF_MK,		  //����
} infantry_state_e;

// rm���ͳһ���ݽṹ��
typedef struct
{
	uint16_t position;
	int16_t speed;
} motor_measure_t;

//��������
typedef struct
{
	float input_voltage;	   //�����ѹ
	float Capacitance_voltage; //���ݵ�ѹ
	float Input_current;	   //�������
	float Set_power;		   //�趨����
} Supercapacitor_receive_t;	   //����������

typedef struct
{
	motor_measure_t *chassis_motor_measure; //���յ��������
	fp32 Speed_Set;							//�����ٶ�
	int16_t give_current;					// pid���
} Motor3508_t;

typedef struct
{
	RC_ctrl_t *Chassis_RC; //����ң������

	chassis_behaviour_e *behaviour; //����ģʽ
	infantry_state_e *state;		//����״̬

	Motor3508_t Chassis_Motor[4];		  //�����ĸ����
	pid_parameter_t Chassis_Speed_Pid[4]; //�����ƶ���pid
	pid_parameter_t Chassis_Location_Pid; //����λ�û�pid
	pid_parameter_t chassis_rotate_pid;	  //��תpid

	first_order_filter_type_t LowFilt_chassis_vx; //��ͨ�˲���
	first_order_filter_type_t LowFilt_chassis_vy; //��ͨ�˲���

	fp32 Chassis_Speed_X_Set; //����x������ٶ�
	fp32 Chassis_Speed_Y_Set; //����y������ٶ�
	fp32 Chassis_Speed_Z_Set; //����z������ٶ�  ��ת

	fp32 Chassis_Gimbal_Diference_Angle; //��������̨�Ĳ��

	Supercapacitor_receive_t *super_cap_c; //����
	fp32 chassis_speed_gain;			   //�ٶ�����
	fp32 chassis_last_speed_gain;

} chassis_control_t;

#endif
