#ifndef __MYIIC_H
#define __MYIIC_H
#include "gpio.h"


// ��1 / ��0 SCL�ܽ�
#define SET_SCL(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SCL(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// ��1 / ��0 SDA�ܽ�
#define SET_SDA(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SDA(PIN_PORT, PIN) HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// ��ȡSDA�ܽ�״̬
#define READ_SDA(PIN_PORT, PIN) HAL_GPIO_ReadPin(PIN_PORT, PIN)

// ����ö������
typedef enum
{
	ACK = GPIO_PIN_RESET,
	NACK = GPIO_PIN_SET,
} ACK_Value_t;

// IICע��ṹ��
typedef struct 
{
	GPIO_TypeDef *SCL_GPIOx; // SCL�˿���
	uint16_t SCL_GPIO_Pin;	 // SCL����
	GPIO_TypeDef *SDA_GPIOx; // SDA�˿���
	uint16_t SDA_GPIO_Pin;	 // SDA����
} IIC_Data_t;

typedef struct
{
	void (*IIC_Registered)(IIC_Data_t *, GPIO_TypeDef *, uint16_t, GPIO_TypeDef *, uint16_t); // IICע��
	void (*IIC_Start)(IIC_Data_t *);														  // IIC��ʼ�ź�
	void (*IIC_Stop)(IIC_Data_t *);															  // IICֹͣ�ź�
	ACK_Value_t (*IIC_Write_Byte)(IIC_Data_t *, uint8_t);									  // IICд�ֽ�
	uint8_t (*IIC_Read_Byte)(IIC_Data_t *, ACK_Value_t);									  // IIC���ֽ�
	uint8_t (*IIC_Write_Buffer)(IIC_Data_t *, uint8_t, uint8_t, uint32_t, uint8_t *);		  // IICдһ������
	uint8_t (*IIC_Read_Buffer)(IIC_Data_t *, uint8_t, uint8_t, uint32_t, uint8_t *);		  // IIC��һ������
} IIC_Soft_t;

extern IIC_Soft_t IIC_Soft;

#endif
