#include "bluebee.h"
#include <REGX52.H>

char rxdata;
int uartflag;

void Timer2_UART_init(){
	T2CON = 0x34;
	PCON &= 0x7F;	//115200?
	TH2 = 0xFF;
	TL2 = 0xFD;
	RCAP2H = 0xFF;
	RCAP2L = 0xFD;
	SCON = 0x50;		// serial port initialisation
	ES = 1;			// enable serial port interrupt
}

void Timer2_autoreload_init(){
	T2CON = 0x04;
	PCON &= 0x7F;
	TH2 = 0xFF;
	TL2 = 0xFF;	
	RCAP2H = 0xFF;
	RCAP2L = 0xA4;
	PT2 = 1;
}

//void UART_init(){
//	PCON &= 0x7F;
//	SM0 = 0;	
//	SM1 = 1;	//mode = 01 (8-bits UART with variable baud rate)
//	REN = 1;	//receive enable
//	TI = 0;
//	RI = 0;
//	ES = 1; //serial port interruptEN
//}

void UARTRxCallback(void) interrupt 4
{
	RI = 0;
	rxdata = SBUF;
	ES = 0;
}

void UART_Receive(){
	ES = 0;
	RI = 0;
	rxdata = SBUF;
	while(!RI);
}

//void manual_control(void)
//{
//	if(RI == 1){
//			switch(rxdata)
//		{
//			case 'F':
//				car_go_manual();
//			break;
//			
//		case 'B':
//				car_back_manual();
//			break;
//			
//		case 'L':
//				car_leftstop2();
//			break;
//			
//		case 'R':
//				car_rightstop2();
//			break;
//			
//		case 'G':
//				car_leftgo();
//			break;

//		case 'I':
//				car_rightgo();
//			break;

//		case 'H':
//				car_leftback();
//			break;
//			
//		case 'J':
//				car_rightback();
//			break;
//		
//		case 'W':
//			uartflag = 1;
//			break;
//				
//		case 'X':
//			uartflag = 0;
//			car_stop();
//		break;
//					
//			default:
//				car_stop();
//			break;
//		}
//		ES = 1;		//enable the UART IT again to receive next message
//	}
//}