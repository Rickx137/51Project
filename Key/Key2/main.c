#include <REGX52.H>
#include <INTRINS.H>
void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;
	while(xms > 0)
	{
		xms--;
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
	while (1)
	{
		if (P3_1 == 0)
		{
			Delay(20);//消除抖动
			while(P3_1 == 0);//检测松手
			Delay(20);//消抖
			P2_0 = ~P2_0;//状态取反
		}
	}
}