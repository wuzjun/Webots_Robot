#include <webots/robot.h>

// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 64

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

  while (wb_robot_step(TIME_STEP) != -1)
  {
    double left_speed = 1.0;
    double right_speed = 1.0;

    wb_motor_set_velocity(wheels[0], left_speed);
    wb_motor_set_velocity(wheels[1], right_speed); 
    wb_motor_set_velocity(wheels[2], left_speed);
    wb_motor_set_velocity(wheels[3], right_speed);
  }

  wb_robot_cleanup();

  return 0;
}