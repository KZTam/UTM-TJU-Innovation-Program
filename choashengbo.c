#include <REG52.H>
#include <intrins.h>
#include "car.h"
#include "xunji.h"



sbit Trig = P0^6;   //超声波测距发射位点
sbit Echo = P0^5;   //超声波测距接收位点

unsigned int sum;   //超声波测距结果
unsigned int mindistance = 20;    //小车与障碍物的限制距离

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void Delay20us ()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 6;
	while (--i);
}
void chaoshengbo ()   //超声波测距程序
{
	TMOD = 0x11;   //设置定时器的模式
	TL1  = 0;      //设置定时器初始值
	TH1  = 0;      //设置定时初始值
	
	
	Trig = 1;   //发射脉冲至少20us
	Delay20us();
	Trig = 0;
	
	while(!Echo);  //等待超声波模块的返回脉冲
	TR1 = 1;        //打开定时器
	while(Echo);   //等待超声波模块的返回脉冲结束
	TR1 = 0;    //停止定时器，计时结束
	
	sum = ((TH1*256+TL1)*0.034)/2+1;    //计算距离
	
	if (mindistance > sum)
	{
		car_stop ();
		Delay1000ms();
	}

}