#include <REGX52.H>

void Timer0_Init()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TR0 = 1;
	TF0 = 0;
	TL0 = 0xA4;
	TH0 = 0xFF;
	ET0 = 1;
	EA = 1;
	IPH &= 0xFD;
	IPH |= 0x02;
	PT0 = 1;
}