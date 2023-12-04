#ifndef _IRED_H_
#define _IRED_H_

#include "AllHead.h"

//管脚定义
sbit IRED = P3^2; //管脚定义

//声明变量
void ired_init(void);

//函数声明
extern u8 gired_data[4];

#endif
