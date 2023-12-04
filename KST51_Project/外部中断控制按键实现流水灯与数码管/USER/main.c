#include "AllHead.h"

sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

sbit KeyOut1 = P2^3;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;

extern u8 SMG_Flag; //调用外部变量所以前面要加extern

void Delay1ms();   //声明函数
void Delay500ms();
void EXTI0_Init();
void EXTI1_Init();

void main()
{
	EXTI0_Init(); //外部中断初始化
	EXTI1_Init();
	EA = 1;       //开启总中断
	ADDR3 = 1;    //使能74HC138芯片
	ENLED = 0;
	KeyOut1 = 0;  
	KeyIn1 = 1;
	KeyIn2 = 1;

	while(1);
	
}

void Delay500ms()		//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
		 if(1 == KeyIn1) //如果按键1抬起
		 {
				LED_SMG_PORT = 0xFF; //全灭
		 }		
			while (--k);
		} while (--j);	
	} while (--i);
}

void Delay1ms()		//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

//外部中断0初始化
void EXTI0_Init()
{
	EX0 = 1;  //打开外部中断0
	IT0 = 0;  //低电平触发方式
	IE0 = 0;  //中断标志位清0
}

//外部中断1初始化
void EXTI1_Init()
{
	EX1 = 1;  //打开外部中断1
	IT1 = 0;  //低电平触发方式
	IE1 = 0;  //中断标志位清0
}

void EXTI0() interrupt 0
{
	if(0 == KeyIn1) //如果按键1按下
	{
		LED_Flow();   //流水灯流动
		Delay500ms(); //延时500ms
	}
}

void EXTI1() interrupt 2
{
	static u8 i;
	
	if(0 == KeyIn2) //如果按键2按下
	{
		SMG_Flag = 1; //标志位置1
		for (i = 0; i < 250; i++) 
		{
			SMG_Scan();
			SMG_Dispaly();
			if (1 == KeyIn2) //如果按键2抬起
			{
				LED_SMG_PORT = 0xFF; //全灭
				return;
			}
		}
	}
}

