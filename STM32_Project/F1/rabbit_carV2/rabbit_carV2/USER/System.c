/***************************************************************************
 * File: System.c
 * Author: Emily
 * Date: 2023/11/11
 * description: 系统函数
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void System_Run(void);
static void Task_Marks_Handler(void);
static void Task_Pro_Handler(void);
static void System_Error_Handler(void);

/* Public variables==========================================================*/
System_st System = 
{
    .System_Run = &System_Run,
    .Task_Marks_Handler = &Task_Marks_Handler,
    .System_Error_Handler = &System_Error_Handler
};

/*
* @function: System_Run
* @param: None
* @retval: None
* @brief: 系统运行
*/
static void System_Run(void)
{
    Task_Pro_Handler();
}

/*
* @function: Task_Marks_Handler
* @param: None
* @retval: None
* @brief: 任务标记函数
*/
static void Task_Marks_Handler(void)
{
    for (uint8_t i = 0; i < ucTask_MAX; i++)
    {
        if (Task[i].Task_Cnt)   // 表示任务要执行的时间还没到
        {
            Task[i].Task_Cnt--;
            if (0 == Task[i].Task_Cnt)  // 表示任务要执行
            {
                Task[i].Task_Cnt = Task[i].Task_Timer;  // 重载值
                Task[i].Task_Status = TRUE; // 执行任务标志位置1
            }
        }
    }
}

/*
* @function: Task_Pro_Handler
* @param: None
* @retval: None
* @brief: 任务处理函数
*/
static void Task_Pro_Handler(void)
{
    for (uint8_t i = 0; i < ucTask_MAX; i++)
    {
        if (Task[i].Task_Status)    // 判断状态(TRUE表示执行函数)
        {
            Task[i].Task_Status = FALSE;
            Task[i].Task_Hook();    // 执行对应函数
        }
    }
}

/*
* @function: System_Error_Handler
* @param: None
* @retval: None
* @brief:错误处理函数
*/
static void System_Error_Handler(void)
{
    for(;;)
    {
        // 死循环导致不能喂狗导致看门狗系统复位！！！
    }
}