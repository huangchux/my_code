#include "AllHead.h"

u8 code KeyCodeMap[4][4] = { //矩阵按键编号到标准键盘键码的映射表
            { 0x31, 0x32, 0x33, 0x26 }, //数字键 1、数字键 2、数字键 3、向上键
            { 0x34, 0x35, 0x36, 0x25 }, //数字键 4、数字键 5、数字键 6、向左键
            { 0x37, 0x38, 0x39, 0x28 }, //数字键 7、数字键 8、数字键 9、向下键
            { 0x30, 0x1B, 0x0D, 0x27 } //数字键 0、ESC 键、 回车键、 向右键
            };
u8 key_sate[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //全部矩阵按键的当前状态

/* 按键驱动函数，检测按键动作，调度相应动作函数，需在主循环中调用 */
void Key_Driver()
{
	u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //按键值备份，保存前一次的值
	for(i = 0;i < 4;i++) //循环检测 4*4 的矩阵按键
  {
		for(j = 0;j < 4;j++)
		{
			if(backup[i][j] != key_sate[i][j]) //检测按键动作
			{
				if(backup[i][j] != 0)           //按键按下时执行动作
				{
					Key_Action(KeyCodeMap[i][j]); //调用按键动作函数
				}
				backup[i][j] = key_sate[i][j]; //刷新前一次的备份
			}
		}
	}
}

/* 按键动作函数，根据键码执行相应的操作，keycode-按键键码 */
void Key_Action(u8 keycode)
{
	static char oprt = 0;    //用于保存加减运算符
	static long result = 0;  //用于保存运算结果
	static long addend = 0;  //用于保存输入的加数
	
	if ((keycode >= 0x30) && (keycode <= 0x39)) //输入 0-9 的数字
	{
		addend = (addend * 10) + (keycode - 0x30);  //整体十进制左移，新数字进入个位
		SMG_Show(addend); //运算结果显示到数码管
	}
	else if (0x26 == keycode) //向上键用作加号，执行加法或连加运算
	{
		oprt = 0;        //设置运算符变量
		result = addend; //运算数存到结果中，准备进行加减
		addend = 0;      //清零运算数，准备接收下一个运算数
		SMG_Show(addend);//刷新数码管显示
	}
	else if(0x28 == keycode) //向下键用作减号
	{
		oprt = 1;              //设置运算符变量
		result = addend;       //运算数存到结果中，准备进行加减
		addend = 0;            //清零运算数，准备接收下一个运算数
		SMG_Show(addend);      //刷新数码管显示
	}
	else if (0x0D == keycode)  //回车键，执行加减运算
	{
		if(0 == oprt)
		{
			result += addend; //进行加法运算
		}
		else
		{
			result -= addend; //进行减法运算
		}
		addend = 0;
		SMG_Show(result);   //运算结果显示到数码管
	}
	else if (0x1B == keycode) //Esc 键，清零结果
	{
		addend = 0;
		result = 0;
		SMG_Show(addend); //运算结果显示到数码管
	}
}

/* 按键扫描函数，需在定时中断中调用，推荐调用间隔 1ms */
void Key_Scan()
{
	u8 i = 0;
	static u8 KeyOut = 0; //矩阵按键扫描输出索引
	static u8 keybuf[4][4] = {{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
	                          {0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}}; //矩阵按键扫描缓冲区
	//将一行的 4 个按键值移入缓冲区
	keybuf[KeyOut][0] = (keybuf[KeyOut][0] << 1) | KeyIn1;
	keybuf[KeyOut][1] = (keybuf[KeyOut][1] << 1) | KeyIn2;
	keybuf[KeyOut][2] = (keybuf[KeyOut][2] << 1) | KeyIn3;
	keybuf[KeyOut][3] = (keybuf[KeyOut][3] << 1) | KeyIn4;
	//消抖后更新按键状态														
	for (i = 0; i < 4; i++) //每行 4 个按键，所以循环 4 次
	{
		if (0x00 == (keybuf[KeyOut][i] & 0x0F))
	  { //连续 4 次扫描值为 0，即 4*4ms 内都是按下状态时，可认为按键已稳定的按下
			key_sate[KeyOut][i] = 0;
	  }
		else if (0x0F == (keybuf[KeyOut][i] & 0x0F))
	  { //连续 4 次扫描值为 1，即 4*4ms 内都是弹起状态时，可认为按键已稳定的弹起
			key_sate[KeyOut][i] = 1;
	  }
	}
	//执行下一次的扫描输出
	KeyOut++; //输出索引递增
	if (KeyOut >= 4)
	{
		KeyOut = 0;
	}
//	KeyOut = KeyOut & 0x03; //索引值加到 4 即归零
	
	switch(KeyOut) //根据索引，释放当前输出引脚，拉低下次的输出引脚
	{
		case 0: KeyOut4 = 1;KeyOut1 = 0;break;
		case 1: KeyOut1 = 1;KeyOut2 = 0;break;
		case 2: KeyOut2 = 1;KeyOut3 = 0;break;
		case 3: KeyOut3 = 1;KeyOut4 = 0;break;
		default:break;
	}
}
