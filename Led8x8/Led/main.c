#include <REGX52.H>
#include <INTRINS.H>
#include <Timer0.h>
#include <Delay.h>
volatile unsigned char i = 1;
unsigned char j = 0;
sbit SER = P3^4;
sbit RCK = P3^5;
sbit SRCK = P3^6;
void HC595(unsigned char Byte)
{
	unsigned char i;
	for (i = 0; i < 8; i++)
	{
		SER = (Byte & (0x80 >> i)) !=0;
		SRCK = 0;
		SRCK = 1;
	}
	RCK = 0;
	RCK = 1;
}

void HC595_Show(unsigned char hang,unsigned char Data)
{
	HC595(Data);
	P0 = ~(0x80 >> (hang - 1));
	Delay(1);
	P0 = 0xFF;
}

void main()
{
	Timer0_Init();
	while(1)
	{
		switch(i)
		{
			case 1:HC595_Show(3,0x84);HC595_Show(4,0xFC);HC595_Show(5,0x84);break;
			case 2:HC595_Show(3,0xFC);HC595_Show(4,0x04);HC595_Show(5,0x04);break;
			case 3:HC595_Show(2,0x78);HC595_Show(3,0x84);HC595_Show(4,0x84);HC595_Show(5,0x84);HC595_Show(6,0x78);break;
			case 4:HC595_Show(2,0xE0);HC595_Show(3,0x18);HC595_Show(4,0x04);HC595_Show(5,0x18);HC595_Show(6,0xE0);break;
			case 5:HC595_Show(2,0xFE);HC595_Show(3,0x92);HC595_Show(4,0x92);HC595_Show(5,0x92);HC595_Show(6,0x92);break;
			case 6:HC595_Show(2,0xF8);HC595_Show(3,0x04);HC595_Show(4,0x04);HC595_Show(5,0x04);HC595_Show(6,0xF8);break;
			case 7:HC595_Show(1,0x70);HC595_Show(2,0x88);HC595_Show(3,0x84);HC595_Show(4,0x42);HC595_Show(5,0x42);HC595_Show(6,0x84);HC595_Show(7,0x88);HC595_Show(8,0x70);break;
		}
	}
}


void Timer0() interrupt 1
{
	static unsigned int Num = 500;
	static unsigned int Counts = 0;
	TL0 = 0x18;
	TH0 = 0xFC;
	Counts++;
	if(Counts >= Num )
	{
		Counts = 0;
		i++;
		if (i < 7)
			Num = 500;
		else if (i == 7)
			Num = 2000;
		else if (i > 7)
		{	
			i = 1;
			Num = 500;
		}
	}
}
