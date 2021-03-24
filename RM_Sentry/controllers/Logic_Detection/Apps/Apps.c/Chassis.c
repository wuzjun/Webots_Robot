/*
 * File:          Chassis.c
 * Date:       2021/3/16
 * Description:   ���̿���
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

//���ڱ������������ǣ�����Ϊ��
//�����ٶȵ������ǣ�����Ϊ��
//���Խ������������ŵ�ȷ���Ϳ�֪��
void Optimally_Attack_Distance0(double real_Angle, double real_depth, double* b)
{

	Chassis.Yaw_Raw_Increment_Radian = (real_Angle - 0 +(2 * pai * Cloud.Yaw_Counts));						//��0��Ϊ�ο�ϵ����ȷ���õ��ĽǵĻ���ֵΪ��ֵ��
	if (Chassis.Yaw_Raw_Increment_Radian > pai)					//�ж��Ƿ����180�㣬���ڹ��һ��
	{
		Chassis.Yaw_Increment_Radian = Chassis.Yaw_Raw_Increment_Radian - pai;
	}
	else                                                        //�������һ��ʱ����̨�ĽǵĻ���ֵ��Ҫ������ʹ�䴦�ڸ�180����(�����ɴ����������ڽǺ�)
	{
		Chassis.Yaw_Increment_Radian = Chassis.Yaw_Raw_Increment_Radian;
	}

	float a = Best_Attcak_Distance; 
	float c = real_depth;

	//�������A������ֵ
	double COS_A = cos(Chassis.Yaw_Increment_Radian);

	//�������Ҷ�����б�ʽ ���delta
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

//����+������ ���Ƴ�ʼ��
void Chassis_add_Encoder_Init(void)
{
	//����ǰ�ĵ��̵�λ�þ�����ΪĿ�����
	Chassis.Target_Distance = Chassis.Real_Distance;
	//
	Chassis.Incremnet_Distance = 0;
	//ֱ��ʹ���̲���
	Chassis.Encoder_pid.pwm = 0;
	//���̱�����PID�ĳ�ʼ��
	PositionPID_paraReset(&Chassis.Encoder_pid, 40.0, 0.0, 0.0, 50, 0.0);
}

//����+������ ����
void Chassis_add_Encoder_Control(float* VX)
{
	//�ڹ����һ��
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
	else            //�ڹ������һ�ࣨ�ƶ���ֻ��Ҫ�ı䷽�򣬼��Ǹı�����ƶ������ķ��򣻶���λ�ļ��ܵ������������Ӱ�죬Ҳ��Ҫ�ı䣻PID�ľͲ��ñ䣩
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

	//����������
	Position_PID(&Chassis.Encoder_pid, Chassis.Target_Distance, Chassis.Real_Distance);
	//���õ���ٶ�
	*VX = Chassis.Encoder_pid.pwm;

}



