#include "AllHead.h"

void main()
{
	ENLED = 0;  //选择数码管进行显示
	ADDR3 = 1;
	Time_Init(); //定时器初始化
	SMG_BUFF[0] = gsmg[0]; //上电显示 0
	while(1)
	{
		Key_Driver(); //调用按键驱动函数
	}
}

/* T0 中断服务函数，用于数码管显示扫描与按键扫描 */
void time0() interrupt 1
{
	TH0 = 0xFC; //重新加载初值
	TL0 = 0x66;
	SMG_Scan(); //调用数码管显示扫描函数
	Key_Scan(); //调用按键扫描函数
}