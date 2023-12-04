#include "AllHead.h"

/******************************************************************************
* �� �� �� : key_scan
* �������� : �����������Ƿ��£������򷵻ض�Ӧ��ֵ
* �� ��    : mode=0������ɨ�谴��
             mode=1������ɨ�谴��
* �� �� :    KEY1_PRESS��K1 ����
             KEY2_PRESS��K2 ����
             KEY3_PRESS��K3 ����
             KEY4_PRESS��K4 ����
             KEY_UNPRESS��δ�а�������
********************************************************************************/
/*u8 key_scan(u8 mode)
{
	static u8 key = 1; //����һ����̬����
	if(mode) key = 1; //���mode=1���ʾ����ɨ�谴�� ���mode=0�������仰
	if(key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0 )) //���ⰴ������
	{
		Delay1ms(10);  //����
		key = 0;
		if(KEY1 == 0)         //���������Ȼ���ڱ�����״̬�����������ı�������
			return KEY1_PRESS;  
		else if(KEY2 == 0)
			return KEY2_PRESS;
		else if(KEY3 == 0)
			return KEY3_PRESS;
		else if(KEY4 == 0)
			return KEY4_PRESS;
	}
	else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1 )  //�ް�������
	{
		key = 1;
	}
	return KEY_UNPRESS;
}*/


/***************************************************************************************
* �� �� �� : key_matrix_ranks_scan
* �������� : ʹ������ʽɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* �� �� : ��
* �� �� : key_value��1-16����Ӧ S1-S16 ����
0������δ����
****************************************************************************************/
/*u8 key_matrix_ranks_scan(void) //����ʽɨ�躯��
{
	u8 key_value = 0;
	KEY_MATRIX_PORT = 0xf7;  //����һ�и�ֵ0������ȫΪ1  1111 0111 --> 0xf7
	if(KEY_MATRIX_PORT != 0xf7)  //�жϵ�һ�а����Ƿ���(����������󰴼����ƹܽŲ�����0xf7)
	{
		Delay1ms(10);  //����
		switch(KEY_MATRIX_PORT) //�����һ�а������º�ļ�ֵ
		{
			case 0x77: key_value = 1;  break; //S1
			case 0xb7: key_value = 5;  break; //S5
			case 0xd7: key_value = 9;  break; //S9
			case 0xe7: key_value = 13; break; //S13
		}
	}
	while(KEY_MATRIX_PORT != 0xf7); //�ȴ������ɿ�(�ɿ����󰴼����ƹܽŵ���0xf7���˳�ѭ��)
	
	KEY_MATRIX_PORT = 0xfb;  //���ڶ��и�ֵ0������ȫΪ1  1111 1011 --> 0xfb
	if(KEY_MATRIX_PORT != 0xfb)  //�жϵڶ��а����Ƿ���(����������󰴼����ƹܽŲ�����0xfb)
	{
		Delay1ms(10);  //����
		switch(KEY_MATRIX_PORT) //����ڶ��а������º�ļ�ֵ
		{
			case 0x7b: key_value = 2;  break;  //S2
			case 0xbb: key_value = 6;  break;  //S6
			case 0xdb: key_value = 10;  break; //S10
			case 0xeb: key_value = 14; break;  //S14
		}
	}
	while(KEY_MATRIX_PORT != 0xfb); //�ȴ������ɿ�(�ɿ����󰴼����ƹܽŵ���0xfb���˳�ѭ��)
	
	KEY_MATRIX_PORT = 0xfd;  //�������и�ֵ0������ȫΪ1  1111 1101 --> 0xfd
	if(KEY_MATRIX_PORT != 0xfd)  //�жϵ����а����Ƿ���(����������󰴼����ƹܽŲ�����0xfd)
	{
		Delay1ms(10);  //����
		switch(KEY_MATRIX_PORT) //��������а������º�ļ�ֵ
		{
			case 0x7d: key_value = 3;  break; //S3
			case 0xbd: key_value = 7;  break; //S7
			case 0xdd: key_value = 11;  break; //S11
			case 0xed: key_value = 15; break; //S15
		}
	} 
	while(KEY_MATRIX_PORT != 0xfd); //�ȴ������ɿ�(�ɿ����󰴼����ƹܽŵ���0xfd���˳�ѭ��)
	
	KEY_MATRIX_PORT = 0xfe;  //�������и�ֵ0������ȫΪ1  1111 1110 --> 0xfe
	if(KEY_MATRIX_PORT != 0xfe) //�жϵ����а����Ƿ���(����������󰴼����ƹܽŲ�����0xfe)
	{
		Delay1ms(10);  //����
		switch(KEY_MATRIX_PORT) //��������а������º�ļ�ֵ
		{
			case 0x7e: key_value = 4;  break; //S4
			case 0xbe: key_value = 8;  break; //S8
			case 0xde: key_value = 12;  break; //S12
			case 0xee: key_value = 16; break; //S16
		}
	}
	while(KEY_MATRIX_PORT != 0xfe); //�ȴ������ɿ�(�ɿ����󰴼����ƹܽŵ���0xfe���˳�ѭ��)
	
	return key_value; 
}*/


/*******************************************************************************

* �� �� �� : key_matrix_flip_scan
* �������� : ʹ���߷�תɨ�跽���������󰴼��Ƿ��£������򷵻ض�Ӧ��ֵ
* �� �� : ��
* �� �� : key_value��1-16����Ӧ S1-S16 ����
0������δ����
********************************************************************************/
/*u8 key_matrix_flip_scan(void)
{
  static u8 key_value = 0; //��ֵ
	KEY_MATRIX_PORT = 0x0f;  //��Ϊ�͵�ƽ�������� �������и�ֵ0����ȫΪ1  0000 1111 --> 0x0f
	if(KEY_MATRIX_PORT != 0x0f)  //�жϰ����Ƿ���(����������󰴼����ƹܽŲ�����0x0f)
	{
		Delay1ms(10);  //����
		if(KEY_MATRIX_PORT != 0x0f)
		{ 
			//������
			KEY_MATRIX_PORT = 0x0f;  //��Ϊ�͵�ƽ�������� �������и�ֵ0����ȫΪ1  0000 1111 --> 0x0f
			switch(KEY_MATRIX_PORT)  //������Ϊ0���������º����ֵ
			{
				case 0x07: key_value = 1; break; //��һ�� 0000 0111 --> 0x07
				case 0x0b: key_value = 2; break; //�ڶ��� 0000 1011 --> 0x0b
				case 0x0d: key_value = 3; break; //������ 0000 1101 --> 0x0d
				case 0x0e: key_value = 4; break; //������ 0000 1110 --> 0x0e
			}
			//������
			KEY_MATRIX_PORT = 0xf0;  //��Ϊ�͵�ƽ�������� �������и�ֵ1����ȫΪ0  1111 0000 --> 0xf0
			switch(KEY_MATRIX_PORT)  //������Ϊ0���������º�ļ�ֵ
			{
				case 0x70: key_value = key_value;      break;  //��һ�� 0111 0000 --> 0x70
				case 0xb0: key_value = key_value + 4;  break;  //�ڶ��� 1011 0000 --> 0xb0
				case 0xd0: key_value = key_value + 8;  break;  //������ 1101 0000 --> 0xd0
				case 0xe0: key_value = key_value + 12; break;  //������ 1110 0000 --> 0xe0
			}
			while(KEY_MATRIX_PORT != 0xf0);  //�ȴ������ɿ�(�ɿ����󰴼����ƹܽŵ���0xf0���˳�ѭ��)
		}
	}
	else 
		key_value = 0;
	return key_value;
}*/


//u8 key_ketNumber = 0;
/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
/*u8 key(void)
{
	u8 temp;
	temp = key_ketNumber;
	key_ketNumber = 0;
	return temp;
}*/


/**
  * @brief  ��ȡ��ǰ������״̬�������������ּ��
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
/*u8 Key_GetState()
{
	u8 KeyNumber = 0;
	if(KEY1 == 0)             //�������1����
		KeyNumber = KEY1_PRESS; // ����ֵ1
	if(KEY2 == 0)             //�������2����
		KeyNumber = KEY2_PRESS; // ����ֵ2
	if(KEY3 == 0)             //�������3����
		KeyNumber = KEY3_PRESS; // ����ֵ3
	if(KEY4 == 0)             //�������4����
		KeyNumber = KEY4_PRESS; // ����ֵ4
	return KeyNumber;         //���ذ���ֵ
}*/
	
/**
  * @brief  �����������������ж��е���
  * @param  ��
  * @retval ��
  */
/*void Key_loop(void)
{
	static u8 NowState,LastState;
	LastState = NowState;      //����״̬����
	NowState = Key_GetState(); //��ȡ��ǰ����״̬
	//����ϸ�ʱ��㰴�����£����ʱ���δ���£���������˲�䣬�Դ˱������������ּ��
	if(LastState == KEY1_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY1_PRESS;
	if(LastState == KEY2_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY2_PRESS;
	if(LastState == KEY3_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY3_PRESS;
	if(LastState == KEY4_PRESS && NowState == KEY_UNPRESS)
		key_ketNumber = KEY4_PRESS;
}*/
	