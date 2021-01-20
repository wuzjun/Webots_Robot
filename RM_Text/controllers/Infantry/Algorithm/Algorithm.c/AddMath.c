/**
  ******************************************************************************
  * @file    UserMath.c
  * @author  IMTao
  * @version V1.1
  * @date    
  * @brief 
  ******************************************************************************
  */
#include <AddMath.h>

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int floatEqual_0(float num) {//���ڴ����ж�float�����Ƿ�Ϊ0 
if (num<(float)flaot0)
{
	return 1;
}
return 0;
}
