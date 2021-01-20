#ifndef __CHIASSIS_H
#define __CHIASSIS_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <PID.h>

#define WheelMaxSpeed 20.0f

/* �����˶� */
typedef struct {
	float targetXRaw;		//����x��ԭʼ����
	float targetYRaw;		//����y��ԭʼ����
	float targetZRaw;		//����z��ԭʼ����
	float LpfAttFactor;		//�����˲�ϵ��
	float targetXLPF;		//����x���˲�������
	float targetYLPF;		//����y���˲�������
	float targetZLPF;		//����z���˲�������

	positionpid_t FollowYawAttitude_pid;		//����Yaw�������̨pid
	positionpid_t FollowYawSpeed_pid;		//����Yaw�������̨pid
	positionpid_t FollowYaw_pid;		//����Yaw�������̨pid
	positionpid_t AutoTrace_pid;                     //�����Զ�׷��pid

}Chassis_t;

void Chassis_Control(float Vx, float Vy, float VOmega, float *speed);
void Chassis_Init(void);

extern WbDeviceTag wheels[4];
extern Chassis_t Chassis;

#endif /* __CHIASSIS_H */


