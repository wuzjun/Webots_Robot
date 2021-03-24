#include <Encoder.h>

//�˱������Ǿ���ʽ�ģ����ҿ����Ƕ��ߵģ��䷵�ص�ֵ�ǻ���
WbDeviceTag Encoder;
Encoder_t Chassis_Encoder;

void Encoder_Init(int TIME_STEP)
{
	//��ȡ����
	Encoder = wb_robot_get_device("Encoder");
	//ʹ�ܱ�����
	wb_position_sensor_enable(Encoder, TIME_STEP);				//����2�������Ĳ������ڣ�ֻ����һ���������ڹ�ȥ�󣬵�һ������ֵ������

}
//���µ��̵�ǰ�Ļ�����
void  Updata_Encoder_Radian(void)
{
	//��ȡ���̵ĵ�ǰ����ֵ
	Chassis_Encoder.Real_Encoder_Radian = wb_position_sensor_get_value(Encoder);
	//����õ����̵�ǰλ�þ�ԭ��λ�õľ���
	Chassis.Real_Distance = (Chassis_Encoder.Real_Encoder_Radian - Chassis_Encoder_Referen_Radian)*Per_Radian_Contact_Distance;

}

