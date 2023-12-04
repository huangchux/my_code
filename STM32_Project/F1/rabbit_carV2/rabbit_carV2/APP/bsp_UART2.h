#ifndef __BSP_UART2_H
#define __BSP_UART2_H
#include "AllHead.h"

// 接收缓存最大值
#define UART2_REC_MAX_LEN 250

typedef struct
{
    uint8_t *UART2_Rec_Buf;          // 串口2接收缓存数组指针
    void (*Bsp_UART2_Init)(void);    // 串口2初始化
    void (*Bsp_UART2_Handler)(void); // 串口2处理函数
} bsp_UART2_st;

extern bsp_UART2_st bsp_UART2;

#endif
