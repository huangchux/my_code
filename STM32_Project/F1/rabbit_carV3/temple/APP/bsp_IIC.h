#ifndef __BSP_IIC_H
#define __BSP_IIC_H
#include "gpio.h"

// 置1 / 清0 SCL管脚
#define SET_SCL(PIN_PORT, PIN)  HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SCL(PIN_PORT, PIN)  HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// 置1 / 清0 SDA管脚
#define SET_SDA(PIN_PORT, PIN)  HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_SET)
#define CLR_SDA(PIN_PORT, PIN)  HAL_GPIO_WritePin(PIN_PORT, PIN, GPIO_PIN_RESET)
// 读取SDA管脚状态
#define READ_SDA(PIN_PORT, PIN) HAL_GPIO_ReadPin(PIN_PORT, PIN)

// 定义枚举类型
typedef enum
{
    ACK = GPIO_PIN_RESET,
    NACK = GPIO_PIN_SET
} ACK_Value_et;

// IIC注册结构体
typedef struct
{
    GPIO_TypeDef *SCL_GPIOx; // SCL端口组
    uint16_t SCL_GPIO_Pin;   // SCL引脚
    GPIO_TypeDef *SDA_GPIOx; // SDA端口组
    uint16_t SDA_GPIO_Pin;   // SDA引脚
} IIC_Parameter_st;

typedef struct
{
    void (*IIC_Registered)(IIC_Parameter_st *, GPIO_TypeDef *, uint16_t, GPIO_TypeDef *, uint16_t); // IIC注册
    void (*IIC_Start)(IIC_Parameter_st *);                                                          // IIC起始信号
    void (*IIC_Stop)(IIC_Parameter_st *);                                                           // IIC停止信号
    ACK_Value_et (*IIC_Write_Byte)(IIC_Parameter_st *, uint8_t);                                    // IIC写字节
    uint8_t (*IIC_Read_Byte)(IIC_Parameter_st *, ACK_Value_et);                                     // IIC读字节
    uint8_t (*IIC_Write_Buffer)(IIC_Parameter_st *, uint8_t, uint8_t, uint32_t, uint8_t *);         // IIC写一串数据
    uint8_t (*IIC_Read_Buffer)(IIC_Parameter_st *, uint8_t, uint8_t, uint32_t, uint8_t *);          // IIC读一串数据
} bsp_IIC_st;

extern bsp_IIC_st bsp_IIC;


#endif
