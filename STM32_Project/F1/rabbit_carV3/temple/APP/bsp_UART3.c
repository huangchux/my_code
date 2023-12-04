/***************************************************************************
 * File: bsp_UART3.c
 * Author: Emily
 * Date: 2023/12/1
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Public variables==========================================================*/
uint8_t UART3_Rec_Arr[UART1_REC_MAX_LEN] = {0};

/* Private function prototypes===============================================*/
static void Bsp_UART3_Init(void);
static void Bsp_UART3_Handler(void);
static void Bsp_UART3_Send_Data(uint8_t *str, uint8_t len);
static void Bsp_UART3_Analyze(void);

/* Public variables==========================================================*/
bsp_UART3_st bsp_UART3 = 
{
    .UART3_Rec_Buf = UART3_Rec_Arr,
    .UART3_Rec_Len = 0,
    .UART3_Rec_Over_Flag = FALSE,
    .Mode_Change_Flag = TRUE,
    .Voice_Mode_Flag = FALSE,

    .Bsp_UART3_Init = &Bsp_UART3_Init,
    .Bsp_UART3_Handler = &Bsp_UART3_Handler,
    .Bsp_UART3_Send_Data = &Bsp_UART3_Send_Data,
    .Bsp_UART3_Analyze = &Bsp_UART3_Analyze
};

/*
* @function: Bsp_UART3_Init
* @param: None
* @retval: None
* @brief: 串口3初始化
*/
static void Bsp_UART3_Init(void)
{
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);                               // 使能串口3空闲中断
    HAL_UART_Receive_DMA(&huart3, bsp_UART3.UART3_Rec_Buf, UART3_REC_MAX_LEN); // 使能串口3DMA接收
}

/*
* @function: Bsp_UART3_Handler
* @param: None
* @retval: None
* @brief: 串口3处理函数
*/
static void Bsp_UART3_Handler(void)
{
    if(bsp_UART3.UART3_Rec_Over_Flag) // 如果串口3接收完成标志位置1
    {
        bsp_UART3.UART3_Rec_Over_Flag = FALSE; // 标志位清0

        HAL_UART_Receive_DMA(&huart3, bsp_UART3.UART3_Rec_Buf, UART3_REC_MAX_LEN); // 使能串口3DMA接收
    }
}

/*
* @function: Bsp_UART3_Send_Data
* @param: None
* @retval: None
* @brief: 串口3发送数据函数
*/
static void Bsp_UART3_Send_Data(uint8_t *str, uint8_t len)
{
    HAL_UART_Transmit(&huart3, str, len, 0x0A);
}

/*
* @function: Bsp_UART3_Analyze
* @param: None
* @retval: None
* @brief: 数据解析
*/
static void Bsp_UART3_Analyze(void)
{
    /************************************  PID调试  ************************************/

    // strncmp用于比较两个字符串的前n个字符是否相等，如果这些字符完全相等，则返回0；如果不相等，则返回一个小于0或大于0的整数，表示它们的大小关系
    if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "L_Target_Speed=", strlen("L_Target_Speed=")) == 0)  // 左电机目标速度
    {
        PID.PID_Parameters_Clear();  // PID清除参数
        // 提取字符串UART3_Rec_Buffer里面=后面的浮点数 赋给结果存储地址
        Public.Str_To_Float((char*)bsp_UART3.UART3_Rec_Buf, &PID_Motor_Left.target_val); 
    }
    else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "R_Target_Speed=", strlen("R_Target_Speed=")) == 0)  // 右电机目标速度
    {
        PID.PID_Parameters_Clear();  // PID清除参数
        // 提取字符串UART3_Rec_Buffer里面=后面的浮点数 赋给结果存储地址
        Public.Str_To_Float((char*)bsp_UART3.UART3_Rec_Buf, &PID_Motor_Right.target_val); 
    }
    else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Track_P=", strlen("Track_P=")) == 0)  // 红外寻迹PID----P
    {
        PID.PID_Parameters_Clear();  // PID清除参数
        // 提取字符串UART3_Rec_Buffer里面=后面的浮点数 赋给结果存储地址
        Public.Str_To_Float((char*)bsp_UART3.UART3_Rec_Buf, &PID_HW_Tracking.Kp); 
    }
    else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Track_I=", strlen("Track_I=")) == 0)  // 红外寻迹PID----I
    {
        PID.PID_Parameters_Clear();  // PID清除参数
        // 提取字符串UART3_Rec_Buffer里面=后面的浮点数 赋给结果存储地址
        Public.Str_To_Float((char*)bsp_UART3.UART3_Rec_Buf, &PID_HW_Tracking.Ki); 
    }
    else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Track_D=", strlen("Track_D=")) == 0)  // 红外寻迹PID----D
    {
        PID.PID_Parameters_Clear();  // PID清除参数
        // 提取字符串UART3_Rec_Buffer里面=后面的浮点数 赋给结果存储地址
        Public.Str_To_Float((char*)bsp_UART3.UART3_Rec_Buf, &PID_HW_Tracking.Kd); 
    }

    /************************************  切换模式  ************************************/

    if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Enter_Bluetooth", strlen("Enter_Bluetooth")) == 0) // 进入蓝牙模式
    {
        PID.PID_Parameters_Clear();        // PID清除参数
        __Motor_Stop(0, 0);                // 停止电机
        bsp_UART3.Mode_Change_Flag = TRUE; // 改变模式标志位  1 --> 蓝牙模式
    }
    if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Enter_Track", strlen("Enter_Track")) == 0) // 进入寻迹模式
    {
        PID.PID_Parameters_Clear();         // PID清除参数
        __Motor_Stop(0, 0);                 // 停止电机
        bsp_UART3.Voice_Mode_Flag = FALSE;  // 语音模式标志位置0，退出语音模式
        bsp_UART3.Mode_Change_Flag = FALSE; // 改变模式标志位  1 --> 蓝牙模式
    }

/************************************  蓝牙模式下的蓝牙控制  ************************************/

    if(bsp_UART3.Mode_Change_Flag)
    {
        if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Go", strlen("Motor_Go")) == 0) // 前进
        {
            PID.PID_Parameters_Clear();         // PID清除参数
            __Motor_Go(1,1); // 前进

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = FALSE; // 关闭左右耳朵继电器标志位
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);  // 关左右耳朵的灯
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Back", strlen("Motor_Back")) == 0) // 后退
        {
            PID.PID_Parameters_Clear();         // PID清除参数
            __Motor_Back(1,1); // 后退

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);  // 关左右耳朵的灯
            Relay.Relay_Control(Relay_Right, RELAY_OFF);

            Relay.Relay_Left_Flip_Flag = TRUE; // 左右耳朵继电器标志位置1
            Relay.Relay_Right_Flip_Flag = TRUE;
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Left", strlen("Motor_Left")) == 0) // 向左转弯
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Left(0.5, 1);       // 向左转弯

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = TRUE; // 左继电器翻转标志位置1
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Right", strlen("Motor_Right")) == 0) // 向右转弯
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Right(1, 0.5);      // 向右转弯

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = FALSE; // 右继电器翻转标志位置1
            Relay.Relay_Right_Flip_Flag = TRUE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Inplace_Left", strlen("Motor_Inplace_Left")) == 0) // 原地左转
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Inplace_Left(1, 1); // 原地左转

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = TRUE; // 左继电器翻转标志位置1
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Inplace_Right", strlen("Motor_Inplace_Right")) == 0) // 原地右转
        {
            PID.PID_Parameters_Clear();  // PID清除参数
            __Motor_Inplace_Right(1, 1); // 原地右转

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;

            Relay.Relay_Left_Flip_Flag = FALSE; // 右继电器翻转标志位置1
            Relay.Relay_Right_Flip_Flag = TRUE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);
        }
        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Motor_Stop", strlen("Motor_Stop")) == 0) // 停止
        {
            PID.PID_Parameters_Clear(); // PID清除参数
            __Motor_Stop(0, 0);         // 停止

            Relay.Relay_Left_Count = 0;  // 计数值清0
            Relay.Relay_Right_Count = 0;
            
            Relay.Relay_Left_Flip_Flag = FALSE; // 关闭左右耳朵继电器标志位
            Relay.Relay_Right_Flip_Flag = FALSE;

            Relay.Relay_Control(Relay_Left, RELAY_OFF);  // 关左右耳朵的灯
            Relay.Relay_Control(Relay_Right, RELAY_OFF);
        }

        else if(strncmp((const char*)bsp_UART3.UART3_Rec_Buf, "Switch_Voice_Mode", strlen("Switch_Voice_Mode")) == 0) // 选择语音模式
        {
            static uint8_t Voice_Change_Flag = FALSE;
            Voice_Change_Flag = !Voice_Change_Flag;
            if(Voice_Change_Flag)
            {
                bsp_UART3.Voice_Mode_Flag = TRUE;  // 语音模式标志位置1
            }   
            else
            {
                Voice_Change_Flag = FALSE;  // 语音模式标志位置0
            }
        }

        else if (strncmp((char *)bsp_UART3.UART3_Rec_Buf, "Relay_ON/OFF", strlen("Relay_ON/OFF")) == 0) // 打开 or 关闭继电器White
        {
            static uint8_t Relay_Flag_1 = FALSE; // 继电器状态标志位
            Relay_Flag_1 = !Relay_Flag_1;        // 继电器状态标志位取反
            Relay.Relay_Left_Count = 0;
            Relay.Relay_Right_Count = 0;

            if (Relay_Flag_1)                    // 继电器状态标志位为1
            {
				__Relay_All_Open();  // 全部继电器打开
            }
            else // 继电器状态标志位为0
            {
				__Relay_All_Close();  // 全部继电器关闭
            } 
        }

        else if (strncmp((char *)bsp_UART3.UART3_Rec_Buf, "Relay_Flip", strlen("Relay_Flip")) == 0) // 翻转继电器
        {
            static uint8_t Relay_Flag_2 = FALSE; // 继电器状态标志位
            Relay_Flag_2 = !Relay_Flag_2;        // 继电器状态标志位取反

            if (Relay_Flag_2) // 继电器状态标志位为1
            {
                Relay.Relay_Flip_Count = 0;   // 继电器翻转计数清0
                Relay.Relay_Flip_Flag = TRUE; // 继电器翻转标志位置1
            }
            else // 继电器状态标志位为0
            {
                Relay.Relay_Flip_Flag = FALSE; // 继电器翻转标志位清0
                __Relay_All_Close();           // 全部继电器关闭
            }
        }

         /***********************速度调整*************************/
         else if (strncmp((char *)bsp_UART3.UART3_Rec_Buf, "Change_Speed", strlen("Change_Speed")) == 0) // 改变速度
         {
            Motor.base_speed = (Motor.base_speed - 0 + 1) % (3 - + 1) + 0; // 速度调整(从0增加到3，到3之后就变为0)
         }
    }
}
 