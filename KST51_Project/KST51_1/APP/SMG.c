#include "AllHead.h"

u8 code gsmg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                  0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E}; //�������ʾ�ַ�ת����

u8 SMG_BUFF[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; //�������ʾ������

/* ����ܶ�̬ɨ��ˢ�º��������ڶ�ʱ�ж��е��� */
void SMG_Scan()
{
	static u8 i = 0; //��̬ɨ�������
	
	LED_SMG_PORT = 0xFF; //��ʾ����
	
	switch(i)
	{
		case 0: ADDR2 = 0;ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[0]; break;
		case 1: ADDR2 = 0;ADDR1 = 0; ADDR0 = 1; i++; LED_SMG_PORT = SMG_BUFF[1]; break;
		case 2: ADDR2 = 0;ADDR1 = 1; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[2]; break;
		case 3: ADDR2 = 0;ADDR1 = 1; ADDR0 = 1; i++; LED_SMG_PORT = SMG_BUFF[3]; break;
		case 4: ADDR2 = 1;ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[4]; break;
		case 5: ADDR2 = 1;ADDR1 = 0; ADDR0 = 1; i=0; LED_SMG_PORT = SMG_BUFF[5]; break;
		default: break;
	}
}

/* ��һ���޷��ų����͵�������ʾ��������ϣ�num-����ʾ���� */
void SMG_Show(u32 num)
{
	signed char i;
	u8 sign = 0;
	u8 buf[6];
	if(num < 0) //������ȡ���ݴ����λ
	{
		sign = 1;
		num = -num;
	}
	else
	{
		sign = 0;
	}
	for (i = 0; i < 6; i++) //�ѳ�������ת��Ϊ 6 λʮ���Ƶ�����
	{
		buf[i] = num % 10;
		num /= 10;
	}
	
	for (i = 5; i > 0; i--) //�����λ������ 0 ת��Ϊ�ո������� 0 ���˳�ѭ��
	{ 
		if (0 == buf[i])
		{
			buf[i] = 0xFF;
		}
		else
		{
			break;
		}
	}
	if(sign == 1) //����ʱ��������ǰ����Ӹ���
	{
		if(i < 5)   //����Чλ��С��6λʱ��Ӹ��ţ�������ʾ������Ǵ��
		{
			SMG_BUFF[i + 1] = 0xBF; //���ŵ������ֵΪ0xBF
		}
	}
	for (; i >= 0; i--) //ʣ���λ����ʵת��Ϊ�������ʾ�ַ�
	{
		SMG_BUFF[i] = gsmg[buf[i]];
	}
}