#ifndef _KEY_H_
#define _KEY_H_

typedef unsigned char u8;

#define KEY1  1
#define KEY2  2
#define KEY3  3
#define KEY4  4
#define NO_KEY4  0xFF

sbit KeyOut1 = P2^3;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;

unsigned char Key_Scan();
#endif
