#ifndef __CHASSIS_BEHAVIOUR_H
#define __CHASSIS_BEHAVIOUR_H


#include "struct_variables.h"
#include "chassis_task.h"


typedef enum
{
	CHASSIS_ZERO_FORCE = 0, //底盘无力
	
	CHASSIS_FOLLOW,     //跟随
    CHASSIS_NO_FOLLOW,  //不跟随
    CHASSIS_TWIST_WAIST, //扭腰
    CHASSIS_ROTATION,    //小陀螺
	CHASSIS_BATTERY,     //炮台模式
} chassis_behaviour_e;

#endif
