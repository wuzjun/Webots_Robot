#ifndef __CLOUD_H
#define __CLOUD_H
#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <PID.h>

#define Cloud_Yaw_Center 0

/* 云台运动 */
typedef struct {
	float Yaw;
	float Accumulate_YAW;   //YAW累加值
	float Pitch;
	float Accumulate_Pitch;   //Pitch累加值

	float angle;
	float IMU_Cloud[3];

	positionpid_t YawAttitude_pid;			//云台yaw轴姿态pid
	positionpid_t YawSpeed_pid;			//云台yaw轴速度pid
	positionpid_t PitchAttitude_pid;			//云台roll轴姿态pid
	positionpid_t PitchSpeed_pid;			//云台roll轴姿态pid

}Cloud_t;

void Cloud_Control(float YAW, float PITCH);
void Cloud_Init(void);

extern Cloud_t Cloud;
extern WbDeviceTag Cloud_Motor[2];

#endif /*__CLOUD_H*/

