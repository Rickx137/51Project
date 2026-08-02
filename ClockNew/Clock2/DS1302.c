#include <REGX52.H>
#include "LCD1602.h"

sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;
sbit DS1302_SCLK = P3^6;

#define Second  0x80
#define Minute  0x82
#define Hour    0x84
#define Date     0x86
#define Month   0x88
#define Day     0x8A
#define Year    0x8C
#define WP      0x8E

char Time[7] = {07,07,07,6,14,30,00};//初次写入时间
char RealTime[7];//存放实时时间
void DS1302_Init(void)//初始化
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_WriteCmd(unsigned char Cmd)//写命令
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        DS1302_IO = (Cmd >> i) & 0x01;
        DS1302_SCLK = 1;
        DS1302_SCLK = 0;
    }
}
void DS1302_WriteData(unsigned char Data)//写数据（本质和写数据一样，只是为了防止自己写的位置不对，提醒一下）
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
       DS1302_IO = (Data >> i) & 0x01;
       DS1302_SCLK = 1;
       DS1302_SCLK = 0;
    }
}
void DS1302_Write(unsigned char Cmd,unsigned char Data)//在某个寄存器写入（包括命令和数据）
{
    DS1302_CE = 1;
    DS1302_WriteCmd(Cmd);
    DS1302_WriteData(Data);
    DS1302_CE = 0;
}
unsigned char DS1302_ReadByte(void)//读取字节（8bit）
{
    unsigned char i,Data = 0x00;
    DS1302_SCLK = 0;
    for (i = 0;i < 8;i++)
    {
        DS1302_SCLK = 1;
         
        if(DS1302_IO)
        {
            Data |= (0x01 << i);
        }
        DS1302_SCLK = 0;
    }
    return Data;
}
unsigned char DS1302_Read(unsigned char Cmd)//在指定位置读出
{
    unsigned char Data;
    DS1302_CE = 1;
    DS1302_WriteCmd(Cmd | 0x01);
    DS1302_IO = 1;
    Data = DS1302_ReadByte();
    DS1302_CE = 0;
    DS1302_IO = 0;//一定一定一定要加上，否则会导致数据读取错乱！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！（使IO不再处于可写入状态，不会被干扰）
    return Data;
}
unsigned char BcdToDec(unsigned char Bcd)//BCD转十进制
{
    unsigned char result;
    result = ((Bcd >> 4) * 10) + (Bcd & 0x0F);
    return result;
}
unsigned char DecToBcd(unsigned char Dec)//十进制转BCD
{
    unsigned char result;
    result = (((Dec / 10) <<4) + (Dec % 10));
    return result;
}
void DS1302_SetTime(void)//初次写入时间
{
   DS1302_Write(WP,0x00);
   
   DS1302_Write(Year,DecToBcd(Time[0]));
   DS1302_Write(Month,DecToBcd(Time[1]));
   DS1302_Write(Date,DecToBcd(Time[2]));
   DS1302_Write(Day,DecToBcd(Time[3]));
   DS1302_Write(Hour,DecToBcd(Time[4]));
   DS1302_Write(Minute,DecToBcd(Time[5]));
   DS1302_Write(Second,DecToBcd(Time[6]));

   DS1302_Write(WP,0x80);
}
void DS1302_GetTime(void)//获取实时时间
{
    RealTime[0] = BcdToDec(DS1302_Read(Year));
    RealTime[1] = BcdToDec(DS1302_Read(Month));
    RealTime[2] = BcdToDec(DS1302_Read(Date));
    RealTime[3] = BcdToDec(DS1302_Read(Day));
    RealTime[4] = BcdToDec(DS1302_Read(Hour));
    RealTime[5] = BcdToDec(DS1302_Read(Minute));
    RealTime[6] = BcdToDec(DS1302_Read(Second));
}
void DS1302_TimeShow(void)//显示实时时间
{
    LCD1602_ShowNum(1,1,20,2);//写入世纪（世纪不会变）
	LCD1602_ShowChar(1,5,'-');//美观符号
	LCD1602_ShowChar(1,8,'-');
	LCD1602_ShowString(1,11,"Date:");
	LCD1602_ShowChar(2,3,':');
	LCD1602_ShowChar(2,6,':');

    DS1302_GetTime();//获取时间
	LCD1602_ShowNum(1,3,RealTime[0],2);//年
	LCD1602_ShowNum(1,6,RealTime[1],2);//月
	LCD1602_ShowNum(1,9,RealTime[2],2);//日
	LCD1602_ShowNum(1,16,RealTime[3],1);//星期
	LCD1602_ShowNum(2,1,RealTime[4],2);//时
	LCD1602_ShowNum(2,4,RealTime[5],2);//分
	LCD1602_ShowNum(2,7,RealTime[6],2);//秒

}
void DS1302_SetRealTime(void)
{
    DS1302_Write(WP,0x00);
   
    DS1302_Write(Year,DecToBcd(RealTime[0]));
    DS1302_Write(Month,DecToBcd(RealTime[1]));
    DS1302_Write(Date,DecToBcd(RealTime[2]));
    DS1302_Write(Day,DecToBcd(RealTime[3]));
    DS1302_Write(Hour,DecToBcd(RealTime[4]));
    DS1302_Write(Minute,DecToBcd(RealTime[5]));
    DS1302_Write(Second,DecToBcd(RealTime[6]));

    DS1302_Write(WP,0x80);
}