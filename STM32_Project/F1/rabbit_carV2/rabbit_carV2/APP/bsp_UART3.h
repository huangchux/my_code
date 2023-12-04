#ifndef __BSP_UART3_H
#define __BSP_UART3_H
#include "AllHead.h"

// 接收缓存最大值
#define UART3_REC_MAX_LEN 66

typedef struct
{
    uint8_t *UART3_Rec_Buffer;          // 串口3接收缓存数组指针
    uint8_t UART3_Rec_Len;              // 串口3接收数据长度
    uint8_t UART3_Rec_Over_Flag;        // 串口3接收完成标志位
    uint8_t Mode_change_flag;           // 改变模式标志位 0 --> 红外寻迹  1 --> 蓝牙模式
    uint8_t Voice_mode_flag;            // 语音模式标志位

    void (*Bsp_UART3_Init)(void);       // 串口3初始化
    void (*Bsp_UART3_Handler)(void);    // 串口3处理函数    
    void (*Bsp_UART3_Send_Data)(uint8_t *, uint16_t);   // 串口3发送数据函数
} bsp_UART3_st;

extern bsp_UART3_st bsp_UART3;

#endif