/*
 * File:          Key.h
 * Date:       2021/3/16
 * Description:   ¼üÅÌ¿ØÖÆ
 * Author:  CJF&WZJ
 * Modifications:
 */

#ifndef __KEY_H
#define __KEY_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/keyboard.h>

typedef struct
{
	float VX;
	float VYaw;
	float VPitch;
}Speed_t;

extern Speed_t All_Speed;

void Keyboard_Init(int TIME_STEP);
void get_Keyboard_Control(float *VX, float *VYaw, float *VPitch);


#endif /*__KEY_H*/