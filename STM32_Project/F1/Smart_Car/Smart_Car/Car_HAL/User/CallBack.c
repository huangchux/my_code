/*******************************************************************************
 * @file    CallBack
 * @author  6+1
 * @date    2023-10-11 15:49:56
 * @brief   回调函数文件
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Public variables-----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  if (GPIO_Pin == KEY1_Pin)
  {
    LED.LED_ON(LED1);
  }
  if (GPIO_Pin == KEY2_Pin)
  {
    LED.LED_OFF(LED1);
  }
}

/**
 * @name   HAL_TIM_PeriodElapsedCallback
 * @brief  定时器中断回调函数
 * @param  *htim -> 处理定时器的结构体指针
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim1.Instance) // 判断定时器是否为htim1 500HZ 2ms 中断一次
  {
    TimerCount++; // 定时器计数器加一

    if (TimerCount % 5 == 0) // 每10ms执行一次
    {
      // 获取编码器1和编码器2的计数值
      Encode1Count = (short)__HAL_TIM_GET_COUNTER(&htim4);
      Encode2Count = -(short)__HAL_TIM_GET_COUNTER(&htim2);

      // 将编码器1和编码器2的计数值重置为0
      __HAL_TIM_SET_COUNTER(&htim4, 0);
      __HAL_TIM_SET_COUNTER(&htim2, 0);

      // 计算速度
      Motor1Speed = (float)Encode1Count * 100 / 9.6 / 11 / 4; // 100*延时10毫秒获得1秒的值
      Motor2Speed = (float)Encode2Count * 100 / 9.6 / 11 / 4;
    }

    if (TimerCount % 10 == 0) // 每20ms执行一次
    {
      /*里程数(cm) += 时间周期（s）*车轮转速(转/s)*车轮周长(cm)*/
      Mileage += 0.02 * Motor1Speed * 22;
      // 计算PID控制器的输出并控制电机运动
      Motor.Motor_set(PID.PID_realize(&PID_Motor1_Speed, Motor1Speed), PID.PID_realize(&PID_Motor2_Speed, Motor2Speed));
      TimerCount = 0; // 定时器计数器重置为0
    }
  }

  // 判断触发回调的定时器是否为 htim3
  if (htim->Instance == htim3.Instance)
  {
    // 判断 usMCU_Run_Timer 是否达到 TIMER3_1S 的值（1秒）
    if (++Timer.usMCU_Run_Timer >= TIMER3_1S)
    {
      // 如果达到1秒，重置 usMCU_Run_Timer 为0，并翻转 LED1
      Timer.usMCU_Run_Timer = 0;
      LED.LED_Flip(LED1);
    }
  }
}

/**
 * @name   HAL_WWDG_EarlyWakeupCallback
 * @brief  窗口看门狗提前唤醒中断回调函数
 * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
 *                the configuration information for the specified WWDG module.
 * @retval None
 */

/**
 * @name   HAL_UART_RxCpltCallback
 * @param  None
 * @retval None
 * @brief  串口中断回调函数
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart3)
  {
    if (Usart3_ReceiveData == 'A')
    {
      Swerve = 1;
      PID.Motor_Set_Speed(MotorSetSpeed, MotorSetSpeed); // 前
    }

    if (Usart3_ReceiveData == 'B')
    {
      Swerve = 0;
      PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed)); // 后
    }

    if (Usart3_ReceiveData == 'C')
    {
      Swerve = 2;
      PID.Motor_Set_Speed(0, 0); // 停
    }

    if (Usart3_ReceiveData == 'D')
    {

      if (Swerve == 1)
      {
        PID.Motor_Set_Speed(MotorSetSpeed, (MotorSetSpeed + 1)); // 左
      }

      else if (Swerve == 0)
      {
        PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed + 1)); // 左
      }

      else if (Swerve == 2)
      {
        PID.Motor_Set_Speed(0, 0); // 停
      }
    }

    if (Usart3_ReceiveData == 'E')
    {
      if (Swerve == 1)
      {
        PID.Motor_Set_Speed((MotorSetSpeed + 1), MotorSetSpeed); // 右
      }
      
      else if (Swerve == 0)
      {
        PID.Motor_Set_Speed(-(MotorSetSpeed + 1), -(MotorSetSpeed)); // 右
      }

      else if (Swerve == 2)
      {
        PID.Motor_Set_Speed(0, 0); // 停
      }
    }

    if (Usart3_ReceiveData == 'F')
    {
      Motor.Motor_SpeedUp(); // 加速
    }

    if (Usart3_ReceiveData == 'G')
    {
      Motor.Motor_SpeedCut(); // 减速
    }
    if (Usart3_ReceiveData == 'H')
    {
      PID.Motor_Set_Speed(-MotorSetSpeed, MotorSetSpeed); // 原地左旋转
    }

    if (Usart3_ReceiveData == 'I')
    {
      PID.Motor_Set_Speed(MotorSetSpeed, -MotorSetSpeed); // 原地右旋转
    }

    HAL_UART_Receive_IT(&huart3, &Usart3_ReceiveData, 1); // 串口3接收数据
  }
}

/********************************************************
  End Of File
********************************************************/
