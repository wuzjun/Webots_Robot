#include <webots/robot.h>
#include <webots/keyboard.h>
#include <webots/camera.h>
#include <stdio.h>
#include <string.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8
#define Speed 20.0f

double get_bearing_in_degrees(double* north)
{
  double rad = atan2(north[0], north[2]);
  double bearing = (rad - 1.5708) / M_PI * 180.0;
  if (bearing < 0.0)
    bearing = bearing + 360.0;
  return bearing;
}

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[4];
  char wheels_names[4][8] = {
      "motor1", "motor2", "motor3", "motor4"};

  for (int i = 0; i < 4; i++)
  {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }
  
  
  WbDeviceTag CAMERA;
  CAMERA = wb_robot_get_device("camera"); 
  wb_camera_enable(CAMERA, TIME_STEP);

  float speed[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float Vx = 0.0f;
  float Vy = 0.0f;
  float VOmega = 0.0f;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    printf("%d\n", key);

    fflush(stdout);
    switch (key)
    {
    case 'A':
      Vx = 0.0f;
      Vy = Speed;
      VOmega = 0.0f;
      break;
    case 'D':
      Vx = 0.0f;
      Vy = -Speed;
      VOmega = 0.0f;
      break;
    case 'S':
      Vx = -Speed;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'W':
      Vx = Speed;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'Q':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = -Speed;
      break;
    case 'E':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = Speed;
      break;
    default:
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
    }

    float tempSpeed[4];
    float MaxSpeed = 0.0f;
    float Param = 1.0f;

    //四轮速度分解
    tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = -Vx - Vy + VOmega;
    tempSpeed[2] = Vx + Vy + VOmega;
    tempSpeed[3] = -Vx + Vy + VOmega;

    //寻找最大速度
    for (int i = 0; i < 4; i++)
    {
      if (abs(tempSpeed[i]) > MaxSpeed)
      {
        MaxSpeed = abs(tempSpeed[i]);
      }
    }

    //速度分配
    if (MaxSpeed > Speed)
    {
      Param = (float)Speed / MaxSpeed;
    }

    for (int i = 0; i < 4; i++)
    {
      speed[i] = tempSpeed[i] * Param;
    }

    wb_motor_set_velocity(wheels[0], speed[0]);
    wb_motor_set_velocity(wheels[1], speed[1]);
    wb_motor_set_velocity(wheels[2], speed[2]);
    wb_motor_set_velocity(wheels[3], speed[3]);
  }

  wb_robot_cleanup();

  return 0;
}