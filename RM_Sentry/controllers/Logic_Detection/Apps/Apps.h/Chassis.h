/*
 * File:          Chassis.h
 * Date:       2021/3/16
 * Description:   µ×ÅÌ¿ØÖÆ
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef __CHIASSIS_H
#define __CHIASSIS_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <Motor.h>
#include <Laser.h>

extern float Chassis_Cruise_Velocity;
void Chassic_Control(float VX);
void Chassis_Cruise_Processing(void);


#endif /* __CHIASSIS_H */


