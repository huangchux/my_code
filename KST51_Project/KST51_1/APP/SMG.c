#include "AllHead.h"

u8 code gsmg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
                  0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E}; //数码管显示字符转换表

u8 SMG_BUFF[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}; //数码管显示缓冲区

/* 数码管动态扫描刷新函数，需在定时中断中调用 */
void SMG_Scan()
{
	static u8 i = 0; //动态扫描的索引
	
	LED_SMG_PORT = 0xFF; //显示消隐
	
	switch(i)
	{
		case 0: ADDR2 = 0;ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[0]; break;
		case 1: ADDR2 = 0;ADDR1 = 0; ADDR0 = 1; i++; LED_SMG_PORT = SMG_BUFF[1]; break;
		case 2: ADDR2 = 0;ADDR1 = 1; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[2]; break;
		case 3: ADDR2 = 0;ADDR1 = 1; ADDR0 = 1; i++; LED_SMG_PORT = SMG_BUFF[3]; break;
		case 4: ADDR2 = 1;ADDR1 = 0; ADDR0 = 0; i++; LED_SMG_PORT = SMG_BUFF[4]; break;
		case 5: ADDR2 = 1;ADDR1 = 0; ADDR0 = 1; i=0; LED_SMG_PORT = SMG_BUFF[5]; break;
		default: break;
	}
}

/* 将一个无符号长整型的数字显示到数码管上，num-待显示数字 */
void SMG_Show(u32 num)
{
	signed char i;
	u8 sign = 0;
	u8 buf[6];
	if(num < 0) //首先提取并暂存符号位
	{
		sign = 1;
		num = -num;
	}
	else
	{
		sign = 0;
	}
	for (i = 0; i < 6; i++) //把长整型数转换为 6 位十进制的数组
	{
		buf[i] = num % 10;
		num /= 10;
	}
	
	for (i = 5; i > 0; i--) //从最高位起，遇到 0 转换为空格，遇到非 0 则退出循环
	{ 
		if (0 == buf[i])
		{
			buf[i] = 0xFF;
		}
		else
		{
			break;
		}
	}
	if(sign == 1) //负数时，需在最前面添加负号
	{
		if(i < 5)   //当有效位数小于6位时添加负号，否则显示结果将是错的
		{
			SMG_BUFF[i + 1] = 0xBF; //负号的数码管值为0xBF
		}
	}
	for (; i >= 0; i--) //剩余低位都如实转换为数码管显示字符
	{
		SMG_BUFF[i] = gsmg[buf[i]];
	}
}