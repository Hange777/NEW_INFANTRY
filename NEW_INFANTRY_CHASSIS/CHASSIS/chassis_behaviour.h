#ifndef __CHASSIS_BEHAVIOUR_H
#define __CHASSIS_BEHAVIOUR_H


#include "struct_variables.h"
#include "chassis_task.h"


typedef enum
{
	CHASSIS_ZERO_FORCE = 0, //��������
	
	CHASSIS_FOLLOW,     //����
    CHASSIS_NO_FOLLOW,  //������
    CHASSIS_TWIST_WAIST, //Ť��
    CHASSIS_ROTATION,    //С����
	CHASSIS_BATTERY,     //��̨ģʽ
} chassis_behaviour_e;

#endif
