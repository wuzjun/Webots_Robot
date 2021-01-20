#ifndef __CHIASSIS_H
#define __CHIASSIS_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <PID.h>

#define WheelMaxSpeed 20.0f

/* 底盘运动 */
typedef struct {
	float targetXRaw;		//底盘x轴原始数据
	float targetYRaw;		//底盘y轴原始数据
	float targetZRaw;		//底盘z轴原始数据
	float LpfAttFactor;		//底盘滤波系数
	float targetXLPF;		//底盘x轴滤波后数据
	float targetYLPF;		//底盘y轴滤波后数据
	float targetZLPF;		//底盘z轴滤波后数据

	positionpid_t FollowYawAttitude_pid;		//底盘Yaw轴跟随云台pid
	positionpid_t FollowYawSpeed_pid;		//底盘Yaw轴跟随云台pid
	positionpid_t FollowYaw_pid;		//底盘Yaw轴跟随云台pid
	positionpid_t AutoTrace_pid;                     //底盘自动追踪pid

}Chassis_t;

void Chassis_Control(float Vx, float Vy, float VOmega, float *speed);
void Chassis_Init(void);

extern WbDeviceTag wheels[4];
extern Chassis_t Chassis;

#endif /* __CHIASSIS_H */


