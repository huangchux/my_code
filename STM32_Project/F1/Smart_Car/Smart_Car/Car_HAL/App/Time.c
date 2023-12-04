/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

static void Time_Init(void); // 定时器初始化

/* Public variables-----------------------------------------------------------*/

short Encode1Count = 0, Encode2Count = 0;
float Motor1Speed = 0.00, Motor2Speed = 0.00, Mileage = 0.00;
uint16_t TimerCount = 0;
// int Motor1Pwm = 0, Motor2Pwm = 0;

// 定义结构体
Timer_T Timer =
    {
        .usMCU_Run_Timer = 0,
        .Time_Init = Time_Init,
};

/* function prototypes--------------------------------------------------------*/

/*
 * @name   Time_Init
 * @param  None
 * @retval None
 * @brief  定时器初始化
 */
static void Time_Init(void)
{
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);       // 开启定时器1 通道1 PWM输出
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);       // 开启定时器1 通道4 PWM输出
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL); // 开启定时器2编码器
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL); // 开启定时器4编码器
  HAL_TIM_Base_Start_IT(&htim1);                  // 开启定时器1中断
  HAL_TIM_Base_Start_IT(&htim2);                  // 开启定时器2中断
  HAL_TIM_Base_Start_IT(&htim3);                  // 开启定时器3中断
  HAL_TIM_Base_Start_IT(&htim4);                  // 开启定时器4中断
}

/********************************************************
  End Of File
********************************************************/
