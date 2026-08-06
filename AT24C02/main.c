#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "I2C.h"
#include "Timer0.h"
#include "Key.h"
#include "Leds.h"
unsigned char Temp;

void main()
{
	unsigned char a;
	Timer0_Init();	
	while(1)
	{
		unsigned char Temp;
		a = KEY();
		if (a){Temp = a;}
		Leds(1,Temp);
	}
}

void Timer() interrupt 1
{

	static unsigned int Counts = 0;
	TL0 = 0x18;
	TH0 = 0xFC;
	Counts++;
	if(Counts >= 20)
	{
		Counts = 0;
		Key_Loop();
	}

}



