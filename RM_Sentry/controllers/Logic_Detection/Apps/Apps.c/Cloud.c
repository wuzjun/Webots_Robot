/*
 * File:          Cloud.c
 * Date:       2021/3/16
 * Description:   云台控制
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Cloud.h>

Cloud_t Cloud;

void Cloud_Control(float VYaw, float VPitch)
{
	wb_motor_set_velocity(wheels[1], VYaw);  
	wb_motor_set_velocity(wheels[2], VPitch);
}

void Updata_Cloud_Radian_data(void)
{

	//更新IMU的Pitch轴的弧度
	//将函数返回值的地址中的值复制到数组中
	memcpy(Cloud.Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU), sizeof(double[3]));

	//过零处理
	//何时需要 + pai，后进行过零处理。当转一圈时所对应的值并非是连续单调的，而是转一圈是先单调减后单增的情况，就需要加上个值去使其单调
	Cloud.Yaw_Real_Radian = Cloud.Eular[2] + pai;
	if (Cloud.Yaw_Real_Radian - Cloud.Yaw_Last_Radian < -5.5)
	{
		Cloud.Yaw_Counts--;
	}
	else if (Cloud.Yaw_Last_Radian - Cloud.Yaw_Real_Radian < -5.5)
	{
		Cloud.Yaw_Counts++;
	}

	Cloud.Yaw_total_Radian = Cloud.Yaw_Real_Radian + Cloud.Yaw_Counts * pai;
	
	Cloud.Yaw_Last_Radian = Cloud.Yaw_Real_Radian;

}

/*
void Pitch_Gain_Radian(void)
{
	double y;				//用于算反正弦asin的自变量x 的 y
	double Real_Pitch_Radian;				//当前的Pitch轴的Radian

	//预防运动超限幅，而不符合sin运动函数的系数
	if (Cloud.Eular[1] > Pitch_Max_Radian)
	{
		Real_Pitch_Radian = Pitch_Max_Radian;
	}
	else if (Cloud.Eular[1] < Pitch_Min_Radian)
	{
		Real_Pitch_Radian = Pitch_Min_Radian;
	}
	else
	{
		Real_Pitch_Radian = Cloud.Eular[1];
	}

	y = (double)((Real_Pitch_Radian - Pitch_Centre_Radian) /(Pitch_Max_Radian - Pitch_Centre_Radian));

	Cloud.x_about_Radian = asin(y);

	printf("y = %lf\n", y);
	
}

void Pitch_Scan_Init(void)
{

	Pitch_Gain_Radian();

	Cloud.i = 1;

	//云台方向
	Cloud.Pitch_Scan_Dir = 1;
	//当前弧度作为目标弧度
	Cloud.Pitch_Target_Radian = Cloud.Eular[1];
	//当前速度作为目标速度
	Cloud.Pitch_Radian_pid.pwm = 0;

	//外环：弧度环初始化
	PositionPID_paraReset(&Cloud.Pitch_Radian_pid, 6.0f, 0.0f, 0.0f, 50.0f, 0.0f);
	//内环：速度环初始
	//PositionPID_paraReset(&Cloud.Pitch_Velocity_pid, -3.0f, 0.0f, 0.0f, 80.0f, 0.0f);
	//不可给内环：它不比6020，它并非是通过电压来控制的。
	//6020：速度PID输出的电压值，是要使其当前速度追上目标速度
	//webots：速度PID输出的只能再作为速度值，这就使原先向趋向的目标速度，又给取代掉了


}

void Pitch_Scan_Processing(void)
{
	float Kp = 1;

	Cloud.Pitch_Target_Radian = (Pitch_Max_Radian - Pitch_Centre_Radian)*sin(Cloud.x_about_Radian) +(Pitch_Centre_Radian );

	//外环
	Position_PID(&Cloud.Pitch_Radian_pid, Cloud.Pitch_Target_Radian, Cloud.Eular[1]);
	//内环：
	//Position_PID(&Cloud.Pitch_Velocity_pid, Cloud.Pitch_Radian_pid.pwm, Cloud.Pitch_Velocity);
	wb_motor_set_velocity(wheels[2], Cloud.Pitch_Radian_pid.pwm);

	Cloud.x_about_Radian += (Cloud.Pitch_Scan_Dir * uint_Radian_Increment * Kp);
	
}
void Yaw_Scan_Init(void)
{
	Cloud.Yaw_Target_Radian = Cloud.Eular[2];					//刚进入扫描时，保存此刻的值
	Cloud.Yaw_Scan_Dir = 1;
	Cloud.Yaw_Scan_Status = 1;

	Cloud.Yaw_Radian_pid.pwm = 0;

	Cloud.i = 1;

	//外环：弧度环初始化
	PositionPID_paraReset(&Cloud.Yaw_Radian_pid, 50.0f, 0.0f, 0.0f, 50.0f, 0.0f);				//Kp得到50 才跟的上
		

}

void Yaw_Scan_Processing(void)
{
	float Kp = 1;
	Cloud.Yaw_Target_Radian += Cloud.Yaw_Scan_Dir * Radian_To_Angle * Kp;
	
	//左右摇摆
	if (Cloud.Yaw_Target_Radian >= Yaw_Max_Radian && Cloud.Yaw_Scan_Status == 1)
	{
		Cloud.Yaw_Scan_Dir = -1;
		Cloud.Yaw_Scan_Status = 0;
	}
	else if (Cloud.Yaw_Target_Radian <= Yaw_Min_Radian && Cloud.Yaw_Scan_Status == 0)
	{
		Cloud.Yaw_Scan_Dir = 1;
		Cloud.Yaw_Scan_Status = 1;
	}
	//外环
	Position_PID(&Cloud.Yaw_Radian_pid, Cloud.Yaw_Target_Radian, Cloud.Eular[2]);
	//
	wb_motor_set_velocity(wheels[1], Cloud.Yaw_Radian_pid.pwm);

}
*/