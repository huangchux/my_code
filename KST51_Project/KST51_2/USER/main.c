#include "AllHead.h"

sbit ADDR0 = P0^0;
sbit ADDR1 = P0^1;
sbit ADDR2 = P0^2;
sbit ADDR3 = P0^3;
sbit ENLED = P0^4;

void main()
{
	EA = 1;     //使能总中断
  ES = 1;     //使能串口中断
	ADDR3 = 1;
	ENLED = 0;
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	P0 = 0xFF;
	UAER_Init(9600);
	while(1)
	{
		if(flag)
		{
			if(strcmp(rec_buf,"open") == 0)
			{
				P0 = 0x00;
			}
			if(strcmp(rec_buf,"close") == 0)
			{
				P0 = 0xFF;
			}
			flag = 0;
		}
	}
}




//void Key_Action(u8 keycode);
//void SetDACOut(unsigned char val);

//void main()
//{
//	Time0_Init(1);  //T0 定时 1ms

//	while(1)
//	{
//		Key_Driver();
//	}
//}

///* 按键动作函数，根据键码执行相应的操作，keycode-按键键码 */
//void Key_Action(u8 keycode)
//{
// static u8 volt = 0; //输出电压值，隐含了一位十进制小数位
// 
// if (0x26 == keycode) //向上键，增加 0.1V 电压值
// {
//	if (volt < 25)
//	{
//		volt++;
//		SetDACOut(volt * 255 / 25); //转换为 AD 输出值
//	}
// }
// else if (keycode == 0x28) //向下键，减小 0.1V 电压值
// {
//		if (volt > 0)
//		{
//			volt--;
//			SetDACOut(volt * 255 / 25); //转换为 AD 输出值
//		}
//	}
//}

///* 设置 DAC 输出值，val-设定值 */
//void SetDACOut(unsigned char val)
//{
// I2C_Start();
// if (!I2C_Write(0x90)) //寻址 PCF8591，如未应答，则停止操作并返回
// {
//	 I2C_Stop();
//	 return;
// }
// I2C_Write(0x40); //写入控制字节
// I2C_Write(val); //写入 DA 值 
// I2C_Stop();
//}

///* T0 中断服务函数，执行数码管扫描显示 */
//void time0() interrupt 1
//{
//	TH0 = T0RH;      //加载T0重载值
//	TL0 = T0RL;
//	Key_Scan(); //按键扫描
//}
