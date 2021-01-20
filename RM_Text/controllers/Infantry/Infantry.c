/*
 * File:          Infantry.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

 /*
  * You may need to add include files like <webots/distance_sensor.h> or
  * <webots/motor.h>, etc.
  */
#include <webots/robot.h>
#include <stdio.h>
#include <stdint.h>
#include <Math.h>
  // Added a new include file
#include <webots/motor.h>
#include <PID.h>
#include <Chassis.h>
#include <Cloud.h>
#include <Key.h>
#include <Filter.h>
#include <AddMath.h>
#include <SpeedRamp.h>
//#include <IMU.h>
#include <Cameras.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 8

 /*
  * This is the main program.
  * The arguments of the main function can be specified by the
  * "controllerArgs" field of the Robot node
  */
int main(int argc, char **argv)
{
	wb_robot_init();
	IMU_Init();
	Gyro_Init();
	Cameras_Init();
	Cloud_Init();
	Chassis_Init();



	float speed[4] = { 0.0f };

	wb_keyboard_enable(TIME_STEP);

	while (wb_robot_step(TIME_STEP) != -1)
	{
		get_Keyboard_Control(&Chassis.targetXLPF, &Chassis.targetYLPF, &Cloud.Accumulate_YAW, &Cloud.Accumulate_Pitch);

		Cloud_Control(Cloud.Accumulate_YAW, Cloud.Accumulate_Pitch);

		//Chassis_Control(Chassis.targetXLPF, Chassis.targetYLPF, Chassis.targetZLPF, speed);


	}

	/* Enter your cleanup code here */

	/* This is necessary to cleanup webots resources */
	wb_robot_cleanup();

	return 0;
}
