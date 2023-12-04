#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "AllHead.h"

//void EEPROM_write_one_byte(u8 addr,u8 dat);
//u8 EEPROM_read_one_byte(u8 addr);

void EEPROM_WriteByte(u8 addr,u8 Data);
u8 EEPROM_ReadByte(u8 addr);

#endif
