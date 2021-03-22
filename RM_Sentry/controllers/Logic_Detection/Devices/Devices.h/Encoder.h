#ifndef ENCODER_H
#define ENCODER_H

#include <webots/position_sensor.h>
#include <webots/robot.h>
#include <Chassis.h>

#define Chassis_Encoder_Referen_Radian -28.0				//底盘编码器的参考弧度
#define Per_Radian_Contact_Distance	0.03				//单位弧度对应的弧长	
 
extern WbDeviceTag Encoder;

typedef struct
{
	double Real_Encoder_Radian;

}Encoder_t;
extern Encoder_t Chassis_Encoder;

void Encoder_Init(int TIME_STEP);

void  Updata_Encoder_Radian(void);

#endif