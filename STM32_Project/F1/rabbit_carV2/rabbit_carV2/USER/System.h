#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "AllHead.h"

typedef struct
{
    void (*System_Run)(void);           // 系统运行
    void (*Task_Marks_Handler)(void);   // 任务标记函数
    void (*System_Error_Handler)(void); // 错误处理函数
} System_st;

extern System_st System;

#endif