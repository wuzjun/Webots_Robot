/*
 * File:          Cloud.h
 * Date:       2021/3/16
 * Description:   云台控制
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


#define Pitch_Max_Radian 0.81				//上限位
#define Pitch_Min_Radian -1.54				//下限位
#define Pitch_Centre_Radian (Pitch_Max_Radian + Pitch_Min_Radian)/2				//中心值

#define uint_Radian_Increment 0.04				//此值是y=sinx 的x的自变量的增量，此值不可以过大，
//												  有可能单位时钟节拍内增加得太大，使得函数在周期内的y值实际上取到的值就没有几个 
//												  而此值较大时，PID的Kp也要相应的增大，才能使其在有限的时钟节拍内追上目标弧度值，否则，可能追不上目标弧度值时，就到了下个时钟节拍，弧度值又变了。
#define Radian_To_Angle 0.0174532925194			//角度对应的弧度
#define Yaw_Max_Radian 3.0				//Yaw轴的上限位
#define Yaw_Min_Radian -3.0                //Yaw轴的下限位

#define pai 3.1415926535

typedef struct {

	double Eular[3];

	double x_about_Radian;				//关于弧度的sin函数的自变量
	
	double Pitch_Target_Radian;				//Pitch目标弧度
	double Yaw_Target_Radian;				//Yaw目标弧度

	double Yaw_Real_Radian;				//Yaw轴的当前弧度
	double Yaw_Last_Radian;				//Yaw轴的上此弧度
	int32_t Yaw_Counts;					//Yaw轴的圈数
	double Yaw_total_Radian;			//Yaw轴的总弧度

	uint8_t Pitch_Scan_Dir;				//Pitch轴扫描方向
	int8_t Yaw_Scan_Dir;				//Yaw轴扫描方向:注意它需要负值，不能搞个uint8_t数据类型了
	uint8_t Yaw_Scan_Status;			//Yaw扫描状态标志位

	positionpid_t Pitch_Radian_pid;				//Pitch外环弧度环PID
	positionpid_t Yaw_Radian_pid;				//Yaw外环弧度环PID

	uint8_t i;				//扫描获取弧度值无法放在While外，可能时IMU初始化完成后，无法立刻获取其当前值
							//所以只能用变量控制其，第一次进入While时，获取一些扫描弧度值
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
