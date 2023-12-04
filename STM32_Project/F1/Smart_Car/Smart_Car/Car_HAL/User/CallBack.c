/*******************************************************************************
 * @file    CallBack
 * @author  6+1
 * @date    2023-10-11 15:49:56
 * @brief   �ص������ļ�
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
 * @brief  ��ʱ���жϻص�����
 * @param  *htim -> ����ʱ���Ľṹ��ָ��
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim1.Instance) // �ж϶�ʱ���Ƿ�Ϊhtim1 500HZ 2ms �ж�һ��
  {
    TimerCount++; // ��ʱ����������һ

    if (TimerCount % 5 == 0) // ÿ10msִ��һ��
    {
      // ��ȡ������1�ͱ�����2�ļ���ֵ
      Encode1Count = (short)__HAL_TIM_GET_COUNTER(&htim4);
      Encode2Count = -(short)__HAL_TIM_GET_COUNTER(&htim2);

      // ��������1�ͱ�����2�ļ���ֵ����Ϊ0
      __HAL_TIM_SET_COUNTER(&htim4, 0);
      __HAL_TIM_SET_COUNTER(&htim2, 0);

      // �����ٶ�
      Motor1Speed = (float)Encode1Count * 100 / 9.6 / 11 / 4; // 100*��ʱ10������1���ֵ
      Motor2Speed = (float)Encode2Count * 100 / 9.6 / 11 / 4;
    }

    if (TimerCount % 10 == 0) // ÿ20msִ��һ��
    {
      /*�����(cm) += ʱ�����ڣ�s��*����ת��(ת/s)*�����ܳ�(cm)*/
      Mileage += 0.02 * Motor1Speed * 22;
      // ����PID����������������Ƶ���˶�
      Motor.Motor_set(PID.PID_realize(&PID_Motor1_Speed, Motor1Speed), PID.PID_realize(&PID_Motor2_Speed, Motor2Speed));
      TimerCount = 0; // ��ʱ������������Ϊ0
    }
  }

  // �жϴ����ص��Ķ�ʱ���Ƿ�Ϊ htim3
  if (htim->Instance == htim3.Instance)
  {
    // �ж� usMCU_Run_Timer �Ƿ�ﵽ TIMER3_1S ��ֵ��1�룩
    if (++Timer.usMCU_Run_Timer >= TIMER3_1S)
    {
      // ����ﵽ1�룬���� usMCU_Run_Timer Ϊ0������ת LED1
      Timer.usMCU_Run_Timer = 0;
      LED.LED_Flip(LED1);
    }
  }
}

/**
 * @name   HAL_WWDG_EarlyWakeupCallback
 * @brief  ���ڿ��Ź���ǰ�����жϻص�����
 * @param  hwwdg : pointer to a WWDG_HandleTypeDef structure that contains
 *                the configuration information for the specified WWDG module.
 * @retval None
 */

/**
 * @name   HAL_UART_RxCpltCallback
 * @param  None
 * @retval None
 * @brief  �����жϻص�����
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart3)
  {
    if (Usart3_ReceiveData == 'A')
    {
      Swerve = 1;
      PID.Motor_Set_Speed(MotorSetSpeed, MotorSetSpeed); // ǰ
    }

    if (Usart3_ReceiveData == 'B')
    {
      Swerve = 0;
      PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed)); // ��
    }

    if (Usart3_ReceiveData == 'C')
    {
      Swerve = 2;
      PID.Motor_Set_Speed(0, 0); // ͣ
    }

    if (Usart3_ReceiveData == 'D')
    {

      if (Swerve == 1)
      {
        PID.Motor_Set_Speed(MotorSetSpeed, (MotorSetSpeed + 1)); // ��
      }

      else if (Swerve == 0)
      {
        PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed + 1)); // ��
      }

      else if (Swerve == 2)
      {
        PID.Motor_Set_Speed(0, 0); // ͣ
      }
    }

    if (Usart3_ReceiveData == 'E')
    {
      if (Swerve == 1)
      {
        PID.Motor_Set_Speed((MotorSetSpeed + 1), MotorSetSpeed); // ��
      }
      
      else if (Swerve == 0)
      {
        PID.Motor_Set_Speed(-(MotorSetSpeed + 1), -(MotorSetSpeed)); // ��
      }

      else if (Swerve == 2)
      {
        PID.Motor_Set_Speed(0, 0); // ͣ
      }
    }

    if (Usart3_ReceiveData == 'F')
    {
      Motor.Motor_SpeedUp(); // ����
    }

    if (Usart3_ReceiveData == 'G')
    {
      Motor.Motor_SpeedCut(); // ����
    }
    if (Usart3_ReceiveData == 'H')
    {
      PID.Motor_Set_Speed(-MotorSetSpeed, MotorSetSpeed); // ԭ������ת
    }

    if (Usart3_ReceiveData == 'I')
    {
      PID.Motor_Set_Speed(MotorSetSpeed, -MotorSetSpeed); // ԭ������ת
    }

    HAL_UART_Receive_IT(&huart3, &Usart3_ReceiveData, 1); // ����3��������
  }
}

/********************************************************
  End Of File
********************************************************/
