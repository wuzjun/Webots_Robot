#include <webots/robot.h>
#include <stdio.h>
#include <stdint.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>
#include <Filter.h>
#include <AddMath.h>
#include <SpeedRamp.h>
#include <PID.h>
#include <Chassis.h>
#include <Key.h>


#define TIME_STEP 64
#define WheelMaxSpeed 5.0f

int main(int argc, char **argv)
{
	wb_robot_init();

	// initialize motors
	WbDeviceTag wheels[4];
	WbDeviceTag Turntable[4];
	char Turntable_names[4][8] = {
		"motor1", "motor2", "motor3", "motor4" };
	char wheels_names[4][8] = {
		"motor5", "motor6", "motor7", "motor8" };

	for (int i = 0; i < 4; i++)
	{
		//转盘电机
		Turntable[i] = wb_robot_get_device(Turntable_names[i]);
		wb_motor_set_velocity(Turntable[i], 5);
		//轮子电机
		wheels[i] = wb_robot_get_device(wheels_names[i]);
		wb_motor_set_position(wheels[i], INFINITY);
	}

	float position[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float Last_Position[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float Vx = 0.0f;
	float VOmega = 0.0f;
	int key = 0;

	wb_keyboard_enable(TIME_STEP);

	while (wb_robot_step(TIME_STEP) != -1)
	{
		get_Keyboard_Control(&Vx, &VOmega, &key);
		RubberWheel_Solve(&VOmega, position, Last_Position, key);

		for (int i = 0; i < 4; i++)
		{
			wb_motor_set_position(Turntable[i], position[i]);
		}

		for (int i = 0; i < 4; i++)
		{
			wb_motor_set_velocity(wheels[i], Vx);
		}
	}

	wb_robot_cleanup();

	return 0;
}