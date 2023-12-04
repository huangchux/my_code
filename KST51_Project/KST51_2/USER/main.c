#include "AllHead.h"

sbit ADDR0 = P0^0;
sbit ADDR1 = P0^1;
sbit ADDR2 = P0^2;
sbit ADDR3 = P0^3;
sbit ENLED = P0^4;

void main()
{
	EA = 1;     //ʹ�����ж�
  ES = 1;     //ʹ�ܴ����ж�
	ADDR3 = 1;
	ENLED = 0;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	P0 = 0xFF;
	UAER_Init(9600);
	while(1)
	{
		if(flag)
		{
			if(strcmp(rec_buf,"open") == 0)
			{
				P0 = 0x00;
			}
			if(strcmp(rec_buf,"close") == 0)
			{
				P0 = 0xFF;
			}
			flag = 0;
		}
	}
}




//void Key_Action(u8 keycode);
//void SetDACOut(unsigned char val);

//void main()
//{
//	Time0_Init(1);  //T0 ��ʱ 1ms

//	while(1)
//	{
//		Key_Driver();
//	}
//}

///* �����������������ݼ���ִ����Ӧ�Ĳ�����keycode-�������� */
//void Key_Action(u8 keycode)
//{
// static u8 volt = 0; //�����ѹֵ��������һλʮ����С��λ
// 
// if (0x26 == keycode) //���ϼ������� 0.1V ��ѹֵ
// {
//	if (volt < 25)
//	{
//		volt++;
//		SetDACOut(volt * 255 / 25); //ת��Ϊ AD ���ֵ
//	}
// }
// else if (keycode == 0x28) //���¼�����С 0.1V ��ѹֵ
// {
//		if (volt > 0)
//		{
//			volt--;
//			SetDACOut(volt * 255 / 25); //ת��Ϊ AD ���ֵ
//		}
//	}
//}

///* ���� DAC ���ֵ��val-�趨ֵ */
//void SetDACOut(unsigned char val)
//{
// I2C_Start();
// if (!I2C_Write(0x90)) //Ѱַ PCF8591����δӦ����ֹͣ����������
// {
//	 I2C_Stop();
//	 return;
// }
// I2C_Write(0x40); //д������ֽ�
// I2C_Write(val); //д�� DA ֵ 
// I2C_Stop();
//}

///* T0 �жϷ�������ִ�������ɨ����ʾ */
//void time0() interrupt 1
//{
//	TH0 = T0RH;      //����T0����ֵ
//	TL0 = T0RL;
//	Key_Scan(); //����ɨ��
//}
