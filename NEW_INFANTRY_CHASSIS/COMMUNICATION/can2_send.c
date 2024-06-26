#include "can2_send.h"
#include "can.h"

static CAN_TxHeaderTypeDef Txmessage; //发送的信息

/**
 * @brief		底盘CAN2发送键盘的数据
 * @param		none
 *	@retval		none
 */
void can2_chassis_to_gambal(const RC_ctrl_t *can2_MK_send)
{
	uint32_t send_mail_box; //发送邮箱
	uint8_t Data[8];		//发送数据的数组

	Txmessage.StdId = 0x401;	  //根据820r设置标识符
	Txmessage.IDE = CAN_ID_STD;	  //指定将要传输的消息的标识符的类型
	Txmessage.RTR = CAN_RTR_DATA; //指定的帧将被传输的消息的类型   数据帧或远程帧
	Txmessage.DLC = 8;

	Data[0] = (can2_MK_send->mouse.x >> 8);
	Data[1] = can2_MK_send->mouse.x;
	Data[2] = (can2_MK_send->mouse.y >> 8);
	Data[3] = can2_MK_send->mouse.y;
	Data[4] = (can2_MK_send->kb.key_code >> 8);
	Data[5] = can2_MK_send->kb.key_code;
	Data[6] = (can2_MK_send->rc.s[0]) * 10 + (can2_MK_send->rc.s[1]);
	Data[7] = ((can2_MK_send->mouse.press_l + 1) * 10 + can2_MK_send->mouse.press_r);

	HAL_CAN_AddTxMessage(&hcan2, &Txmessage, Data, &send_mail_box); //将一段数据通过 CAN 总线发送
}
