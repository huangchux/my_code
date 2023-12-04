//#include "AllHead.h"

//#define I2C_Delay() {_nop_();_nop_();_nop_();_nop_();} //宏定义延时函数(一个_nop_()的时间就是一个机器周期)

///* 产生总线起始信号 */
//void I2C_Start()
//{
//	I2C_SCL = 1;  //首先确保 SDA、SCL 都是高电平
//	I2C_SDA = 1;
//	I2C_Delay();
//	I2C_SDA = 0;  //当SCL为高电平时，SDA由高变为低
//	I2C_Delay();
//	I2C_SCL = 0;  //钳住I2C总线，准备发送或接收数据(SCL为低电平时数据可以改变)
//}

///* 产生总线停止信号 */
//void I2C_Stop()
//{
//	I2C_SCL = 0;  //首先确保 SDA、SCL 都是低电平
//	I2C_SDA = 0;
//	I2C_Delay();
//	I2C_SCL = 1;  //先拉高 SCL
//	I2C_Delay();
//	I2C_SDA = 1;  //当SCL为高电平时，SDA由低变为高
//	I2C_Delay();
//}

///* I2C 总线写操作，dat-待写入字节，返回值-从机应答位的值 */
//bit I2C_Write(u8 dat)
//{
//	bit ack; //用于暂存应答位的值
//	u8 i;
//	for(i = 0;i < 8; i++)
//	{
//		if((dat & 0x80) > 0) //比较最高位 (如1011 0100 & 1000 0000 --> 1000 0000 最高位等于1 大于0)
//			I2C_SDA = 1;
//		else
//			I2C_SDA = 0;
//		dat <<= 1;           //左移一位(将次高位移到最高位)
//		I2C_Delay();
//		I2C_SCL = 1;         //为1数据稳定等待下一次传输
//		I2C_Delay();
//		I2C_SCL = 0;         //数据传输完毕，让SCL为0，使下一次数据可以改变并进行传输
//	}
//	I2C_SDA = 1;     //8 位数据发送完后，主机释放 SDA，以检测从机应答
//	I2C_Delay();
//	I2C_SCL = 1;     //拉高 SCL
//	ack = I2C_SDA;   //读取此时的 SDA 值，即为从机的应答值
//	I2C_Delay();
//	I2C_SCL = 0;     //再拉低 SCL 完成应答位，并保持住总线
//	return (~ack);   //应答值取反以符合通常的逻辑：
//}                  //0=不存在或忙或写入失败，1=存在且空闲或写入成功

///* I2C 总线读操作，并发送非应答信号，返回值-读到的字节 */
//u8 I2C_ReadNACK()
//{
//	u8 receive = 0;         //保存读取的数据
//	u8 i;
//	I2C_SDA = 1;            //首先确保主机释放 SDA
//	for(i = 0; i < 8; i++)
//	{
//		I2C_SCL = 0;
//		I2C_Delay();
//		I2C_SCL = 1;      //SCL为1时数据稳定，可以传输数据
//		receive <<= 1;    //将接收到的数据向左移动一位    (假设要传输 1001 1000，则先接收到高位1，则SDA为1，
//		if(1 == I2C_SDA)  //如果SDA为1                    receive加1，则receive为 0000 0001，之后将receive
//			receive++;      //则接收到的数据加1             向左移动一位，则receive为 0000 0010,接着传输第二位0，
//		I2C_Delay();                                   //则SDA为0，不进入if语句，receive接收到0，则receive
//		I2C_SCL = 0;//再拉低 SCL，以使从机发送出下一位    为 0000 0010，之后将receive向左移动一位，则receive为
//	}                                                //0000 0100 以此类推接收数据，直到数据传输完成则跳出循环)
//	I2C_SDA = 1;   //8 位数据发送完后，拉高 SDA，发送非应答信号
//	I2C_Delay();
//	I2C_SCL = 1;   //拉高 SCL
//	I2C_Delay();
//	I2C_SCL = 0;   //再拉低 SCL 完成非应答位，并保持住总线
//	
//	return receive;
//}

///* I2C 总线读操作，并发送应答信号，返回值-读到的字节 */
//u8 I2C_ReadACK()
//{
//	u8 receive = 0;         //保存读取的数据
//	u8 i;
//	I2C_SDA = 1;            //首先确保主机释放 SDA
//	for(i = 0; i < 8; i++)
//	{
//		I2C_SCL = 0;
//		I2C_Delay();
//		I2C_SCL = 1;      //SCL为1时数据稳定，可以传输数据
//		receive <<= 1;    //将接收到的数据向左移动一位  (假设要传输 1001 1000，则先接收到高位1，则SDA为1，
//		if(1 == I2C_SDA)  //如果SDA为1                  receive加1，则receive为 0000 0001，之后将receive
//			receive++;      //则接收到的数据加1           向左移动一位，则receive为 0000 0010,接着传输第二位0，
//		I2C_Delay();                                 //则SDA为0，不进入if语句，receive接收到0，则receive
//		I2C_SCL = 0;                                 //为 0000 0010，之后将receive向左移动一位，则receive为
//	}                                              //0000 0100 以此类推接收数据，直到数据传输完成则跳出循环)
//	I2C_SDA = 0;  //8 位数据发送完后，拉低 SDA，发送应答信号
//	I2C_Delay();
//	I2C_SCL = 1;  //拉高 SCL
//	I2C_Delay();
//	I2C_SCL = 0;  //再拉低 SCL 完成应答位，并保持住总线
//	
//	return receive;
//}
