#include "AllHead.h"
void LED_Contral(u8 dir)
{
	if(dir == 0)                  //左移
	{
		static u8 Led_state = 0x01; //LED状态
	  Led_Buff[6] = ~Led_state;   //取反赋给数组里的第七个元素(也就是使能LEDS6，才可以点亮LED)
		Led_state <<= 1;            //左移一位
		if(Led_state == 0)          
		{
			Led_state = 0x01;         //左移到最高位后重新设置为第一个LED灯
		}
	}
	if(dir == 1)                  //右移
	{
		static u8 Led_state = 0x80;
	  Led_Buff[6] = ~Led_state;   //取反赋给数组里的第七个元素(也就是使能LEDS6，才可以点亮LED)
		Led_state >>= 1;            //右移一位
		if(Led_state == 0)
		{
			Led_state = 0x80;         //右移到最低位后重新设置为第八个LED灯
		}
	}
}
 