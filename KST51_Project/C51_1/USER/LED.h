#ifndef __LED_H
#define __LED_H

#include "AllHead.h"

sbit LED1 = P2^0; //将p2^0管脚定义为LED1
sbit LED2 = P2^1;
#define LED_PORT	P2 //宏定义P2端口

/*=============函数声明区=============*/
void LED_flicker();
void LED_fall();
void LED_ku_fall();


#endif 
