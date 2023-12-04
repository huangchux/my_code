/***************************************************************************
 * File: bsp_UART2.c
 * Author: Emily
 * Date: 2023/11/21
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private variables=========================================================*/
uint8_t UART2_Rec_Arr[UART2_REC_MAX_LEN] = {0}; // 定义一个接收数组

///* Private function prototypes===============================================*/
static void Bsp_UART2_Init(void);
static void Bsp_UART2_Handler(void);
///* Public variables==========================================================*/
bsp_UART2_st bsp_UART2 = 
{
    .UART2_Rec_Buf = UART2_Rec_Arr,
    .Bsp_UART2_Init = &Bsp_UART2_Init,
    .Bsp_UART2_Handler = &Bsp_UART2_Handler
};

/*
* @function: Bsp_UART2_Init
* @param: None
* @retval: None
* @brief: 串口2初始化
*/
static void Bsp_UART2_Init(void)
{
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);                               // 使能串口2空闲中断
    HAL_UART_Receive_DMA(&huart2, bsp_UART2.UART2_Rec_Buf, UART2_REC_MAX_LEN); // 使能串口2DMA接收
}

/*
* @function: Bsp_UART2_Handler
* @param: None
* @retval: None
* @brief: 串口2处理函数
*/
static void Bsp_UART2_Handler(void)
{
    if(bsp_UART3.Voice_mode_flag) // 进入语音模式
    {
        if (Voice_Motor_Go == Voice.Voice_Control_Status) // 【前进】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Go(1, 1);           // 前进

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;   

            Relay.Relay_Left_Flip_Flag = FALSE;  // 关闭左右耳朵继电器标志位
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);  // 关左右耳朵的灯
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if (Voice_Motor_Back == Voice.Voice_Control_Status) // 【后退】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Back(1, 1);         // 后退

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);  // 关左右耳朵的灯
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
            
            Relay.Relay_Left_Flip_Flag = TRUE;   // 打开左右耳朵继电器标志位
            Relay.Relay_Right_Flip_Flag = TRUE;
        }
        else if (Voice_Motor_Left == Voice.Voice_Control_Status) // 【向左转弯】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Left(0.5, 1);       // 向左转弯

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = TRUE;
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if (Voice_Motor_Right == Voice.Voice_Control_Status) // 【向右转弯】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Right(1, 0.5);      // 向右转弯

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Right_Flip_Flag = TRUE;
            Relay.Relay_Left_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);
        }
        else if (Voice_Motor_Inplace_Left == Voice.Voice_Control_Status) // 【原地左转】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Inplace_Left(1, 1); // 原地左转

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;  

            Relay.Relay_Left_Flip_Flag = TRUE;
            Relay.Relay_Right_Flip_Flag = FALSE;
            
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if (Voice_Motor_Inplace_Right == Voice.Voice_Control_Status) // 【原地右转】
        {
            PID.PID_Parameters_Clear();  // PID清除参数
            __Motor_Inplace_Right(1, 1); // 原地右转

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Right_Flip_Flag = TRUE;
            Relay.Relay_Left_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);
        }   
        else if (Voice_Motor_Stop == Voice.Voice_Control_Status) // 【停止】
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Stop(0, 0);         // 停止

            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = FALSE;
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if (Voice_Relay_ON == Voice.Voice_Control_Status) // 【开灯】
        {
            Relay.Relay_Flip_Flag = FALSE;                    // 继电器翻转标志位清0
            __Relay_All_Open();
        }
        else if (Voice_Relay_OFF == Voice.Voice_Control_Status) // 【关灯】
        {
            Relay.Relay_Flip_Flag = FALSE;                     // 继电器翻转标志位清0
            __Relay_All_Close();
        }
        else if (Voice_Relay_Flip == Voice.Voice_Control_Status) // 【灯光闪烁】
        {
            Relay.Relay_Flip_Count = 0;          // 继电器翻转计数清0
            Relay.Relay_Flip_Flag = TRUE;        // 继电器翻转标志位置1
            Relay.Relay_Left_Flip_Flag = FALSE;  // 左转关闭
            Relay.Relay_Right_Flip_Flag = FALSE; // 右转关闭
        }           
    }
    Voice.Voice_Control_Status = Voice_Not_Control;    //  未进入语音控制命令    
}