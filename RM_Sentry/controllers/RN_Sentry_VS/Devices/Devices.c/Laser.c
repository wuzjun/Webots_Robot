/*
 * File:          Laser.c
 * Date:       2021/3/16
 * Description:   º§π‚≤‚æ‡
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Laser.h>

WbDeviceTag laser0;
double distance;

void Laser_Init(int TIME_STEP)
{
	laser0 = wb_robot_get_device("laser0");
	wb_distance_sensor_enable(laser0, TIME_STEP);
}

void Laser_get_Data(void)
{
	distance = wb_distance_sensor_get_value(laser0);
	//printf("æ‡¿Î «£∫%lf\n", distance);
}