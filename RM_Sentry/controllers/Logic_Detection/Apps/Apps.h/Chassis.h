/*
 * File:          Chassis.h
 * Date:       2021/3/16
 * Description:   底盘控制
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

/* 最佳攻击距离的参数 */
#define Yaw_Reference_Radain pai				//云台Yaw轴参考的弧度(作为测量角度的起点) 枪管与轨道的左侧平行
#define Best_Attcak_Distance 3.20					//最佳攻击距离

#define Chassis_Max_Distance 1.55				//底盘最大的移动路程
#define Chassis_Min_Distance 0.1						//底盘最小的移动距离

typedef struct
{
	double Yaw_Raw_Increment_Radian;
	double Yaw_Increment_Radian;				//云台的弧度增量

	double Incremnet_Distance;			//底盘移动的路程增量

	double Real_Distance;				//底盘的当前路程
	positionpid_t Encoder_pid;				//底盘编码器环的pid

	double Target_Distance;					//底盘的目标距离

}Chassis_t;
extern Chassis_t Chassis;

void Chassic_Control(float VX);
void Chassis_Cruise_Processing(void);
void Optimally_Attack_Distance0(double real_Angle, double real_depth, double* b);
void Chassis_add_Encoder_Init(void);
void Chassis_add_Encoder_Control(float* VX);


#endif /* __CHIASSIS_H */


