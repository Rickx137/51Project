#ifndef __OneWire_H__
#define __OneWire_H__

unsigned char OneWire_Init(void);
void OneWire_WriteBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit(void);
void OneWire_WriteByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte(void);

#endif
