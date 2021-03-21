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

void Updata_Cloud_data(void)
{
	//������̨Pitch���ת��
	Cloud.Pitch_Velocity = wb_motor_get_max_velocity(wheels[2]);
	
	//����IMU��Pitch��Ļ���
	//����������ֵ�ĵ�ַ�е�ֵ���Ƶ�������
	memcpy(Cloud.Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU), sizeof(double[3]));

	//printf("Pitch : %lf\n", Cloud.Eular[1]);

}

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
	PositionPID_paraReset(&Cloud.Pitch_Radian_pid, 6.0f, 0.0f, 0.0f, 80.0f, 0.0f);
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

	printf("Cloud.Pitch_Target_Radian: %lf\n", Cloud.Pitch_Target_Radian);

	//�⻷
	Position_PID(&Cloud.Pitch_Radian_pid, Cloud.Pitch_Target_Radian, Cloud.Eular[1]);
	//�ڻ���
	//Position_PID(&Cloud.Pitch_Velocity_pid, Cloud.Pitch_Radian_pid.pwm, Cloud.Pitch_Velocity);
	wb_motor_set_velocity(wheels[2], Cloud.Pitch_Radian_pid.pwm);

	Cloud.x_about_Radian += (Cloud.Pitch_Scan_Dir * uint_Radian_Increment * Kp);
	

}
