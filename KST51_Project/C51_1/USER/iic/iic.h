#ifndef _IIC_H_
#define _IIC_H_

#include "AllHead.h"

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


//void iic_start(void);
//void iic_stop(void);
//void iic_ack(void);
//void iic_nack(void);
//u8 iic_wait_ack(void);
//void iic_write_byte(u8 dat);
//u8 iic_read_byte(u8 ack);


void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(u8 Byte);
u8 I2C_ReceiveByte(void);
void I2C_SendAck(u8 AckBit);
u8 I2C_ReceiveAck(void);
#endif
