/*
 * File:          Laser.h
 * Date:       2021/3/16
 * Description:   ¼¤¹â²â¾à
 * Author:  CJF&WZJ
 * Modifications:
 */
#ifndef ___LASER_H
#define ___LASER_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/distance_sensor.h>

extern double distance[3];

void Laser_Init(int TIME_STEP);
void Laser_get_Data(void);

#endif/*___LASER_H*/