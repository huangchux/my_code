#include "AllHead.h"
u8 flag1 = 0; //标志位
u8 flag2 = 0; //标志位
u8 hour,min,sec; //时分秒
void main()
{
	ENLED = 0;  //E1 E2低电平有效
	ADDR3 = 1;  //G1(E3) 使能管脚高电平
	Time0_Init(); //调用定时器初始化函数
	while(1)
	{
		if(flag1 == 1) //判断1s定时标志
		{
			flag1 = 0;   //清除中断标志
			smg_show();  //时钟计数函数
		}
		if(flag2 == 1)
		{
			flag2 = 0;
			LED_Contral(1); //LED流水灯函数(0代表左移，1代表右移)
		}
	}
}

void time0() interrupt 1 //定时器0中断服务函数
{
	static u16 count1 = 0;  //记录T0中断次数
	static u16 count2 = 0;  //记录T0中断次数
	TH0 = 0XFC; //重载初值
	TL0 = 0x66;
	count1++;    //中断计数+1
	if(count1 == 1000) //中断1000次相当于1秒 (1000ms = 1s)
	{
		count1 = 0;   //溢出中断清0
		flag1 = 1;    //设置中断标志位
	}
	count2++;
	if(count2  == 1000)
	{
		count2 = 0;
		flag2 = 1;
	}		
	smg_display(); //动态数码管显示函数
}
