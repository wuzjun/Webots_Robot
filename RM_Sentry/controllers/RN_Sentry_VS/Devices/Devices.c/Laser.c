/*
 * File:          Laser.c
 * Date:       2021/3/16
 * Description:   ¼¤¹â²â¾à
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Laser.h>

WbDeviceTag laser[3];
double distance[3];

void Laser_Init(int TIME_STEP)
{
	char lasters_names[3][8] = {
		"laser0", "laser1", "laser2" };

	for (int i = 0; i < 3; i++)
	{
		laser[i] = wb_robot_get_device(lasters_names[i]);
		wb_distance_sensor_enable(laser[i], TIME_STEP);
	}

}

void Laser_get_Data(void)
{
	for (int i = 0; i < 3; i++)
	{
		distance[i] = wb_distance_sensor_get_value(laser[i]);

	}
	//printf("distance0 = %lf\n", distance[0]);
	//printf("distance1 = %lf\n", distance[1]);
	//printf("distance2 = %lf\n", distance[2]);
}