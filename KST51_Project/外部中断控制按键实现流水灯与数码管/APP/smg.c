#include "AllHead.h"

u8 gsmg[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; //�����1-9
u8 SMG_BUFF[2] = {0xFF,0xFF}; //����ܻ���������ֵ0xFF
u8 SMG_Flag = 0;

extern void Delay1ms();

void SMG_Scan()
{
	static u8 i = 0;
	
	LED_SMG_PORT = 0xFF; //��Ӱ
	switch(i)
	{
		case 0: ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[0];Delay1ms(); //���ﲻҪ��break,��Ȼִ��������ͻ������������ʾ����ȥ��
		case 1: ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i=0; LED_SMG_PORT = SMG_BUFF[1];Delay1ms();break;
		default: break;
	}
}

void SMG_Dispaly()
{
	static u8 sec = 0;
	
	if (SMG_Flag) //�����־λ��1
	{
		SMG_Flag = 0; //��־λ��0
		sec++;
		if(sec >= 100)
		{
			sec = 0;
		}		
	}

	SMG_BUFF[0] = gsmg[sec % 10]; //��λ
	SMG_BUFF[1] = gsmg[sec / 10]; //ʮλ
}