#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Key.h"
#include "DS1302.h"
#include "Timer0.h"
#include "Buzzer.h"

#define Second  0x80
#define Minute  0x82
#define Hour    0x84
#define Date    0x86
#define Month   0x88
#define Day     0x8A
#define Year    0x8C
#define WP      0x8E
unsigned char KeyNum,MODE = 0,TimeSetSelect = 0,TimeSetFlashFlag,BuzzerFlag = 0;
void DS1302_TimeSet()
{
	if (KeyNum == 2)
	{
		TimeSetSelect++;
		TimeSetSelect %= 7;
	}
	if (KeyNum == 4)
	{
		RealTime[TimeSetSelect]++;
		if (TimeSetSelect == 0)
		{
			if (RealTime[TimeSetSelect] > 99)
			RealTime[TimeSetSelect] = 00;
		}
		else if (TimeSetSelect == 1)
		{
			if (RealTime[TimeSetSelect] > 12)
			RealTime[TimeSetSelect] = 01;
			if (RealTime[1] == 4 || RealTime[1] == 6 || RealTime[1] == 9 || RealTime[1] == 11)
			{
				if (RealTime[2] > 30)
				RealTime[2] = 01;

			}
			else if (RealTime[1] == 2)
			{
				if (RealTime[0] % 4 == 0)
				{
					if (RealTime[2] > 29)
					RealTime[2] = 01;

				}
				else 
				{
					if (RealTime[2] > 28)
					RealTime[2] = 01;

				}
			}
		} 
		else if (TimeSetSelect == 2)
		{
			if (RealTime[1] == 1 || RealTime[1] == 3 || RealTime[1] == 5 || RealTime[1] == 7 || RealTime[1] == 8 || RealTime[1] == 10 || RealTime[1] == 12)
			{
				if (RealTime[TimeSetSelect] > 31)
				RealTime[TimeSetSelect] = 01;
			}
			else if (RealTime[1] == 4 || RealTime[1] == 6 || RealTime[1] == 9 || RealTime[1] == 11)
			{
				if (RealTime[TimeSetSelect] > 30)
				RealTime[TimeSetSelect] = 01;
			}
			else if (RealTime[1] == 2)
			{
				if (RealTime[0] % 4 == 0)
				{
					if (RealTime[TimeSetSelect] > 29)
					RealTime[TimeSetSelect] = 01;
				}
				else 
				{
					if (RealTime[TimeSetSelect] > 28)
					RealTime[TimeSetSelect] = 01;
				}
			}
		}
		else if (TimeSetSelect == 3)
		{
			if (RealTime[TimeSetSelect] > 7)
			RealTime[TimeSetSelect] = 1;
		}
		else if (TimeSetSelect == 4)
		{
			if (RealTime[TimeSetSelect] > 23)
			RealTime[TimeSetSelect] = 00;
		}
		else if (TimeSetSelect == 5)
		{
			if (RealTime[TimeSetSelect] > 59)
			RealTime[TimeSetSelect] = 00;
		}
		else if (TimeSetSelect == 6)
		{
			if (RealTime[TimeSetSelect] > 59)
			RealTime[TimeSetSelect] = 00;
		}
		
	}
	if (KeyNum == 3)
	{
		RealTime[TimeSetSelect]--;
		if (TimeSetSelect == 0)
		{
			if (RealTime[TimeSetSelect] < 0)
			RealTime[TimeSetSelect] = 99;
		}
		else if (TimeSetSelect == 1)
		{
			if (RealTime[TimeSetSelect] < 1)
			RealTime[TimeSetSelect] = 12;

			if (RealTime[1] == 4 || RealTime[1] == 6 || RealTime[1] == 9 || RealTime[1] == 11)
			{
				if (RealTime[2] > 30)
				RealTime[2] = 01;

			}
			else if (RealTime[1] == 2)
			{
				if (RealTime[0] % 4 == 0)
				{
					if (RealTime[2] > 29)
					RealTime[2] = 01;

				}
				else 
				{
					if (RealTime[2] > 28)
					RealTime[2] = 01;

				}
			}

		} 
		else if (TimeSetSelect == 2)
		{
			if (RealTime[1] == 1 || RealTime[1] == 3 || RealTime[1] == 5 || RealTime[1] == 7 || RealTime[1] == 8 || RealTime[1] == 10 || RealTime[1] == 12)
			{
				if (RealTime[TimeSetSelect] < 1)
				RealTime[TimeSetSelect] = 31;

			}
			else if (RealTime[1] == 4 || RealTime[1] == 6 || RealTime[1] == 9 || RealTime[1] == 11)
			{
				if (RealTime[TimeSetSelect] < 1)
				RealTime[TimeSetSelect] = 30;

			}
			else if (RealTime[1] == 2)
			{
				if (RealTime[0] % 4 == 0)
				{
					if (RealTime[TimeSetSelect] < 1)
					RealTime[TimeSetSelect] = 29;

				}
				else 
				{
					if (RealTime[TimeSetSelect] < 1)
					RealTime[TimeSetSelect] = 28;

				}
			}
		}
		
		else if (TimeSetSelect == 3)
		{
			if (RealTime[TimeSetSelect] < 1)
			RealTime[TimeSetSelect] = 7;
		}
		else if (TimeSetSelect == 4)
		{
			if (RealTime[TimeSetSelect] < 00)
			RealTime[TimeSetSelect] = 23;
		}
		else if (TimeSetSelect == 5)
		{
			if (RealTime[TimeSetSelect] < 00)
			RealTime[TimeSetSelect] = 59;
		}
		else if (TimeSetSelect == 6)
		{
			if (RealTime[TimeSetSelect] < 00)
			RealTime[TimeSetSelect] = 59;
		}
		
	}

	DS1302_SetRealTime();
	if (TimeSetSelect == 0 && TimeSetFlashFlag == 1){LCD1602_ShowString(1,3,"  ");}
	else {LCD1602_ShowNum(1,3,RealTime[0],2);}//年
	if (TimeSetSelect == 1 && TimeSetFlashFlag == 1){LCD1602_ShowString(1,6,"  ");}
	else {LCD1602_ShowNum(1,6,RealTime[1],2);}//月
	if (TimeSetSelect == 2 && TimeSetFlashFlag == 1){LCD1602_ShowString(1,9,"  ");}
	else {LCD1602_ShowNum(1,9,RealTime[2],2);}//日
	if (TimeSetSelect == 3 && TimeSetFlashFlag == 1){LCD1602_ShowChar(1,16,' ');}
	else {LCD1602_ShowNum(1,16,RealTime[3],1);}//星期
	if (TimeSetSelect == 4 && TimeSetFlashFlag == 1){LCD1602_ShowString(2,1,"  ");}
	else {LCD1602_ShowNum(2,1,RealTime[4],2);}//时
	if (TimeSetSelect == 5 && TimeSetFlashFlag == 1){LCD1602_ShowString(2,4,"  ");}
	else {LCD1602_ShowNum(2,4,RealTime[5],2);}//分
	if (TimeSetSelect == 6 && TimeSetFlashFlag == 1){LCD1602_ShowString(2,7,"  ");}
	else {LCD1602_ShowNum(2,7,RealTime[6],2);}//秒

}
void main()
{
	LCD1602_Init();//初始化LCD1602显示屏
	DS1302_Init();//初始化DS1302
	DS1302_SetTime();//写入时间
	Timer0_Init();

	while(1)
	{
		KeyNum = Key();
		if (KeyNum == 1)
		{
			if (MODE == 0)
			{
				MODE = 1;
				TimeSetSelect = 0;
			}
			else if (MODE == 1)
			{
				MODE = 0;
			}
		}
		switch (MODE)
		{
			case 0: DS1302_TimeShow();break;
			case 1: DS1302_TimeSet();break;
		}
		if (KeyNum == 3)
		{
			BuzzerFlag = !BuzzerFlag;
		} 
		if(BuzzerFlag==0)
			{
				if(KeyNum)
				{
					Buzzer_Time(50);
				}
			}

	}
}

void Timer0_FlashFlag() interrupt 1
{
	static unsigned int Timer0Count;
	TL0 = 0x18;
	TH0 = 0xFC;
	Timer0Count++;
	if (Timer0Count >= 500)
	{
		Timer0Count = 0;
		if (MODE == 1)
		TimeSetFlashFlag = !TimeSetFlashFlag;
		else 
		TimeSetFlashFlag = 0;
	}

}


