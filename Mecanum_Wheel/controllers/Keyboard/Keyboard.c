#include <webots/robot.h>
#include <webots/keyboard.h>
#include <webots/mouse.h>
#include <webots/inertial_unit.h>
#include <webots/gyro.h>
#include <webots/accelerometer.h>
#include <webots/compass.h>
#include <stdio.h>
#include <string.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8

double get_bearing_in_degrees(double *north)
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

  // initialize IMU
  WbDeviceTag IMU;
  IMU = wb_robot_get_device("imu");
  wb_inertial_unit_enable(IMU, TIME_STEP);

  // initialize Gyro
  WbDeviceTag GYRO;
  GYRO = wb_robot_get_device("gyro1");
  wb_gyro_enable(GYRO, TIME_STEP);

  // initialize Accelerometer
  WbDeviceTag ACCELEROMETER;
  ACCELEROMETER = wb_robot_get_device("accelerometer1");
  wb_accelerometer_enable(ACCELEROMETER, TIME_STEP);

  // initialize Compass
  WbDeviceTag COMPASS;
  COMPASS = wb_robot_get_device("compass1");
  wb_compass_enable(COMPASS, TIME_STEP);

  
  double Eular[3] = {0};
  double Angular_velocity[3] = {0};
  double Acceleration[3] = {0};
  double Magnetometer[3] = {0};
  float speed[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  float Vx = 0.0f;
  float Vy = 0.0f;
  float VOmega = 0.0f;

  wb_keyboard_enable(TIME_STEP);
  wb_mouse_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    // printf("%d\n", key);
    memcpy(Eular, wb_inertial_unit_get_roll_pitch_yaw(IMU), sizeof(double[3]));
    memcpy(Angular_velocity, wb_gyro_get_values(GYRO), sizeof(double[3]));
    memcpy(Acceleration, wb_accelerometer_get_values(ACCELEROMETER), sizeof(double[3]));
    memcpy(Magnetometer, wb_compass_get_values(COMPASS), sizeof(double[3]));
    for (int i = 0; i < 3; i++)
    {
      Eular[i] *= 180.0 / 3.14159;
      Eular[i] += 180.0;
    }
    // printf("roll = %lf:\n", Eular[0]);
    // printf("pitch = %lf:\n", Eular[1]);
    // printf("yaw = %lf:\n", Eular[2]);

    // printf("Vx = %lf:\n", Angular_velocity[0]);
    // printf("Vy = %lf:\n", Angular_velocity[1]);
    // printf("Vz = %lf:\n", Angular_velocity[2]);

    // printf("xAxis = %lf:\n", Acceleration[0]);
    // printf("yAxis = %lf:\n", Acceleration[1]);
    // printf("zAxis = %lf:\n", Acceleration[2]);

    // printf("xAxis = %lf:\n", Magnetometer[0]);
    // printf("yAxis = %lf:\n", Magnetometer[1]);
    // printf("zAxis = %lf:\n", Magnetometer[2]);
    WbMouseState Mouse1 = wb_mouse_get_state();

    printf("mouse.left = %d:\n", Mouse1.left);
    printf("mouse.middle = %d:\n", Mouse1.middle);
    printf("mouse.right = %d:\n", Mouse1.right);
    printf("mouse.u = %lf:\n", Mouse1.u);
    printf("mouse.v = %lf:\n", Mouse1.v);

    double angle = get_bearing_in_degrees(Magnetometer);
    // printf("angle = %lf:\n", angle);

    fflush(stdout);
    switch (key)
    {
    case 'A':
      Vx = 0.0f;
      Vy = 20.0f;
      VOmega = 0.0f;
      break;
    case 'D':
      Vx = 0.0f;
      Vy = -20.0f;
      VOmega = 0.0f;
      break;
    case 'S':
      Vx = -20.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'W':
      Vx = 20.0f;
      Vy = 0.0f;
      VOmega = 0.0f;
      break;
    case 'Q':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = -20.0f;
      break;
    case 'E':
      Vx = 0.0f;
      Vy = 0.0f;
      VOmega = 20.0f;
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
    if (MaxSpeed > 20.0f)
    {
      Param = (float)20.0f / MaxSpeed;
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