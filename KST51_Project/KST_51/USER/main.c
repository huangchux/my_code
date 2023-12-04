#include <reg52.h>
typedef unsigned char u8; //对系统默认数据类型进行重命名
#define LED_SMG_PORT	P0  //宏定义数码管端口

u8 gsmg[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90}; //数码管1-9
u8 Led_Buff[6] = {0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF}; //数码管缓存区，初值0xFF,确保启动时都不亮

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;

u8 flag = 0; //定义标志位

void Time0_Init();
void SMG_Show();
void SMG_Scan();

void main()
{
    ENLED = 0;     //E1 E2低电平有效
    ADDR3 = 1;     //G1(E3) 使能管脚高电平
    Time0_Init();
    while(1)
    {
        if(1 == flag)   //判断定时标志
        {
            flag = 0;   //清除中断标志
            SMG_Show(); //调用数码管显示函数
        }
    }
}
void Time0_Init()
{
    EA = 1;       //开启总中断
		TMOD &= 0xF0; //设置定时器模式
    TMOD |= 0x02; //定时器0模式2
    TH0 = 0xA4;   //100us
    TL0 = 0xA4;
    ET0 = 1;      //使能定时器0中断
    TR0 = 1;      //启动定时器0
}

void SMG_Show() //数码管显示函数
{
		static u8 min = 1;   //定义初始值
	  static u8 sec = 30;
	  static u8 msec = 30;
	  
	  Led_Buff[0] = gsmg[msec % 10]; //毫秒个位
    Led_Buff[1] = gsmg[msec / 10]; //毫秒十位
    Led_Buff[2] = gsmg[sec % 10];  //秒个位
    Led_Buff[3] = gsmg[sec / 10];  //秒十位
    Led_Buff[4] = gsmg[min % 10];  //分个位
    Led_Buff[5] = gsmg[min / 10];  //分十位
	
		if(msec > 0) //如果毫秒大于0
		{
			msec--;    //毫秒-1
			if((msec == 0) && (sec > 0)) //在秒大于0的情况下毫秒才能在等于0的时候重新赋值
			{
				msec = 99;
				sec--; //秒-1
				if((sec == 0) && (min > 0)) //在分钟大于0的情况下秒才能在等于0的时候重新赋值
				{
					sec = 59;
					min--;
					if(min == 0) //分=0
					{
						min = 0;   //清零

					}
				}
			}
		}
}

void SMG_Scan()
{
	static u8 i = 0;  //动态扫描的索引
	//以下代码完成数码管动态刷新
	LED_SMG_PORT = 0xFF; //消隐
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
    static u8 count = 0; //记录中断次数
    TH0 = 0xA4;  //重载初值
    TL0 = 0xA4;
    count++;     //中断计数+1
    if(count > 100)
    {
        count = 0; //溢出中断清0
        flag = 1;  //设置中断标志位
    }
		SMG_Scan();    //数码管扫描函数
}