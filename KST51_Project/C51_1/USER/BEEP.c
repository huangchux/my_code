#include "AllHead.h"

/*void BEEP_Time(u8 ms) 
{
	u8 i = 0;
	for(i = 0;i < ms; i++)
	{
		BEEP = !BEEP; //产生一定频率的脉冲信号
		Delay1ms(1);
	}
}*/

/*void BEEP_Contral()
{
	u16 i = 2000;
	while(1)
	{
		while(i--)  //循环2000次
		{
			BEEP = !BEEP; //产生一定频率的脉冲信号
			Delay1ms(1);
		}
		i = 0;  //清零 赋0蜂鸣器就不会再响了
		BEEP  = 0;  //关闭蜂鸣器 赋0和1都行
	}
}*/