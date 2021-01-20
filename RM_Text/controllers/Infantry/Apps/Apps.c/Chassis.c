#include <Chassis.h>
#include <Cloud.h>
#include <IMU.h>

Chassis_t Chassis;

WbDeviceTag wheels[4];

/**
  * @brief  底盘初始化
  * @param  None
  * @retval None
  */
void Chassis_Init(void)
{
	Chassis.targetXLPF = 0;
	Chassis.targetYLPF = 0;
	Chassis.targetZLPF = 0;

	// initialize motors

	char wheels_names[4][8] = {
	"motor1", "motor2", "motor3", "motor4" };

	//轮子电机
	for (int i = 0; i < 4; i++)
	{
		wheels[i] = wb_robot_get_device(wheels_names[i]);
		wb_motor_set_position(wheels[i], INFINITY);
		wb_motor_set_velocity(wheels[i], 0);
	}
}


//运动解算
void Wheat_Wheel_Solution(float Vx, float Vy, float VOmega, float *speed)
{
	float tempSpeed[4];
	float MaxSpeed = 0.0f;
	float Param = 1.0f;

	//四轮速度分解
	tempSpeed[0] = Vx - Vy + VOmega;
	tempSpeed[1] = -Vx - Vy + VOmega;
	tempSpeed[2] = Vx + Vy + VOmega;
	tempSpeed[3] = -Vx + Vy + VOmega;

	//寻找最大速度
	for (int i = 0; i < 4; i++)
	{
		if (abs(tempSpeed[i]) > MaxSpeed)
		{
			MaxSpeed = abs(tempSpeed[i]);
		}
	}

	//速度分配
	if (MaxSpeed > WheelMaxSpeed)
	{
		Param = (float)WheelMaxSpeed / MaxSpeed;
	}

	for (int i = 0; i < 4; i++)
	{
		speed[i] = tempSpeed[i] * Param;
	}

}


int ComputeMinOffset(int target, int value) //计算最小偏差，底盘跟随应该往哪个方向去完成跟随动作。
{
	int err = target - value;

	if (err > 180)
	{
		err -= 360;
	}
	else if (err < -180)
	{
		err += 360;
	}
	return err;
}



void Chassis_Control(float Vx, float Vy, float VOmega, float *speed)
{
	Cloud.angle = ComputeMinOffset(0, IMU.Eular[2]);

	VOmega = Position_PID(&Chassis.FollowYawAttitude_pid, Cloud.angle, 0.0f);
	//Position_PID(&Chassis.FollowYawSpeed_pid, Chassis.FollowYawAttitude_pid.pwm, IMUExport_Chassis.Finally_Gyro.z);

	Wheat_Wheel_Solution(Vx, Vy, VOmega, speed);

	for (int i = 0; i < 4; i++)
	{
		wb_motor_set_velocity(wheels[i], speed[i]);

	}

}