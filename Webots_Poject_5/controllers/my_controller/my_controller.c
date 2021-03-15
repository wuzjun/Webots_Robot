#include <webots/robot.h>
#include <webots/keyboard.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 64

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[2];
  char wheels_names[2][8] = {
      "motor1", "motor2"};
  for (int i = 0; i < 2; i++)
  {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  float Target_angle = 0.0f;
  float Vx = 0.0f;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    // printf("%d\n", key);
    fflush(stdout);
    switch (key)
    {
    case 'A':
      Vx = 2.0f;
      break;
    case 'D':
      Vx = 2.0f;
      break;
    case 'S':
      Vx = -2.0f;
      break;
    case 'W':
      Vx = 2.0f;
      break;
    default:
      Vx = 0.0f;
    }

    for (int i = 0; i < 2; i++)
    {
      wb_motor_set_velocity(wheels[i], Vx);
    }
  }

  wb_robot_cleanup();

  return 0;
}