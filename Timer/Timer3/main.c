#include <REGX52.H>
#include <Delay.h>
#include <Timer0.h>
#include <Leds.h>
unsigned char Sec = 0;
unsigned char Min = 0;
unsigned char Hour = 0;
unsigned int Timer0Counts = 0;
unsigned char Sec1=0;
unsigned char Sec2=0;
unsigned char Min1=0;
unsigned char Min2=0;
unsigned char Hour1=0;
unsigned char Hour2=0;
unsigned char Time[9] = {255,255,255,255,255,255,255,255,255};
unsigned char i = 0;
void main()
{
	Timer0_Init();
	while(1)
	{
		if(Sec < 60)
		{
			Sec1 = Sec / 10;
			Sec2 = Sec % 10;
		}
		if(Sec >= 60)
		{
			Min++;
			Sec = 0;
			if (Min < 60)
			{
				Min1 = Min / 10;
			  Min2 = Min % 10;
			}
			if(Min >= 60)
			{
				Hour++;
				Min = 0;
				Hour1 = Hour / 10;
				Hour2 = Hour % 10;
			}
		}
		Time[1] = Hour1;
		Time[2] = Hour2;
		Time[3] = 100;
		Time[4] = Min1;
		Time[5] = Min2;
		Time[6] = 100;
		Time[7] = Sec1;
		Time[8] = Sec2;
		
		for ( i = 1;i<=8;i++)
		{
			Leds(i,Time[i]);
		}
			
	
	}
}


void Timer0() interrupt 1
{
		TL0 = 0x18;
		TH0 = 0xFC;
		Timer0Counts++;
		if (Timer0Counts >=1000)
		{
			Timer0Counts = 0;
			Sec++;
			if (Sec >= 60)
				Sec = 60;
		}
}
	
	