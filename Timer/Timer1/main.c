#include <REGX52.H>

void Timer_Init()
{
	//TMOD = 0x01;会导致高四位被置1
	TMOD &= 0xF0;//与等于
	TMOD |= 0x01;//或等于
	TF0 = 0;
	TR0 = 1;
	TH0 = 0xFC;
	TL0 = 0x18;
	ET0 = 1;
	EA = 1;
	IPH = 0x02;
	PT0 = 1;
}

void main()
{
	Timer_Init();
	while(1)
	{
			
	}
}
	
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Counts = 0;
	T0Counts++;
	TH0 = 0xFC;
	TL0 = 0x18;
	if(T0Counts >= 1000)
	{
		T0Counts = 0;
		P2_0 = ~P2_0;
	}
}

