#include <reg52.h>
#include <stdio.h>
#include <string.h>

//��ϵͳĬ���������ͽ���������
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

//����KEY����
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;
sbit KeyOut1 = P2^3;
sbit KeyOut2 = P2^2;
sbit KeyOut3 = P2^1;
sbit KeyOut4 = P2^0;

//����LCD1602����
#define LCD1602_DB	P0
sbit LCD1602_RS = P1^0;
sbit LCD1602_RW = P1^1;
sbit LCD1602_E = P1^5;

//����TIM����
u8 T0RH = 0;  //T0 ����ֵ�ĸ��ֽ�
u8 T0RL = 0;  //T0 ����ֵ�ĵ��ֽ�

//����KEY����
u8 code KeyCodeMap[4][4] =   //���󰴼���ŵ���׼���̼����ӳ���
{
	  { '1', '2', '3', 0x26 }, //���ּ� 1�����ּ� 2�����ּ� 3�����ϼ�
    { '4', '5', '6', 0x25 }, //���ּ� 4�����ּ� 5�����ּ� 6�������
    { '7', '8', '9', 0x28 }, //���ּ� 7�����ּ� 8�����ּ� 9�����¼�
    { '0', 0x1B, 0x0D, 0x27 } //���ּ� 0��ESC ���� �س����� ���Ҽ�
};

u8 pdata Key_state[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //������ǰ״̬
u16 Number = 0;

/***************************************** ���������� *****************************************/
void Time0_Init(u16 ms);
void LCD_WaitReady();
void LCD_WriteCmd(u8 cmd);
void LCD_WriteDat(u8 dat);
void LCD_SetCursor(u8 x,u8 y);
void LCD_Showstr(u8 x,u8 y,u8 *str);
void LCD_Init();
void Key_scan();
void Key_driver();
void Key_Action(u8 keycode);
u8 LongToString(u8 *str,u32 dat);
void LCD_AreaClear(u8 x,u8 y, u8 len);

/***************************************** ������ *****************************************/

void main()
{
	Time0_Init(1);  //���� T0 ��ʱ 1ms
	EA = 1;         //�����ж�
	LCD_Init();     //��ʼ��Һ��
	while(1)
	{
		Key_driver();  //���ð�������
	}
}

/* T0 �жϷ�������ִ�а���ɨ�� */
void Time0() interrupt 1
{
	TH0 = T0RH; //���¼�������ֵ
	TL0 = T0RL;
	Key_scan(); //����ɨ�躯��
}

/***************************************** TIM *****************************************/

/* ���ò�����T0��ms-T0��ʱʱ�� */
void Time0_Init(u16 ms)
{
	u32 temp = 0;                        //��ʱ����
	temp = 11059200 / 12;                //��ʱ������Ƶ��
	temp = (temp * ms) / 1000;           //��������ļ���ֵ
	temp = 65536 - temp;	               //���㶨ʱ������ֵ
	temp += 18;	                         //�����ж���Ӧ��ʱ��ɵ����
	T0RH = (unsigned char)(temp >> 8);   //��ʱ������ֵ���Ϊ�ߵ��ֽ�
	T0RL = (unsigned char)temp;
	TMOD &= 0xF0;   //����T0�Ŀ���λ
	TMOD |= 0x01;   //����T0Ϊģʽ1
	TH0 = T0RH;     //����T0����ֵ
	TL0 = T0RL;
	ET0 = 1;        //ʹ��T0�ж�
	TR0 = 1;        //����T0
}

/***************************************** LCD1602 *****************************************/

/* �ȴ�Һ��׼���� */
void LCD_WaitReady()    //��״̬��RS = L��R/W = H��E = H
{
	u8 sta = 0;           //����һ��״̬����
	LCD1602_DB = 0xFF;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do  //do while�������ִ��һ����䣬�ٶ�ѭ�����������ж�
	{
		LCD1602_E = 1;     //ʹ��
		sta = LCD1602_DB;  //��ȡ״̬��
		LCD1602_E = 0;     //���곷��ʹ�ܣ���ֹҺ��������ݸ��� P0 ����
	}while(sta & 0x80);  //���λ���� 1 ��ʾҺ����æ���ظ����ֱ������� 0 Ϊֹ
}

/* �� LCD1602 Һ��д��һ�ֽ����cmd-��д������ֵ */
void LCD_WriteCmd(u8 cmd) //дָ�RS = L��R/W = L��D0~D7 = ָ���룬E = ������
{
	LCD_WaitReady();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
}

/* �� LCD1602 Һ��д��һ�ֽ����ݣ�dat-��д������ֵ */
void LCD_WriteDat(u8 dat)  //д���ݣ�RS = H��R/W = L��D0~D7 = ���ݣ�E = ������
{
	LCD_WaitReady();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}

/* ������ʾ RAM ��ʼ��ַ���༴���λ�ã�(x,y)-��Ӧ��Ļ�ϵ��ַ����� */
void LCD_SetCursor(u8 x,u8 y)
{
	u8 addr;
	if(0 == y)           //���������Ļ���������ʾRAM�ĵ�ַ
	{
		addr = 0x00 + x;   //��һ���ַ���ַ��0x00��ʼ
	}
	else
	{
		addr = 0x40 + x;   //�ڶ����ַ���ַ��0x40��ʼ
	}
	LCD_WriteCmd(addr | 0x80); //����RAM��ַ
}

/* ��Һ������ʾ�ַ�����(x,y)-��Ӧ��Ļ�ϵ���ʼ���꣬str-�ַ���ָ�룬len-����ʾ���ַ����� */
void LCD_Showstr(u8 x,u8 y,u8 *str)
{
	LCD_SetCursor(x,y);   //������ʼ��ַ
	while(*str != '\0')
	{
		LCD_WriteDat(*str++);  //��ȡstrָ�������Ȼ�����д���ݺ�����Ȼ��str�Լ�1,���ȼ�һ����������
	}
}

/* ��ʼ�� 1602 Һ�� */
void LCD_Init()
{
	LCD_WriteCmd(0x38);  //16*2��ʾ��5*7����8λ���ݽӿ�
	LCD_WriteCmd(0x0C);  //��ʾ���������رգ���˸�ر�	0000 1100
	LCD_WriteCmd(0x06);  //���ֲ�������ַ�Զ�+1 0000 0110
	LCD_WriteCmd(0x01);  //����
}

/* ��������ת��Ϊ�ַ�����str-�ַ���ָ�룬dat-��ת����������ֵ-�ַ������� */
u8 LongToString(u8 *str,u32 dat)
{
	signed char i = 0;
	u8 len = 0;
	u8 buf[12];
	do
	{
		buf[i++] = dat % 10;  //��ת��Ϊ��λ��ǰ��ʮ��������
		dat /= 10;
	}while(dat > 0);
	len += i;         //i ����ֵ������Ч�ַ��ĸ���
	while(i-- > 0)    //������ֵת��Ϊ ASCII �뷴�򿽱�������ָ����
	{
		*str++ = buf[i] + '0';
	}
	*str = '\0';  //����ַ���������
	return len;   //�����ַ�������
}

/* ��������������(x,y)������ʼ�� len ���ַ�λ */
void LCD_AreaClear(u8 x,u8 y, u8 len)
{
	LCD_SetCursor(x,y);  //������ʼ��ַ
	while(len--)         //����д��ո�
	{
		LCD_WriteDat(' ');
	}
}


/***************************************** KEY *****************************************/

/* ����ɨ�躯�������ڶ�ʱ�ж��е��� */
void Key_scan()
{
	u8 i = 0;
	static u8 KeyOut = 0;  //���󰴼�ɨ���������
	static u8 Keybuf[4][4] = {{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}};  //���󰴼�ɨ�軺����
	
	//��һ�е� 4 ������ֵ���뻺����
	Keybuf[KeyOut][0] = (Keybuf[KeyOut][0] << 1) | KeyIn1;
	Keybuf[KeyOut][1] = (Keybuf[KeyOut][1] << 1) | KeyIn2;
	Keybuf[KeyOut][2] = (Keybuf[KeyOut][2] << 1) | KeyIn3;
	Keybuf[KeyOut][3] = (Keybuf[KeyOut][3] << 1) | KeyIn4;
	//��������°���״̬
	for(i = 0; i < 4; i++)  //ÿ�� 4 ������������ѭ�� 4 ��
	{
		if(0x00 == (Keybuf[KeyOut][i] & 0x0F))
		{
			//���� 4 ��ɨ��ֵΪ 0���� 4*4ms �ڶ��ǰ���״̬ʱ������Ϊ�������ȶ��İ���
			Key_state[KeyOut][i] = 0;
		}
		else if(0x0F == (Keybuf[KeyOut][i] & 0x0F))
		{
			//���� 4 ��ɨ��ֵΪ 1���� 4*4ms �ڶ��ǵ���״̬ʱ������Ϊ�������ȶ��ĵ���
			Key_state[KeyOut][i] = 1;
		}
	}
	//ִ����һ�ε�ɨ�����
	KeyOut++;  //�����������
	KeyOut = KeyOut & 0x03;
	switch(KeyOut)  //�����������ͷŵ�ǰ������ţ������´ε��������
	{
		case 0:KeyOut4 = 1;KeyOut1 = 0;break;
		case 1:KeyOut1 = 1;KeyOut2 = 0;break;
		case 2:KeyOut2 = 1;KeyOut3 = 0;break;
		case 3:KeyOut3 = 1;KeyOut4 = 0;break;
	}
}

/* ����������������ⰴ��������������Ӧ����������������ѭ���е��� */
void Key_driver()
{
	u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //����ֵ���ݣ�����ǰһ�ε�ֵ
	for(i = 0; i < 4; i++)  //ѭ��ɨ�� 4*4 �ľ��󰴼�
	{
		for(j = 0; j < 4; j++)
		{
			if(backup[i][j] != Key_state[i][j]) //��ǰֵ��ǰ��ֵ�����˵����ʱ�����ж���
			{
				if(backup[i][j] != 0)  //ǰ��ֵ������0����ǰֵ����0����������
				{
					Key_Action(KeyCodeMap[i][j]);
				}
				backup[i][j] = Key_state[i][j]; //����ǰһ�εı���ֵ
			}
		}
	}
}

/* �����������������ݼ���ִ����Ӧ�Ĳ�����keycode-�������� */
void Key_Action(u8 keycode)  //�����������������ݼ���ִ����Ӧ����
{
	u8 str[20];
	u8 len = 0;
	if((keycode >= '0') && (keycode <= '9'))  //����0~9
	{
		len = LongToString(str,keycode - '0'); //������ת��Ϊ�ַ��� keycode - '0'��ʾת��Ϊ����
		LCD_AreaClear(0,0,16 - len);           //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,str); 
	}
	if(0x26 == keycode)  //���ϼ�
	{
		len = strlen("UP");              // �����ַ�������
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"UP");
	}
	else if(0x28 == keycode) //���¼�
	{
		len = strlen("DOWN");
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"DOWN");
	} 
	else if(0x25 == keycode) //�����
	{
		len = strlen("LEFT");
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"LEFT");
		
	} 
	else if(0x27 == keycode) //���Ҽ�
	{
		len = strlen("RIGHT");
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"RIGHT");
	} 
	else if(0x0D == keycode) //�س���
	{
		len = strlen("ENTER");
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"ENTER");
	} 
	else if(0x1B == keycode)  //Esc��
	{
		len = strlen("ESC");
		LCD_AreaClear(0,0,16 - len);     //�����һ���ַ����ұߵ��ַ�λ
		LCD_Showstr(0,0,"ESC");
	}
}