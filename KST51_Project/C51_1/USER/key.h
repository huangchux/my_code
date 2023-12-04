#ifndef _KEY_H_
#define _KEY_H_

#include "AllHead.h"

//定义4个独立按键控制管脚
sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//使用宏定义独立按键按下的键值（如果按下则返回）
#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4

#define KEY_MATRIX_PORT  P1  //使用宏定义矩阵按键控制管脚

//没按下
#define KEY_UNPRESS	0

u8 key_scan(u8 mode);
u8 key_matrix_ranks_scan(void);
u8 key_matrix_flip_scan(void);
u8 Key_GetState();
u8 key(void);
void Key_loop(void);

#endif
