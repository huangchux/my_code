#include <reg52.h>
#include "key.h"
#include "delay.h"
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;

void main()
{
	u8 Key_Num = NO_KEY4;
	ADDR0 = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	ADDR3 = 1;
	ENLED = 0;
	P0 = 0xFF;
	while(1)
	{
		Key_Num = Key_Scan();
		if(Key_Num != NO_KEY4)
		{
			if(Key_Num == KEY1)
			{
				LED1 = !LED1;
				Delay500ms();
			}
			if(Key_Num == KEY2)
			{
				LED2 = !LED2;
				Delay500ms();
			}
			if(Key_Num == KEY3)
			{
				LED3 = !LED3;
				Delay500ms();
			}
			if(Key_Num == KEY4)
			{
				LED4 = !LED4;
				Delay500ms();
			}
		}
	}
}
