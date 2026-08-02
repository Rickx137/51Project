#include <REGX52.H>
#include <Delay.h>
#include <uart.h>
volatile unsigned char SendFlag = 0;
volatile unsigned char Sec = 0;


void main()
{
	UART_Init();
	while(1)
	{
		if (SendFlag)
		{
			SendFlag = 0;
			UART_SendByte(Sec);
			UART_SendByte(0x41);
		}
	}
	
	
}
	
void Timer0() interrupt 1
{
	
	static unsigned int Timer0Counts = 0;
	
	TH0 = 0xFC;
	TL0 = 0x66;
	Timer0Counts++;
	if(Timer0Counts >=1000)
	{
		SendFlag = 1;
		Sec++;
		Timer0Counts = 0;
	}
}
	
void UART_R() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		P2 = SBUF;
	}
}
	