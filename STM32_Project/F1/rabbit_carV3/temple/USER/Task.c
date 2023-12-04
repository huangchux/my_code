/***************************************************************************
 * File: Task.c
 * Author: Emily
 * Date: 2023/11/20
 * description: 任务管理
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void TasksHandler_2Ms(void);
static void TasksHandler_10Ms(void);
static void TasksHandler_50Ms(void);
static void TasksHandler_200Ms(void);
static void TasksHandler_500Ms(void);
static void TasksHandler_1s(void);

/* Public variables==========================================================*/
Task_st Task[] = 
{
    {FALSE, 2, 2, TasksHandler_2Ms},
    {FALSE, 10, 10, TasksHandler_10Ms},
    {FALSE, 50, 50, TasksHandler_50Ms},
    {FALSE, 200, 200, TasksHandler_200Ms},
    {FALSE, 500, 500, TasksHandler_500Ms},
    {FALSE, 1000, 1000, TasksHandler_1s},
};

/* Public variables==========================================================*/
uint8_t ucTask_MAX = sizeof(Task) / sizeof(Task[0]); // 计算数组元素  数组全部元素的字节 / 第一个元素的字节 = 数组里面有多少个元素

static void TasksHandler_2Ms(void)
{
    bsp_UART3.Bsp_UART3_Handler();
    bsp_UART2.Bsp_UART2_Handler();
}

static void TasksHandler_10Ms(void)
{
    KEY.KEY_Handler();
}

static void TasksHandler_50Ms(void)
{
    bsp_UART1.Bsp_UART1_Handler();
}

static void TasksHandler_200Ms(void)
{
    Menu.Menu_Handler();
}

static void TasksHandler_500Ms(void)
{
    LED.LED_Flip();  // 系统运行灯
}

static void TasksHandler_1s(void)
{
    uint8_t arr[20];

    sprintf((char *)arr, "Base_Speed: %d\r\n", Motor.base_speed);
    bsp_UART3.Bsp_UART3_Send_Data(arr, strlen((char *)arr));  // 打印基础速度

    if(bsp_UART3.Voice_Mode_Flag)  // 进入语音模式标志位
    {
        bsp_UART3.Bsp_UART3_Send_Data((uint8_t*)"已进入语音模式", strlen((char*)"已进入语音模式"));
    }
    else
    {
        bsp_UART3.Bsp_UART3_Send_Data((uint8_t*)"未进入语音模式", strlen((char*)"未进入语音模式"));
    }
}
