#include <webots/robot.h>
#include <webots/keyboard.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[3];
  char wheels_names[3][8] = {
      "motor1", "motor2", "motor3"};
  int i;
  for (i = 0; i < 3; i++)
  {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  float speed_1 = 0.0f;
  float speed_2 = 0.0f;
  float speed_3 = 0.0f;
  float Vx = 0.0f;
  float Vy = 0.0f;
  float VOmega = 0.0f;
  const float Radian = 3.14159 / 6;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    printf("%d\n", key);
    fflush(stdout);
    switch (key)
    {
    case 'A':
      Vx = 5.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'D':
      Vx = -5.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'S':
      Vx = 0.0f;
      Vy = 5.0f;
      VOmega = 0.0f;
      break;
    case 'W':
      Vx = 0.0f;
      Vy = -5.0f;
      VOmega = 0.0f;
      break;
    case 'Q':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = -5.0f;
      break;
    case 'E':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = 5.0f;
      break;
    default:
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
    }

    float tempSpeed[3];
    float MaxSpeed = 0.0f;
    float Param = 1.0f;

    //四轮速度分解
    tempSpeed[0] = -Vx + VOmega;
    tempSpeed[1] = Vx * sin(Radian) - Vy * cos(Radian) + VOmega;
    tempSpeed[2] = Vx * sin(Radian) + Vy * cos(Radian) + VOmega;

    //寻找最大速度
    for (int i = 0; i < 3; i++)
    {
      if (abs(tempSpeed[i]) > MaxSpeed)
      {
        MaxSpeed = abs(tempSpeed[i]);
      }
    }

    //速度分配
    if (MaxSpeed > 5.0f)
    {
      Param = (float)5.0f / MaxSpeed;
    }

    speed_1 = tempSpeed[0] * Param;
    speed_2 = tempSpeed[1] * Param;
    speed_3 = tempSpeed[2] * Param;

    wb_motor_set_velocity(wheels[0], speed_1);
    wb_motor_set_velocity(wheels[1], speed_2);
    wb_motor_set_velocity(wheels[2], -speed_3);
  }

  wb_robot_cleanup();

  return 0;
}