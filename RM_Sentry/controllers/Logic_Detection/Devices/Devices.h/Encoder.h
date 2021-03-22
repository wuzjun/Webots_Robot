#ifndef ENCODER_H
#define ENCODER_H

#include <webots/position_sensor.h>
#include <webots/robot.h>
#include <Chassis.h>

#define Chassis_Encoder_Referen_Radian -28.0				//���̱������Ĳο�����
#define Per_Radian_Contact_Distance	0.03				//��λ���ȶ�Ӧ�Ļ���	
 
extern WbDeviceTag Encoder;

typedef struct
{
	double Real_Encoder_Radian;

}Encoder_t;
extern Encoder_t Chassis_Encoder;

void Encoder_Init(int TIME_STEP);

void  Updata_Encoder_Radian(void);

#endif