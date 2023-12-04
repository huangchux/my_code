#include <reg52.h>
#include "KEY.h"

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	LED2 = 1; //先让LED熄灭
  LED3 = 1;
  LED4 = 1;
  LED5 = 1;
	
	ENLED = 0; //使能LEDS6
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	EA = 1;         //使能总中断
	TMOD |= 0x01;   //设置 T0 为模式 1
	TH0 = 0xF8;     //定时2ms
	TL0 = 0xCD;
	ET0 = 1;        //使能 T0 中断
	TR0 = 1;        //启动 T0
	
	while(1)
	{
		Key_Driver();  //按键驱动函数
		Key_Handler(); //按键处理函数
	}
}

/* 定时器0中断服务函数 */
void time0() interrupt 1
{
	TH0 = 0xF8; //重载初值
	TL0 = 0xCD;
	Key_Scan(); //调用按键扫描函数
}