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

void Vision_Init(void)
{
	Vision.VisionPage_Width = wb_camera_get_width(CAMERA);
	Vision.VisionPage_Height = wb_camera_get_height(CAMERA);
}

/*************************************
* Method:    Vision_getOffset
* Returns:   int16_t
* Parameter: int16_t length
* Parameter: int16_t Value
* 说明：计算value 与 坐标系中点的偏差值。
************************************/
int16_t  Vision_getOffset(int16_t length, int16_t Value) {
	return  Value - length / 2;
}


void Vision_Updata(void)
{
	Camera_get_Data(&Vision);

	if (Vision.ID == 0)
	{
		Vision.x = 640;
		Vision.y = 400;
	}

	Vision.Finally_X = Vision_getOffset(Vision.VisionPage_Width, Vision.x);
	Vision.Finally_Y = Vision_getOffset(Vision.VisionPage_Height, Vision.y);



	printf("ID = %d\n", Vision.ID);
	printf("Vision_Yaw = %d\n", Vision.Finally_X);
	printf("Vision_Pitch = %d\n", Vision.Finally_Y);


}

