/*
 * File:          Vision.h
 * Date:       2021/3/17
 * Description:   视觉识别处理
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef __VISION_H
#define __VISION_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
//#include <webots/camera.h>
//#include <webots/camera_recognition_object.h>


typedef struct
{
	int ID;
	int x;
	int y;
	int depth;
}Vision_t;

extern Vision_t Vision;

void Vision_Updata(void);

#endif/*__VISION_H*/
