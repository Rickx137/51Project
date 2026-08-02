#ifndef __DS1302_H__
#define __DS1302_H__

extern char Time[7];
extern char RealTime[7];
void DS1302_Init(void);
void DS1302_WriteCmd(unsigned char Cmd);
void DS1302_WriteData(unsigned char Data);
void DS1302_Write(unsigned char Cmd,unsigned char Data);
unsigned char DS1302_ReadByte(void);
unsigned char DS1302_Read(unsigned char Cmd);
unsigned char BcdToDec(unsigned char Bcd);
unsigned char DecToBcd(unsigned char Dec);
void DS1302_SetTime(void);
void DS1302_GetTime(void);
void DS1302_TimeShow(void);
void DS1302_SetRealTime(void);

#endif
