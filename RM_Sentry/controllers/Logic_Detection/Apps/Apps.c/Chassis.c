/*
 * File:          Chassis.c
 * Date:       2021/3/16
 * Description:   µ×ÅÌ¿ØÖÆ
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Chassis.h>

void Chassic_Control(float VX)
{
	wb_motor_set_velocity(wheels[0], VX);

}

float Chassis_Cruise_Velocity = 25;
void Chassis_Cruise_Processing(void)
{
	if (Chassis_Cruise_Velocity > 0 && distance[2] < 0.2)
	{
		Chassis_Cruise_Velocity = -25;
	}
	else if (Chassis_Cruise_Velocity < 0 && distance[1] < 0.2)
	{
		Chassis_Cruise_Velocity = 25;
	}

	wb_motor_set_velocity(wheels[0], Chassis_Cruise_Velocity);

}

