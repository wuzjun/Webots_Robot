/*
 * File:          RN_Sentry_VS.c
 * Date:       2021/3/16
 * Description:   ģ���ڱ����˶��켣
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
#include <IMU.h>
#include <Encoder.h>

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
	IMU_Init(TIME_STEP);
	Encoder_Init(TIME_STEP);

	Cloud.i = 0;
	/* main loop
	 * Perform simulation steps of TIME_STEP milliseconds
	 * and leave the loop when the simulation is over
	 */
	while (wb_robot_step(TIME_STEP) != -1) {


		//���µ��̱�������ֵ
		Updata_Encoder_Radian();
		//������̨��Pitch��Yaw���ֵ
		Updata_Cloud_Radian_data();
		//�����Ӿ�������
		Vision_Updata();
		//���¼��������
		Laser_get_Data();

		if (Cloud.i == 0)
		{
			//����+������ �ĳ�ʼ��
			Chassis_add_Encoder_Init();
			//��̨�����Ŀ������ڻ�δ��IMU��û��PID
			//�Ӿ���ʼ��
			Vision_Init();

			Cloud.i = 1;
		}

		//����Ŀ��ƺ�������������������̨��ͬ������ƽṹ�����
		Vision_Control(&Vision, &All_Speed.VYaw, &All_Speed.VPitch);
		//��̨��ֱ�ӿ��ƺ���
		Cloud_Control(All_Speed.VYaw, All_Speed.VPitch);
		//��ѹ�������
		Optimally_Attack_Distance0(Cloud.Yaw_total_Radian, distance[0], &Chassis.Incremnet_Distance);
		//����+�������Ŀ��ƺ���
		Chassis_add_Encoder_Control(&All_Speed.VX);
		//����ֱ�ӿ��ƺ���
		Chassic_Control(All_Speed.VX);

		printf("Distance : %lf\n", distance[0]);
		////���°�����ֵ���������ڲ����ṹ�������
		//get_Keyboard_Control(&All_Speed.VX, &All_Speed.VYaw, &All_Speed.VPitch);

	};

	/* Enter your cleanup code here */

	/* This is necessary to cleanup webots resources */
	wb_robot_cleanup();

	return 0;
}
