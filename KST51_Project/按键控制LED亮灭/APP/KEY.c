#include <reg52.h>
#include "KEY.h"

u8 Key_State[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //ȫ�����󰴼��ĵ�ǰ״̬
u8 KeyDown_State; //����״̬
	
/*============================��������============================*/
//����������������ⰴ��������������Ӧ��������
void Key_Driver()
{
	static u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //����ֵ���ݣ�����ǰһ�ε�ֵ
	for(i = 0; i < 4; i++) //ѭ����� 4*4 �ľ��󰴼�
	{
		for(j = 0; j < 4; j++)
		{
			if(Key_State[i][j] != backup[i][j]) //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���
			{
				if(backup[i][j] != 0) //ǰ��ֵ������0����ǰֵ����0����������
				{
					Key_Test(); //���ð�����⺯��
				}
				backup[i][j] = Key_State[i][j]; //����ǰһ�εı���ֵ
			}
		}
	}
}

/*============================�������============================*/
void Key_Test() //������⺯��
{
	if(0 == KeyIn1)      //�������1����
	{
		KeyDown_State = 1; //����״̬Ϊ1
	}
	else if(0 == KeyIn2) //�������2����
	{
		KeyDown_State = 2; //����״̬Ϊ2
	}
	else if(0 == KeyIn3) //�������3����
	{
		KeyDown_State = 3; //����״̬Ϊ3
	}
	else if(0 == KeyIn4) //�������4����
	{
		KeyDown_State = 4; //����״̬Ϊ4
	}
}

/*============================����������============================*/
void Key_Handler()
{
	if(1 == KeyDown_State)       //�����������״̬Ϊ1�����ʾ����1����
	{
		KeyDown_State = 0;         //����״̬��0
		LED2 = !LED2;              //LED2״̬��ת
	}
	else if(2 == KeyDown_State)  //�����������״̬Ϊ2�����ʾ����2����
	{
		KeyDown_State = 0;         //����״̬��0
		LED3 = !LED3;              //LED3״̬��ת
	}
	else if(3 == KeyDown_State)  //�����������״̬Ϊ3�����ʾ����3����
	{
		KeyDown_State = 0;         //����״̬��0
		LED4 = !LED4;              //LED4״̬��ת
	}
	else if(4 == KeyDown_State)  //�����������״̬Ϊ4�����ʾ����4����
	{
		KeyDown_State = 0;         //����״̬��0
		LED5 = !LED5;              //LED4״̬��ת
	}
}

/* ����ɨ�躯�������ڶ�ʱ�ж��е���*/
void Key_Scan()
{
	static u8 i = 0;
	static u8 KeyOut = 0; //���󰴼�ɨ���������
	static u8 keybuf[4][4] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF},
                            {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}
                           }; //���󰴼�ɨ�軺����
	keybuf[KeyOut][0] = (keybuf[KeyOut][0] << 1) | KeyIn1; //����������һλ��������ǰɨ��ֵ�������λ
	keybuf[KeyOut][1] = (keybuf[KeyOut][1] << 1) | KeyIn2; //1111 1111 << 1 --> 1111 1110 | KeyIn1 --> 1111 1111
	keybuf[KeyOut][2] = (keybuf[KeyOut][2] << 1) | KeyIn3;
  keybuf[KeyOut][3] = (keybuf[KeyOut][3] << 1) | KeyIn4;
	//��������°���״̬
	for(i = 0; i < 4; i++) //ÿ�� 4 ������������ѭ�� 4 ��
  {
		if(0x00 == (keybuf[KeyOut][i] & 0x0F)) //����ֻ��Ҫ�ж������λ������Ҫ & ��0x0F
	  {
			//���� 4 ��ɨ��ֵΪ 0���� 4*4ms �ڶ��ǰ���״̬ʱ������Ϊ�������ȶ��İ���
		  Key_State[KeyOut][i] = 0;
	  }
		else if(0x0F == (keybuf[KeyOut][i] & 0x0F))
	  {
			//���� 4 ��ɨ��ֵΪ 1���� 4*4ms �ڶ��ǵ���״̬ʱ������Ϊ�������ȶ��ĵ���
		  Key_State[KeyOut][i] = 1;
	  }
  }
	KeyOut1 = 0; //��������ֻ��Ҫ��һ�е��ĸ�����������ֻ��ҪKeyOut1 = 0�ͺ�
}