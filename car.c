#include <REGX52.H>
#include "motor.h"

sbit  ENA = P1^0;//enable pin for left motor
sbit  ENB = P1^5;//enable pin for right motor

unsigned char counter0,speed;

void Timer0_Init()        
{
	TMOD |= 0x01;     //set mode
	TL0 = 0xA4;     // starting oxffa4 increment to 0xffff
	TH0 = 0xFF;      
	TF0 = 0;    //reset the timer 0 flag, when timer overflow, TF0 = 1 
	TR0 = 1;      //start timer 0
	ET0 = 1;         //timer 0 enable
	PT0 = 1;        //timer priority (higher the value, higher priority)
}

void Timer1_Init(){	//no use
	TMOD |= 0x10;
	TL1 = 0;	//0xF830
	TH1 = 0;
	TF1 = 0;
	TR1 = 0;
	ET1 = 1;
	PT1 = 1;
}

void Timer1_Routine() interrupt 2
{
	//nothing
}

void Timer0_Routine() interrupt 1  //timer 0 innterrupt (PWM)
{
	TL0 = 0xA4;      
	TH0 = 0xFF;      
		
	counter0++;
	if (counter0 >=100)
	{
		counter0 = 0;
	}
	if (counter0 < speed)	//PWM for motors
	{
		ENA = 1;
		ENB = 1;
	}
	else
	{
		ENA = 0;
		ENB = 0;
	}
}

void car_go ()   //foward
{
	speed = 35;	//50
	L_motor_go ();
	R_motor_go ();
}
void car_go_manual ()   //foward
{
	speed = 50;	//50
	L_motor_go ();
	R_motor_go ();
}
void car_back_manual ()   //hou tui
{
	speed = 50;	//50
	L_motor_back ();
	R_motor_back ();
}
void car_stop ()    //stop
{
	speed = 0;
	L_motor_stop ();
	R_motor_stop ();
}
void car_leftgo ()    //turn left, left motor stop
{
	speed = 75;	//45
	R_motor_go ();
	L_motor_stop ();
}
void car_rightgo ()    //turn right, right motor stop
{
	speed = 75;
	L_motor_go ();
	R_motor_stop ();
}
void car_leftback ()    //turn left, left motor stop
{
	speed = 75;	//45
	R_motor_back ();
	L_motor_stop ();
}
void car_rightback ()    //turn right, right motor stop
{
	speed = 75;
	L_motor_back ();
	R_motor_stop ();
}
void car_rightstop ()   //lock point turn right (fast)
{
	speed = 100;
	L_motor_go ();
	R_motor_back ();
}
void car_leftstop ()   //lock point turn left (fast)
{
	speed = 100;
 	R_motor_go ();
	L_motor_back ();
}

void car_rightstop2 ()   //lock point turn right 
{
	speed = 65;	//90
	L_motor_go ();
	R_motor_back ();
}
void car_leftstop2 ()   //lock point turn left 
{
	speed = 65;	//90
 	R_motor_go ();
	L_motor_back ();
}