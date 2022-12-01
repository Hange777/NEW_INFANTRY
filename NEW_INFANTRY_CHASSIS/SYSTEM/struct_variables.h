#ifndef __STRUCT_VARIABLES_H
#define __STRUCT_VARIABLES_H


#include "main.h"
#include "parameter.h"


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
//#include "pid.h"
//#include "maths.h"
//#include "rm_motor.h"


/********************REFEREE********************/
//#include "crc.h"
//#include "referee_deal.h"



typedef enum
{
	INF_STOP = 0, //停止
	INF_RC,       //遥控器
	INF_MK,       //键盘
} infantry_state_e;


//rm电机统一数据结构体
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


//超级电容
typedef struct
{		
	float input_voltage;  //输入电压
	float Capacitance_voltage;  //电容电压
	float Input_current;  //输入电流
	float Set_power;  //设定功率
}Supercapacitor_receive_t;    //超级电容器



//Y轴数据  数据类型没变
typedef struct //__packed
{		
	int8_t photoelectric_zero;   //Y轴中值光电标志
	int8_t Gimbal_supply_flag;   //补给状态标志位(0:归中状态，进入补给状态  1:云台90度转动中  2:到达指定位置  3:归中中   4：补给模式结束)
	int8_t Gimbal_all_flag;      //发送给底盘的初始化成功标志
	
	float chassis_gimbal_angel;
	int16_t pitch_angle;
	uint8_t gimbal_beh;
	
} chassis_receive_gimbal_t;



/***************************************底盘*******************************/
typedef struct
{
	  motor_measure_t *chassis_motor_measure;  //接收电机的数据
    fp32 accel;
    fp32 speed;
    fp32 Speed_Set;
	fp32 position;

	int16_t give_current;
    int16_t pid_output;
	
}Motor_t;


/*键盘按键结构体*/
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
	const RC_ctrl_t *Chassis_RC;  //底盘遥控数据
	MK_Key_WSAD_t Key;			  //底盘键盘数据
	
	const chassis_receive_gimbal_t *Gimbal_Yaw_Data; //云台板处理数据，数据由can2传输给底盘板，底盘板再输出给yaw轴电机
	const Supercapacitor_receive_t *super_cap_c;
	
	Motor_t    Chassis_Motor[4];      //底盘四个电机
//	PidTypeDef Chassis_Speed_Pid[4];  //正常移动的pid
//	PidTypeDef Chassis_Location_Pid;  //底盘位置环pid
//	PidTypeDef Chassis_Spin_Pid;      //旋转pid
//	PidTypeDef Chassis_Power_Pid;     //功率限制pid
//	
//	first_order_filter_type_t LowFilt_chassis_vx; //低通滤波器
//  first_order_filter_type_t LowFilt_chassis_vy; //低通滤波器
	
	
	fp32 Chassis_Speed_X_Set;   //底盘x方向的速度
	fp32 Chassis_Speed_Y_Set;	//底盘y方向的速度
	fp32 Chassis_Speed_Z_Set;	//底盘z方向的速度  旋转
	
	
	fp32 Chassis_Gimbal_Diference_Angle;  //底盘与云台的差角
	uint8_t SuperCap_Discharge_Flag;      //超级电容放电标志位
	
	fp32 chassis_speed_gain;
	fp32 chassis_last_speed_gain;
	
	
}chassis_control_t;




extern void system_state_set(infantry_state_e state);
extern infantry_state_e system_state_return(void);



#endif

