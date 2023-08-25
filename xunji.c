#include <REGX52.H>
#include <intrins.h>
#include "car.h"
#include "xunji.h"

sbit D1 = P0^0;
sbit D2 = P0^1;
sbit D3 = P0^2;
sbit D4 = P0^3;
int lineflag = 0;
int counter = 0;

void Delay50ms ()   //@11.0952MHz
{
	unsigned char i,j;
	
	i = 90;
	j = 163;
	do
	{while  (--j);
	}while  (--i);
}

void delaymicroseconds(unsigned int micro)
{
   while(micro--) {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }	
//		unsigned char i;	//miliseconds

//	while (micro--) {
//		for (i = 0; i < 120; i++);
//	}
}
void xunji ()
{
	if(D1==1&&D2==1&&D3==1&&D4==1)//È«²¿¼ì²âµ½ºÚÏß
	{car_go ();}
	if(D1==0&&D2==0&&D3==1&&D4==0)//ÏòÓÒÎ¢µ÷
	{
		
		car_rightgo ();
	
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{car_go ();}
	}
	if(D1==0&&D2==1&&D3==0&&D4==0)//Ïò×óÎ¢µ÷
	{
		car_stop ();
		car_leftgo ();
		Delay50ms ();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{car_go ();}
	}
	if(D1==1&&D2==1&&D3==0&&D4==0)//Ö±½Ç×ó¹Õ
	{
		car_go ();
		Delay50ms ();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			car_stop ();
			Delay50ms ();
			car_leftstop ();
		}
	}
	if(D1==0&&D2==0&&D3==1&&D4==1)//Ö±½ÇÓÒ¹Õ
	{
		car_go ();
		Delay50ms ();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			car_stop ();
			Delay50ms ();
			car_rightstop ();
		}
	}
	if((D1==1&&D2==0&&D3==0&&D4==0)||(D1==1&&D2==1&&D3==0&&D4==0)||(D1==1&&D2==1&&D3==1&&D4==0))//Èñ½Ç×ó¹Õ
	{
		car_go ();
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			car_stop ();
			Delay50ms ();
			car_leftstop ();
		}
	}
	if((D1==0&&D2==0&&D3==0&&D4==1)||(D1==0&&D2==0&&D3==1&&D4==1)||(D1==0&&D2==1&&D3==1&&D4==1))//Èñ½ÇÓÒ¹Õ
	{
		car_go ();
		Delay50ms();
		if(D1==0&&D2==0&&D3==0&&D4==0)
		{
			car_stop ();
			Delay50ms ();
			car_rightstop ();
		}
	}
	if(D1==0&&D2==1&&D3==1&&D4==0)
	{
		if(D4==1)
		{
			car_rightstop ();
		}
	}
	
	if(D1==0&&D2==1&&D3==1&&D4==0)
	{
		if(D1==1)
		{
			car_leftstop ();
		}
	}
}

void jiuzheng(){
			while(!(D1==0&&D2==0&&D3==0&&D4==0)){
				if(D1==0&&D2==0&&D3==1&&D4==0 || D1==0&&D2==0&&D3==0&&D4==1 || D1==0&&D2==0&&D3==1&&D4==1 || D1==0&&D2==1&&D3==1&&D4==1)	{
					car_rightstop2();
				//delaymicroseconds(5000);
				}
				else if(D1==0&&D2==1&&D3==0&&D4==0 || D1==1&&D2==0&&D3==0&&D4==0 || D1==1&&D2==1&&D3==0&&D4==0 || D1==1&&D2==1&&D3==1&&D4==0) {
					car_leftstop2();
					//delaymicroseconds(5000);
				}	
			}
}

void linefollow(){	//black = 1, white = 0
	if((D1==0&&D2==0&&D3==0&&D4==0 || D1==1&&D2==1&&D3==1&&D4==1) && !lineflag)	car_go();
	else if((D1==0&&D2==0&&D3==1&&D4==0) && !lineflag){
			car_rightstop();
	}
	else if((D1==0&&D2==1&&D3==0&&D4==0) && !lineflag){
			car_leftstop();
	}
	else if((D1==1&&D2==0&&D3==1&&D4==0 || D1==0&&D2==1&&D3==1&&D4==0) && !lineflag){	//ramp climbing
		car_go_manual();
	}
	else if(D1==1&&D2==1&&D3==0&&D4==0 || D1==1&&D2==1&&D3==1&&D4==0 || D1==1&&D2==0&&D3==0&&D4==0){
		while(D1==0&&D2==0&&D3==1&&D4==1 || D1==0&&D2==1&&D3==1&&D4==1 || D1==0&&D2==0&&D3==0&&D4==1 || D1==0&&D2==0&&D3==1&&D4==0){
			car_go();
			lineflag = 1;
			if(D1==0&&D2==0&&D3==0&&D4==0) break;
		}
		delaymicroseconds(6000);	//5000
		if(D1==0&&D2==0&&D3==0&&D4==0){
			//car_stop();
			//delaymicroseconds(10000);
			while(D1==0&&D2==0&&D3==0&&D4==0 || D1==1&&D2==0&&D3==0&&D4==0 || D1==1&&D2==1&&D3==0&&D4==0){
				car_leftstop2();
				//LED7 = 1;
			}
			//LED7 = 0;
			lineflag = 0;
		}
		else lineflag = 0;
	}

	else if(D1==0&&D2==0&&D3==1&&D4==1 || D1==0&&D2==1&&D3==1&&D4==1 || D1==0&&D2==0&&D3==0&&D4==1){
		while(D1==0&&D2==0&&D3==1&&D4==1 || D1==0&&D2==1&&D3==1&&D4==1 || D1==0&&D2==0&&D3==0&&D4==1 || D1==0&&D2==0&&D3==1&&D4==0){
			car_go();
			lineflag = 1;
		if(D1==0&&D2==0&&D3==0&&D4==0) break;
		}
			delaymicroseconds(6000);	//5000
		if(D1==0&&D2==0&&D3==0&&D4==0){
			//car_stop();
			//delaymicroseconds(10000);
			while(D1==0&&D2==0&&D3==0&&D4==0 || D1==0&&D2==0&&D3==0&&D4==1 || D1==0&&D2==0&&D3==1&&D4==1){
				car_rightstop2();
				//LED7 = 1;
			}
			//LED7 = 0;
			lineflag = 0;
		}
		else lineflag = 0;
	}
	else car_stop();
}

void avoidance(){
	car_leftstop();
	delaymicroseconds(10000);
	car_go();
	delaymicroseconds(12000);
	car_rightstop();
	delaymicroseconds(10000);
	car_go();
	delaymicroseconds(20000);
	car_rightstop();
	delaymicroseconds(12000);
	/*while(D1==0&&D2==0&&D3==0&&D4==0)*/ car_go();
	delaymicroseconds(12000);
	while(D1==0&&D2==0&&D3==0&&D4==0 || D1==1&&D2==0&&D3==0&&D4==0 || D1==1&&D2==1&&D3==0&&D4==0) car_leftstop();
}