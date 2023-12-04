#ifndef _SMG_H_
#define _SMG_H_

#include "AllHead.h"
#define SMG_A_DP_PORT P0  //宏定义数码管P0端口

sbit LSA = P2^2; //将P2.2管脚定义为LSA
sbit LSB = P2^3; //将P2.3管脚定义为LSB
sbit LSC = P2^4; //将P2.4管脚定义为LSC

void smg_display(u8 dat[], u8 location);
//void smg_loop(void);
//void smg_SetBuf(u8 location,u8 number);

extern u8 gsmg_code[17]; //允许外部进行调用就得用extern

#endif

