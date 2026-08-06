#include <REGX52.H>
sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


void I2C_Start(void)//开始标志
{
    I2C_SCL = 1;
    I2C_SDA = 1;
    I2C_SDA = 0;
    I2C_SCL = 0;
}
void I2C_Stop(void)//结束标志
{
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_SDA = 1; 
}
void I2C_SendByte(unsigned char Byte)//写字节
{
    unsigned char i;
    for (i = 0;i < 8;i++)
    {
        I2C_SDA = Byte & (0x80 >> i);
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}
unsigned char I2C_ReadByte(void)//读字节
{
    unsigned char i;
    unsigned char Byte = 0x00;
    I2C_SDA = 1;
    for (i = 0;i < 8;i++)
    {
        I2C_SCL = 1;
        if (I2C_SDA == 1){Byte |= (0x80 >> i);}
        I2C_SCL = 0;
    }
    return Byte;
}
void I2C_SendAck(unsigned char AckBit)//发送ack
{
    I2C_SCL = 0;
    I2C_SDA = AckBit;
    I2C_SCL = 1;
    I2C_SCL = 0;
}
unsigned char I2C_ReciveAck(void)//读取ack
{
    unsigned char AckBit;  
    I2C_SCL = 0;//将scl变为0，使sda可变，并且防止sda变化触发s/p
    I2C_SDA = 1;//释放总线，使sda可写
 
    I2C_SCL = 1;//读取sda的状态
    AckBit = I2C_SDA;
    I2C_SCL = 0;
    return AckBit;
}