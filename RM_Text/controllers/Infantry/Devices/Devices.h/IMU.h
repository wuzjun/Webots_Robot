#ifndef __IMU_H
#define __IMU_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <PID.h>
#include <AddMath.h>
#include <webots/inertial_unit.h>
#include <webots/gyro.h>

/* Õ”¬›“«‘À∂Ø */
typedef struct {
	double Eular_total[3];
	double Eular[3];
	double Last_Eular[3];
	double Eular_turnCount[3];
	double Angular_velocity[3];

}IMU_t;

void IMU_Init(void);
void Get_IMU(IMU_t *IMU);
void Gyro_Init(void);
void Get_Gyro(double *Angular_velocity);

extern IMU_t IMU;

#endif /* __IMU_H */
