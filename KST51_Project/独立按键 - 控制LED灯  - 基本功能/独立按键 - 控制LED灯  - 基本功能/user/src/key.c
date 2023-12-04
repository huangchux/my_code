#include <reg52.h>
#include "key.h"
#include "delay.h"



u8 Key_sta = 0; //允许识别按键
u8 Key_Scan()
{
	static u8 key1 = NO_KEY4, key2, key3;
	static u8 timer = 0;
	u8 key;
	KeyOut1 =0;
	KeyIn1 = 1;
	KeyIn2 = 1;
	KeyIn3 = 1;
	KeyIn4 = 1;
	key3 = key2;
	key2 = key1;
	timer++;
	if((1 == Key_sta) && (0 == KeyIn1) || (0 == KeyIn2) || (0 == KeyIn3)|| (0 == KeyIn4))
	{
		if(KeyIn1 == 0)
		{
			key1 = KEY1;
		}
		else if(KeyIn2 == 0)
		{
			key1 = KEY2;
		}
		else if(KeyIn3 == 0)
		{
			key1 = KEY3;
		}
		else if(KeyIn4 == 0)
		{
			key1 = KEY4;
		}
		if(3 == timer)
		{
			timer = 0;
			Key_sta = 0;
			key = key1;
		}
	}
	else if((KeyIn1 == 1) && (KeyIn2 == 1) && (KeyIn3 == 1) && (KeyIn4 == 1))
	{
		Key_sta = 1;
		timer = 0;
	}
	return key;
}