//#include "AllHead.h"

///* �ȴ�Һ��׼���� */
//void Lcd_WaitReady() //��״̬��RS = L��R/W = H��E = H
//{
//	u8 sta = 0;
//	LCD1602_DB = 0xFF; 
//	LCD1602_RS = 0;
//	LCD1602_RW = 1;
//	do                   //do while�������ִ��һ����䣬�ٶ�ѭ�����������ж�
//	{
//		LCD1602_E = 1;     //ʹ��
//		sta = LCD1602_DB;  //��ȡ״̬��
//		LCD1602_E = 0;     //���곷��ʹ�ܣ���ֹҺ��������ݸ��� P0 ����
//	}while(sta & 0x80);  //���λ���� 1 ��ʾҺ����æ���ظ����ֱ������� 0 Ϊֹ
//}

///* �� LCD1602 Һ��д��һ�ֽ����cmd-��д������ֵ */
//void Lcd_WriteCmd(u8 cmd) //дָ�RS = L��R/W = L��D0~D7 = ָ���룬E = ������
//{
//	Lcd_WaitReady();
//	LCD1602_RS = 0;
//	LCD1602_RW = 0;
//	LCD1602_DB = cmd;
//	LCD1602_E = 1;
//	LCD1602_E = 0;
//}

///* �� LCD1602 Һ��д��һ�ֽ����ݣ�dat-��д������ֵ */
//void Lcd_WriteDat(u8 dat) //д���ݣ�RS = H��R/W = L��D0~D7 = ���ݣ�E = ������
//{
//	Lcd_WaitReady();
//	LCD1602_RS = 1;
//	LCD1602_RW = 0;
//	LCD1602_DB = dat;
//	LCD1602_E = 1;
//	LCD1602_E = 0;
//}

///* ������ʾ RAM ��ʼ��ַ���༴���λ�ã�(x,y)-��Ӧ��Ļ�ϵ��ַ����� */
//void Lcd_SetCursor(u8 x, u8 y)
//{
//	u8 addr;
//	if(0 == y)          //���������Ļ���������ʾRAM�ĵ�ַ
//	{
//		addr = 0x00 + x;  //��һ���ַ���ַ��0x00��ʼ
//	}
//	else
//	{
//		addr = 0x40 + x;  //�ڶ����ַ���ַ��0x40��ʼ
//	}
//	Lcd_WriteCmd(addr | 0x80); //����RAM��ַ
//}

///* ��Һ������ʾ�ַ�����(x,y)-��Ӧ��Ļ�ϵ���ʼ���꣬str-�ַ���ָ�� */
//void Lcd_ShowStr(u8 x, u8 y, u8 *str)
//{
//	Lcd_SetCursor(x,y);  //������ʼ��ַ
//	while(*str != '\0')         
//	{
//		Lcd_WriteDat(*str++); //��ȡstrָ�������Ȼ�����д���ݺ�����Ȼ��str�Լ�1,���ȼ�һ����������
//	}
//}

///* ��������������(x,y)������ʼ�� len ���ַ�λ */
////void Lcd_AreaClear(u8 x, u8 y, u8 len)
////{
////	Lcd_SetCursor(x,y);  //������ʼ��ַ
////	while(len--)         //����д��ո�
////	{
////		Lcd_WriteDat(' ');
////	}
////}

///* ��ʼ�� 1602 Һ�� */
//void Lcd1602_Init()
//{
//	Lcd_WriteCmd(0x38); //16*2��ʾ��5*7����8λ���ݽӿ�
//	Lcd_WriteCmd(0x0C); //��ʾ���������رգ���˸�ر�	0000 1100
//	Lcd_WriteCmd(0x06); //���ֲ�������ַ�Զ�+1 0000 0110
//	Lcd_WriteCmd(0x01); //����
//}

