#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT24C02_ReciveByte(unsigned char WordAddress);

#endif