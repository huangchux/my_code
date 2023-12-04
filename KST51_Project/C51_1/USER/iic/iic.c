#include "AllHead.h"

///*******************************************************************************
//* 函 数 名 : iic_start
//* 函数功能 : 产生 IIC 起始信号
//* 输 入 : 无
//* 输 出 : 无
//*******************************************************************************/
//void iic_start(void)
//{
//	IIC_SCL = 1;
//	IIC_SDA = 1;
//	delay_10us(1);
//	IIC_SDA = 0;   //当SCL为高电平时，SDA由高变为低
//	delay_10us(1);
//	IIC_SCL = 0;   //钳住I2C总线，准备发送或接收数据(SCL为低电平时数据可以改变)
//}

///*******************************************************************************
//* 函 数 名 : iic_stop
//* 函数功能 : 产生 IIC 停止信号
//* 输 入 : 无
//* 输 出 : 无
//*******************************************************************************/
//void iic_stop(void)
//{
//	IIC_SCL = 1;
//	IIC_SDA = 0;
//	delay_10us(1);
//	IIC_SDA = 1;    //当SCL为高电平时，SDA由低变为高
//	delay_10us(1);
//}

///*******************************************************************************
//* 函 数 名 : iic_ack
//* 函数功能 : 产生 ACK 应答
//* 输 入 : 无
//* 输 出 : 无
//*******************************************************************************/
//void iic_ack(void)
//{
//	IIC_SCL = 0;
//	IIC_SDA = 0;   //SDA为低电平
//	delay_10us(1);
//	IIC_SCL = 1;
//	delay_10us(1);
//	IIC_SCL = 0;
//}

///*******************************************************************************
//* 函 数 名 : iic_nack
//* 函数功能 : 产生 NACK 非应答
//* 输 入 : 无
//* 输 出 : 无
//*******************************************************************************/
//void iic_nack(void)
//{
//	IIC_SCL = 0;
//	IIC_SDA = 1;   //SDA为高电平
//	delay_10us(1);
//	IIC_SCL = 1;
//	delay_10us(1);
//	IIC_SCL = 0;
//}

///*******************************************************************************
//* 函 数 名 : iic_wait_ack
//* 函数功能 : 等待应答信号到来
//* 输 入 : 无
//* 输 出 : 1，接收应答失败
//          0，接收应答成功
//*******************************************************************************/
//u8 iic_wait_ack(void)
//{
//	u8 time_temp = 0; //计时变量
//	IIC_SCL = 1;
//	delay_10us(1);
//	while(IIC_SDA)  //等待SDA为低电平(SDA为1进入循环，为0则跳出循环)
//	{
//		time_temp++;
//		if(time_temp > 100)  //超时则强制结束IIC通信
//		{
//			iic_stop();        //强制结束IIC通信
//			return 1;          //返回1(接收应答失败)
//		}	
//	}
//	IIC_SCL = 0;
//	return 0;              //返回0(接收应答成功)
//}


///*******************************************************************************
//* 函 数 名 : iic_write_byte
//* 函数功能 : IIC 发送一个字节
//* 输 入 : dat：发送一个字节
//* 输 出 : 无
//*******************************************************************************/
//void iic_write_byte(u8 dat)
//{
//	u8 i = 0;
//	IIC_SCL = 0;  //为0数据才可以改变
//	for(i = 0;i < 8; i++)
//	{
//		if((dat & 0x80) > 0) //比较最高位 (如1011 0100 & 1000 0000 --> 1000 0000 最高位等于1 大于0)
//			IIC_SDA = 1;
//		else
//			IIC_SDA = 0;
//		dat <<= 1;     //左移一位(将次高位移到最高位)
//		delay_10us(1);
//		IIC_SCL = 1;  //为1数据稳定等待下一次传输
//		delay_10us(1);
//		IIC_SCL = 0;  //数据传输完毕，让SCL为0，使下一次数据可以改变并进行传输
//		delay_10us(1);
//	}
//}


///*******************************************************************************
//* 函 数 名 : iic_read_byte
//* 函数功能 : IIC 读一个字节
//* 输 入 : ack=1 时，发送 ACK，ack=0，发送 nACK
//* 输 出 : 应答或非应答
//*******************************************************************************/
//u8 iic_read_byte(u8 ack)
//{
//	u8 i = 0;
//	u8 receive = 0;  //保存读取的数据
//	for(i = 0; i < 8; i++)  //循环8次将一个字节读出，先读高位再传低位
//	{
//		IIC_SCL = 0;
//		delay_10us(1);
//		IIC_SCL = 1;   //SCL为1时数据稳定，可以传输数据
//		delay_10us(1);
//		receive <<= 1; //将接收到的数据向左移动一位 (假设要传输 1001 1000，则先接收到高位1，则SDA为1，
//		if(IIC_SDA)    //如果SDA为1                 receive加1，则receive为 0000 0001，之后将receive
//			receive++;   //则接收到的数据加1          向左移动一位，则receive为 0000 0010,接着传输第二位0，
//		delay_10us(1);                      //     则SDA为0，不进入if语句，receive接收到0，则receive   
//                                        //     为 0000 0010，之后将receive向左移动一位，则receive为	
//  }                                     //		 0000 0100 以此类推接收数据，直到数据传输完成则跳出循环)
//	if(!ack)
//		iic_nack();     //非应答
//	else
//		iic_ack();      //应答
//	return receive;   //返回出去
//}




///**
//  * @brief    I2C开始 产生 IIC 起始信号
//  * @param    无
//  * @retval   无
//  */
//void I2C_Start(void)
//{
//	I2C_SDA=1;  //先确保SDA为1
//	I2C_SCL=1;  //再把SCL拉高
//	I2C_SDA=0;  //当SCL为高电平时，SDA由高变为低
//	I2C_SCL=0;  //钳住I2C总线，准备发送或接收数据(SCL为低电平时数据可以改变)
//}

///**
//  * @brief  I2C停止 产生IIC停止信号
//  * @param  无
//  * @retval 无
//  */
//void I2C_Stop(void)
//{
//	I2C_SDA=0;  //先把SDA拉低
//	I2C_SCL=1;  //再把SCL拉高
//	I2C_SDA=1;  //当SCL为高电平时，SDA由低变为高
//}

///**
//  * @brief  I2C发送一个字节
//  * @param  Byte 要发送的字节
//  * @retval 无
//  */
//void I2C_SendByte(u8 Byte)
//{
//	u8 i;
//	for(i=0;i<8;i++)
//	{                         //先传高位再传低位
//		I2C_SDA=Byte&(0x80>>i); //取出最高位把值赋给SDA，接着再右移一位再取出来赋给SDA，以此类推循环八次
//		I2C_SCL=1;  //为1数据稳定等待下一次传输
//		I2C_SCL=0;  //数据传输完毕，让SCL为0，使下一次数据可以改变并进行传输
//	}
//}

///**
//  * @brief  I2C接收一个字节
//  * @param  无
//  * @retval 接收到的一个字节数据
//  */
//u8 I2C_ReceiveByte(void)
//{
//	u8 i,Byte=0x00;
//	I2C_SDA=1;
//	for(i=0;i<8;i++)
//	{
//		I2C_SCL=1;    //SCL为1时数据稳定，可以传输数据
//		if(I2C_SDA)   //如果SDA为1
//		{
//			Byte|=(0x80>>i); //进入该循环表示Byte接收到1，如果SDA等于0，则默认Byte接收到0，不进入循环
//		}
//		I2C_SCL=0;    //数据传输完毕，让SCL为0，使下一次数据可以改变并进行传输
//	}
//	return Byte;
//}

///**
//  * @brief  I2C发送应答
//  * @param  AckBit 应答位，0为应答，1为非应答
//  * @retval 无
//  */
//void I2C_SendAck(u8 AckBit)
//{
//	I2C_SDA=AckBit; //应答位赋给SDA
//	I2C_SCL=1;      //把SCL拉高
//	I2C_SCL=0;      //再把SCL拉低
//}

///**
//  * @brief  I2C接收应答位
//  * @param  无
//  * @retval 接收到的应答位，0为应答，1为非应答
//  */
//u8 I2C_ReceiveAck(void)
//{
//	u8 AckBit;
//	I2C_SDA=1;
//	I2C_SCL=1;
//	AckBit=I2C_SDA; //SDA为0接收应答，为0为非应答
//	I2C_SCL=0;
//	return AckBit;
//}
