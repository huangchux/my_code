#include "AllHead.h"
void LED_Contral(u8 dir)
{
	if(dir == 0)                  //����
	{
		static u8 Led_state = 0x01; //LED״̬
	  Led_Buff[6] = ~Led_state;   //ȡ������������ĵ��߸�Ԫ��(Ҳ����ʹ��LEDS6���ſ��Ե���LED)
		Led_state <<= 1;            //����һλ
		if(Led_state == 0)          
		{
			Led_state = 0x01;         //���Ƶ����λ����������Ϊ��һ��LED��
		}
	}
	if(dir == 1)                  //����
	{
		static u8 Led_state = 0x80;
	  Led_Buff[6] = ~Led_state;   //ȡ������������ĵ��߸�Ԫ��(Ҳ����ʹ��LEDS6���ſ��Ե���LED)
		Led_state >>= 1;            //����һλ
		if(Led_state == 0)
		{
			Led_state = 0x80;         //���Ƶ����λ����������Ϊ�ڰ˸�LED��
		}
	}
}
 