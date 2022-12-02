#ifndef __CHASSIS_BEHAVIOUR_H
#define __CHASSIS_BEHAVIOUR_H

#include "struct_variables.h"

void chassis_behaviour_react(chassis_control_t *Chassis_behaviour_react_f);
void chassis_behaviour_choose(chassis_control_t *Chassis_behaviour_f);
void chassis_motion_decomposition(chassis_control_t *chassis_motion_decomposition_f);

chassis_behaviour_e *get_chassis_behaviour_point(void);
infantry_state_e *get_chassis_state_point(void);

#endif
