#include "AllHead.h"

void LED_Flow()
{ 
	static u8 LED_state = 0x01;  // led��ʼ״̬
	
	ADDR2 = 1;  //A2��A0��ֵΪ110����ʹY6Ϊ�͵�ƽ����LEDS6Ϊ�͵�ƽ��ʹ�����ܵ�ͨ������LED��
	ADDR1 = 1;
	ADDR0 = 0;	
	
	LED_SMG_PORT = ~LED_state; //ȡ������LED�˿ڣ��൱���ȵ�����һ��LED
	LED_state <<= 1;     //����һλ
	if(0 == LED_state)
	{
		LED_state = 0x01;  //���Ƶ����λ����������Ϊ��һ��LED��
	}
}