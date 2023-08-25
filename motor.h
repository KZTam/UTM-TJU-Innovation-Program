#ifndef __MOTOR_H_
#define __MOTOR_H_


void L_motor_go ();//左侧电机正转
void R_motor_go ();//右侧电机正转
void L_motor_back ();//左侧电机反转
void R_motor_back ();//右侧电机反转
void L_motor_stop ();//左侧电机停止
void R_motor_stop();//右侧电机停止
void Timer0_Init();
void Timer1_Init();
#endif