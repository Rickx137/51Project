#include <REGX52.H>
#include <Timer0.h>
#include <Key.h>
#include <INTRINS.H>
unsigned char Mode = 0;
void main()
{
	P2 = 0xFE;//1111 1110
	Timer0_Init();//初始化计时器
	while(1)
	{
		unsigned char Num = Key();
		if (Num == 1)//左移Mode
			Mode = 1;
		else if (Num == 2)//右移
			Mode = 2;
		else if (Num == 3)//停止
			Mode = 3;
	}
}

void Timer0() interrupt 1//中断器1
{
	static unsigned int Timer0Counts = 0;
	TL0 = 0x18;//初始化
	TH0 = 0xFC;//同上
	Timer0Counts++;
	if(Timer0Counts >= 200)//200ms
	{
		Timer0Counts = 0;
		if (Mode == 1)
			P2 = _cror_(P2,1);
		else if (Mode == 2)
			P2 = _crol_(P2,1);
	}
}