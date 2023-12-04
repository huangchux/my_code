#include "AllHead.h"

sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

sbit KeyOut1 = P2^3;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;

extern u8 SMG_Flag; //�����ⲿ��������ǰ��Ҫ��extern

void Delay1ms();   //��������
void Delay500ms();
void EXTI0_Init();
void EXTI1_Init();

void main()
{
	EXTI0_Init(); //�ⲿ�жϳ�ʼ��
	EXTI1_Init();
	EA = 1;       //�������ж�
	ADDR3 = 1;    //ʹ��74HC138оƬ
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
		 if(1 == KeyIn1) //�������1̧��
		 {
				LED_SMG_PORT = 0xFF; //ȫ��
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

//�ⲿ�ж�0��ʼ��
void EXTI0_Init()
{
	EX0 = 1;  //���ⲿ�ж�0
	IT0 = 0;  //�͵�ƽ������ʽ
	IE0 = 0;  //�жϱ�־λ��0
}

//�ⲿ�ж�1��ʼ��
void EXTI1_Init()
{
	EX1 = 1;  //���ⲿ�ж�1
	IT1 = 0;  //�͵�ƽ������ʽ
	IE1 = 0;  //�жϱ�־λ��0
}

void EXTI0() interrupt 0
{
	if(0 == KeyIn1) //�������1����
	{
		LED_Flow();   //��ˮ������
		Delay500ms(); //��ʱ500ms
	}
}

void EXTI1() interrupt 2
{
	static u8 i;
	
	if(0 == KeyIn2) //�������2����
	{
		SMG_Flag = 1; //��־λ��1
		for (i = 0; i < 250; i++) 
		{
			SMG_Scan();
			SMG_Dispaly();
			if (1 == KeyIn2) //�������2̧��
			{
				LED_SMG_PORT = 0xFF; //ȫ��
				return;
			}
		}
	}
}

