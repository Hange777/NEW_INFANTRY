#ifndef __STRUCT_VARIABLES_H
#define __STRUCT_VARIABLES_H

#include "main.h"
#include "parameter.h"
#include "struct_typedef.h"

/*  系统头文件 */
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
	CHASSIS_ZERO_FORCE = 0, //底盘无力
	CHASSIS_FOLLOW,			//跟随
	CHASSIS_NO_FOLLOW,		//不跟随
	CHASSIS_ROTATION,		//小陀螺
	CHASSIS_BATTERY,		//炮台模式
} chassis_behaviour_e;

typedef enum
{
	INF_STOP = 0, //停止
	INF_RC,		  //遥控器
	INF_MK,		  //键盘
} infantry_state_e;

// rm电机统一数据结构体
typedef struct
{
	uint16_t position;
	int16_t speed;
} motor_measure_t;

//超级电容
typedef struct
{
	float input_voltage;	   //输入电压
	float Capacitance_voltage; //电容电压
	float Input_current;	   //输入电流
	float Set_power;		   //设定功率
} Supercapacitor_receive_t;	   //超级电容器

typedef struct
{
	motor_measure_t *chassis_motor_measure; //接收电机的数据
	fp32 Speed_Set;							//设置速度
	int16_t give_current;					// pid输出
} Motor3508_t;

typedef struct
{
	RC_ctrl_t *Chassis_RC; //底盘遥控数据

	chassis_behaviour_e *behaviour; //底盘模式
	infantry_state_e *state;		//键鼠状态

	Motor3508_t Chassis_Motor[4];		  //底盘四个电机
	pid_parameter_t Chassis_Speed_Pid[4]; //正常移动的pid
	pid_parameter_t Chassis_Location_Pid; //底盘位置环pid
	pid_parameter_t chassis_rotate_pid;	  //旋转pid

	first_order_filter_type_t LowFilt_chassis_vx; //低通滤波器
	first_order_filter_type_t LowFilt_chassis_vy; //低通滤波器

	fp32 Chassis_Speed_X_Set; //底盘x方向的速度
	fp32 Chassis_Speed_Y_Set; //底盘y方向的速度
	fp32 Chassis_Speed_Z_Set; //底盘z方向的速度  旋转

	fp32 Chassis_Gimbal_Diference_Angle; //底盘与云台的差角

	Supercapacitor_receive_t *super_cap_c; //超电
	fp32 chassis_speed_gain;			   //速度因子
	fp32 chassis_last_speed_gain;

} chassis_control_t;

#endif
