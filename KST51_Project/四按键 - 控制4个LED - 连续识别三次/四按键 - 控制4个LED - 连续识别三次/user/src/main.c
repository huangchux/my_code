#include <reg52.h>
#include "key.h"

#define LED_SMG_PORT	P0 //定义LED和数码管端口

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

u8 code KeyCode[] =	{
											0xE7,0xD7,0xB7,0x77,
											0xEB,0xDB,0xBB,0x7B,
											0xED,0xDD,0xBD,0x7D,
											0xEE,0xDE,0xBE,0x7E
										}; //对应某一个按键按下的键值(按键键值表)

u8 code SMG_Char[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //数码管段码0~9
u8 SMG_buff[2] = {0xFF, 0xFF}; //数码管缓冲区
u8 num = NO_KEY;

void Time0_Init();
void SMG_Dispaly();

void main()
{
	u8 key_num = NO_KEY; //按键未按下
	u8 i;
	ADDR3 = 1;    //G1(E3) 使能管脚高电平
	ENLED = 0;    //E1 E2低电平有效
	Time0_Init(); //定时器0初始化
	
	while(1)
	{
		key_num = Key_Scan();  //接收键值
		if(key_num != NO_KEY)  //如果按键按下
		{
			for(i = 0; i < 16; i++) 
			{
				if(key_num == KeyCode[i]) //表示某一个按键按下
				{
					num = i; //把按键键值表中对应的位置取出来赋给num
					break;
				}
			}
		}
		SMG_buff[0] = SMG_Char[(num + 1) % 10]; //按键值与数码管上显示的数相对应(所以要num + 1)
		SMG_buff[1] = SMG_Char[(num + 1) / 10];
	}
}

void Time0_Init()
{
    EA = 1;        //开启总中断
    TMOD &= 0xF0;  //设置定时器模式
    TMOD |= 0x01;  //定时器模式1
    TH0 = 0XFC;    //定时1毫秒
    TL0 = 0x66;
    ET0 = 1;       //使能定时器0中断
    TR0 = 1;       //启动定时器0
}

void SMG_Dispaly()
{
	static u8 i = 0; //动态扫描的索引
	//以下代码完成数码管动态刷新
	LED_SMG_PORT = 0xFF; //消隐
	switch(i)
	{
		case 0: ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++; LED_SMG_PORT = SMG_buff[0];break;
		case 1: ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i=0; LED_SMG_PORT = SMG_buff[1];break;
		default:break;
	}
}

void time0() interrupt 1
{
	TH0 = 0xFC; //重载初值
	TL0 = 0x66;
	if(num != NO_KEY) //按键按下才在数码管上表示数值
		SMG_Dispaly();
}
