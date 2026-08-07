#include <REGX52.H>
#include "OneWire.h"
#include "Delay.h"
#include "LCD1602.h"

#define DS18B20_SkipRom     0xCC
#define DS18B20_ConvertT    0x44
#define DS18B20_ReadScratchpad      0xBE
#define DS18B20_WriteScratchppad    0x4E
#define DS18B20_CopyScratchpad      0x48

unsigned char DS18B20_Start(void)
{
    unsigned char Ack;
    Ack = OneWire_Init();
    if (Ack)
    {
        return 1;
    }
    OneWire_WriteByte(DS18B20_SkipRom);
    OneWire_WriteByte(DS18B20_ConvertT);
    return 0;

}

float DS18B20_ReadT(void)
{
    unsigned char TLSB,TMSB;
    int Temp;
    float T;
    OneWire_Init();

    OneWire_WriteByte(DS18B20_SkipRom);
    OneWire_WriteByte(DS18B20_ReadScratchpad);
    TLSB = OneWire_ReceiveByte();
    TMSB = OneWire_ReceiveByte();
    Temp = (TLSB | (TMSB << 8));
    T = Temp /16.0;
    return T;

}
void DS18B20_BitSet(unsigned char Bit)
{
    unsigned char BIT;

    switch(Bit)
    {
        case 9:
            BIT = 0x1F;
            break;
        case 10:
            BIT = 0x3F;
            break;
        case 11:
            BIT = 0x5F;
            break;
        default:
            BIT = 0x7F;//12bit
            break;
    }
    OneWire_Init();
    OneWire_WriteByte(DS18B20_SkipRom);
    OneWire_WriteByte(DS18B20_WriteScratchppad);
    OneWire_WriteByte(0x23);//最高阈值
    OneWire_WriteByte(0x14);//最低阈值
    OneWire_WriteByte(BIT);//精度设置

    OneWire_Init();
    OneWire_WriteByte(DS18B20_SkipRom);
    OneWire_WriteByte(DS18B20_CopyScratchpad);//保存设置至eeprom
    Delay(50);
}