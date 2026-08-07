#ifndef __DS18B20_H__
#define __DS18B20_H__

unsigned char DS18B20_Start(void);
float DS18B20_ReadT(void);
void DS18B20_BitSet(unsigned char Bit);

#endif
