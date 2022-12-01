/**
 *****************************��ݸ����ѧԺACEʵ���� *****************************
 * @file 			can2_receive.c
 *
 * @brief 		CAN2�˲�������
                ����CAN2���գ�
 *              ��̨CAN2���գ�
 * @history     2022��
 *
 @verbatim
 ==============================================================================


==============================================================================
 @endverbatim
 *****************************��ݸ����ѧԺACEʵ���� *****************************
 */


#include "can2_receive.h"
#include "can.h"
#include "parameter.h"
#include "struct_variables.h"
//#include "cmsis_os.h"

extern CAN_HandleTypeDef hcan2;

extern chassis_control_t chassis_control;


/*--------------------����-----------------------*/
/*static*/ motor_measure_t motor_yaw;
extern RC_ctrl_t rc_ctrl;
static chassis_receive_gimbal_t gimbal_receive;

static portTickType CAN2LostTime = 0;
static uint16_t shooter_heat0_speed_limit = 0;
static uint8_t can2_red_or_blue = 0;


//���ؽ�����̨���ݣ�ͨ��ָ�뷽ʽ��ȡԭʼ����
const chassis_receive_gimbal_t *get_yaw_receive_measure_point(void)
{
    return &gimbal_receive;
}
//����yaw���������ַ��ͨ��ָ�뷽ʽ��ȡԭʼ����
motor_measure_t *get_yaw_gimbal_motor_measure_point(void)
{
    return &motor_yaw;
}


/**
	* @brief		can2�˲�������
	* @param		none
	*	@retval		none
  */

void CAN2_filter_config(void)
{
    CAN_FilterTypeDef CAN2_FIilter_InitStruct;

								//�����˲���
    CAN2_FIilter_InitStruct.FilterMode = CAN_FILTERMODE_IDMASK;				  //����ģʽ
    CAN2_FIilter_InitStruct.FilterScale = CAN_FILTERSCALE_32BIT;				//32λ����
    CAN2_FIilter_InitStruct.FilterIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdHigh = 0x0000;
    CAN2_FIilter_InitStruct.FilterMaskIdLow = 0x0000;
    CAN2_FIilter_InitStruct.FilterBank = 14;                                     // CAN2 �˲�����Ϊ14
		CAN2_FIilter_InitStruct.SlaveStartFilterBank = 14;
    CAN2_FIilter_InitStruct.FilterFIFOAssignment = CAN_RX_FIFO0;				//ָ����������
	  CAN2_FIilter_InitStruct.FilterActivation = ENABLE;	
	
    HAL_CAN_ConfigFilter(&hcan2, &CAN2_FIilter_InitStruct);							//����ָ������CAN���չ�����
    HAL_CAN_Start(&hcan2);																							//����can2
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);	//�����ж�

}


/*************************************can2����*************************************/
/**
  * @brief      ���̰�can2���ջص�����
  * @param[in]  *rx_message: can2���սṹ��
  * @retval     none
  * @attention  �� chassis_app.h ��ע�ᣬ�жϵ��ã�can2_callback(&rx2_message);��
  */
void chassis_can2_callback(CAN_HandleTypeDef *hcan)
{
	CAN_RxHeaderTypeDef	Rxmessage;															//������Ϣ�ṹ��
	uint8_t Rx_Data[8];																					//���յ���Ϣ���������

	if(  HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &Rxmessage, Rx_Data) == HAL_OK)	//��ȡ���յ���Ϣ
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
  * @brief          ����can2���ջ�����17mmǹ����������
  * @param[in]      none
  * @retval         17mmǹ����������
  * @attention      ������̨��
  */
uint16_t re_can2_shooter_heat0_speed_limit(void)
{
    return (shooter_heat0_speed_limit);
}

/**
  * @brief          ����can2���ջ����ĵ��̺���̨�Ĳ��
  * @param[in]      none
  * @retval         ���̺���̨�Ĳ��
  * @attention      ���ڵ��̰�
  */
float re_chassis_gimbal_angel(void)
{
    return (gimbal_receive.chassis_gimbal_angel);
}

/**
  * @brief          ����can2���ջ�����pitch��Ƕ�
  * @param[in]      none
  * @retval         pitch��Ƕ�
  * @attention      ���ڵ��̰�
  */
float re_gimbal_pitch_angle(void)
{
    return (fp32)(gimbal_receive.pitch_angle * 360.0f / 1024);   //P�����������ת���ɽǶ�
}

/**
  * @brief          ����can2���ջ�������̨ģʽ
  * @param[in]      none
  * @retval         ��̨ģʽ
  * @attention      ���ڵ��̰�
  */
int re_gimbal_behaviour(void)
{
    return (int)(gimbal_receive.gimbal_beh);
}

/**
  * @brief          ����can2���ջ����ĺ췽 ����
  * @param[in]      none
  * @retval         �����Ǻ췽��������
  * @attention      ������̨��
  */
uint8_t re_robot_red_or_blue(void)
{
	return can2_red_or_blue;
}



