//#include "AllHead.h"

///* 复位总线，获取存在脉冲，以启动一次读写操作 */
//bit Get_18B20Ack()
//{
//	bit ack;
//	
//	EA = 0;              //禁止总中断
//	DS18B20_IO = 0;      //产生 500us 复位脉冲
//	Delay_10us(50);
//	DS18B20_IO = 1;
//	Delay_10us(6);       //延时 60us
//	ack = DS18B20_IO;    //读取存在脉冲
//	while(!DS18B20_IO);  //等待存在脉冲结束
//	EA = 1;              //重新使能总中断
//  return ack;
//}

///* 向 DS18B20 写入一个字节，dat-待写入字节 */
//void DS18B20_Write(u8 dat)
//{
//	u8 i;
//	 
//	EA = 0;                 //禁止总中断
//	for(i = 0; i < 8; i++)
//	{
//		DS18B20_IO = 0;       //产生 2us 低电平脉冲
//		_nop_(); _nop_();
//		if((dat & 0x01) > 0)  //dat最低位如果为大于0（等于1）
//			DS18B20_IO = 1;     
//		else
//			DS18B20_IO = 0;
//		dat >>= 1;           //右移一位
//		Delay_10us(6);       //延时 60us
//		DS18B20_IO = 1;      //拉高通信引脚
//	}
//	EA = 1;                //重新使能总中断
//}

///* 从 DS18B20 读取一个字节，返回值-读到的字节 */
//u8 DS18B20_Read()
//{
//	u8 i;
//	u8 dat = 0;
//	
//	EA = 0;                 //禁止总中断

//	for(i = 0; i < 8; i++)
//	{
//		DS18B20_IO = 0;       //产生 2us 低电平脉冲
//		_nop_(); _nop_();
//		DS18B20_IO = 1;       //结束低电平脉冲，等待 18B20 输出数据
//		_nop_(); _nop_();     //延时 2us		
//		dat >>= 1;            //右移一位
//		if(DS18B20_IO)        //如果通信引脚上的值为1
//			dat |= 0x80;        //dat最高位赋为1
//		Delay_10us(5);        //再延时 50us
//	}
//	EA = 1;                 //重新使能总中断
//	return dat;
//}

///* 启动一次 18B20 温度转换，返回值-表示是否启动成功 */
//bit DS18B20_Start()
//{
//	bit ack;
//	ack = Get_18B20Ack();   //执行总线复位，并获取 18B20 应答
//	if(0 == ack)            //如 18B20 正确应答，则启动一次转换
//	{
//		DS18B20_Write(0xCC);  //跳过 ROM 操作
//		DS18B20_Write(0x44);  //启动一次温度转换
//	}
//	return ~ack;            //ack==0 表示操作成功，所以返回值对其取反
//}

///* 读取 DS18B20 转换的温度值，返回值-表示是否读取成功 */
//bit DS18B20_Read_Temp(int *temp)
//{
//	bit ack;
//	u8 LSB,MSB;                         //16bit 温度值的低字节和高字节
//	ack = Get_18B20Ack();               //执行总线复位，并获取 18B20 应答
//	if(0 == ack)                        //如 18B20 正确应答，则读取温度值
//	{
//		DS18B20_Write(0xCC);              //跳过 ROM 操作
//		DS18B20_Write(0xBE);              //发送读命令
//		LSB = DS18B20_Read();             //读温度值的低字节
//		MSB = DS18B20_Read();             //读温度值的高字节
//		*temp = ((int)MSB << 8) + LSB;    //合成为 16bit 整型数
//	}
//	return ~ack;                        //ack==0 表示操作应答，所以返回值为其取反值
//} 
