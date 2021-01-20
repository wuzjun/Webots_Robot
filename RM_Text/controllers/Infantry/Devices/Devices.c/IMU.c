#include <IMU.h>

IMU_t IMU;
WbDeviceTag IMU1;
WbDeviceTag GYRO1;

// initialize IMU
void IMU_Init(void)
{
	IMU1 = wb_robot_get_device("imu1");
	wb_inertial_unit_enable(IMU1, 8);

	memcpy(IMU.Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU1), sizeof(double[3]));
	for (int i = 0; i < 3; i++)
	{
		IMU.Eular[i] *= 180.0 / PI;
		//Eular[i] += 180.0;
	}
}

/**
  * @brief  获取角度
  * @param[in]  Eular		角度
  *                          Eular[0]——roll        Eular[0]——pitch        Eular[2]——yaw
  * @retval None
  */
void Get_IMU(IMU_t *IMU)
{
	memcpy(IMU->Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU1), sizeof(double[3]));

	for (int i = 0; i < 3; i++)
	{
		IMU->Eular[i] *= 180.0 / PI;
		//Eular[i] += 180.0;

		if (IMU->Eular[i] - IMU->Last_Eular[i] < -300) {//经过跳变边沿。
			IMU->Eular_turnCount[i]++;
		}
		if (IMU->Last_Eular[i] - IMU->Eular[i] < -300) {
			IMU->Eular_turnCount[i]--;
		}

		IMU->Eular_total[i] = IMU->Eular[2] + (360 * IMU->Eular_turnCount[i]);

		IMU->Last_Eular[i] = IMU->Eular[i];
	}




}

// initialize Gyro
void Gyro_Init(void)
{
	GYRO1 = wb_robot_get_device("gyro1");
	wb_gyro_enable(GYRO1, 8);
}


/**
  * @brief  获取角速度
  * @param[in]  Angular_velocity		角速度
  *                          Angular_velocity[0]——Vx        Angular_velocity[1]——Vy        Angular_velocity[2]——Vz
  * @retval None
  */
void Get_Gyro(double *Angular_velocity)
{
	memcpy(Angular_velocity, wb_gyro_get_values(GYRO1), sizeof(double[3]));

}


