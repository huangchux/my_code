#ifndef _BEEP_H_
#define _BEEP_H_
#include "AllHead.h"

sbit BEEP = P2^5;  //��P2.5�ܽŶ���ΪBEEP


void BEEP_Contral();
void BEEP_Time(u8 ms);

#endif
