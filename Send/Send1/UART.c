#include <REGX52.H>

void UART_Init()
{
	SCON = 0x50;//配置串口模式
	PCON &= 0x7F;
	TMOD = 0x21;//配置计时器
	TH1 = 0xFA;		
	TL1 = 0xFA;
	TH0 = 0xFC;
	TL0 = 0x66;
	TF1 = 0;
	TF0 = 0;
	ET0 = 1;
	ET1 = 0;
  EA = 1;
	ES = 1;
	PS = 1;
	PT0 = 0;
	IPH &= 0xE7;
	IPH |= 0x18;
	TR1 = 1;
	TR0 = 1;
}



void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0);
	TI = 0;
}