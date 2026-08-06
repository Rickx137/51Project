#include <REGX52.H>
#include "OneWire.h"

#define DS18B20_SkipRom     0xCC
#define DS18B20_ConvertT    0x44
#define DS18B20_ReadScratchpad     0xBE

void DS18B20_Start(void)
{
    OneWire_Init();
    OneWire_WriteByte(DS18B20_SkipRom);
    OneWire_WriteByte(DS18B20_ConvertT);
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