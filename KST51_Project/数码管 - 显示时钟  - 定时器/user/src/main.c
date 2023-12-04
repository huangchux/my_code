#include <reg52.h>
#include "delay.h"
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit P32 = P3^2;
unsigned char T0RH = 0;
unsigned char T0RL = 0;

unsigned char LEDSChar[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned char hour = 16;
unsigned char min = 45;
unsigned char sec = 30;
void show();

void INT0_Init()
{
	EA = 1;
	EX0 = 1;
	IE0 = 0;
	IT0 = 0;
}

void Timer0Init(unsigned int ms)
{
	unsigned long temp;
	temp = 11059200 / 12;      //��ʱ��������Ƶ��
	temp = (temp * ms) / 1000; // ���������ֵ
	temp += 12;                //�����ж���Ӧ��ʱ��ɵ����
	temp = 65536 - temp;       //���㶨ʱ������ֵ
	T0RH = (unsigned char)(temp >> 8); //��ʼֵ�ĸ߰�λ
	T0RH = (unsigned char)temp;        //��ʼֵ�ĵڰ�λ
	EA = 1;
	TMOD &= 0xF0;              //��T0�Ĺ���ģʽ������0
	TMOD |= 0X01;
	TH0 = T0RH;
	TL0 = T0RL;
	TR0 = 1;
	ET0 = 1;
}
void main()
{
	PX0 = 1;
	PT0 = 0;
	P32 = 1;
	Timer0Init(1);
	INT0_Init();
	P2 = 0xF7;
	while(1)
	{
		show();
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
		case 0:ADDR2=0;ADDR1=0;ADDR0=0;P0=LEDSChar[sec%10];i++;break;
		case 1:ADDR2=0;ADDR1=0;ADDR0=1;P0=LEDSChar[sec/10];i++;break;
		case 2:ADDR2=0;ADDR1=1;ADDR0=0;P0=LEDSChar[min%10];i++;break;
		case 3:ADDR2=0;ADDR1=1;ADDR0=1;P0=LEDSChar[min/10];i++;break;
		case 4:ADDR2=1;ADDR1=0;ADDR0=0;P0=LEDSChar[hour%10];i++;break;
		case 5:ADDR2=1;ADDR1=0;ADDR0=1;P0=LEDSChar[hour/10];i=0;break;
		default:break;
	}
}

void time0() interrupt 1
{
	static unsigned int count = 0;
	TF0 = 0;
	TH0 = T0RH;
	TL0 = T0RL;
	count++;
	if((count>1000) && (0 == IE0)) //�������ⲿ�ж�
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
