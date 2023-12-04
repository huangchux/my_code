#ifndef __BSP_UART1_H
#define __BSP_UART1_H
#include "AllHead.h"

// 接收缓存最大值
#define UART1_REC_MAX_LEN 66

typedef struct
{
    uint8_t *UART1_Rec_Buffer;          // 串口1接收缓存数组指针
    uint8_t UART1_Rec_Len;              // 串口1接收数据长度
    uint8_t UART1_Rec_Over_Flag;        // 串口1接收完成标志位

    void (*Bsp_UART1_Init)(void);       // 串口1初始化
    void (*Bsp_UART1_Handler)(void);    // 串口1处理函数    
} bsp_UART1_st;


extern bsp_UART1_st bsp_UART1;
#endif
