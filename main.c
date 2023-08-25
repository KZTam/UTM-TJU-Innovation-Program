#include "car.h"
#include "xunji.h"
#include "motor.h"
#include "chaoshengbo.h"
#include "bluebee.h"
#include <REGX52.H>

sbit S1 = P3^5;
sbit S2 = P3^4;
sbit S3 = P3^3;
sbit S4 = P3^2;
sbit LED7 = P1^6;
sbit LED8 = P1^7;

unsigned int dist = 0;	//in cm
int ultra_counter = 0;

int main_flag = 0;
int avoid_flag = 0;

//void Timer2_routine(void) interrupt 5	//not work
//{
////	TH2 = 0xFF;
////	TL2 = 0xFF;
//	RCAP2H = 0xFF;
//	RCAP2L = 0xA4;
//	LED7 = !LED7;
//	
//	if(main_flag)	linefollow();
//}

int main ()
{
	
	Timer0_Init();
	Timer1_Init();
	Timer2_UART_Init();
	//Timer2_autoreload_init();
		EA = 1; 

	while (1)
	{
		if(!S4){
			LED8 = !LED8;
			main_flag = !main_flag;
			while(!S4);
		}
		UART_Receive();
			if(RI == 1){
			switch(SBUF)
		{
			case 'F':
				car_go_manual();
			break;
			
		case 'B':
				car_back_manual();
			break;
			
		case 'L':
				car_leftstop2();
			break;
			
		case 'R':
				car_rightstop2();
			break;
			
		case 'G':
				car_leftgo();
			break;

		case 'I':
				car_rightgo();
			break;

		case 'H':
				car_leftback();
			break;
			
		case 'J':
				car_rightback();
			break;
		
		case 'W':
			main_flag = 1;
			LED8 = 1;
			break;
				
		case 'X':
			main_flag = 0;
			car_stop();
			LED8 = 0;
		break;
					
			default:
				car_stop();
			break;
		}
		ES = 1;		//enable the UART IT again to receive next message
	}
			//ultrasound code (will delay 10microseconds and cause line follow sensitivity reduced)
		if(ultra_counter > 10000){	//0.5s interval
				ultrasound_send();
				Echo_wait();
				LED7 = !LED7;
				dist = (unsigned int)(((float) (TH1<<8 | TL1))*0.0343/2);
				TH1 = 0;
				TL1 = 0;
				ultra_counter = 0;
				avoid_flag = 0;
		}
		ultra_counter++;
			
		if(main_flag){
			if(dist <= 25 && !avoid_flag){ 
				//main_flag = 0;
				avoidance();
				avoid_flag = 1;
			}
			else	
				linefollow();
		}
		else {
			//car_stop();	//uncomment this when manual control disabled
		}
	}
}

