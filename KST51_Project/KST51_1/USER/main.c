#include "AllHead.h"

void main()
{
	ENLED = 0;  //ѡ������ܽ�����ʾ
	ADDR3 = 1;
	Time_Init(); //��ʱ����ʼ��
	SMG_BUFF[0] = gsmg[0]; //�ϵ���ʾ 0
	while(1)
	{
		Key_Driver(); //���ð�����������
	}
}

/* T0 �жϷ������������������ʾɨ���밴��ɨ�� */
void time0() interrupt 1
{
	TH0 = 0xFC; //���¼��س�ֵ
	TL0 = 0x66;
	SMG_Scan(); //�����������ʾɨ�躯��
	Key_Scan(); //���ð���ɨ�躯��
}