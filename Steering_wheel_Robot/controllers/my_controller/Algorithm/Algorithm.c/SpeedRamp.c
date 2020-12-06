#include <SpeedRamp.h>
#include <AddMath.h>

/**
	* @brief  б�º�������
  * @param	б�º����ṹ��
  * @retval None
  */
 int16_t SpeedRampCalc(SpeedRamp_t *SpeedRamp)
{

	SpeedRamp->count += SpeedRamp->rate;
	VAL_LIMIT(SpeedRamp->count,
		SpeedRamp->mincount,
		SpeedRamp->maxcount);

	return SpeedRamp->count;
}


/**
	* @brief  б�¼���ֵ����
  * @param	б�º����ṹ��
  * @retval None
  */
 void CountReset(SpeedRamp_t *SpeedRamp)
{
	 
	 if (abs(SpeedRamp->count)<abs(SpeedRamp->rate))
	 {
		 SpeedRamp->count = 0;
	 }
	 else
	 {

		SpeedRamp->count -= SpeedRamp->count*0.2f;
	 }
	//if (SpeedRamp->count > abs(SpeedRamp->rate))
	//{
	//	SpeedRamp->count -= abs(SpeedRamp->rate);
	//}
	//else if (SpeedRamp->count < -abs(SpeedRamp->rate))
	//{
	//	SpeedRamp->count += abs(SpeedRamp->rate);
	//}
	//else
	//{
	//	
	//}

}
