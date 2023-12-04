#include <reg52.h>
#include "key.h"

#define LED_SMG_PORT	P0 //����LED������ܶ˿�

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

u8 code KeyCode[] =	{
											0xE7,0xD7,0xB7,0x77,
											0xEB,0xDB,0xBB,0x7B,
											0xED,0xDD,0xBD,0x7D,
											0xEE,0xDE,0xBE,0x7E
										}; //��Ӧĳһ���������µļ�ֵ(������ֵ��)

u8 code SMG_Char[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //����ܶ���0~9
u8 SMG_buff[2] = {0xFF, 0xFF}; //����ܻ�����
u8 num = NO_KEY;

void Time0_Init();
void SMG_Dispaly();

void main()
{
	u8 key_num = NO_KEY; //����δ����
	u8 i;
	ADDR3 = 1;    //G1(E3) ʹ�ܹܽŸߵ�ƽ
	ENLED = 0;    //E1 E2�͵�ƽ��Ч
	Time0_Init(); //��ʱ��0��ʼ��
	
	while(1)
	{
		key_num = Key_Scan();  //���ռ�ֵ
		if(key_num != NO_KEY)  //�����������
		{
			for(i = 0; i < 16; i++) 
			{
				if(key_num == KeyCode[i]) //��ʾĳһ����������
				{
					num = i; //�Ѱ�����ֵ���ж�Ӧ��λ��ȡ��������num
					break;
				}
			}
		}
		SMG_buff[0] = SMG_Char[(num + 1) % 10]; //����ֵ�����������ʾ�������Ӧ(����Ҫnum + 1)
		SMG_buff[1] = SMG_Char[(num + 1) / 10];
	}
}

void Time0_Init()
{
    EA = 1;        //�������ж�
    TMOD &= 0xF0;  //���ö�ʱ��ģʽ
    TMOD |= 0x01;  //��ʱ��ģʽ1
    TH0 = 0XFC;    //��ʱ1����
    TL0 = 0x66;
    ET0 = 1;       //ʹ�ܶ�ʱ��0�ж�
    TR0 = 1;       //������ʱ��0
}

void SMG_Dispaly()
{
	static u8 i = 0; //��̬ɨ�������
	//���´����������ܶ�̬ˢ��
	LED_SMG_PORT = 0xFF; //����
	switch(i)
	{
		case 0: ADDR2 = 0;ADDR1 = 0;ADDR0 = 0;i++; LED_SMG_PORT = SMG_buff[0];break;
		case 1: ADDR2 = 0;ADDR1 = 0;ADDR0 = 1;i=0; LED_SMG_PORT = SMG_buff[1];break;
		default:break;
	}
}

void time0() interrupt 1
{
	TH0 = 0xFC; //���س�ֵ
	TL0 = 0x66;
	if(num != NO_KEY) //�������²���������ϱ�ʾ��ֵ
		SMG_Dispaly();
}
