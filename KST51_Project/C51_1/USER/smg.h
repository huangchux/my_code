#ifndef _SMG_H_
#define _SMG_H_

#include "AllHead.h"
#define SMG_A_DP_PORT P0  //�궨�������P0�˿�

sbit LSA = P2^2; //��P2.2�ܽŶ���ΪLSA
sbit LSB = P2^3; //��P2.3�ܽŶ���ΪLSB
sbit LSC = P2^4; //��P2.4�ܽŶ���ΪLSC

void smg_display(u8 dat[], u8 location);
//void smg_loop(void);
//void smg_SetBuf(u8 location,u8 number);

extern u8 gsmg_code[17]; //�����ⲿ���е��þ͵���extern

#endif

