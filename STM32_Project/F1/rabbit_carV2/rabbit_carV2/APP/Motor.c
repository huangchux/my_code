/***************************************************************************
 * File: Motor.c
 * Author: Emily
 * Date: 2023/11/12
 * description: 
-----------------------------------
注意：
    实物电机1 --- 左 BIN1 PWMB
    实物电机2 --- 右 AIN1 PWMA
----------------------------------- 
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Motor_Init(void);
static void Motor_Set_Direction(Motor_Switch_et Motor, Motor_Direction_et dir);
static void Motor_Set_PWM(Motor_Switch_et Motor, int16_t duty);
static void Motor_PID_Set_Speed(float Left_target, float Right_target);
/* Public variables==========================================================*/
Motor_st Motor = 
{
    .base_speed = 0,
    .Motor_Init = &Motor_Init,
    .Motor_Set_Direction = &Motor_Set_Direction,
    .Motor_Set_PWM = &Motor_Set_PWM,
    .Motor_PID_Set_Speed = &Motor_PID_Set_Speed
};


/*
* @function: Motor_Init
* @param: None
* @retval: None
* @brief: 电机初始化
*/
static void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);   // 使能TIM1--CH1 PWM功能
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);   // 使能TIM1--CH4 PWM功能
    Motor_Set_PWM(Motor_Left, 0);    // 电机默认占空比0
    Motor_Set_PWM(Motor_Right, 0);   // 电机默认占空比0
	HAL_TIM_Base_Start_IT(&htim1);  // 启动TIM1中断
}

/*
* @function: Motor_Set_Direction
* @param: Motor -> 选择电机(Motor_Left/Motor_Right)  dir -> 选择方向(Motor_Forward/Motor_Reverse)
* @retval: None
* @brief: 设置哪个电机的方向
*/
static void Motor_Set_Direction(Motor_Switch_et Motor, Motor_Direction_et dir)
{
    if (Motor_Left == Motor)  // 如果是左边的电机
    {
        switch (dir)          // 选择方向
        {
            case Motor_Forward:   // 正向
            {
                HAL_GPIO_WritePin(Motor_BIN1_GPIO_Port, Motor_BIN1_Pin, GPIO_PIN_RESET); 
                break;
            }
            case Motor_Reverse:   // 反向
            {
                HAL_GPIO_WritePin(Motor_BIN1_GPIO_Port, Motor_BIN1_Pin, GPIO_PIN_SET); 
                break;
            }
            default:
                break;
        }
    }
    else if (Motor_Right == Motor) // 如果是右边的电机
    {
        switch (dir)     // 选择方向
        {
            case Motor_Forward:  // 正向
            {
                HAL_GPIO_WritePin(Motor_AIN1_GPIO_Port, Motor_AIN1_Pin, GPIO_PIN_RESET); 
                break;
            }
            case Motor_Reverse:  // 反向
            {
                HAL_GPIO_WritePin(Motor_AIN1_GPIO_Port, Motor_AIN1_Pin, GPIO_PIN_SET); 
                break;
            }
            default:
                break;
        }        
    }
}

/*
* @function: Motor_Set_PWM
* @param: Motor -> 选择电机(Motor_Left/Motor_Right) Duty -> 占空比(1~100)
* @retval: None
* @brief: 设置电机PWM值
*/
static void Motor_Set_PWM(Motor_Switch_et Motor, int16_t duty)
{
    // ********** 判断方向 **********
    if (Motor_Left == Motor)  // 如果是左边的电机
    {
        //根据参数正负 设置选择方向
        if (duty < 0)  // 如果传入参数为负
        {
            Motor_Set_Direction(Motor, Motor_Reverse);  // 反向
            if (duty < -99)
            {
                duty = -99;
            }
            TIM1->CCR1 = (100 + duty); // 设置占空比 这里要+100 因为写入寄存器必须为正数 值越大速度越快
        }
        else   // 如果传入参数为正
        {
            Motor_Set_Direction(Motor, Motor_Forward);  // 正向
            if (duty > 99) 
            {
                duty = 99;
            }
            TIM1->CCR1 = duty; // 设置占空比
        }
    }
    else if (Motor_Right == Motor)  // 如果是右边的电机
    {
        //根据参数正负 设置选择方向
        if (duty < 0)  // 如果传入参数为负
        {
            Motor_Set_Direction(Motor, Motor_Reverse);  // 反向
            if (duty < -99)
            {
                duty = -99;
            }
            TIM1->CCR4 = (100 + duty); // 设置占空比
        }
        else // 如果传入参数为正
        {
            Motor_Set_Direction(Motor, Motor_Forward); // 正向
            if (duty > 99) 
            {
                duty = 99;
            }
            TIM1->CCR4 = duty; // 设置占空比
        }
    }
}

/*
* @function: Motor_PID_Set_Speed
* @param: Left_target -> 左电机目标速度 Right_target -> 右电机目标速度
* @retval: None
* @brief: 设置电机PID目标速度
*/
static void Motor_PID_Set_Speed(float Left_target, float Right_target)
{
    // 设置目标速度
    PID_Motor_Left.target_val = Left_target;    // 传入左电机目标速度
    PID_Motor_Right.target_val = Right_target;  // 传入右电机目标速度

    // 计算PID输出作用到电机  参数1 -> 左边电机的PID结构体  参数2 -> 左边编码器的速度
    PID_Motor_Left.PWM_out = PID.PID_Control(&PID_Motor_Left, Encoder.Encoder_Left_Speed);
    Motor_Set_PWM(Motor_Left, PID_Motor_Left.PWM_out);  // 设置电机PWM值
    
    // 计算PID输出作用到电机  参数1 -> 右边电机的PID结构体  参数2 -> 右边编码器的速度
    PID_Motor_Right.PWM_out = PID.PID_Control(&PID_Motor_Right, Encoder.Encoder_Right_Speed);
    Motor_Set_PWM(Motor_Right, PID_Motor_Right.PWM_out);    // 设置电机PWM值
}