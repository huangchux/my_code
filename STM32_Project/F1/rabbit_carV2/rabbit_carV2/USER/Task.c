/***************************************************************************
 * File: Task.c
 * Author: Emily
 * Date: 2023/11/11
 * description: 任务管理
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void TasksHandler_2MS(void);
static void TasksHandler_10MS(void);
static void TasksHandler_50MS(void);
static void TasksHandler_100MS(void);
static void TasksHandler_200MS(void);
static void TasksHandler_500MS(void);
static void TasksHandler_1S(void);

/* Public variables==========================================================*/
Task_st Task[] = 
{
    {FALSE, 2, 2, TasksHandler_2MS},
    {FALSE, 10, 10, TasksHandler_10MS},
    {FALSE, 50, 50, TasksHandler_50MS},  
	{FALSE, 100, 100, TasksHandler_100MS},  
    {FALSE, 200, 200, TasksHandler_200MS},    
    {FALSE, 500, 500, TasksHandler_500MS},
    {FALSE, 1000, 1000, TasksHandler_1S}
};

/* Public variables==========================================================*/
uint8_t ucTask_MAX = sizeof(Task) / sizeof(Task[0]);    // 计算数组元素

static void TasksHandler_2MS(void)
{
    bsp_UART3.Bsp_UART3_Handler();
    bsp_UART2.Bsp_UART2_Handler();
}

static void TasksHandler_10MS(void)
{
    KEY.KEY_Handler();
}

static void TasksHandler_50MS(void)
{
    bsp_UART1.Bsp_UART1_Handler();
}

static void TasksHandler_100MS(void)
{
#if 0
    uint8_t arr[20];
    // sprintf((char*)arr, "%.1f, %.1f\r\n", Encoder.Encoder_Left_Speed, PID_Motor_Left.target_val);   // 左电机
    // sprintf((char*)arr, "%.1f, %.1f\r\n", Encoder.Encoder_Right_Speed, PID_Motor_Right.target_val);
    bsp_UART3.Bsp_UART3_Send_Data(arr, strlen((char*)arr));
#endif    
}

static void TasksHandler_200MS(void)
{
    Menu.Menu_Handler();
}

static void TasksHandler_500MS(void)
{
	LED.LED_Flip();	// 系统运行灯
}

static void TasksHandler_1S(void)
{
    uint8_t arr[20];

    sprintf((char*)arr, "Base Speed: %d\r\n",Motor.base_speed); 
    bsp_UART3.Bsp_UART3_Send_Data(arr, strlen((char*)arr));        // 打印基础速度

   if (bsp_UART3.Voice_mode_flag)    // 进入语音模式标志位
   {
     bsp_UART3.Bsp_UART3_Send_Data((uint8_t*)"已进入语音模式", strlen((char*)"已进入语音模式"));
   } 
   else
   {
    bsp_UART3.Bsp_UART3_Send_Data((uint8_t*)"未进入语音模式", strlen((char*)"未进入语音模式"));
   }
}

