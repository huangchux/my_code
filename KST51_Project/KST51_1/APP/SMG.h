#ifndef __SMG_H
#define __SMG_H


#define LED_SMG_PORT	P0

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;


void SMG_Scan();
void SMG_Show(u32 num);

extern u8 code gsmg[];
extern u8 SMG_BUFF[6];


#endif