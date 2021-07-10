#include <webots/robot.h>
#include <webots/keyboard.h>
#include <stdio.h>
#include <Math.h>
// Added a new include file
#include <webots/motor.h>

#define TIME_STEP 8
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)

float Vx = 0.0f;
float Vy = 0.0f;
float VOmega = 0.0f;
int key = 0;
float position[3] = {0.0f};

typedef struct
{
  float O_L_Angle;
  float O_Angle;
  float turnCount;
  float O_T_Angle;
  float R_Speed;
} Chassis_t;

Chassis_t Chassis[3];

/**
  * @brief  舵轮速度解算
  * @param[in]  Vx		x轴速度
  *				VOmega	自转速度
  * @param[out]	Speed	速度
  * @retval None
  */
void HelmCalculate(float Vx, float Vy, float VOMEGA, float AngleN, Chassis_t *Chassis)
{

  float velN, VelDirection = 0.0f;
  float sumVelX = 0.0f;
  float sumVelY = 0.0f;
  velN = DEG_TO_RAD * (VOMEGA)*100; 

  VelDirection = AngleN;

  // VAL_LIMIT(VelDirection, -180, 180);

  sumVelX = Vx + velN * cos(DEG_TO_RAD * (VelDirection));

  sumVelY = Vy + velN * sin(DEG_TO_RAD * (VelDirection));

  float Angle = atan2(sumVelY, sumVelX);
  Chassis->O_L_Angle = Chassis->O_Angle;
  Chassis->O_Angle = degrees(Angle);
  // if ((Chassis->O_Angle - Chassis->O_L_Angle) < 170)
  // {
  //   Chassis->turnCount++;
  // }

  // if ((Chassis->O_L_Angle - Chassis->O_Angle) < 170)
  // {
  //   Chassis->turnCount--;
  // }

  Chassis->O_T_Angle = Chassis->O_Angle + (360 * Chassis->turnCount);

  float O_Speed = (pow(sumVelY, 2) + pow(sumVelX, 2));
  Chassis->R_Speed = sqrt(O_Speed);
}

//键盘控制
void get_Keyboard_Control(float *VX, float *Vy, float *VOMEGA, int *key)
{
  *key = wb_keyboard_get_key();
  // printf("%d\n", *key);
  printf("%d\n", (int)Chassis[0].O_T_Angle);
  printf("%d\n", (int)Chassis[1].O_T_Angle);
  printf("%d\n", (int)Chassis[2].O_T_Angle);
  fflush(stdout);
  switch (*key)
  {
  case 'A':
    *VX = 5.0f;
    *Vy = 0.0f;
    *VOMEGA = 0.0f;
    break;
  case 'D':
    *VX = -5.0f;
    *Vy = 0.0f;
    *VOMEGA = 0.0f;
    break;
  case 'S':
    *VX = 0.0f;
    *Vy = -5.0f;
    *VOMEGA = 0.0f;
    break;
  case 'W':
    *VX = 0.0f;
    *Vy = 5.0f;
    *VOMEGA = 0.0f;
    break;
  case 'Q':
    *VX = 0.0f;
    *Vy = 0.0f;
    *VOMEGA = 1.0f;
    break;
  case 'E':
    *VX = 0.0f;
    *Vy = 0.0f;
    *VOMEGA = -1.0f;  
    break;
  case 316:
    *VX = 5.0f;
    *Vy = 0.0f;
    *VOMEGA = -1.0f;
    break;
  case 314:
    *VX = 5.0f;
    *Vy = 0.0f;
    *VOMEGA = 1.0f;
    break;
  default:
    *VX = 0.0f;
    *Vy = 0.0f;
    *VOMEGA = 0.0f;
  }
}

int main(int argc, char **argv)
{
  wb_robot_init();

  // initialize motors
  WbDeviceTag Turntable[3];
  char Turntable_names[3][8] = {
      "motor1", "motor2", "motor3"};

  WbDeviceTag wheels[3];
  char wheels_names[3][9] = {
      "motor11", "motor22", "motor33"};

  for (int i = 0; i < 3; i++)
  {
    //转盘电机
    Turntable[i] = wb_robot_get_device(Turntable_names[i]);
    wb_motor_set_velocity(Turntable[i], 5);

    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY);
  }

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1)
  {
    get_Keyboard_Control(&Vy, &Vx, &VOmega, &key);

    HelmCalculate(Vx, Vy, VOmega, 90.0f, &Chassis[0]); 
    HelmCalculate(Vx, Vy, VOmega, -150.0f, &Chassis[1]);
    HelmCalculate(Vx, Vy, VOmega, -30.0f, &Chassis[2]);

    wb_motor_set_position(Turntable[0], radians(Chassis[0].O_T_Angle));
    wb_motor_set_position(Turntable[1], radians(Chassis[1].O_T_Angle));
    wb_motor_set_position(Turntable[2], radians(Chassis[2].O_T_Angle));

    wb_motor_set_velocity(wheels[0], Chassis[0].R_Speed);
    wb_motor_set_velocity(wheels[1], Chassis[1].R_Speed);
    wb_motor_set_velocity(wheels[2], Chassis[2].R_Speed);
  }

  wb_robot_cleanup();

  return 0;
}