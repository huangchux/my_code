#ifndef _KEY_H_
#define _KEY_H_

typedef unsigned char u8; //对系统默认数据类型进行重命名

sbit KeyIn1 = P2^4; //定义按键管脚
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;
sbit KeyOut1 = P2^3;

sbit LED2 = P0^0; //定义LED管脚
sbit LED3 = P0^1;
sbit LED4 = P0^2;
sbit LED5 = P0^3;

void Key_Driver();
void Key_Scan();
void Key_Test();
void Key_Handler();

#endif
