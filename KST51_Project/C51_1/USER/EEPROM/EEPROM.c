#include "AllHead.h"

///*******************************************************************************
//* 函 数 名 : EEPROM_write_one_byte
//* 函数功能 : 在 EEPROM 指定地址写入一个数据
//* 输 入 : addr:写入数据的目的地址
//          dat:要写入的数据
//* 输 出 : 无
//*******************************************************************************/
//void EEPROM_write_one_byte(u8 addr,u8 dat)
//{
//	iic_start();
//	iic_write_byte(0xA0);  //发送写命令(前面4位固定，后面三位接gnd所以是0)
//	iic_wait_ack();
//	iic_write_byte(addr);  //发送写地址
//	iic_wait_ack();
//	iic_write_byte(dat);   //发送字节
//	iic_wait_ack();
//	iic_stop();            //产生一个停止条件
//	Delay1ms(10);
//}


///*******************************************************************************
//* 函 数 名 : EEPROM_read_one_byte
//* 函数功能 : 在 EEPROM 指定地址读出一个数据
//* 输 入 : addr:开始读数的地址
//* 输 出 : 读到的数据
//*******************************************************************************/
//u8 EEPROM_read_one_byte(u8 addr)
//{
//	u8 receive = 0;
//	iic_start();
//	iic_write_byte(0xA0);  //发送写命令(寻找从机) 最后一位为0表示主机向从机写数据
//	iic_wait_ack();
//	iic_write_byte(addr);  //在EEPROM指定一个地址(将要接收的数据存放到这个地址)
//	iic_wait_ack();
//	iic_start();           //再次启动总线
//  iic_write_byte(0xA1);	 //进入接收模式   最后一位为1表示主机由从机读数据
//	iic_wait_ack();
//	receive = iic_read_byte(addr);  //读取字节
//	iic_stop();            //产生一个停止条件
//	return receive;        //返回读取的数据
//}




///**
//  * @brief  AT24C02写入一个字节
//  * @param  WordAddress 要写入字节的地址
//  * @param  Data 要写入的数据
//  * @retval 无
//  */
//void EEPROM_WriteByte(u8 addr,u8 Data)
//{
//	I2C_Start();
//	I2C_SendByte(0xA0);  //发送写命令(前面4位固定，后面三位接gnd所以是0)
//	I2C_ReceiveAck();
//	I2C_SendByte(addr);  //发送写地址
//	I2C_ReceiveAck();
//	I2C_SendByte(Data);  //发送字节
//	I2C_ReceiveAck();
//	I2C_Stop();          //产生一个停止条件
//}

///**
//  * @brief  AT24C02读取一个字节
//  * @param  WordAddress 要读出字节的地址
//  * @retval 读出的数据
//  */
//u8 EEPROM_ReadByte(u8 addr)
//{
//	u8 Data;
//	I2C_Start();
//	I2C_SendByte(0xA0);  //发送写命令(寻找从机) 最后一位为0表示主机向从机写数据
//	I2C_ReceiveAck();
//	I2C_SendByte(addr);  //在EEPROM指定一个地址(将要接收的数据存放到这个地址)
//	I2C_ReceiveAck();
//	I2C_Start();         //再次启动总线
//	I2C_SendByte(0xA1);  //进入接收模式   最后一位为1表示主机由从机读数据
//	I2C_ReceiveAck();
//	Data=I2C_ReceiveByte();  //读取字节
//	I2C_SendAck(1);
//	I2C_Stop();          //产生一个停止条件
//	return Data;         //返回读取的数据
//}