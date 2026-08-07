#include <REGX52.H>
sbit OneWire_DQ = P3^7;

unsigned char OneWire_Init(void)
{   
    unsigned char i;
    unsigned char AckBit;
    EA = 0;//防止定时器干扰时序读写
    OneWire_DQ = 1;//确定状态
    OneWire_DQ = 0;
	i = 227;while (--i);//Delay 500us
    OneWire_DQ = 1;
    i = 29;while (--i);//Delay 70us
    AckBit = OneWire_DQ;
    i = 158;while (--i);//Delay 350us
    EA = 1;
    return AckBit;//确定从机是否存在（存在返回0，因为待机状态有上拉电阻置1）
}
void OneWire_WriteBit(unsigned char Bit)
{
    unsigned char i;
    EA = 0;
    OneWire_DQ = 0;
    i = 3;while (--i);//Delay 10us
    OneWire_DQ = Bit;//如果是写0，正好不变，写1则拉高
    i = 24;while (--i);//Delay 50us
    OneWire_DQ = 1;//如果是1就没有变化，0正好结束
    EA = 1;

}
unsigned char OneWire_ReceiveBit(void)
{
    unsigned char i;
    unsigned char Bit;
    EA = 0;
    OneWire_DQ = 0;//开始读的标志
    i = 1;while (--i);//Delay 5us
    OneWire_DQ = 1;//释放总线，让从机决定电平
    i = 1;while (--i);//Delay 5us
    Bit = OneWire_DQ;
    i = 22;while (--i);//Delay 50us
    EA = 1;
    return Bit;
}
void OneWire_WriteByte(unsigned char Byte)
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        OneWire_WriteBit(Byte&(0x01 << i));
    }
}
unsigned char OneWire_ReceiveByte(void)
{
    unsigned char i;
    unsigned char Byte = 0x00;
    for (i = 0;i < 8;i++)
    {
        if(OneWire_ReceiveBit()){Byte |= (0x01 << i);}
    }
    return Byte;
}