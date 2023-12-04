#include "AllHead.h"

////数码管显示缓存区
//u8 smg_Buf[9] = {0,10,10,10,10,10,10,10,10};
////数码管段码表
//u8 gsmg_code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40}; 
//                                    //定义数组存放0-F段码,gsmg中g代表全局变量

u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				          0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//定义数组存放0-F段码,gsmg中g代表全局变量

/**
  * @brief  设置显示缓存区
  * @param  Location 要设置的位置，范围：1~8
  * @param  Number 要设置的数字，范围：段码表索引范围
  * @retval 无
  */
/*void smg_SetBuf(u8 location,u8 number)
{
	smg_Buf[location] = number; //将某个位置的数码管改成某个数字
}*/
							
/********************************************
* 函 数 名 : smg_display
* 函数功能 : 动态数码管显示
*********************************************/
/*void smg_display(u8 location,u8 number)
{
	  SMG_A_DP_PORT = 0x00;         //消影
		switch(location)
		{
			case 1: LSC = 1;LSB = 1;LSA = 1;break; //Y7 LED8 板子从左边数第一个数码管
			case 2: LSC = 1;LSB = 1;LSA = 0;break; //Y6 LED7 板子从左边数第二个数码管
			case 3: LSC = 1;LSB = 0;LSA = 1;break; //Y5 LED6 板子从左边数第三个数码管
			case 4: LSC = 1;LSB = 0;LSA = 0;break; //Y4 LED5 板子从左边数第四个数码管
			case 5: LSC = 0;LSB = 1;LSA = 1;break; //Y3 LED4 板子从左边数第五个数码管
			case 6: LSC = 0;LSB = 1;LSA = 0;break; //Y2 LED3 板子从左边数第六个数码管
			case 7: LSC = 0;LSB = 0;LSA = 1;break; //Y1 LED2 板子从左边数第七个数码管
			case 8: LSC = 0;LSB = 0;LSA = 0;break; //Y0 LED1 板子从左边数第八个数码管
		}
		SMG_A_DP_PORT = gsmg_code[number]; //传输段选数据
}*/

/**
  * @brief  数码管驱动函数，在中断中调用
  * @param  无
  * @retval 无
  */
/*void smg_loop(void)
{
	static u8 i = 1;
	smg_display(i,smg_Buf[i]);
	i++;
	if(i > 8)
		i = 1;
}*/

/*******************************************************************************
* 函 数 名       : smg_display
* 函数功能		     : 动态数码管显示
* 输    入       : dat：要显示的数据
				           location：从左开始第几个位置开始显示，范围1-8
* 输    出    	 : 无
*******************************************************************************/
void smg_display(u8 dat[], u8 location)
{
	u8 i = 0;
	u8 location_temp = location - 1;
	for(i = location_temp; i < 8;i++)
	{
		switch(i)
		{
			case 0: LSC = 1;LSB = 1;LSA = 1;break; //Y7 LED8 板子从左边数第一个数码管
			case 1: LSC = 1;LSB = 1;LSA = 0;break; //Y6 LED7 板子从左边数第二个数码管
			case 2: LSC = 1;LSB = 0;LSA = 1;break; //Y5 LED6 板子从左边数第三个数码管
			case 3: LSC = 1;LSB = 0;LSA = 0;break; //Y4 LED5 板子从左边数第四个数码管
			case 4: LSC = 0;LSB = 1;LSA = 1;break; //Y3 LED4 板子从左边数第五个数码管
			case 5: LSC = 0;LSB = 1;LSA = 0;break; //Y2 LED3 板子从左边数第六个数码管
			case 6: LSC = 0;LSB = 0;LSA = 1;break; //Y1 LED2 板子从左边数第七个数码管
			case 7: LSC = 0;LSB = 0;LSA = 0;break; //Y0 LED1 板子从左边数第八个数码管
		}
		SMG_A_DP_PORT = dat[i - location_temp]; //传送段选数据
		delay_10us(100);//延时一段时间，等待显示稳定
		SMG_A_DP_PORT=0x00;//消音
	}
}


