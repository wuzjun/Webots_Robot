#include <Cloud.h>
#include <Chassis.h>
#include <IMU.h>

Cloud_t Cloud;

WbDeviceTag Cloud_Motor[2];

/**
  * @brief  ��ȡ��̨Yaw��ת�ĽǶȣ�ƫ�Ƴ���ǰ���ĽǶ�-���ĵ㣩
  * @param[in]  None
  * @retval 360�ȵĽǶ�ֵ��
  */
float Cloud_getYawAngleWithCenter(float angle) {
	return (angle - Cloud_Yaw_Center);
}

/**
  * @brief  ��̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
	Cloud.IMU_Cloud[2] = IMU.Eular[2];
	Cloud.IMU_Cloud[1] = 0;
	PositionPID_paraReset(&Chassis.FollowYawAttitude_pid, 7.0f, 0.0f, 0.0f, 30, 0);
	PositionPID_paraReset(&Chassis.FollowYawSpeed_pid, 0.34f, 0.0f, 0.0f, 30, 0);

	PositionPID_paraReset(&Cloud.YawAttitude_pid, -0.2f, 0.0f, 0.0f, 20, 3000);
	PositionPID_paraReset(&Cloud.YawSpeed_pid, 0.99f, 0.0f, 0.0f, 20, 3000);

	char Cloud_names[2][8] = {
		"motor5", "motor6" };

	Cloud_Motor[0] = wb_robot_get_device(Cloud_names[0]);
	//wb_motor_set_position(Cloud_Motor[0], 5);
	wb_motor_set_velocity(Cloud_Motor[0], 0);

	Cloud_Motor[1] = wb_robot_get_device(Cloud_names[1]);
	wb_motor_set_velocity(Cloud_Motor[1], 20);

}


/**
  * @brief  ��̨���ƴ���-��IMUģʽ
  * @param[in]  delta_yaw		����Ǳ仯��
  *				delta_pitch		�����Ǳ仯��
  * @retval None
  */
void Cloud_Control(float YAW, float PITCH)
{
	//Cloud.Yaw += YAW;
	Cloud.IMU_Cloud[2] += YAW;
	Cloud.IMU_Cloud[1] += PITCH;
	Get_IMU(&IMU);
	Get_Gyro(IMU.Angular_velocity);

	Position_PID(&Cloud.YawAttitude_pid, Cloud.IMU_Cloud[2], IMU.Eular_total[2]);
	Position_PID(&Cloud.YawSpeed_pid, Cloud.YawAttitude_pid.pwm, IMU.Angular_velocity[1]);
	
	wb_motor_set_velocity(Cloud_Motor[0], Cloud.YawSpeed_pid.pwm);
	wb_motor_set_position(Cloud_Motor[1], Cloud.IMU_Cloud[1]);

	//printf("roll = %lf:\n", IMU.Eular[0]);
	/*printf("Cloud.YawSpeed_pid.pwm = %lf:\n", Cloud.YawSpeed_pid.pwm);*/
	printf("Cloud_Motor[0] = %lf:\n", wb_motor_get_target_position(Cloud_Motor[0]));
	//printf("pitch = %lf:\n", IMU.Eular[1]);
	//printf("yaw = %lf:\n", IMU.Eular[2]);

	//printf("%f\n", wb_motor_get_target_position(Cloud_Motor[0]));
	//printf("%f\n", wb_motor_get_target_position(Cloud_Motor[1]));

}




