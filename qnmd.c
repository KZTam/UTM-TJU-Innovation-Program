#include <qnmd.h>

int counter == 0;
{
	if(counter == 0)
	{
		TRACK();				
		Measure_Distance();		//����ѭ��
		if(Distance <= 20)		//��ʼ���ϵľ��룬���������
		{counter = 20000;}
	}
	else if(counter >= 10000)		//1000~500��ת
	{
		Motor_Left(1, 20); Motor_Right(1, 80);
		counter--;
	}
	else if(counter >= 0)		//500~0��ת
	{
		Motor_Left(1, 80); Motor_Right(1, 20);
		counter--;
	}
	else
		counter = 0;
}