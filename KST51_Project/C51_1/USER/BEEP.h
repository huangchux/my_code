#ifndef _BEEP_H_
#define _BEEP_H_
#include "AllHead.h"

sbit BEEP = P2^5;  //将P2.5管脚定义为BEEP


void BEEP_Contral();
void BEEP_Time(u8 ms);

#endif
