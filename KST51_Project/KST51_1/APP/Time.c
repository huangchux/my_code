#include "AllHead.h"

void Time_Init()
{
	EA = 1;       //ʹ�����ж�
	TMOD |= 0x01; //���� T0 Ϊģʽ 1
	TH0 = 0xFC;   //Ϊ T0 ����ֵ����ʱ 1ms
	TL0 = 0x66;
	ET0 = 1;      //ʹ�� T0 �ж�
	TR0 = 1;      //���� T0
}