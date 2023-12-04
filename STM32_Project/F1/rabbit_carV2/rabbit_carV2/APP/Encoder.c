/***************************************************************************
 * File: xxx.c
 * Author: Emily
 * Date: 2023/11/13
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Encoder_Init(void);
static void Encoder_Get_Speed(void);
static void Encoder_Get_Mileage(void);

/* Public variables==========================================================*/
Encoder_st Encoder = 
{
    .Mileage = 0.0,
    .Encoder_Left_Speed = 0.0,
    .Encoder_Right_Speed = 0.0,

    .Encoder_Init = &Encoder_Init,
    .Encoder_Get_Speed = &Encoder_Get_Speed,
    .Encoder_Get_Mileage = &Encoder_Get_Mileage
};

/*
* @function: Encoder_Init
* @param: None
* @retval: None
* @brief: 编码器初始化
*/
static void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // 打开TIM2编码器模式
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // 打开TIM4编码器模式
    HAL_TIM_Base_Start_IT(&htim2);  // 打开TIM2中断
    HAL_TIM_Base_Start_IT(&htim4);  // 打开TIM4中断
}

/*
* @function: Encoder_Get_Speed
* @param: None
* @retval: None
* @brief: 获取编码器速度
*/
static void Encoder_Get_Speed(void)
{
    int16_t Encoder_Left_Count = 0;   // 编码器计数值
    int16_t Encoder_Right_Count = 0;
    
    // 获取计数值
    Encoder_Left_Count = (int16_t)TIM4->CNT;  
    Encoder_Right_Count = -(int16_t)TIM2->CNT;

    // 清0计数值
    TIM2->CNT = 0;
    TIM4->CNT = 0;

    // 计算速度 10ms计算编码器速度 10ms*100 --> 1s
    Encoder.Encoder_Left_Speed = (float)Encoder_Left_Count * 100 / 9.6 / 11 / 4;
    Encoder.Encoder_Right_Speed = (float)Encoder_Right_Count * 100 / 9.6 / 11 / 4;
}

/*
* @function: Encoder_Get_Mileage
* @param: None
* @retval: None
* @brief: 获取里程数
*/
static void Encoder_Get_Mileage(void)
{
    // 里程数(cm) = 时间周期(s) * 左边编码器速度 * 车轮周长
    Encoder.Mileage += 0.02 * Encoder.Encoder_Left_Speed * Perimeter;
}