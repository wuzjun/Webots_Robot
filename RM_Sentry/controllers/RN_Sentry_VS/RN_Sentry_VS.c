/*
 * File:          RN_Sentry_VS.c
 * Date:       2021/3/16
 * Description:   模拟哨兵的运动轨迹
 * Author:  CJF&WZJ
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
#include <Chassis.h>
#include <Cloud.h>
#include <Key.h>
#include <Camera.h>
#include <Motor.h>
#include <Laser.h>

/*
 * You may want to add macros here.
 */
 //#define TIME_STEP 8
int TIME_STEP = 8;

/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
	/* necessary to initialize webots stuff */
	wb_robot_init();

	/*
	 * You should declare here WbDeviceTag variables for storing
	 * robot devices like this:
	 *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
	 *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
	 */
	Motor_Init();
	Keyboard_Init(TIME_STEP);
	Camera_Init(TIME_STEP);
	Laser_Init(TIME_STEP);
	Vision_Init();

	/* main loop
	 * Perform simulation steps of TIME_STEP milliseconds
	 * and leave the loop when the simulation is over
	 */
	while (wb_robot_step(TIME_STEP) != -1) {
		get_Keyboard_Control(&All_Speed.VX, &All_Speed.VYaw, &All_Speed.VPitch);
		//printf("Yaw_speed = %f\n", All_Speed.VYaw);
		//printf("Pitch_Speed = %f\n", All_Speed.VPitch);

		Vision_Updata();
		Vision_Control(&Vision, &All_Speed.VYaw, &All_Speed.VPitch);
		Chassic_Control(All_Speed.VX);
		Cloud_Control(All_Speed.VYaw, All_Speed.VPitch);
		Laser_get_Data();


	};

	/* Enter your cleanup code here */

	/* This is necessary to cleanup webots resources */
	wb_robot_cleanup();

	return 0;
}
