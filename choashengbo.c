#include <REG52.H>
#include <intrins.h>
#include "car.h"
#include "xunji.h"



sbit Trig = P0^6;   //��������෢��λ��
sbit Echo = P0^5;   //������������λ��

unsigned int sum;   //�����������
unsigned int mindistance = 20;    //С�����ϰ�������ƾ���

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
void chaoshengbo ()   //������������
{
	TMOD = 0x11;   //���ö�ʱ����ģʽ
	TL1  = 0;      //���ö�ʱ����ʼֵ
	TH1  = 0;      //���ö�ʱ��ʼֵ
	
	
	Trig = 1;   //������������20us
	Delay20us();
	Trig = 0;
	
	while(!Echo);  //�ȴ�������ģ��ķ�������
	TR1 = 1;        //�򿪶�ʱ��
	while(Echo);   //�ȴ�������ģ��ķ����������
	TR1 = 0;    //ֹͣ��ʱ������ʱ����
	
	sum = ((TH1*256+TL1)*0.034)/2+1;    //�������
	
	if (mindistance > sum)
	{
		car_stop ();
		Delay1000ms();
	}

}