#ifndef __LED_H
#define __LED_H

typedef enum
{
    LED_ON = 1,
    LED_OFF = 0
}LED_State_et;

typedef struct
{
    void (*LED_Contral)(LED_State_et); // 控制LED单个灯点亮
    void (*LED_Flip)(void);            // LED翻转
}LED_st;  // 类型名

extern LED_st LED; // 外部可调用

#endif
