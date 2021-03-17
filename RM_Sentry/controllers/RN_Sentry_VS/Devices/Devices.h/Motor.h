/*
 * File:          Motor.h
 * Date:       2021/3/16
 * Description:   电机使用
 * Author:  CJF&WZJ
 * Modifications:
 */

#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/motor.h>

extern WbDeviceTag wheels[3];

void Motor_Init(void);


#endif /*__MOTOR_H*/