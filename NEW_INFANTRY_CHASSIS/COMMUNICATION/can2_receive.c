/**
 *****************************东莞理工学院ACE实验室 *****************************
 * @file 			can2_receive.c
 *
 * @brief 		CAN2滤波器配置
                底盘CAN2接收：
 *              云台CAN2接收：
 * @history     2022年
 *
 @verbatim
 ==============================================================================


==============================================================================
 @endverbatim
 *****************************东莞理工学院ACE实验室 *****************************
 */


#include "can2_receive.h"
#include "can.h"
#include "parameter.h"
#include "struct_variables.h"
//#include "cmsis_os.h"

extern CAN_HandleTypeDef hcan2;

extern chassis_control_t chassis_control;


/*--------------------变量-----------------------*/
/*static*/ motor_measure_t motor_yaw;
extern RC_ctrl_t rc_ctrl;
static chassis_receive_gimbal_t gimbal_receive;

static portTickType CAN2LostTime = 0;
static uint16_t shooter_heat0_speed_limit = 0;
static uint8_t can2_red_or_blue = 0;


//返回接收云台数据，通过指针方式获取原始数据
const chassis_receive_gimbal_t *get_yaw_receive_measure_point(void)
{
    return &gimbal_receive;
}
//返回yaw电机变量地址，通过指针方式获取原始数据
motor_measure_t *get_yaw_gimbal_motor_measure_point(void)
{
    return &motor_yaw;
}


/**
	* @brief		can2滤波器配置
	* @param		none
	*	@retval		none
  */

void CAN2_filter_config(void)
{
    CAN_FilterTypeDef CAN2_FIilter_InitStruct;

								//开启滤波器
    CAN2_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //掩码模式
    CAN2_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32位工作
    CAN2_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterBank = 14;                                     // CAN2 滤波器组为14
		CAN2_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN2_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//指定接收邮箱
	  CAN2_FIilter_InitStruct.FilterActivation = ENABLE;	
	
    HAL_CAN_ConfigFilter(&hcan2, &CAN2_FIilter_InitStruct);							//根据指定配置CAN接收过滤器
    HAL_CAN_Start(&hcan2);																							//开启can2
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);	//启动中断

}


/*************************************can2接收*************************************/
/**
  * @brief      底盘板can2接收回调函数
  * @param[in]  *rx_message: can2接收结构体
  * @retval     none
  * @attention  在 chassis_app.h 中注册，中断调用（can2_callback(&rx2_message);）
  */
void chassis_can2_callback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef	Rxmessage;															//接收信息结构体
	uint8_t Rx_Data[8];																					//接收的信息缓存的数组

	if(  HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &Rxmessage, Rx_Data) == HAL_OK)	//读取接收的信息
	{
		switch (Rxmessage.StdId)
		{
//			case 0x201:
//			{
//				motor_yaw.position = (uint16_t)(Rx_Data[0] << 8)|Rx_Data[1];
//				motor_yaw.speed = (uint16_t)(Rx_Data[2] << 8)|Rx_Data[3];
//				break;
//			}
			case 0x300:
			{

				gimbal_receive.chassis_gimbal_angel = (((Rx_Data[0] << 8 | Rx_Data[1]) / 100.f) - 180.f);
			    break;
			}
			
		}
	}
	

}

/**
  * @brief          返回can2接收回来的17mm枪管射速上限
  * @param[in]      none
  * @retval         17mm枪管射速上限
  * @attention      用于云台板
  */
uint16_t re_can2_shooter_heat0_speed_limit(void)
{
    return (shooter_heat0_speed_limit);
}

/**
  * @brief          返回can2接收回来的底盘和云台的差角
  * @param[in]      none
  * @retval         底盘和云台的差角
  * @attention      用于底盘板
  */
float re_chassis_gimbal_angel(void)
{
    return (gimbal_receive.chassis_gimbal_angel);
}

/**
  * @brief          返回can2接收回来的pitch轴角度
  * @param[in]      none
  * @retval         pitch轴角度
  * @attention      用于底盘板
  */
float re_gimbal_pitch_angle(void)
{
    return (fp32)(gimbal_receive.pitch_angle * 360.0f / 1024);   //P轴编码器数据转化成角度
}

/**
  * @brief          返回can2接收回来的云台模式
  * @param[in]      none
  * @retval         云台模式
  * @attention      用于底盘板
  */
int re_gimbal_behaviour(void)
{
    return (int)(gimbal_receive.gimbal_beh);
}

/**
  * @brief          返回can2接收回来的红方 蓝方
  * @param[in]      none
  * @retval         自身是红方还是蓝方
  * @attention      用于云台板
  */
uint8_t re_robot_red_or_blue(void)
{
	return can2_red_or_blue;
}




