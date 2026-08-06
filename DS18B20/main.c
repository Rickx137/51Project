#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "OneWire.h"
#include "DS18B20.h"

void main()
{
	float T;
	
	LCD1602_Init();
	while(1)
	{
		DS18B20_Start();
		Delay(750);
		T = DS18B20_ReadT();
		if(T < 0)
		{
			LCD1602_ShowChar(1,1,'-');
			T = -T;
		}
		else
		{
			LCD1602_ShowChar(1,1,'+');
		}
		LCD1602_ShowNum(1,2,T,3);
		LCD1602_ShowChar(1,5,'.');
		LCD1602_ShowNum(1,6,(unsigned long)(T*10000)%10000,4);
	}
}