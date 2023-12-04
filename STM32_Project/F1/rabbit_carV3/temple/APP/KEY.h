#ifndef __KEY_H
#define __KEY_H

#define KEY1    HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2    HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)

typedef enum
{
    KEY_NULL = 0x00,   // 按键未按下
    KEY1_DOWN = 0x01,  // 按键1按下
    KEY2_DOWN = 0x02   // 按键2按下
}Key_Number_et;

typedef struct
{
    uint16_t Key_Long_Count;           // 按键长按计数
    uint16_t volatile Key_Flag_Arr[4]; // 按键标志位数组
    void (*Key_Scan)(void);            // 按键扫描 --- 按键三行消抖
    void (*KEY_Handler)(void);         // 按键处理函数
}KEY_st;

extern KEY_st KEY;

#endif
