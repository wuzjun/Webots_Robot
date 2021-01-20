#include <Key.h>

//¼üÅÌ¿ØÖÆ
void get_Keyboard_Control(float *VX, float *VY, float *YAW, float *PITCH)
{
	int key = wb_keyboard_get_key();

	fflush(stdout);
	switch (key)
	{
	case 'A':
		*VX = 0.0f;
		*VY = Speed;
		*YAW = 0.0f;
		*PITCH = 0.0f;
		break;
	case 'D':
		*VX = 0.0f;
		*VY = -Speed;
		*YAW = 0.0f;
		*PITCH = 0.0f;
		break;
	case 'S':
		*VX = -Speed;
		*VY = 0.0f;
		*YAW = 0.0f;
		*PITCH = 0.0f;
		break;
	case 'W':
		*VX = Speed;
		*VY = 0.0f;
		*YAW = 0.0f;
		*PITCH = 0.0f;
		break;
	case 314:
		*VX = 0.0f;
		*VY = 0.0f;
		*YAW = 0.5f;
		*PITCH = 0.0f;
		break;
	case 316:
		*VX = 0.0f;
		*VY = 0.0f;
		*YAW = -0.5f;
		*PITCH = 0.0f;
		break;
	case 315:
		*VX = 0.0f;
		*VY = 0.0f;
		*YAW = 0.0f;
		*PITCH = -0.02f;
		break;
	case 317:
		*VX = 0.0f;
		*VY = 0.0f;
		*YAW = 0.0f;
		*PITCH = 0.02f;
		break;
	default:
		*VX = 0.0f;
		*VY = 0.0f;
		*YAW = 0.0f;
		*PITCH = 0.0f;
	}
}


