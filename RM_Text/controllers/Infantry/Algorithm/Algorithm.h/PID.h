#ifndef ___PID_H
#define ___PID_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>


typedef struct {
	float Target; 			        //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float err_beforeLast; 			//���ϴ�ƫ��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float p_out, i_out, d_out;//���������ֵ
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
	uint32_t IntegralLimit;			//�����޷� 
}incrementalpid_t;

typedef struct {
	float Target; 					    //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						      //����ƫ��ֵ
	float err_last; 				    //��һ��ƫ��
	float err_change; 				    //���仯��
	float Kp, Ki, Kd;				    //Kp, Ki, Kd����ϵ��
	float p_out, i_out, d_out;//���������ֵ
	float pwm; 						      //pwm���
	uint32_t MaxOutput;				  //����޷�
	uint32_t IntegralLimit;			//�����޷� 
}positionpid_t;

void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
void PositionPID_setPara(positionpid_t *pid_t, float kp, float ki, float kd);
float Position_PID(positionpid_t *pid_t, float target, float measured);

void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
void IncrementalPID_setPara(incrementalpid_t *pid_t, float kp, float ki, float kd);
float Incremental_PID(incrementalpid_t *pid_t, float target, float measured);

#endif

