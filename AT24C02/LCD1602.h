#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD1602_WriteCmd(unsigned char Cmd);
void LCD1602_WriteData(unsigned char Data);
void LCD1602_Init();
void LCD1602_CursorSet(unsigned char Line,unsigned char Col);
void LCD1602_ShowChar(unsigned char Line,unsigned char Col,unsigned char Char);
void LCD1602_ShowString(unsigned char Line,unsigned char Col,unsigned char *String);
void LCD1602_ShowNum(unsigned char Line,unsigned char Col,unsigned int Num,unsigned char Lenth);
void LCD1602_ShowSignedNum(unsigned char Line,unsigned char Col,int Num,unsigned char Lenth);
void LCD1602_ShowHex(unsigned char Line,unsigned char Col,unsigned int Num);

#endif