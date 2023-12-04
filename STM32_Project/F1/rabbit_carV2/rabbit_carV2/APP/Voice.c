/***************************************************************************
 * File: Voice.c
 * Author: Emily
 * Date: 2023/11/21
 * description: 语音识别
 -----------------------------------
协议：
    语音识别开发板发送给STM32协议格式：【0xAA 0xXX 0xXX 0xBB】
    STM32发送给语音识别开发板是字符串形式...
 -----------------------------------
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Voice_Protocol_Analyze(void);

/* Public variables==========================================================*/
Voice_st Voice = 
{
    .Voice_Control_Status = 0,
    .Voice_Protocol_Analyze = &Voice_Protocol_Analyze,
};

/*
* @function: Voice_Protocol_Analyze
* @param: None
* @retval: None
* @brief: 语音模块协议解析
*/
static void Voice_Protocol_Analyze(void)
{
    uint8_t i,index = 0;

    HAL_UART_DMAStop(&huart2);  // 在解析协议时停止DMA接收

    // 过滤数据
    for(i = 0; i < UART2_REC_MAX_LEN; i++)
    {
        if(0 == index) // 起始数据
        {
            // 检测起始数据是不是0xAA
            if(*(bsp_UART2.UART2_Rec_Buf + i) != 0xAA) // 判断接收的第一个数据是不是0xAA
            {
                continue;  // 如果接收的第一个数据不是0xAA则跳过这个数据 直到第一个数据为0xAA则跳出语句
            }
        }
        *(bsp_UART2.UART2_Rec_Buf + index) = *(bsp_UART2.UART2_Rec_Buf + i); // 如果第一个数据为0xAA则开始接收数据

        // 已读4个字节
        if(index == Voice_Protocol_Data_LEN)  //接收4个数据之后就跳出
        {
            break;
        }
        index++; 
    }

    // 进行数据处理
    if ((*(bsp_UART2.UART2_Rec_Buf + 1) == 0x01) && (*(bsp_UART2.UART2_Rec_Buf + 3) == 0xBB))
    {
        switch (*(bsp_UART2.UART2_Rec_Buf + 2)) // 判断第3个元素
        {
            //与语音模块发出的请求数据命令格式一样则根据语音模块接收指令执行相应操作
            case 0x00:
            {
                Voice.Voice_Control_Status = Voice_Motor_Go; // 前进
                break;
            }
            case 0x01:
            {
                Voice.Voice_Control_Status = Voice_Motor_Back; // 后退
                break;
            }
            case 0x02:
            {
                Voice.Voice_Control_Status = Voice_Motor_Left; // 向左转弯
                break;
            }
            case 0x03:
            {
                Voice.Voice_Control_Status = Voice_Motor_Right; // 向右转弯
                break;
            }
            case 0x04:
            {
                Voice.Voice_Control_Status = Voice_Motor_Inplace_Left; // 原地左转
                break;
            }
            case 0x05:
            {
                Voice.Voice_Control_Status = Voice_Motor_Inplace_Right; // 原地右转
                break;
            }
            case 0x06:
            {
                Voice.Voice_Control_Status = Voice_Motor_Stop; // 停止
                break;
            }
            case 0x07:
            {
                Voice.Voice_Control_Status = Voice_Relay_ON; // 打开继电器
                break;
            }
            case 0x08:
            {
                Voice.Voice_Control_Status = Voice_Relay_OFF; // 关闭继电器
                break;
            }
            case 0x09:
            {
                Voice.Voice_Control_Status = Voice_Relay_Flip; // 继电器翻转
                break;
            }                                    
            default: 
            {
                Voice.Voice_Control_Status = Voice_Not_Control; // 未进入语音控制命令
                break;
            }
        }
    }
}