#ifndef __KEY_H
#define __KEY_H

sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;
sbit KeyOut1 = P2^3;
sbit KeyOut2 = P2^2;
sbit KeyOut3 = P2^1;
sbit KeyOut4 = P2^0;


void Key_Driver();
void Key_Action(u8 keycode);
void Key_Scan();

extern u8 code KeyCodeMap[4][4];
extern u8 key_sate[4][4];


#endif