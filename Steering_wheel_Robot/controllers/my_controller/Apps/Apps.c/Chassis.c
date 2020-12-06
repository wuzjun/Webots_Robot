#include <Chassis.h>

//‘À∂ØΩ‚À„
void RubberWheel_Solve(float *VOMEGA, float *Position, float *Last_Position, int key)
{

	if (key == 'A' || key == 'D')
	{
		for (int i = 0; i < 4; i++)
		{
			Position[i] += *VOMEGA;
			if (Position[i] > Last_Position[i] + 1.57079632f)
			{
				Position[i] = Last_Position[i] + 1.57079632f;
			}
			else if (Position[i] < Last_Position[i] - 1.57079632f)
			{
				Position[i] = Last_Position[i] - 1.57079632f;
			}
		}
	}
	else if (key == 316 || key == 314)
	{
		for (int i = 0; i < 4; i++)
		{
			Position[i] += *VOMEGA;
			Last_Position[i] = Position[i];
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			Position[i] = Last_Position[i];
		}
	}
}