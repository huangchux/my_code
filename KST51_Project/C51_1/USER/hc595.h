#ifndef _HC595_H_
#define _HC595_H_

#include "AllHead.h"

//定义74HC595控制管脚
sbit SER = P3^4;            //串行数据输入
sbit rCLK = P3^5;           //存储寄存器时钟输入
sbit SRCLK = P3^6;          //移位寄存器时钟输入
 
#define LEDDZ_COL_PORT  P0  //点阵列控制端口

void hc595_write_data(u8 dat);
void MatrixLED_ShowCol(u8 col,u8 dat);

#endif
