#ifndef _SMG_H_
#define _SMG_H_

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;

void SMG_Scan();
void SMG_Dispaly();

extern u8 SMG_BUFF[2];

#endif