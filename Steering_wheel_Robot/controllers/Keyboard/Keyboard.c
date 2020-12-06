#include <webots/robot.h>
#include <webots/keyboard.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 64
#define WheelMaxSpeed 5.0f

//键盘控制
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

//运动解算
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

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[4];
  WbDeviceTag Turntable[4];
  char Turntable_names[4][8] = {
      "motor1", "motor2", "motor3", "motor4"};
  char wheels_names[4][8] = {
      "motor5", "motor6", "motor7", "motor8"};

  for (int i = 0; i < 4; i++)
  {
    //转盘电机
    Turntable[i] = wb_robot_get_device(Turntable_names[i]);
    wb_motor_set_velocity(Turntable[i], 5);
    //轮子电机
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  float position[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float Last_Position[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float Vx = 0.0f;
  float VOmega = 0.0f;
  int key = 0;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {
    get_Keyboard_Control(&Vx, &VOmega, &key);
    RubberWheel_Solve(&VOmega, position, Last_Position, key);

    for (int i = 0; i < 4; i++)
    {
      wb_motor_set_position(Turntable[i], position[i]);
    }

    for (int i = 0; i < 4; i++)
    {
      wb_motor_set_velocity(wheels[i], Vx);
    }
  }

  wb_robot_cleanup();

  return 0;
}