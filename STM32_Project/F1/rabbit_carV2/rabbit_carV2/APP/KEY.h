#ifndef __KEY_H
#define __KEY_H
#include "AllHead.h"

#define KEY2    HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)

typedef enum
{
    KEY_NULL = 0x00,  // 按键未按下
    KEY2_DOWN = 0x01  // 按键2按下
} Key_Number_et;

typedef struct
{
    uint16_t Key_Long_Count;          // 按键长按计数
    uint8_t volatile Key_Flag_Arr[2]; // 按键标志位数组
    void (*KEY_Scan)(void);           // 按键扫描 --- 按键三行消抖
    void (*KEY_Handler)(void);        // 按键处理函数
} KEY_st;

extern KEY_st KEY;

#endif
