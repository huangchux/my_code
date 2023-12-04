#ifndef _DS18B20_H
#define _DS18B20_H

#include "AllHead.h"

sbit DS18B20_PORT = P3^7; //����ds18b20 DQ�Ĺܽ�

void ds18b20_reset(void);
u8 ds18b20_check(void);
u8 ds18b20_init(void);
void ds18b20_write_byte(u8 dat);
u8 ds18b20_read_bit(void);
void ds18b20_write_byte(u8 dat);
void ds18b20_start(void);
u8 ds18b20_read_temperture(void);

#endif
