#include "AllHead.h"

/******************************************************************************
* 函 数 名 : key_scan
* 函数功能 : 检测独立按键是否按下，按下则返回对应键值
* 输 入    : mode=0：单次扫描按键
             mode=1：连续扫描按键
* 输 出 :    KEY1_PRESS：K1 按下
             KEY2_PRESS：K2 按下
             KEY3_PRESS：K3 按下
             KEY4_PRESS：K4 按下
             KEY_UNPRESS：未有按键按下
********************************************************************************/
/*u8 key_scan(u8 mode)
{
	static u8 key = 1; //定义一个静态变量
	if(mode) key = 1; //如果mode=1则表示连续扫描按键 如果mode=0则忽略这句话
	if(key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0 )) //任意按键按下
	{
		Delay1ms(10);  //消抖
		key = 0;
		if(KEY1 == 0)         //如果按键仍然处于被按下状态则表明按键真的被按下了
			return KEY1_PRESS;  
		else if(KEY2 == 0)
			return KEY2_PRESS;
		else if(KEY3 == 0)
			return KEY3_PRESS;
		else if(KEY4 == 0)
			return KEY4_PRESS;
	}
	else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1 )  //无按键按下
	{
		key = 1;
	}
	return KEY_UNPRESS;
}*/


/***************************************************************************************
* 函 数 名 : key_matrix_ranks_scan
* 函数功能 : 使用行列式扫描方法，检测矩阵按键是否按下，按下则返回对应键值
* 输 入 : 无
* 输 出 : key_value：1-16，对应 S1-S16 键，
0：按键未按下
****************************************************************************************/
/*u8 key_matrix_ranks_scan(void) //行列式扫描函数
{
	u8 key_value = 0;
	KEY_MATRIX_PORT = 0xf7;  //给第一列赋值0，其余全为1  1111 0111 --> 0xf7
	if(KEY_MATRIX_PORT != 0xf7)  //判断第一列按键是否按下(若按下则矩阵按键控制管脚不等于0xf7)
	{
		Delay1ms(10);  //消抖
		switch(KEY_MATRIX_PORT) //保存第一列按键按下后的键值
		{
			case 0x77: key_value = 1;  break; //S1
			case 0xb7: key_value = 5;  break; //S5
			case 0xd7: key_value = 9;  break; //S9
			case 0xe7: key_value = 13; break; //S13
		}
	}
	while(KEY_MATRIX_PORT != 0xf7); //等待按键松开(松开矩阵按键控制管脚等于0xf7则退出循环)
	
	KEY_MATRIX_PORT = 0xfb;  //给第二列赋值0，其余全为1  1111 1011 --> 0xfb
	if(KEY_MATRIX_PORT != 0xfb)  //判断第二列按键是否按下(若按下则矩阵按键控制管脚不等于0xfb)
	{
		Delay1ms(10);  //消抖
		switch(KEY_MATRIX_PORT) //保存第二列按键按下后的键值
		{
			case 0x7b: key_value = 2;  break;  //S2
			case 0xbb: key_value = 6;  break;  //S6
			case 0xdb: key_value = 10;  break; //S10
			case 0xeb: key_value = 14; break;  //S14
		}
	}
	while(KEY_MATRIX_PORT != 0xfb); //等待按键松开(松开矩阵按键控制管脚等于0xfb则退出循环)
	
	KEY_MATRIX_PORT = 0xfd;  //给第三列赋值0，其余全为1  1111 1101 --> 0xfd
	if(KEY_MATRIX_PORT != 0xfd)  //判断第三列按键是否按下(若按下则矩阵按键控制管脚不等于0xfd)
	{
		Delay1ms(10);  //消抖
		switch(KEY_MATRIX_PORT) //保存第三列按键按下后的键值
		{
			case 0x7d: key_value = 3;  break; //S3
			case 0xbd: key_value = 7;  break; //S7
			case 0xdd: key_value = 11;  break; //S11
			case 0xed: key_value = 15; break; //S15
		}
	} 
	while(KEY_MATRIX_PORT != 0xfd); //等待按键松开(松开矩阵按键控制管脚等于0xfd则退出循环)
	
	KEY_MATRIX_PORT = 0xfe;  //给第四列赋值0，其余全为1  1111 1110 --> 0xfe
	if(KEY_MATRIX_PORT != 0xfe) //判断第四列按键是否按下(若按下则矩阵按键控制管脚不等于0xfe)
	{
		Delay1ms(10);  //消抖
		switch(KEY_MATRIX_PORT) //保存第四列按键按下后的键值
		{
			case 0x7e: key_value = 4;  break; //S4
			case 0xbe: key_value = 8;  break; //S8
			case 0xde: key_value = 12;  break; //S12
			case 0xee: key_value = 16; break; //S16
		}
	}
	while(KEY_MATRIX_PORT != 0xfe); //等待按键松开(松开矩阵按键控制管脚等于0xfe则退出循环)
	
	return key_value; 
}*/


/*******************************************************************************

* 函 数 名 : key_matrix_flip_scan
* 函数功能 : 使用线翻转扫描方法，检测矩阵按键是否按下，按下则返回对应键值
* 输 入 : 无
* 输 出 : key_value：1-16，对应 S1-S16 键，
0：按键未按下
********************************************************************************/
/*u8 key_matrix_flip_scan(void)
{
  static u8 key_value = 0; //键值
	KEY_MATRIX_PORT = 0x0f;  //行为低电平，测试列 给所有行赋值0，列全为1  0000 1111 --> 0x0f
	if(KEY_MATRIX_PORT != 0x0f)  //判断按键是否按下(若按下则矩阵按键控制管脚不等于0x0f)
	{
		Delay1ms(10);  //消抖
		if(KEY_MATRIX_PORT != 0x0f)
		{ 
			//测试列
			KEY_MATRIX_PORT = 0x0f;  //行为低电平，测试列 给所有行赋值0，列全为1  0000 1111 --> 0x0f
			switch(KEY_MATRIX_PORT)  //保存行为0，按键按下后的列值
			{
				case 0x07: key_value = 1; break; //第一列 0000 0111 --> 0x07
				case 0x0b: key_value = 2; break; //第二列 0000 1011 --> 0x0b
				case 0x0d: key_value = 3; break; //第三列 0000 1101 --> 0x0d
				case 0x0e: key_value = 4; break; //第四列 0000 1110 --> 0x0e
			}
			//测试行
			KEY_MATRIX_PORT = 0xf0;  //列为低电平，测试行 给所有行赋值1，列全为0  1111 0000 --> 0xf0
			switch(KEY_MATRIX_PORT)  //保存列为0，按键按下后的键值
			{
				case 0x70: key_value = key_value;      break;  //第一行 0111 0000 --> 0x70
				case 0xb0: key_value = key_value + 4;  break;  //第二行 1011 0000 --> 0xb0
				case 0xd0: key_value = key_value + 8;  break;  //第三行 1101 0000 --> 0xd0
				case 0xe0: key_value = key_value + 12; break;  //第四行 1110 0000 --> 0xe0
			}
			while(KEY_MATRIX_PORT != 0xf0);  //等待按键松开(松开矩阵按键控制管脚等于0xf0则退出循环)
		}
	}
	else 
		key_value = 0;
	return key_value;
}*/


//u8 key_ketNumber = 0;
/**
  * @brief  获取按键键码
  * @param  无
  * @retval 按下按键的键码，范围：0,1~4,0表示无按键按下
  */
/*u8 key(void)
{
	u8 temp;
	temp = key_ketNumber;
	key_ketNumber = 0;
	return temp;
}*/


/**
  * @brief  获取当前按键的状态，无消抖及松手检测
  * @param  无
  * @retval 按下按键的键码，范围：0,1~4,0表示无按键按下
  */
/*u8 Key_GetState()
{
	u8 KeyNumber = 0;
	if(KEY1 == 0)             //如果按键1按下
		KeyNumber = KEY1_PRESS; // 按键值1
	if(KEY2 == 0)             //如果按键2按下
		KeyNumber = KEY2_PRESS; // 按键值2
	if(KEY3 == 0)             //如果按键3按下
		KeyNumber = KEY3_PRESS; // 按键值3
	if(KEY4 == 0)             //如果按键4按下
		KeyNumber = KEY4_PRESS; // 按键值4
	return KeyNumber;         //返回按键值
}*/
	
/**
  * @brief  按键驱动函数，在中断中调用
  * @param  无
  * @retval 无
  */
/*void Key_loop(void)
{
	static u8 NowState,LastState;
	LastState = NowState;      //按键状态更新
	NowState = Key_GetState(); //获取当前按键状态
	//如果上个时间点按键按下，这个时间点未按下，则是松手瞬间，以此避免消抖和松手检测
	if(LastState == KEY1_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY1_PRESS;
	if(LastState == KEY2_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY2_PRESS;
	if(LastState == KEY3_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY3_PRESS;
	if(LastState == KEY4_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY4_PRESS;
}*/
	