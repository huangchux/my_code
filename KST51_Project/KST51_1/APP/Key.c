#include "AllHead.h"

u8 code KeyCodeMap[4][4] = { //���󰴼���ŵ���׼���̼����ӳ���
            { 0x31, 0x32, 0x33, 0x26 }, //���ּ� 1�����ּ� 2�����ּ� 3�����ϼ�
            { 0x34, 0x35, 0x36, 0x25 }, //���ּ� 4�����ּ� 5�����ּ� 6�������
            { 0x37, 0x38, 0x39, 0x28 }, //���ּ� 7�����ּ� 8�����ּ� 9�����¼�
            { 0x30, 0x1B, 0x0D, 0x27 } //���ּ� 0��ESC ���� �س����� ���Ҽ�
            };
u8 key_sate[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //ȫ�����󰴼��ĵ�ǰ״̬

/* ����������������ⰴ��������������Ӧ����������������ѭ���е��� */
void Key_Driver()
{
	u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //����ֵ���ݣ�����ǰһ�ε�ֵ
	for(i = 0;i < 4;i++) //ѭ����� 4*4 �ľ��󰴼�
  {
		for(j = 0;j < 4;j++)
		{
			if(backup[i][j] != key_sate[i][j]) //��ⰴ������
			{
				if(backup[i][j] != 0)           //��������ʱִ�ж���
				{
					Key_Action(KeyCodeMap[i][j]); //���ð�����������
				}
				backup[i][j] = key_sate[i][j]; //ˢ��ǰһ�εı���
			}
		}
	}
}

/* �����������������ݼ���ִ����Ӧ�Ĳ�����keycode-�������� */
void Key_Action(u8 keycode)
{
	static char oprt = 0;    //���ڱ���Ӽ������
	static long result = 0;  //���ڱ���������
	static long addend = 0;  //���ڱ�������ļ���
	
	if ((keycode >= 0x30) && (keycode <= 0x39)) //���� 0-9 ������
	{
		addend = (addend * 10) + (keycode - 0x30);  //����ʮ�������ƣ������ֽ����λ
		SMG_Show(addend); //��������ʾ�������
	}
	else if (0x26 == keycode) //���ϼ������Ӻţ�ִ�мӷ�����������
	{
		oprt = 0;        //�������������
		result = addend; //�������浽����У�׼�����мӼ�
		addend = 0;      //������������׼��������һ��������
		SMG_Show(addend);//ˢ���������ʾ
	}
	else if(0x28 == keycode) //���¼���������
	{
		oprt = 1;              //�������������
		result = addend;       //�������浽����У�׼�����мӼ�
		addend = 0;            //������������׼��������һ��������
		SMG_Show(addend);      //ˢ���������ʾ
	}
	else if (0x0D == keycode)  //�س�����ִ�мӼ�����
	{
		if(0 == oprt)
		{
			result += addend; //���мӷ�����
		}
		else
		{
			result -= addend; //���м�������
		}
		addend = 0;
		SMG_Show(result);   //��������ʾ�������
	}
	else if (0x1B == keycode) //Esc ����������
	{
		addend = 0;
		result = 0;
		SMG_Show(addend); //��������ʾ�������
	}
}

/* ����ɨ�躯�������ڶ�ʱ�ж��е��ã��Ƽ����ü�� 1ms */
void Key_Scan()
{
	u8 i = 0;
	static u8 KeyOut = 0; //���󰴼�ɨ���������
	static u8 keybuf[4][4] = {{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
	                          {0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}}; //���󰴼�ɨ�軺����
	//��һ�е� 4 ������ֵ���뻺����
	keybuf[KeyOut][0] = (keybuf[KeyOut][0] << 1) | KeyIn1;
	keybuf[KeyOut][1] = (keybuf[KeyOut][1] << 1) | KeyIn2;
	keybuf[KeyOut][2] = (keybuf[KeyOut][2] << 1) | KeyIn3;
	keybuf[KeyOut][3] = (keybuf[KeyOut][3] << 1) | KeyIn4;
	//��������°���״̬														
	for (i = 0; i < 4; i++) //ÿ�� 4 ������������ѭ�� 4 ��
	{
		if (0x00 == (keybuf[KeyOut][i] & 0x0F))
	  { //���� 4 ��ɨ��ֵΪ 0���� 4*4ms �ڶ��ǰ���״̬ʱ������Ϊ�������ȶ��İ���
			key_sate[KeyOut][i] = 0;
	  }
		else if (0x0F == (keybuf[KeyOut][i] & 0x0F))
	  { //���� 4 ��ɨ��ֵΪ 1���� 4*4ms �ڶ��ǵ���״̬ʱ������Ϊ�������ȶ��ĵ���
			key_sate[KeyOut][i] = 1;
	  }
	}
	//ִ����һ�ε�ɨ�����
	KeyOut++; //�����������
	if (KeyOut >= 4)
	{
		KeyOut = 0;
	}
//	KeyOut = KeyOut & 0x03; //����ֵ�ӵ� 4 ������
	
	switch(KeyOut) //�����������ͷŵ�ǰ������ţ������´ε��������
	{
		case 0: KeyOut4 = 1;KeyOut1 = 0;break;
		case 1: KeyOut1 = 1;KeyOut2 = 0;break;
		case 2: KeyOut2 = 1;KeyOut3 = 0;break;
		case 3: KeyOut3 = 1;KeyOut4 = 0;break;
		default:break;
	}
}
