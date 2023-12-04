#ifndef _UART_H_
#define _UART_H_

extern void UAER_Init(u16 baud);
extern void Uart_Write(u8 *buf, u8 len);
u8 UartRead(u8 *buf, u8 len);
extern void Uart_RxMonitor(u8 ms);
extern void Uart_Driver();
extern void Uart_Action(u8 *buf, u8 len);


extern u8 rec_buf[10];
extern bit flag;
#endif