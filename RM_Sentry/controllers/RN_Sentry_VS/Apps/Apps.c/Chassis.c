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

