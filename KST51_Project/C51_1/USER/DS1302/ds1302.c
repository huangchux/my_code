#include "AllHead.h"

////---DS1302写入和读取时分秒的地址命令---//
////---秒分时日月周年 最低位读写位;-------//
//u8 gWRITE_addr[7] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};//数据可查看各类寄存器
//u8 gRREAD_addr[7] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};

////---DS1302时钟初始化2023年8月8日星期二17点25分47秒。---//
////---存储顺序是秒分时日月周年,存储格式是用BCD码---//
//u8 gDS1302_TIME[7] = {0x01,0x34,0x18,0x08,0x08,0x02,0x23};

///*******************************************************************************
//* 函 数 名       : ds1302_write_byte
//* 函数功能		     : DS1302写单字节
//* 输    入       : addr：地址/命令
//				           dat：数据
//* 输    出    	 : 无
//*******************************************************************************/
//void ds1302_write_byte(u8 addr,u8 dat)
//{
//	u8 i = 0;
//	DS1302_CE = 0;    //首先CE输出低电平
//	_nop_();          //延时1us
//	DS1302_SCLK = 0;  //SCLK也输出低电平
//	_nop_();
//	DS1302_CE = 1;    //在读写过程，CE要保持高电平
//	_nop_();
//	
//	for(i = 0;i < 8;i++)  //循环8次，每次写1位，先写低位再写高位
//	{
//		DS1302_IO = addr & 0x01; //取出控制寄存器地址的最低位赋给DS1302的IO口
//		addr >>= 1;              //将控制寄存器地址的次低位移到最低位
//		DS1302_SCLK = 1;         //SCLK由低到高产生一个上升沿，从而写入数据
//		_nop_();
//		DS1302_SCLK = 0;         //SCLK先拉低，以便下一次上升沿
//		_nop_();
//	}
//	for(i = 0;i < 8;i++) //循环8次，每次写1位，先写低位再写高位
//	{
//		DS1302_IO = dat & 0x01; //取出写入数据的最低位赋给DS1302的IO口
//		dat >>= 1;              //将数据的次低位移到最低位
//		DS1302_SCLK = 1;        //SCLK由低到高产生一个上升沿，从而写入数据
//		_nop_();                //延时1us
//		DS1302_SCLK = 0;        //SCLK先拉低，以便下一次上升沿
//		_nop_();
//	}
//	DS1302_CE = 0; //RST拉低
//	_nop_();
//}

///*******************************************************************************
//* 函 数 名       : ds1302_read_byte
//* 函数功能		     : DS1302读单字节
//* 输    入       : addr：地址/命令
//* 输    出    	 : 读取的数据
//*******************************************************************************/
//u8 ds1302_read_byte(u8 addr)
//{
//	u8 i = 0;
//	u8 temp = 0; //接收数据中一个位的变量
//	u8 dat = 0;  //将接收到的数据存放到这个变量
//	
//	DS1302_CE = 0;    //首先CE输出低电平
//	_nop_();          //延时1us
//	DS1302_SCLK = 0;  //SCLK也输出低电平
//	_nop_();
//	DS1302_CE = 1;    //在读写过程，CE要保持高电平
//	_nop_();
//	
//	for(i = 0;i < 8;i++)  //循环8次，每次写1位，先写低位再写高位
//	{
//		DS1302_IO = addr & 0x01; //取出控制寄存器地址的最低位赋给DS1302的IO口
//		addr >>= 1;              //将控制寄存器地址的次低位移到最低位
//		DS1302_SCLK = 1;         //SCLK由低到高产生一个上升沿，从而写入数据
//		_nop_();
//		DS1302_SCLK = 0;         //SCLK先拉低，以便下一次上升沿
//		_nop_();
//	}
//	for(i = 0;i < 8;i++) //循环8次，每次读1位，先读低位再读高位
//	{
//		temp = DS1302_IO;  //将在IO口接收到的数据中的一位存放到temp变量中
//		dat = (temp << 7) | (dat >> 1); //先将dat右移1位，然后temp左移7位，最后或运算(或运算中或符号后面的数据优先级比较高)
//		DS1302_SCLK = 1;         
//		_nop_();
//		DS1302_SCLK = 0;         //SCLK由高到低产生一个下降沿，从而读入数据
//		_nop_();
//	}
//	DS1302_CE = 0; //CE拉低
//	_nop_();
//	DS1302_SCLK = 1; //对于实物中，P3.4口没有外接上拉电阻的，此处代码需要添加，使数据口有一个上升沿脉冲
//	_nop_();
//	DS1302_IO = 0;  
//	_nop_();
//	DS1302_IO = 1;  //读取字节之前，将 IO 设置为输入口，读取完之后，要将其改回输出口
//	_nop_();
//	return dat;  //将读取到的数据返回出去
//}

///*******************************************************************************
//* 函 数 名       : ds1302_init
//* 函数功能		     : DS1302初始化时间
//* 输    入       : 无
//* 输    出    	 : 无
//*******************************************************************************/
//void ds1302_init(void)
//{
//	u8 i = 0;
//	ds1302_write_byte(0x8E,0X00); //关闭写保护(写保护寄存器的地址为0x8E,WP为其中的最高位，WP为0即为关闭写保护)
//	for(i = 0;i < 7;i++)
//	{
//		ds1302_write_byte(gWRITE_addr[i],gDS1302_TIME[i]);
//	}
//	ds1302_write_byte(0x8E,0X80); //打开写保护，以防止意外修改DS1302内部寄存器(WP为1即为打开写保护)
//}

///*******************************************************************************
//* 函 数 名       : ds1302_read_time
//* 函数功能		     : DS1302读取时间
//* 输    入       : 无
//* 输    出    	 : 无
//*******************************************************************************/
//void ds1302_read_time(void)
//{
//	u8 i = 0;
//	for(i = 0;i < 7;i++)
//	{
//		gDS1302_TIME[i] = ds1302_read_byte(gRREAD_addr[i]);
//	}
//}