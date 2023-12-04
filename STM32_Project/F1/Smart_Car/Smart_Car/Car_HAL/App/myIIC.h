#ifndef __MYIIC_H
#define __MYIIC_H
#include "gpio.h"


// 置1 / 清0 SCL管脚
#define SET_SCL(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SCL(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// 置1 / 清0 SDA管脚
#define SET_SDA(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SDA(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// 读取SDA管脚状态
#define READ_SDA(PIN_PORT, PIN) HAL_GPIO_ReadPin(PIN_PORT, PIN)

// 定义枚举类型
typedef enum
{
	ACK = GPIO_PIN_RESET,
	NACK = GPIO_PIN_SET,
} ACK_Value_t;

// IIC注册结构体
typedef struct 
{
	GPIO_TypeDef *SCL_GPIOx; // SCL端口组
	uint16_t SCL_GPIO_Pin;	 // SCL引脚
	GPIO_TypeDef *SDA_GPIOx; // SDA端口组
	uint16_t SDA_GPIO_Pin;	 // SDA引脚
} IIC_Data_t;

typedef struct
{
	void (*IIC_Registered)(IIC_Data_t *, GPIO_TypeDef *, uint16_t, GPIO_TypeDef *, uint16_t); // IIC注册
	void (*IIC_Start)(IIC_Data_t *);														  // IIC起始信号
	void (*IIC_Stop)(IIC_Data_t *);															  // IIC停止信号
	ACK_Value_t (*IIC_Write_Byte)(IIC_Data_t *, uint8_t);									  // IIC写字节
	uint8_t (*IIC_Read_Byte)(IIC_Data_t *, ACK_Value_t);									  // IIC读字节
	uint8_t (*IIC_Write_Buffer)(IIC_Data_t *, uint8_t, uint8_t, uint32_t, uint8_t *);		  // IIC写一串数据
	uint8_t (*IIC_Read_Buffer)(IIC_Data_t *, uint8_t, uint8_t, uint32_t, uint8_t *);		  // IIC读一串数据
} IIC_Soft_t;

extern IIC_Soft_t IIC_Soft;

#endif
