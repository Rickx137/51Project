#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{
	char Lednum = 0;
	P2 = ~0x01;
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			Lednum = (Lednum <= 0 ) ? 7 :Lednum - 1;
			P2 = ~(0x01<<Lednum);
		}
		if (P3_0 == 0)
		{
			Delay(20);
			while(P3_0 == 0);
			Delay(20);
			Lednum = (Lednum >= 7 ) ? 0 : Lednum + 1;
			P2 = ~(0x01<<Lednum);
		}
	}
}