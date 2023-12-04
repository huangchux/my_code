//#include "AllHead.h"

//u8 T0RH = 0; //T0 重载值的高字节
//u8 T0RL = 0; //T0 重载值的低字节

///* 配置并启动T0，ms-T0定时时间 */
//void Time0_Init(u16 ms)
//{
//	u32 temp = 0; //临时变量
//	temp = 11059200 / 12;              //定时器计数频率
//	temp = (temp * ms) / 1000;         //计算所需的计数值
//	temp = 65536 - temp;               //计算定时器重载值
//	temp += 18;                        //补偿中断响应延时造成的误差
//	T0RH = (unsigned char)(temp >> 8); //定时器重载值拆分为高低字节
//	T0RL = (unsigned char)temp;
//	EA = 1;       //开总中断
//	TMOD &= 0xF0; //清零T0的控制位
//	TMOD |= 0x01; //配置T0为模式1
//	TH0 = T0RH;   //加载T0重载值
//	TL0 = T0RL;
//	ET0 = 1;      //使能T0中断
//	TR0 = 1;      //启动T0
//}

