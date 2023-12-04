#include <reg52.h>
#include "KEY.h"

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	LED2 = 1; //����LEDϨ��
  LED3 = 1;
  LED4 = 1;
  LED5 = 1;
	
	ENLED = 0; //ʹ��LEDS6
	ADDR3 = 1;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	EA = 1;         //ʹ�����ж�
	TMOD |= 0x01;   //���� T0 Ϊģʽ 1
	TH0 = 0xF8;     //��ʱ2ms
	TL0 = 0xCD;
	ET0 = 1;        //ʹ�� T0 �ж�
	TR0 = 1;        //���� T0
	
	while(1)
	{
		Key_Driver();  //������������
		Key_Handler(); //����������
	}
}

/* ��ʱ��0�жϷ����� */
void time0() interrupt 1
{
	TH0 = 0xF8; //���س�ֵ
	TL0 = 0xCD;
	Key_Scan(); //���ð���ɨ�躯��
}