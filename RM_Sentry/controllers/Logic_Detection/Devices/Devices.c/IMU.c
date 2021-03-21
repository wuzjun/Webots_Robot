#include <IMU.h>

WbDeviceTag IMU;

void IMU_Init(int TIME_STEP)
{

	IMU = wb_robot_get_device("Cloud_imu");
	wb_inertial_unit_enable(IMU, TIME_STEP);

}

