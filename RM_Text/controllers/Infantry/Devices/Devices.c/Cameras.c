#include <Cameras.h>

/**
  * @brief  �����ʼ��
  * @param[in]  None
  * @retval
  */
void Cameras_Init(void)
{
	WbDeviceTag Camera_1;
	Camera_1 = wb_robot_get_device("camera1");
	wb_camera_enable(Camera_1, 8);
}





