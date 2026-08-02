#include <REGX52.H>
#include <Delay.h>
sbit SER = P3^4;
sbit RCK = P3^5;
sbit SRCK = P3^6;

void HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for (i = 0;i<8;i++)
	{
		SER = (Byte & 0x80 >> i) != 0;
		SRCK = 0;
		SRCK = 1;
	}
	RCK = 0;
	RCK = 1;
}


void Led8x8(unsigned char Lie,unsigned char Data)//ÏÔÊ¾Ò»ÁÐ
{
	P0 = ~(0x80 >> (Lie - 1));
	HC595_WriteByte(Data);
	Delay(1);
	P0 = 0xFF;
}

