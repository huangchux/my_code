#include "AllHead.h"
u8 gsmg[10]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; //数码管1-9
u8 Led_Buff[7] = {0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF}; //数码管缓存区，初值0xFF,确保启动时都不亮

/*时钟计数函数*/
void smg_display()
{
	static u8 i = 0;       //动态扫描的索引
	//以下代码完成数码管动态刷新
	LED_SMG_PORT = 0xFF; //消隐
	switch(i)
	{
		case 0: ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[0];break;
		case 1: ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i++;LED_SMG_PORT = Led_Buff[1];break;
		case 2: ADDR2 = 0;ADDR1 = 1;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[2];break;
		case 3: ADDR2 = 0;ADDR1 = 1;ADDR0 = 1;i++;LED_SMG_PORT = Led_Buff[3];break;
		case 4: ADDR2 = 1;ADDR1 = 0;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[4];break;
		case 5: ADDR2 = 1;ADDR1 = 0;ADDR0 = 1;i++;LED_SMG_PORT = Led_Buff[5];break;
		case 6: ADDR2 = 1;ADDR1 = 1;ADDR0 = 0;i=0;LED_SMG_PORT = Led_Buff[6];break; //点亮LED需要使能LEDS6
		default:break;
	}
}

/*动态数码管显示函数*/
void smg_show()
{
	static u8 hour,min,sec; //时分秒
	Led_Buff[0] = gsmg[sec % 10]; //秒个位
	Led_Buff[1] = gsmg[sec / 10]; //秒十位
	Led_Buff[2] = gsmg[min % 10]; //分个位
	Led_Buff[3] = gsmg[min / 10]; //分十位
	Led_Buff[4] = gsmg[hour % 10];//小时个位
	Led_Buff[5] = gsmg[hour / 10];//时十位
	sec++;
	if(sec >= 60)
	{
		sec = 0;
		min++;
		if(min >= 60)
		{
			min = 0;
			hour++;
			if(hour >= 24)
			{
				hour = 0;
			}
		}
	}
}