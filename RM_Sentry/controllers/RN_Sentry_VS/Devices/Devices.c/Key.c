/*
 * File:          Key.c
 * Date:       2021/3/16
 * Description:   ¼üÅÌ¿ØÖÆ
 * Author:  CJF&WZJ
 * Modifications:
 */
#include <Key.h>

#define Chaiss_Speed 50.0f
#define Cloud_YAW_Speed 5.0f
#define Chaiss_PITCH_Speed 5.0f

Speed_t All_Speed;

 //¼üÅÌ³õÊ¼»¯
void Keyboard_Init(int TIME_STEP)
{
	wb_keyboard_enable(TIME_STEP);

}

//¼üÅÌ¿ØÖÆ
void get_Keyboard_Control(float *VX, float *VYaw, float *VPitch)
{
	int key = wb_keyboard_get_key();
	//printf("%d\n", key);
	fflush(stdout);
	switch (key)
	{
	case 'A':
		*VX = Chaiss_Speed;
		*VYaw = 0.0f;
		*VPitch = 0.0f;
		break;
	case 'D':
		*VX = -Chaiss_Speed;
		*VYaw = 0.0f;
		*VPitch = 0.0f;
		break;
	case 315:
		*VX = 0.0f;
		*VYaw = 0.0f;
		*VPitch = Chaiss_PITCH_Speed;
		break;
	case 317:
		*VX = 0.0f;
		*VYaw = 0.0f;
		*VPitch = -Chaiss_PITCH_Speed;
		break;
	case 314:
		*VX = 0.0f;
		*VYaw = Cloud_YAW_Speed;
		*VPitch = 0.0f;
		break;
	case 316:
		*VX = 0.0f;
		*VYaw = -Cloud_YAW_Speed;
		*VPitch = 0.0f;
		break;
	default:
		*VX = 0.0f;
		*VYaw = 0.0f;
		*VPitch = 0.0f;
	}

}


