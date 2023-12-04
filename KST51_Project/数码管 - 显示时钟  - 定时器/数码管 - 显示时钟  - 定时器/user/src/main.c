#include <reg52.h>
#include "delay.h"
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
unsigned char LEDSChar[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned char hour = 16;
unsigned char min = 45;
unsigned char sec = 30;
void show();

void Timer0Init()
{
	TMOD &= 0XF0;
	TMOD |= 0X01;
	TF0 = 0;
	TH0 = 0XFC;
	TL0 = 0X66;
	TR0 = 1;
}
void main()
{
	unsigned int count=0;
	Timer0Init();
	P0 = 0XFF;
	while(1)
	{
		show();
		if(TF0==1)
		{
			TF0 = 0;
			TH0 = 0XFC;
			TL0 = 0X66;
			count++;
			if(count>1000)
			{
				count = 0;
				sec++;
				if(sec>59)
				{
					sec = 0;
					min ++;
					if(min>59)
					{
						min=0;
						hour++;
						if(hour>23)
						{
							hour = 0;
							min = 0;
							sec = 0;
						}
					}
				}
			}
		}
			
	}
}


void show()
{
	static unsigned char i=0;
	ADDR3 = 1;
	ENLED = 0;
	P0=0XFF;
	switch(i)
	{
		case 0:ADDR2=0;ADDR1=0;ADDR0=0;P0=LEDSChar[sec%10];Delay1ms();i++;break;
		case 1:ADDR2=0;ADDR1=0;ADDR0=1;P0=LEDSChar[sec/10];Delay1ms();i++;break;
		case 2:ADDR2=0;ADDR1=1;ADDR0=0;P0=LEDSChar[min%10];Delay1ms();i++;break;
		case 3:ADDR2=0;ADDR1=1;ADDR0=1;P0=LEDSChar[min/10];Delay1ms();i++;break;
		case 4:ADDR2=1;ADDR1=0;ADDR0=0;P0=LEDSChar[hour%10];Delay1ms();i++;break;
		case 5:ADDR2=1;ADDR1=0;ADDR0=1;P0=LEDSChar[hour/10];Delay1ms();i=0;break;
		default:break;
	}
}
