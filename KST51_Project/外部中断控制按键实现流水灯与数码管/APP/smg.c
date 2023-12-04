#include "AllHead.h"

u8 gsmg[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; //数码管1-9
u8 SMG_BUFF[2] = {0xFF,0xFF}; //数码管缓存区，初值0xFF
u8 SMG_Flag = 0;

extern void Delay1ms();

void SMG_Scan()
{
	static u8 i = 0;
	
	LED_SMG_PORT = 0xFF; //消影
	switch(i)
	{
		case 0: ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[0];Delay1ms(); //这里不要用break,不然执行这个语句就会跳到数码管显示函数去了
		case 1: ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i=0; LED_SMG_PORT = SMG_BUFF[1];Delay1ms();break;
		default: break;
	}
}

void SMG_Dispaly()
{
	static u8 sec = 0;
	
	if (SMG_Flag) //如果标志位置1
	{
		SMG_Flag = 0; //标志位清0
		sec++;
		if(sec >= 100)
		{
			sec = 0;
		}		
	}

	SMG_BUFF[0] = gsmg[sec % 10]; //个位
	SMG_BUFF[1] = gsmg[sec / 10]; //十位
}