/*
 * File:          Cloud.h
 * Date:       2021/3/16
 * Description:   ��̨����
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef __CLOUD_H
#define __CLOUD_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <Motor.h>
#include <IMU.h>
#include <string.h>
#include <stdint.h>
#include <PID.h>


#define Pitch_Max_Radian 0.81				//����λ
#define Pitch_Min_Radian -1.54				//����λ
#define Pitch_Centre_Radian (Pitch_Max_Radian + Pitch_Min_Radian)/2				//����ֵ

#define uint_Radian_Increment 0.04				//��ֵ��y=sinx ��x���Ա�������������ֵ�����Թ���
//												  �п��ܵ�λʱ�ӽ��������ӵ�̫��ʹ�ú����������ڵ�yֵʵ����ȡ����ֵ��û�м��� 
//												  ����ֵ�ϴ�ʱ��PID��KpҲҪ��Ӧ�����󣬲���ʹ�������޵�ʱ�ӽ�����׷��Ŀ�껡��ֵ�����򣬿���׷����Ŀ�껡��ֵʱ���͵����¸�ʱ�ӽ��ģ�����ֵ�ֱ��ˡ�
#define Radian_To_Angle 0.0174532925194			//�Ƕȶ�Ӧ�Ļ���
#define Yaw_Max_Radian 3.0				//Yaw�������λ
#define Yaw_Min_Radian -3.0                //Yaw�������λ

#define pai 3.1415926535

typedef struct {

	double Eular[3];

	double x_about_Radian;				//���ڻ��ȵ�sin�������Ա���
	
	double Pitch_Target_Radian;				//PitchĿ�껡��
	double Yaw_Target_Radian;				//YawĿ�껡��

	double Yaw_Real_Radian;				//Yaw��ĵ�ǰ����
	double Yaw_Last_Radian;				//Yaw����ϴ˻���
	int32_t Yaw_Counts;					//Yaw���Ȧ��
	double Yaw_total_Radian;			//Yaw����ܻ���

	uint8_t Pitch_Scan_Dir;				//Pitch��ɨ�跽��
	int8_t Yaw_Scan_Dir;				//Yaw��ɨ�跽��:ע������Ҫ��ֵ�����ܸ��uint8_t����������
	uint8_t Yaw_Scan_Status;			//Yawɨ��״̬��־λ

	positionpid_t Pitch_Radian_pid;				//Pitch�⻷���Ȼ�PID
	positionpid_t Yaw_Radian_pid;				//Yaw�⻷���Ȼ�PID

	uint8_t i;				//ɨ���ȡ����ֵ�޷�����While�⣬����ʱIMU��ʼ����ɺ��޷����̻�ȡ�䵱ǰֵ
							//����ֻ���ñ��������䣬��һ�ν���Whileʱ����ȡһЩɨ�軡��ֵ
	uint8_t j;

}Cloud_t;

extern Cloud_t Cloud;

void Cloud_Control(float VYaw, float VPitch);
void Updata_Cloud_Radian_data(void);

//void Pitch_Gain_Radian(void);
//void Pitch_Scan_Init(void);
//void Pitch_Scan_Processing(void);
//
//void Yaw_Scan_Init(void);
//void Yaw_Scan_Processing(void);

#endif/*__CLOUD_H*/
