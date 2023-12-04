#ifndef _DS1302_H_
#define _DS1302_H_

#include "AllHead.h"

sbit DS1302_CE = P3^5;   //��λ�ܽ�
sbit DS1302_IO = P3^4;   //���ݹܽ�
sbit DS1302_SCLK = P3^6; //ʱ�ӹܽ�

void ds1302_write_byte(u8 addr,u8 dat);
u8 ds1302_read_byte(u8 addr);
void ds1302_init(void);
void ds1302_read_time(void);

extern u8 gDS1302_TIME[7];//ʹ��extern֮���ⲿ�ļ��Ϳ��Ե���


#endif

