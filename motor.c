#include <REGX52.H>
//λ����
sbit IN1 = P1^1;
sbit IN2 = P1^2;
sbit IN3 = P1^3;
sbit IN4 = P1^4;


void L_motor_go ()  //�����ת��
{IN1 = 0;IN2 = 1;}
void L_motor_back ()  //�������ת
{IN1 = 1;IN2 = 0;}
void L_motor_stop ()  //�����ֹͣ
{IN1 = 0;IN2 = 0;}
void R_motor_go ()  //�Ҳ���ת��
{IN3 = 1;IN4 = 0;}
void R_motor_back ()  //�Ҳ�����ת
{IN3 = 0;IN4 = 1;}
void R_motor_stop ()  //�Ҳ���ֹͣ
{IN3 = 0;IN4 = 0;}