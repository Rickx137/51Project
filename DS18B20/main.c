#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "OneWire.h"
#include "DS18B20.h"

void main()
{
	float T;
	
	LCD1602_Init();
	//DS18B20_BitSet(10);//设置为10bit，第一次烧录后可注释掉，已存入eeprom里
	while(1)
	{
		if(DS18B20_Start() == 1)//测量温度
		{
			LCD1602_ShowString(1,1,"Err   ");
		}
		else
		{
			while(!OneWire_ReceiveBit());//测温时返回0，完成返回1，以此判断
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
			LCD1602_ShowNum(1,2,T,2);
			LCD1602_ShowChar(1,4,'.');
			LCD1602_ShowNum(1,5,(unsigned long)(T*100)%100,2);//显示小数部分

		}

	}
}