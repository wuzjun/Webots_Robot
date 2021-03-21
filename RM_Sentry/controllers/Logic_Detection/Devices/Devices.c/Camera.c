/*
 * File:          Camera.c
 * Date:       2021/3/16
 * Description:   …„œÒÕ∑
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Camera.h>


WbDeviceTag CAMERA;

void Camera_Init(int TIME_STEP)
{
	CAMERA = wb_robot_get_device("camera1");
	wb_camera_enable(CAMERA, TIME_STEP);
	wb_camera_recognition_enable(CAMERA, TIME_STEP);
}

void Camera_get_Data(Vision_t  *Vision)
{
	int number_of_objects = wb_camera_recognition_get_number_of_objects(CAMERA);
	const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(CAMERA);

	//for (int i = 0; i < number_of_objects; ++i)
	//{
	//	printf("Position of the object %d on the camera image: %d %d\n", i, objects[i].position_on_image[0],
	//		objects[i].position_on_image[1]);
	//}


	Vision->x = objects[0].position_on_image[0];
	Vision->y = objects[0].position_on_image[1];
	Vision->ID = objects[0].id;


}