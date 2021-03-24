/*
 * File:          Chassis.h
 * Date:       2021/3/16
 * Description:   ���̿���
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef __CHIASSIS_H
#define __CHIASSIS_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <Motor.h>
#include <Laser.h>
#include <Cloud.h>
#include <Encoder.h>
#include <PID.h>

extern float Chassis_Cruise_Velocity;

/* ��ѹ�������Ĳ��� */
#define Yaw_Reference_Radain pai				//��̨Yaw��ο��Ļ���(��Ϊ�����Ƕȵ����) ǹ�����������ƽ��
#define Best_Attcak_Distance 3.20					//��ѹ�������

#define Chassis_Max_Distance 1.55				//���������ƶ�·��
#define Chassis_Min_Distance 0.1						//������С���ƶ�����

typedef struct
{
	double Yaw_Raw_Increment_Radian;
	double Yaw_Increment_Radian;				//��̨�Ļ�������

	double Incremnet_Distance;			//�����ƶ���·������

	double Real_Distance;				//���̵ĵ�ǰ·��
	positionpid_t Encoder_pid;				//���̱���������pid

	double Target_Distance;					//���̵�Ŀ�����

}Chassis_t;
extern Chassis_t Chassis;

void Chassic_Control(float VX);
void Chassis_Cruise_Processing(void);
void Optimally_Attack_Distance0(double real_Angle, double real_depth, double* b);
void Chassis_add_Encoder_Init(void);
void Chassis_add_Encoder_Control(float* VX);


#endif /* __CHIASSIS_H */


