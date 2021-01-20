#ifndef __CLOUD_H
#define __CLOUD_H
#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <PID.h>

#define Cloud_Yaw_Center 0

/* ��̨�˶� */
typedef struct {
	float Yaw;
	float Accumulate_YAW;   //YAW�ۼ�ֵ
	float Pitch;
	float Accumulate_Pitch;   //Pitch�ۼ�ֵ

	float angle;
	float IMU_Cloud[3];

	positionpid_t YawAttitude_pid;			//��̨yaw����̬pid
	positionpid_t YawSpeed_pid;			//��̨yaw���ٶ�pid
	positionpid_t PitchAttitude_pid;			//��̨roll����̬pid
	positionpid_t PitchSpeed_pid;			//��̨roll����̬pid

}Cloud_t;

void Cloud_Control(float YAW, float PITCH);
void Cloud_Init(void);

extern Cloud_t Cloud;
extern WbDeviceTag Cloud_Motor[2];

#endif /*__CLOUD_H*/

