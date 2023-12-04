#include "AllHead.h"

bit flag = 0;
u8 rec_buf[10];

/* 串口配置函数，baud-通信波特率 */
void UAER_Init(u16 baud)
{
	  SCON = 0x50;  //配置串口为模式 1  0101 0000 --> 0x50
    TMOD &= 0x0F; //清零 T1 的控制位
    TMOD |= 0x20; //配置 T1 为模式 2  0010 0000 --> 0x20
    TH1 = 256 - (11059200 / 12 / 32) / baud; //计算 T1 重载值
    TL1 = TH1;  //初值等于重载值
    
    ET1 = 0;    //禁止 T1 中断
    TR1 = 1;    //启动 T1
}


/* 串口中断服务函数 */
void UART() interrupt 4
{
	u8 rec_dat = 0;
	static u8 i = 0;
	if((1 == RI) && (0 == flag))  //接收到新字节
	{
		rec_dat = SBUF;
		if((rec_dat == '\n') && (rec_buf[i - 1] == '\r'))
		{
			rec_buf[i - 1] = '\0'; // \r 的位置等于结束符
			i = 0;
			flag = 1;
		}
		else
		{
			rec_buf[i] = rec_dat;
			i++;
		}
	}
	RI = 0;
}


///* 串口数据写入，即串口发送函数，buf-待发送数据的指针，len-指定的发送长度 */
//void Uart_Write(u8 *buf, u8 len)
//{
//	while(len--)  //循环发送所有字节
//	{
//		flagTxd = 0;      //清零发送标志
//		SBUF = *buf++;    //发送一个字节数据
//		while(!flagTxd);  //等待该字节发送完成
//	} 
//}

///* 串口数据读取函数，buf-接收指针，len-指定的读取长度，返回值-实际读到的长度 */
//u8 UartRead(u8 *buf, u8 len)
//{
//	u8 i = 0;
//	if(len > cntRxd) //指定读取长度大于实际接收到的数据长度时
//	{
//		len = cntRxd;  //读取长度设置为实际接收到的数据长度
//	}
//	for(i = 0; i < len; i++) //拷贝接收到的数据到接收指针上
//	{
//		*buf++ = bufRxd[i];
//	}
//	cntRxd = 0; //接收计数器清零
//	return len; //返回实际读取长度
//}

///* 串口接收监控，由空闲时间判定帧结束，需在定时中断中调用，ms-定时间隔 */
//void Uart_RxMonitor(u8 ms)
//{
//	static u8 cntbkp = 0;   //前一次接收到数据的长度
//  static u8 idletmr = 0;  //空闲计时

//	if(cntRxd > 0)          //接收计数器大于零时，监控总线空闲时间
//	{
//		if(cntbkp != cntRxd)  //接收计数器改变，即刚接收到数据时，清零空闲计时(与前一次接收到的数据长度不一样代表接收到数据)
//		{
//			cntbkp = cntRxd;    //把本次接收到数据赋给前一次接收到的数据
//			idletmr = 0;
//		}
//		else                  //接收计数器未改变，即总线空闲时，累积空闲时间
//	  {
//		  if(idletmr < 30)    //空闲计时小于 30ms 时，持续累加
//		  {
//			  idletmr += ms;
//			  if(idletmr >= 30) //空闲时间达到 30ms 时，即判定为一帧接收完毕
//			  {
//				  flagFrame = 1;  //设置帧接收完成标志
//			  }
//		  }
//	  }
//	}
//	else
//		cntbkp = 0;
//}

///* 串口驱动函数，监测数据帧的接收，调度功能函数，需在主循环中调用 */
//void Uart_Driver()
//{
//	u8 len;
//  u8 pdata buf[40]; //数据缓冲区
//	if(flagFrame)     //有命令到达时，读取处理该命令
//	{
//		flagFrame = 0;
//		len = UartRead(buf,sizeof(buf)); //将接收到的命令读取到缓冲区中
//		Uart_Action(buf, len);           //传递数据帧，调用动作执行函数
//	}
//}