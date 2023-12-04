#include "AllHead.h"

void Time_Init()
{
	EA = 1;       //使能总中断
	TMOD |= 0x01; //设置 T0 为模式 1
	TH0 = 0xFC;   //为 T0 赋初值，定时 1ms
	TL0 = 0x66;
	ET0 = 1;      //使能 T0 中断
	TR0 = 1;      //启动 T0
}