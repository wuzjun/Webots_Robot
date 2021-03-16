#include <webots/robot.h>
#include <webots/keyboard.h>
#include <webots/camera.h>
#include <webots/camera_recognition_object.h>
#include <webots/distance_sensor.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag wheels[4];
  char wheels_names[4][8] = {
      "motor1", "motor2", "motor3", "motor4"};
  int i;
  for (i = 0; i < 4; i++)
  {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  WbDeviceTag CAMERA = wb_robot_get_device("camera1");
  wb_camera_enable(CAMERA, TIME_STEP);
  wb_camera_recognition_enable(CAMERA, TIME_STEP);

  WbDeviceTag laser0 = wb_robot_get_device("laser0");
  wb_distance_sensor_enable(laser0, TIME_STEP);

  float left_speed = 0.0f;
  float right_speed = 0.0f;
  float Vx = 0.0f;
  float VOmega = 0.0f;
  double distance = 0.0;

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {

    int key = wb_keyboard_get_key();
    // printf("%d\n", key);
    fflush(stdout);
    switch (key)
    {
    case 'A':
      Vx = 0.0f;
      VOmega = -20.0f;
      break;
    case 'D':
      Vx = 0.0f;
      VOmega = 20.0f;
      break;
    case 'S':
      Vx = -20.0f;
      VOmega = 0.0f;
      break;
    case 'W':
      Vx = 20.0f;
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
    if (MaxSpeed > 20.0f)
    {
      Param = (float)20.0f / MaxSpeed;
    }

    left_speed = tempSpeed[0] * Param;
    right_speed = tempSpeed[1] * Param;

    wb_motor_set_velocity(wheels[0], left_speed);
    wb_motor_set_velocity(wheels[1], right_speed);
    wb_motor_set_velocity(wheels[2], left_speed);
    wb_motor_set_velocity(wheels[3], right_speed);

    int number_of_objects = wb_camera_recognition_get_number_of_objects(CAMERA);
    printf("\nRecognized %d objects.\n", number_of_objects);

    const WbCameraRecognitionObject *objects = wb_camera_recognition_get_objects(CAMERA);
    distance = wb_distance_sensor_get_value(laser0);

    for (int i = 0; i < number_of_objects; ++i)
    {
      printf("Model of object %d: %s\n", i, objects[i].model);
      printf("Id of object %d: %d\n", i, objects[i].id);
      printf("Relative position of object %d: %lf %lf %lf\n", i, objects[i].position[0], objects[i].position[1],
             objects[i].position[2]);
      printf("Relative orientation of object %d: %lf %lf %lf %lf\n", i, objects[i].orientation[0], objects[i].orientation[1],
             objects[i].orientation[2], objects[i].orientation[3]);
      printf("Size of object %d: %lf %lf\n", i, objects[i].size[0], objects[i].size[1]);
      printf("Position of the object %d on the camera image: %d %d\n", i, objects[i].position_on_image[0],
             objects[i].position_on_image[1]);
      printf("Size of the object %d on the camera image: %d %d\n", i, objects[i].size_on_image[0], objects[i].size_on_image[1]);
      for (int j = 0; j < objects[i].number_of_colors; ++j)
        printf("- Color %d/%d: %lf %lf %lf\n", j + 1, objects[i].number_of_colors, objects[i].colors[3 * j],
               objects[i].colors[3 * j + 1], objects[i].colors[3 * j + 2]);
    }
    printf("距离是：%lf\n", distance);
  }

  wb_robot_cleanup();

  return 0;
}