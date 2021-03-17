/*
 * File:          Cloud.c
 * Date:       2021/3/16
 * Description:   ÔÆÌ¨¿ØÖÆ
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Cloud.h>

void Cloud_Control(float VYaw, float VPitch)
{
	wb_motor_set_velocity(wheels[1], VYaw);  
	wb_motor_set_velocity(wheels[2], VPitch);
}