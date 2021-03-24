#include <Encoder.h>

//此编码器是绝对式的，并且可能是多线的，其返回的值是弧度
WbDeviceTag Encoder;
Encoder_t Chassis_Encoder;

void Encoder_Init(int TIME_STEP)
{
	//获取其句柄
	Encoder = wb_robot_get_device("Encoder");
	//使能编码器
	wb_position_sensor_enable(Encoder, TIME_STEP);				//参数2传感器的采样周期，只有在一个采样周期过去后，第一个测量值才有用

}
//更新底盘当前的弧度数
void  Updata_Encoder_Radian(void)
{
	//获取底盘的当前弧度值
	Chassis_Encoder.Real_Encoder_Radian = wb_position_sensor_get_value(Encoder);
	//计算得到底盘当前位置距原点位置的距离
	Chassis.Real_Distance = (Chassis_Encoder.Real_Encoder_Radian - Chassis_Encoder_Referen_Radian)*Per_Radian_Contact_Distance;

}

