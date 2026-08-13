#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "Timer0.h"
#include "Key.h"
#include "AT24C02.h"
#include "Buzzer.h"

void main()
{
	float T;
	float TD;
	char TLow;
	char THigh;
	unsigned char K;
	LCD1602_Init();
	Timer0_Init();
	THigh = AT24C02_ReciveByte(0);//上电读取eeprom里的数据
	TLow = (signed char)AT24C02_ReciveByte(1);//转化成有符号的
	if(THigh > 125 || TLow < -55 || THigh <= TLow)//防止第一次读取错误数据，初始化
	{
		THigh = 35;
		TLow = 18;
		AT24C02_WriteByte(0,THigh);
		Delay(5);//留出时间写
		AT24C02_WriteByte(1,TLow);
		Delay(5);
	}
	//DS18B20_BitSet(10);//设置为10bit，第一次烧录后可注释掉，已存入eeprom里
	while(1)
	{
		if(DS18B20_Start() == 1)//检测设备是否存在
		{
			LCD1602_ShowString(1,1,"Err             ");//清屏并显示错误
			LCD1602_ShowString(2,1,"                ");
			Buzzer_Time(150);//警报
		}
		else
		{
			K = KEY();
			LCD1602_ShowString(1,1,"T:");
			LCD1602_ShowString(2,8,"TL:");
			LCD1602_ShowString(2,1,"TH:");
			if(K)//按键控制阈值，并逻辑判断，保存
			{
				if(K == 1)
				{
					THigh++;
					if(THigh >= 125)
					{
						THigh = 125;
					}
				}
				else if(K == 2)
				{
					THigh--;
					if(THigh <= TLow)
					{
						THigh++;
					}
				}
				else if(K == 3)
				{
					TLow++;
					if(TLow >= THigh)
					{
						TLow--;
					}
					else if(TLow == 0)
					{
						LCD1602_ShowChar(2,13,' ');//防止在==0的时候有一位仍保留
					}
				}
				else if(K == 4)
				{
					TLow--;
					if(TLow <= -55)
					{
						TLow = -55;
					}
					else if(TLow == 0)
					{
						LCD1602_ShowChar(2,13,' ');
					}
				}
				AT24C02_WriteByte(0,THigh);
				Delay(5);
				AT24C02_WriteByte(1,TLow);
				Delay(5);
			}
			LCD1602_ShowSignedNum(2,4,THigh,3);
			LCD1602_ShowSignedNum(2,11,TLow,2);
			while(!OneWire_ReceiveBit());//测温时返回0，完成返回1，以此判断
			T = DS18B20_ReadT();
			if(T < 0)
			{
				LCD1602_ShowChar(1,3,'-');
				TD = -T;//使现实的翻转，用原始数据与阈值比大小
			}
			else
			{
				LCD1602_ShowChar(1,3,'+');
				TD = T;
			}
			LCD1602_ShowNum(1,4,TD,2);
			LCD1602_ShowChar(1,6,'.');
			LCD1602_ShowNum(1,7,(unsigned long)(TD*100)%100,2);//显示小数部分
			if(T >= THigh)
			{
				LCD1602_ShowString(1,11,"H!");//高温预警
				Buzzer_Time(200);
			}
			else if(T <= TLow)
			{
				LCD1602_ShowString(1,11,"L!");//低温预警
				Buzzer_Time(200);
			}
			else if(T < THigh && T > TLow)
			{
				LCD1602_ShowString(1,11,"  ");//清除预警
			}

		}

	}
}


void Timer0() interrupt 1//检测按键
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