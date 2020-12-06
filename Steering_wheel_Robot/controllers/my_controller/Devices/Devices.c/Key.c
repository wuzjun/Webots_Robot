#include <Key.h>

//¼üÅÌ¿ØÖÆ
void get_Keyboard_Control(float *VX, float *VOMEGA, int *key)
{
	*key = wb_keyboard_get_key();
	printf("%d\n", *key);
	fflush(stdout);
	switch (*key)
	{
	case 'A':
		*VX = 5.0f;
		*VOMEGA = 2.0f;
		break;
	case 'D':
		*VX = 5.0f;
		*VOMEGA = -2.0f;
		break;
	case 'S':
		*VX = -5.0f;
		*VOMEGA = 0.0f;
		break;
	case 'W':
		*VX = 5.0f;
		*VOMEGA = 0.0f;
		break;
	case 'Q':
		*VX = 5.0f;
		*VOMEGA = 2.0f;
		break;
	case 'E':
		*VX = 5.0f;
		*VOMEGA = -2.0f;
		break;
	case 316:
		*VX = 5.0f;
		*VOMEGA = -0.2f;
		break;
	case 314:
		*VX = 5.0f;
		*VOMEGA = 0.2f;
		break;
	default:
		*VX = 0.0f;
		*VOMEGA = 0.0f;
	}
}


