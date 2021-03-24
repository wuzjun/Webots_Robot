/*
 * File:          Chassis.c
 * Date:       2021/3/16
 * Description:   底盘控制
 * Author:  CJF&WZJ
 * Modifications:
 */

#include <Chassis.h>

Chassis_t Chassis;

void Chassic_Control(float VX)
{
	wb_motor_set_velocity(wheels[0], VX);

}

float Chassis_Cruise_Velocity = 25;
void Chassis_Cruise_Processing(void)
{
	if (Chassis_Cruise_Velocity > 0 && distance[2] < 0.2)
	{
		Chassis_Cruise_Velocity = -25;
	}
	else if (Chassis_Cruise_Velocity < 0 && distance[1] < 0.2)
	{
		Chassis_Cruise_Velocity = 25;
	}
	wb_motor_set_velocity(wheels[0], Chassis_Cruise_Velocity);

}

//对于编码器的坐标是：以右为正
//对于速度的坐标是：以左为正
//所以将来参数正负号的确定就可知了
void Optimally_Attack_Distance0(double real_Angle, double real_depth, double* b)
{

	Chassis.Yaw_Raw_Increment_Radian = (real_Angle - 0 +(2 * pai * Cloud.Yaw_Counts));						//以0作为参考系可以确保得到的角的弧度值为正值。
	if (Chassis.Yaw_Raw_Increment_Radian > pai)					//判断是否大于180°，即在轨道一侧
	{
		Chassis.Yaw_Increment_Radian = Chassis.Yaw_Raw_Increment_Radian - pai;
	}
	else                                                        //轨道的另一侧时，云台的角的弧度值需要做处理，使其处于个180°内(即不可大于三角形内角和)
	{
		Chassis.Yaw_Increment_Radian = Chassis.Yaw_Raw_Increment_Radian;
	}

	float a = Best_Attcak_Distance; 
	float c = real_depth;

	//计算出角A的余弦值
	double COS_A = cos(Chassis.Yaw_Increment_Radian);

	//根据余弦定理和判别公式 算出delta
	double delta = pow(a, 2) - pow(c, 2) + pow(c, 2)*pow(COS_A, 2);

	if (delta <= 0.0f)
	{
		*b = COS_A * c;
	}
	else
	{
		*b = COS_A * c - sqrt(delta);
	}
}

//底盘+编码器 控制初始化
void Chassis_add_Encoder_Init(void)
{
	//将当前的底盘的位置距离作为目标距离
	Chassis.Target_Distance = Chassis.Real_Distance;
	//
	Chassis.Incremnet_Distance = 0;
	//直接使底盘不动
	Chassis.Encoder_pid.pwm = 0;
	//底盘编码器PID的初始化
	PositionPID_paraReset(&Chassis.Encoder_pid, 40.0, 0.0, 0.0, 50, 0.0);
}

//底盘+编码器 控制
void Chassis_add_Encoder_Control(float* VX)
{
	//在轨道的一侧
	if (Chassis.Yaw_Raw_Increment_Radian > pai)
	{
		Chassis.Target_Distance =   Chassis.Real_Distance - Chassis.Incremnet_Distance;
		if (Chassis.Real_Distance <= Chassis_Min_Distance && Chassis.Incremnet_Distance <= 0)
		{
			*VX = 0;
			return;
		}
		else if (Chassis.Real_Distance >= Chassis_Max_Distance && Chassis.Incremnet_Distance >= 0)
		{
			*VX = 0;
			return;
		}
	}
	else            //在轨道的另一侧（移动的只需要改变方向，即是改变底盘移动增量的方向；而限位的即受底盘增量方向的影响，也需要改变；PID的就不用变）
	{
		Chassis.Target_Distance = Chassis.Incremnet_Distance + Chassis.Real_Distance;
		if (Chassis.Real_Distance <= Chassis_Min_Distance && Chassis.Incremnet_Distance >= 0)
		{
			*VX = 0;
			return;
		}
		else if (Chassis.Real_Distance >= Chassis_Max_Distance && Chassis.Incremnet_Distance <= 0)
		{
			*VX = 0;
			return;
		}

	}

	//编码器环：
	Position_PID(&Chassis.Encoder_pid, Chassis.Target_Distance, Chassis.Real_Distance);
	//设置电机速度
	*VX = Chassis.Encoder_pid.pwm;

}



