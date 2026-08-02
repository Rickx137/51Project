#include <REGX52.H>
#include "Delay.h"
sbit LCD1602_WR = P2^5;
sbit LCD1602_RS = P2^6;
sbit LCD1602_EN = P2^7;
#define LCD1602_DataPort    P0

unsigned long Pow(int X,unsigned int Y)//X的Y次方
{
    unsigned char i;
    unsigned long result = 1;
    if (Y > 0)
    {
        for (i = Y;i > 0;i--)
        {
            result *= X;
        }
    }
    else if (Y == 0)
    {
        result = 1;
    }
    return result;
}
void LCD1602_WriteCmd(unsigned char Cmd)//写命令
{
    LCD1602_WR = 0;
    LCD1602_RS = 0;
    LCD1602_DataPort = Cmd;
    LCD1602_EN = 1;
    Delay(1);
    LCD1602_EN = 0;
    Delay(1);
}


void LCD1602_WriteData(unsigned char Data)//写数据（一个字符）
{
    LCD1602_WR = 0;
    LCD1602_RS = 1;
    LCD1602_DataPort = Data;
    LCD1602_EN = 1;
    Delay(1);
    LCD1602_EN = 0;
    Delay(1);
}
void LCD1602_Init()//初始化
{
    LCD1602_WriteCmd(0x38);
    LCD1602_WriteCmd(0x0C);
    LCD1602_WriteCmd(0x06);
    LCD1602_WriteCmd(0x01);
}

void LCD1602_CursorSet(unsigned char Line,unsigned char Col)//设置光标位置
{
    if(Line == 1)
    {
        LCD1602_WriteCmd(0x80 | (Col - 1));
    }
    else if(Line == 2)
    {
        LCD1602_WriteCmd(0x80 | (Col - 1) + 0x40);
    }
}

void LCD1602_ShowChar(unsigned char Line,unsigned char Col,unsigned char Char)//显示一个字符
{
    LCD1602_CursorSet(Line,Col);
    LCD1602_WriteData(Char);
}
void LCD1602_ShowString(unsigned char Line,unsigned char Col,unsigned char *String)//显示字符串
{
    unsigned char i;
    LCD1602_CursorSet(Line,Col);
    for (i = 0;String[i] != '\0';i++)
    {
        LCD1602_WriteData(String[i]);
    }
}
void LCD1602_ShowNum(unsigned char Line,unsigned char Col,unsigned int Num,unsigned char Lenth)//显示数字
{
    unsigned char i;
    LCD1602_CursorSet(Line,Col);
    for (i = Lenth;i > 0 ; i--)
    {
        LCD1602_WriteData(0x30 + Num / (Pow(10,(i - 1))) % 10);
    }
   
}
void LCD1602_ShowSignedNum(unsigned char Line,unsigned char Col,int Num,unsigned char Lenth)//显示有符号的数字
{
    int Num1;
    unsigned char i;
    LCD1602_CursorSet(Line,Col);
    if (Num > 0)
    {
        LCD1602_WriteData('+');
        Num1 = Num;
    }
    else if (Num < 0)
    {
        LCD1602_WriteData('-');
        Num1 = -Num;
    }
    else if (Num == 0)
    {
        Num1 = Num;
    }
     for (i = Lenth;i > 0 ; i--)
    {
        LCD1602_WriteData(0x30 + Num1 / (Pow(10,(i - 1))) % 10);
    }

}
void LCD1602_ShowHex(unsigned char Line,unsigned char Col,unsigned int Num)//最多可显示四位16进制数字，若不足4位，前面补零
{
    unsigned char Temp;
    unsigned char i;
    
    LCD1602_ShowString(Line,Col,"0x");
    for (i = 1;i != 255;i--)
    {
        Temp = (Num >> (4*i) & 0x0F);
        if (Temp < 10)
        {
            LCD1602_WriteData(Temp + '0');
        }
        else if (Temp >= 10)
        {
            LCD1602_WriteData(Temp-10 + 'A');
        } 
    }

}

