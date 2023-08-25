#include <REG52.H>
#include <intrins.h>
#include "car.h"
#include "xunji.h"

unsigned int  time=0;
unsigned int  timer=0;
unsigned char posit=0;
unsigned long S=0;
//bit      flag =0;
//unsigned charconst discode[] ={ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF,0xff/*-*/};
//unsigned charconst positon[3]={ 0xfe,0xfd,0xfb};
//unsigned chardisbuff[4]	   ={ 0,0,0,0};

sbit Trig = P2^4;   
sbit Echo = P2^5;
sbit digit1 = P1^0;
sbit digit2 = P1^1;
sbit digit3 = P1^2;
sbit digit4 = P1^3;

//intcounter1;

unsigned int sum;
unsigned int mindistance = 20;

void Delay20us ()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 6;
	while (--i);
}

void delaymicro(unsigned int micro)
{
   while(micro--) {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }	
}
	
void chaoshengbo ()   //ultrasound
{	
	Trig = 1;
	Delay20us();
	Trig = 0;
	
	if (Echo == 1)
	{
		TR1 = 0;
		sum = ((TH1*256+TL1)*0.034)/2+1;
		if(mindistance > sum)
		{
			car_stop ();
		}
		else 
		{
			xunji ();
		}
	}
}

void ultrasound_send(){
	Trig = 1;
	delaymicro(10);
	Trig = 0;
}
void Echo_wait(){
		while(!Echo);
		TR1 = 1;
		while(Echo);
		TR1 = 0;
}