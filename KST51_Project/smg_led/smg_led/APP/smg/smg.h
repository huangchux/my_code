#ifndef _SMG_H
#define _SMG_H

typedef unsigned char u8; //对系统默认数据类型进行重命名
typedef unsigned int u16;
#define LED_SMG_PORT	P0  //宏定义数码管P0端口

sbit ADDR0 = 	P1^0;
sbit ADDR1 = 	P1^1;
sbit ADDR2 = 	P1^2;
sbit ADDR3 = 	P1^3;
sbit ENLED = 	P1^4;

extern u8 gsmg[10];    //前面加extern让函数可以在外部使用
extern u8 Led_Buff[7];
void smg_display();
void smg_show();

#endif