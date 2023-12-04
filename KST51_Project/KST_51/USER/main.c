#include <reg52.h>
typedef unsigned char u8; //��ϵͳĬ���������ͽ���������
#define LED_SMG_PORT	P0  //�궨������ܶ˿�

u8 gsmg[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; //�����1-9
u8 Led_Buff[6] = {0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF}; //����ܻ���������ֵ0xFF,ȷ������ʱ������

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;

u8 flag = 0; //�����־λ

void Time0_Init();
void SMG_Show();
void SMG_Scan();

void main()
{
    ENLED = 0;     //E1 E2�͵�ƽ��Ч
    ADDR3 = 1;     //G1(E3) ʹ�ܹܽŸߵ�ƽ
    Time0_Init();
    while(1)
    {
        if(1 == flag)   //�ж϶�ʱ��־
        {
            flag = 0;   //����жϱ�־
            SMG_Show(); //�����������ʾ����
        }
    }
}
void Time0_Init()
{
    EA = 1;       //�������ж�
		TMOD &= 0xF0; //���ö�ʱ��ģʽ
    TMOD |= 0x02; //��ʱ��0ģʽ2
    TH0 = 0xA4;   //100us
    TL0 = 0xA4;
    ET0 = 1;      //ʹ�ܶ�ʱ��0�ж�
    TR0 = 1;      //������ʱ��0
}

void SMG_Show() //�������ʾ����
{
		static u8 min = 1;   //�����ʼֵ
	  static u8 sec = 30;
	  static u8 msec = 30;
	  
	  Led_Buff[0] = gsmg[msec % 10]; //�����λ
    Led_Buff[1] = gsmg[msec / 10]; //����ʮλ
    Led_Buff[2] = gsmg[sec % 10];  //���λ
    Led_Buff[3] = gsmg[sec / 10];  //��ʮλ
    Led_Buff[4] = gsmg[min % 10];  //�ָ�λ
    Led_Buff[5] = gsmg[min / 10];  //��ʮλ
	
		if(msec > 0) //����������0
		{
			msec--;    //����-1
			if((msec == 0) && (sec > 0)) //�������0������º�������ڵ���0��ʱ�����¸�ֵ
			{
				msec = 99;
				sec--; //��-1
				if((sec == 0) && (min > 0)) //�ڷ��Ӵ���0�������������ڵ���0��ʱ�����¸�ֵ
				{
					sec = 59;
					min--;
					if(min == 0) //��=0
					{
						min = 0;   //����

					}
				}
			}
		}
}

void SMG_Scan()
{
	static u8 i = 0;  //��̬ɨ�������
	//���´����������ܶ�̬ˢ��
	LED_SMG_PORT = 0xFF; //����
	switch(i)
	{
		case 0: ADDR2 = 0; ADDR1 = 0;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[0];break;
		case 1: ADDR2 = 0; ADDR1 = 0;ADDR0 = 1;i++;LED_SMG_PORT = Led_Buff[1];break;
		case 2: ADDR2 = 0; ADDR1 = 1;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[2];break;
		case 3: ADDR2 = 0; ADDR1 = 1;ADDR0 = 1;i++;LED_SMG_PORT = Led_Buff[3];break;
		case 4: ADDR2 = 1; ADDR1 = 0;ADDR0 = 0;i++;LED_SMG_PORT = Led_Buff[4];break;
		case 5: ADDR2 = 1; ADDR1 = 0;ADDR0 = 1;i=0;LED_SMG_PORT = Led_Buff[5];break;
		default: break;
	}
}

void time0() interrupt 1
{
    static u8 count = 0; //��¼�жϴ���
    TH0 = 0xA4;  //���س�ֵ
    TL0 = 0xA4;
    count++;     //�жϼ���+1
    if(count > 100)
    {
        count = 0; //����ж���0
        flag = 1;  //�����жϱ�־λ
    }
		SMG_Scan();    //�����ɨ�躯��
}