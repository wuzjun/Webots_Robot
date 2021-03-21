/*
 * File:          Motor.c
 * Date:       2021/3/16
 * Description:   ���ʹ��
 * Author:  CJF&WZJ
 * Modifications:
 */

#include <Motor.h>

WbDeviceTag wheels[3];
//wheels[3]={���̵����Yaw������Pitch����}
void Motor_Init(void)
{
	// initialize motors
	
	char wheels_names[3][8] = {
		"motor1", "motor2", "motor3"};

	for (int i = 0; i < 3; i++)
	{
		wheels[i] = wb_robot_get_device(wheels_names[i]);
		wb_motor_set_position(wheels[i], INFINITY);
	}
					
}

