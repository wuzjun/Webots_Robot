/*
 * File:          Cloud.c
 * Date:       2021/3/16
 * Description:   ��̨����
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

	//����IMU��Pitch��Ļ���
	//����������ֵ�ĵ�ַ�е�ֵ���Ƶ�������
	memcpy(Cloud.Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU), sizeof(double[3]));

	//���㴦��
	//��ʱ��Ҫ + pai������й��㴦����תһȦʱ����Ӧ��ֵ���������������ģ�����תһȦ���ȵ��������������������Ҫ���ϸ�ֵȥʹ�䵥��
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
	double y;				//�����㷴����asin���Ա���x �� y
	double Real_Pitch_Radian;				//��ǰ��Pitch���Radian

	//Ԥ���˶����޷�����������sin�˶�������ϵ��
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

	//��̨����
	Cloud.Pitch_Scan_Dir = 1;
	//��ǰ������ΪĿ�껡��
	Cloud.Pitch_Target_Radian = Cloud.Eular[1];
	//��ǰ�ٶ���ΪĿ���ٶ�
	Cloud.Pitch_Radian_pid.pwm = 0;

	//�⻷�����Ȼ���ʼ��
	PositionPID_paraReset(&Cloud.Pitch_Radian_pid, 6.0f, 0.0f, 0.0f, 50.0f, 0.0f);
	//�ڻ����ٶȻ���ʼ
	//PositionPID_paraReset(&Cloud.Pitch_Velocity_pid, -3.0f, 0.0f, 0.0f, 80.0f, 0.0f);
	//���ɸ��ڻ���������6020����������ͨ����ѹ�����Ƶġ�
	//6020���ٶ�PID����ĵ�ѹֵ����Ҫʹ�䵱ǰ�ٶ�׷��Ŀ���ٶ�
	//webots���ٶ�PID�����ֻ������Ϊ�ٶ�ֵ�����ʹԭ���������Ŀ���ٶȣ��ָ�ȡ������


}

void Pitch_Scan_Processing(void)
{
	float Kp = 1;

	Cloud.Pitch_Target_Radian = (Pitch_Max_Radian - Pitch_Centre_Radian)*sin(Cloud.x_about_Radian) +(Pitch_Centre_Radian );

	//�⻷
	Position_PID(&Cloud.Pitch_Radian_pid, Cloud.Pitch_Target_Radian, Cloud.Eular[1]);
	//�ڻ���
	//Position_PID(&Cloud.Pitch_Velocity_pid, Cloud.Pitch_Radian_pid.pwm, Cloud.Pitch_Velocity);
	wb_motor_set_velocity(wheels[2], Cloud.Pitch_Radian_pid.pwm);

	Cloud.x_about_Radian += (Cloud.Pitch_Scan_Dir * uint_Radian_Increment * Kp);
	
}
void Yaw_Scan_Init(void)
{
	Cloud.Yaw_Target_Radian = Cloud.Eular[2];					//�ս���ɨ��ʱ������˿̵�ֵ
	Cloud.Yaw_Scan_Dir = 1;
	Cloud.Yaw_Scan_Status = 1;

	Cloud.Yaw_Radian_pid.pwm = 0;

	Cloud.i = 1;

	//�⻷�����Ȼ���ʼ��
	PositionPID_paraReset(&Cloud.Yaw_Radian_pid, 50.0f, 0.0f, 0.0f, 50.0f, 0.0f);				//Kp�õ�50 �Ÿ�����
		

}

void Yaw_Scan_Processing(void)
{
	float Kp = 1;
	Cloud.Yaw_Target_Radian += Cloud.Yaw_Scan_Dir * Radian_To_Angle * Kp;
	
	//����ҡ��
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
	//�⻷
	Position_PID(&Cloud.Yaw_Radian_pid, Cloud.Yaw_Target_Radian, Cloud.Eular[2]);
	//
	wb_motor_set_velocity(wheels[1], Cloud.Yaw_Radian_pid.pwm);

}
*/