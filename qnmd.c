#include <qnmd.h>

int counter == 0;
{
	if(counter == 0)
	{
		TRACK();				
		Measure_Distance();		//正常循迹
		if(Distance <= 20)		//开始避障的距离，跟车速相关
		{counter = 20000;}
	}
	else if(counter >= 10000)		//1000~500左转
	{
		Motor_Left(1, 20); Motor_Right(1, 80);
		counter--;
	}
	else if(counter >= 0)		//500~0右转
	{
		Motor_Left(1, 80); Motor_Right(1, 20);
		counter--;
	}
	else
		counter = 0;
}