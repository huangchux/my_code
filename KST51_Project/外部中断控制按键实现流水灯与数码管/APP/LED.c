#include "AllHead.h"

void LED_Flow()
{ 
	static u8 LED_state = 0x01;  // led初始状态
	
	ADDR2 = 1;  //A2到A0的值为110，则使Y6为低电平，则LEDS6为低电平，使三极管导通，点亮LED灯
	ADDR1 = 1;
	ADDR0 = 0;	
	
	LED_SMG_PORT = ~LED_state; //取反赋给LED端口，相当于先点亮第一个LED
	LED_state <<= 1;     //左移一位
	if(0 == LED_state)
	{
		LED_state = 0x01;  //左移到最低位后重新设置为第一个LED灯
	}
}