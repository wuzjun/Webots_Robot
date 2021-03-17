/*
 * File:          Camera.h
 * Date:       2021/3/16
 * Description:   …„œÒÕ∑
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef __CAMERA_H
#define __CAMERA_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>

void Camera_Init(int TIME_STEP);
void Camera_get_Data(void);

#endif/*__CAMERA_H*/