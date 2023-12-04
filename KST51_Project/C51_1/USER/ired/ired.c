#include "AllHead.h"

u8 gired_data[4];

/*******************************************************************************
* 函 数 名         : ired_init
* 函数功能		   : 红外端口初始化函数，外部中断0配置 
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void ired_init(void)
{
	IT0 = 1;  //下降沿触发
	EX0 = 1;  //打开中断0允许
	EA = 1;   //打开总中断
	IRED = 1; //初始化端口
}

void ired() interrupt 0  //外部中断0服务函数
{
	u16 time_cnt = 0;
	u8 i = 0,j = 0;
	u8 ired_high_time = 0;
	
	if(IRED == 0)
	{
		time_cnt = 1000;
		while((!IRED) && (time_cnt))  //等待引导信号9ms低电平结束，若超过10ms强制退出,若高电平则跳出循环
		{
			delay_10us(1);  //延时约10us 10us*1000 = 10000us --> 10ms
			time_cnt--;
			if(time_cnt == 0) return; 
		}
		if(IRED)  //引导信号9ms低电平已过，进入4.5ms高电平
		{
			time_cnt = 500;
			while((IRED) && (time_cnt)) //等待引导信号4.5ms高电平结束，若超过5ms强制退出
			{
				delay_10us(1); //延时约10us 10us*500 = 5000us --> 5ms
				time_cnt--;
			  if(time_cnt == 0) return;
			}
			for(i = 0;i < 4;i++)  //循环4次，读取4个字节数据(地址码、地址反码、控制码、控制反码)
			{
				for(j = 0;j < 8;j++) //循环8次读取每位数据即一个字节
				{
					time_cnt = 600;
					while((!IRED) && (time_cnt)) //等待数据1或0前面的0.56ms结束，若超过6ms强制退出
					{
						delay_10us(1);  //延时约10us 10us*600 = 6000us --> 6ms
						time_cnt--;
			      if(time_cnt == 0) return;
					}
					while(IRED)  //等待数据1或0后面的高电平结束，若超过2ms强制退出
					{
						delay_10us(10);  //约0.1ms 100us*20 == 2000us --> 2ms
						ired_high_time++;
						if(ired_high_time > 20) return;
					}
					gired_data[i] >>=1; //数据是先传低位再传高位，所以接收到的低位数据需要往右移一位
					if(ired_high_time >= 8) //如果高电平时间大于0.8ms，数据则为1，否则为0
						gired_data[i] |= 0x80; //如果高电平时间大于0.8ms则接收到的数据为1，或上0x80相当于取出最高位的数据
					                         //接着向右移动一位
					ired_high_time = 0; //重新清零，等待下一次计算时间
				}
			}
		}
		if(gired_data[2] != ~gired_data[3]) //校验控制码与反码，错误则返回
		{
			for(i = 0;i < 4;i++)
			gired_data[i] = 0; //接收到的数据清0
			return;
		}
	}
}