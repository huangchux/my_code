/***************************************************************************
 * File: bsp_UART1.c
 * Author: Emily
 * Date: 2023/11/27
 * description: 串口1
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Bsp_UART1_Init(void);
static void Bsp_UART1_Handler(void);

/* Public variables==========================================================*/
uint8_t UART1_Rec_Arr[UART1_REC_MAX_LEN] = {0};  // 定义一个接收数组

bsp_UART1_st bsp_UART1 = 
{
    .UART1_Rec_Buf = UART1_Rec_Arr,
    .UART1_Rec_Len = 0,
    .UART1_Rec_Over_Flag = FALSE,

    .Bsp_UART1_Init = &Bsp_UART1_Init,
    .Bsp_UART1_Handler = &Bsp_UART1_Handler
};

/*
* @function: Bsp_UART1_Init
* @param: None
* @retval: None
* @brief: 串口1初始化
*/
static void Bsp_UART1_Init(void)
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);                               // 使能串口1空闲中断
    HAL_UART_Receive_DMA(&huart1, bsp_UART1.UART1_Rec_Buf, UART1_REC_MAX_LEN); // 使能串口1DMA接收
}

/*
* @function: Bsp_UART1_Handler
* @param: None
* @retval: None
* @brief: 串口1处理函数
*/
static void Bsp_UART1_Handler(void)
{
    if(bsp_UART1.UART1_Rec_Over_Flag)  // 如果串口1接收完成标志位置1
    {
        bsp_UART1.UART1_Rec_Over_Flag = FALSE;  // 标志位清0
        HAL_UART_Receive_DMA(&huart1, bsp_UART1.UART1_Rec_Buf, UART1_REC_MAX_LEN); // 使能串口1DMA接收
    }
}
