#ifndef __LED_H
#define __LED_H

#include "AllHead.h"

sbit LED1 = P2^0; //��p2^0�ܽŶ���ΪLED1
sbit LED2 = P2^1;
#define LED_PORT	P2 //�궨��P2�˿�

/*=============����������=============*/
void LED_flicker();
void LED_fall();
void LED_ku_fall();


#endif 
