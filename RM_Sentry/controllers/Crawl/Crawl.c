#include <webots/robot.h>
#include <webots/keyboard.h>
#include <webots/camera.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8
#define SPEED 30.0f

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[4];
  char wheels_names[4][8] = {
      "motor4", "motor5", "motor6", "motor7"};
  int i;
  for (i = 0; i < 4; i++)
  {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }


  float left_speed = 0.0f;
  float right_speed = 0.0f;
  float Vx = 0.0f;
  float VOmega = 0.0f;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    // printf("%d\n", key);
    fflush(stdout);
    switch (key)
    {
    case 'Q':
      Vx = 0.0f;
      VOmega = -SPEED/2.0f;
      break;
    case 'E':
      Vx = 0.0f;
      VOmega = SPEED/2.0f;
      break;
    case 'S':
      Vx = -SPEED;
      VOmega = 0.0f;
      break;
    case 'W':
      Vx = SPEED;
      VOmega = 0.0f;
      break;
    default:
      Vx = 0.0f;
      VOmega = 0.0f;
    }

    float tempSpeed[2];
    float MaxSpeed = 0.0f;
    float Param = 1.0f;

    //四轮速度分解
    tempSpeed[0] = Vx + VOmega;
    tempSpeed[1] = Vx - VOmega;

    //寻找最大速度
    for (int i = 0; i < 2; i++)
    {
      if (abs(tempSpeed[i]) > MaxSpeed)
      {
        MaxSpeed = abs(tempSpeed[i]);
      }
    }

    //速度分配
    if (MaxSpeed > SPEED)
    {
      Param = (float)SPEED / MaxSpeed;
    }

    left_speed = tempSpeed[0] * Param;
    right_speed = tempSpeed[1] * Param;

    wb_motor_set_velocity(wheels[0], left_speed);
    wb_motor_set_velocity(wheels[1], right_speed);
    wb_motor_set_velocity(wheels[2], left_speed);
    wb_motor_set_velocity(wheels[3], right_speed);


  }

  wb_robot_cleanup();

  return 0;
}