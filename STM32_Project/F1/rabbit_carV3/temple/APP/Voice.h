#ifndef __VOICE_H
#define __VOICE_H

// 协议是4个字节
#define Voice_Protocol_Data_LEN (uint8_t)4

typedef enum
{
    Voice_Not_Control = 0,         // 未进入语音控制命令
    Voice_Motor_Go = 1,            // 前进
    Voice_Motor_Back = 2,          // 后退
    Voice_Motor_Left = 3,          // 向左转弯
    Voice_Motor_Right = 4,         // 向右转弯
    Voice_Motor_Inplace_Left = 5,  // 原地左转
    Voice_Motor_Inplace_Right = 6, // 原地右转
    Voice_Motor_Stop = 7,          // 停止
    Voice_Relay_ON = 8,            // 打开继电器
    Voice_Relay_OFF = 9,           // 关闭继电器
    Voice_Relay_Flip = 10          // 翻转继电器
} Voice_state_et;

typedef struct
{
    uint8_t Voice_Control_Status;         // 语音控制状态
    void (*Voice_Protocol_Analyze)(void); // 语音模块协议解析
} Voice_st;

extern Voice_st Voice;

#endif
