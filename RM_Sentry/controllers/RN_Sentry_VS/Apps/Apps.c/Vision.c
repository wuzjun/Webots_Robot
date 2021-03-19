/*
 * File:          Vision.c
 * Date:       2021/3/17
 * Description:   视觉识别处理
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Vision.h>
#include <Camera.h>

Vision_t Vision;

void Vision_Updata(void)
{
	Camera_get_Data(&Vision);

	printf("ID = %d\n", Vision.ID);

	if (Vision.ID == 0)
	{
		Vision.x = 0;
		Vision.y = 0;
	}

	printf("Vision_Yaw = %d\n", Vision.x);
	printf("Vision_Pitch = %d\n", Vision.y);

}

