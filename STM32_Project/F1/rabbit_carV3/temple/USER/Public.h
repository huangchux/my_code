#ifndef __PUBLIC_H
#define __PUBLIC_H

typedef enum
{
    FALSE = 0,
    TRUE = 1
} FlagStatus_et;

typedef struct
{
    void (*Public_Delay_ms)(uint16_t ms);        // ms延时
    void (*Public_Delay_us)(uint16_t us);        // us延时
    void (*Str_To_Float)(const char *, float *); // 提取字符串里面=后面的浮点数
} Public_st;

extern Public_st Public;

#endif