#include <reg52.h>
#include "KEY.h"

u8 Key_State[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //全部矩阵按键的当前状态
u8 KeyDown_State; //按下状态
	
/*============================按键驱动============================*/
//按键驱动函数，检测按键动作，调度相应动作函数
void Key_Driver()
{
	static u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //按键值备份，保存前一次的值
	for(i = 0; i < 4; i++) //循环检测 4*4 的矩阵按键
	{
		for(j = 0; j < 4; j++)
		{
			if(Key_State[i][j] != backup[i][j]) //当前值与前次值不相等说明此时按键有动作
			{
				if(backup[i][j] != 0) //前次值不等于0，则当前值等于0，按键按下
				{
					Key_Test(); //调用按键检测函数
				}
				backup[i][j] = Key_State[i][j]; //更新前一次的备份值
			}
		}
	}
}

/*============================按键检测============================*/
void Key_Test() //按键检测函数
{
	if(0 == KeyIn1)      //如果按键1按下
	{
		KeyDown_State = 1; //按下状态为1
	}
	else if(0 == KeyIn2) //如果按键2按下
	{
		KeyDown_State = 2; //按下状态为2
	}
	else if(0 == KeyIn3) //如果按键3按下
	{
		KeyDown_State = 3; //按下状态为3
	}
	else if(0 == KeyIn4) //如果按键4按下
	{
		KeyDown_State = 4; //按下状态为4
	}
}

/*============================按键处理函数============================*/
void Key_Handler()
{
	if(1 == KeyDown_State)       //如果按键按下状态为1，则表示按键1按下
	{
		KeyDown_State = 0;         //按键状态清0
		LED2 = !LED2;              //LED2状态翻转
	}
	else if(2 == KeyDown_State)  //如果按键按下状态为2，则表示按键2按下
	{
		KeyDown_State = 0;         //按键状态清0
		LED3 = !LED3;              //LED3状态翻转
	}
	else if(3 == KeyDown_State)  //如果按键按下状态为3，则表示按键3按下
	{
		KeyDown_State = 0;         //按键状态清0
		LED4 = !LED4;              //LED4状态翻转
	}
	else if(4 == KeyDown_State)  //如果按键按下状态为4，则表示按键4按下
	{
		KeyDown_State = 0;         //按键状态清0
		LED5 = !LED5;              //LED4状态翻转
	}
}

/* 按键扫描函数，需在定时中断中调用*/
void Key_Scan()
{
	static u8 i = 0;
	static u8 KeyOut = 0; //矩阵按键扫描输出索引
	static u8 keybuf[4][4] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF},
                            {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}
                           }; //矩阵按键扫描缓冲区
	keybuf[KeyOut][0] = (keybuf[KeyOut][0] << 1) | KeyIn1; //缓冲区左移一位，并将当前扫描值移入最低位
	keybuf[KeyOut][1] = (keybuf[KeyOut][1] << 1) | KeyIn2; //1111 1111 << 1 --> 1111 1110 | KeyIn1 --> 1111 1111
	keybuf[KeyOut][2] = (keybuf[KeyOut][2] << 1) | KeyIn3;
  keybuf[KeyOut][3] = (keybuf[KeyOut][3] << 1) | KeyIn4;
	//消抖后更新按键状态
	for(i = 0; i < 4; i++) //每行 4 个按键，所以循环 4 次
  {
		if(0x00 == (keybuf[KeyOut][i] & 0x0F)) //由于只需要判断最后四位，所以要 & 上0x0F
	  {
			//连续 4 次扫描值为 0，即 4*4ms 内都是按下状态时，可认为按键已稳定的按下
		  Key_State[KeyOut][i] = 0;
	  }
		else if(0x0F == (keybuf[KeyOut][i] & 0x0F))
	  {
			//连续 4 次扫描值为 1，即 4*4ms 内都是弹起状态时，可认为按键已稳定的弹起
		  Key_State[KeyOut][i] = 1;
	  }
  }
	KeyOut1 = 0; //由于这里只需要第一行的四个按键，所以只需要KeyOut1 = 0就好
}