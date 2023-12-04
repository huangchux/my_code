#include <reg52.h>
#include "key.h"

u8 Key_Scan()
{
	static u8 key1 = NO_KEY,key2,key3; //定义三个按键值，key1一开始先初始化为 按键未按下
	static u8 time=0; //计算三个按键传递的次数
	u8 key_sta = 1;   //允许识别按键
	u8 Key_value;     //按键键值
	u8 temp;          //中间变量
	
	key3 = key2;      //把第二个按键值传给第三个按键值
	key2 = key1;      //把第一个按键值传给第二个按键值
	time++;           //三个按键传递的次数累加
	KEY_PORT = 0xF0;  //矩阵按键列全为1，行全为0
//	if((key_sta == 1) && ((KEY_PORT & 0xF0) != 0xF0)) //如果允许识别按键且按键与原来键值不一样则表示有按键按下
//	{
//		KEY_PORT = 0xF7; // 第一行某个按键按下
//		if((KEY_PORT & 0xF7) != 0xF7)      //按键发生变化表示第一行有按键按下
//		{
//			temp = 0x07 | (KEY_PORT & 0xF0); //把按键值赋给中间变量(例如第一个按键按下, 0x07 | (0xE7 & 0xF0) --> 0x07 | 0xE0 --> 0xE7)
//			key1 = temp;                     //再把中间变量的按键值赋给第一个按键值
//		}                                  //按键值会传递到三个按键值都一样表示按键按下(这个过程可以把抖动给过滤掉)
//		KEY_PORT = 0xFB; // 第二行某个按键按下按下
//		if((KEY_PORT & 0xFB) != 0xFB)
//		{
//			temp = 0x0B | (KEY_PORT & 0xF0);
//			key1 = temp;
//		}
//		KEY_PORT = 0xFD; // 第三行某个按键按下按下
//		if((KEY_PORT & 0xFD) != 0xFD)
//		{
//			temp = 0x0D | (KEY_PORT & 0xF0);
//			key1 = temp;
//		}
//		KEY_PORT = 0xFE; // 第四行某个按键按下按下
//		if((KEY_PORT & 0xFE) != 0xFE)
//		{
//			temp = 0x0E | (KEY_PORT & 0xF0);
//			key1 = temp;
//		}
		
		if((key_sta == 1) && ((KEY_PORT & 0xF0) != 0xF0)) //如果允许识别按键且按键与原来键值不一样则表示有按键按下
		{
			KEY_PORT = 0xF0; //获取列的编号
			if((KEY_PORT & 0xF0) != 0xF0) //如果按键值发生变化则表示按键按下
			{
				temp = KEY_PORT & 0xF0;     //取出列对应的按键值
			}
			KEY_PORT = 0x0F; //获取行的编号
			if((KEY_PORT & 0x0F) != 0x0F) //如果按键值发生变化则表示按键按下
			{
				key1 = temp | (KEY_PORT & 0x0F); //将列的键值与行的键值拼接在一起获取按下按键的键值
			}
			
			if(time == 3) //三个按键传递的次数等于3表示三个按键值传递到都一样了
		  {
			  time = 0;   //次数清0
			  if((key1 == key2) && (key1 == key3) && (key1 != NO_KEY)) //如果按键值1 2 3都相等且按下的话
			  {
				  Key_value = key1; 
			    key_sta = 0; //不允许识别按键(按键按下所以不允许识别按键)
			  }
		  }
		}
		
	else if((KEY_PORT & 0xF0) == 0xF0) //如果按键列全为高电平表示没有按键按下
	{
		key_sta = 1; //允许识别按键
		time = 0;
	}
	return Key_value;
}