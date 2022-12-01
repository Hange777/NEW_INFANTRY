#ifndef __STRUCT_VARIABLES_H
#define __STRUCT_VARIABLES_H


#include "main.h"
#include "parameter.h"


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
//#include "pid.h"
//#include "maths.h"
//#include "rm_motor.h"


/********************REFEREE********************/
//#include "crc.h"
//#include "referee_deal.h"



typedef enum
{
	INF_STOP = 0, //ֹͣ
	INF_RC,       //ң����
	INF_MK,       //����
} infantry_state_e;


//rm���ͳһ���ݽṹ��
typedef struct
{
    uint16_t position;
    int16_t  speed;
    int16_t  given_current;
    uint8_t  temperate;
    int16_t  last_position;
	
	int16_t speed_filt;
	int16_t first_Flag;
	int32_t actual_Position;
	
	float actPositon_360;
}motor_measure_t;


//��������
typedef struct
{		
	float input_voltage;  //�����ѹ
	float Capacitance_voltage;  //���ݵ�ѹ
	float Input_current;  //�������
	float Set_power;  //�趨����
}Supercapacitor_receive_t;    //����������



//Y������  ��������û��
typedef struct //__packed
{		
	int8_t photoelectric_zero;   //Y����ֵ����־
	int8_t Gimbal_supply_flag;   //����״̬��־λ(0:����״̬�����벹��״̬  1:��̨90��ת����  2:����ָ��λ��  3:������   4������ģʽ����)
	int8_t Gimbal_all_flag;      //���͸����̵ĳ�ʼ���ɹ���־
	
	float chassis_gimbal_angel;
	int16_t pitch_angle;
	uint8_t gimbal_beh;
	
} chassis_receive_gimbal_t;



/***************************************����*******************************/
typedef struct
{
	  motor_measure_t *chassis_motor_measure;  //���յ��������
    fp32 accel;
    fp32 speed;
    fp32 Speed_Set;
	fp32 position;

	int16_t give_current;
    int16_t pid_output;
	
}Motor_t;


/*���̰����ṹ��*/
typedef struct
{
	float key_w;
    float key_s;
    float key_a;
    float key_d;
	
	float last_key_w;
    float last_key_s;
    float last_key_a;
    float last_key_d;
} MK_Key_WSAD_t;

typedef struct
{
	const RC_ctrl_t *Chassis_RC;  //����ң������
	MK_Key_WSAD_t Key;			  //���̼�������
	
	const chassis_receive_gimbal_t *Gimbal_Yaw_Data; //��̨�崦�����ݣ�������can2��������̰壬���̰��������yaw����
	const Supercapacitor_receive_t *super_cap_c;
	
	Motor_t    Chassis_Motor[4];      //�����ĸ����
//	PidTypeDef Chassis_Speed_Pid[4];  //�����ƶ���pid
//	PidTypeDef Chassis_Location_Pid;  //����λ�û�pid
//	PidTypeDef Chassis_Spin_Pid;      //��תpid
//	PidTypeDef Chassis_Power_Pid;     //��������pid
//	
//	first_order_filter_type_t LowFilt_chassis_vx; //��ͨ�˲���
//  first_order_filter_type_t LowFilt_chassis_vy; //��ͨ�˲���
	
	
	fp32 Chassis_Speed_X_Set;   //����x������ٶ�
	fp32 Chassis_Speed_Y_Set;	//����y������ٶ�
	fp32 Chassis_Speed_Z_Set;	//����z������ٶ�  ��ת
	
	
	fp32 Chassis_Gimbal_Diference_Angle;  //��������̨�Ĳ��
	uint8_t SuperCap_Discharge_Flag;      //�������ݷŵ��־λ
	
	fp32 chassis_speed_gain;
	fp32 chassis_last_speed_gain;
	
	
}chassis_control_t;




extern void system_state_set(infantry_state_e state);
extern infantry_state_e system_state_return(void);



#endif

