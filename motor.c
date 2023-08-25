#include <REGX52.H>
//位定义
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;


void L_motor_go ()  //左侧电机转动
{IN1 = 0;IN2 = 1;}
void L_motor_back ()  //左侧电机反转
{IN1 = 1;IN2 = 0;}
void L_motor_stop ()  //左侧电机停止
{IN1 = 0;IN2 = 0;}
void R_motor_go ()  //右侧电机转动
{IN3 = 1;IN4 = 0;}
void R_motor_back ()  //右侧电机反转
{IN3 = 0;IN4 = 1;}
void R_motor_stop ()  //右侧电机停止
{IN3 = 0;IN4 = 0;}