/***************************************************************************
 * File: CallBack.c
 * Author: Emily
 * Date: 2023/11/20
 * description: 中断服务函数
****************************************************************************/
#include "AllHead.h"

/*
* @function: SysTick_Handler
* @param: None
* @retval: None
* @brief: 滴答定时器
*/
void SysTick_Handler(void)
{
    static uint8_t Key_cnt = 0;
    static uint8_t Count_5ms = 0;

    Key_cnt++;
    Count_5ms++;
    if(Key_cnt >= 100)  // 100ms++ *10=1s
    {
        Key_cnt = 0;
        KEY.Key_Long_Count++; // 按键长按计数
    }
    if(Count_5ms >= 5)
    {
        KEY.Key_Scan(); // 按键扫描 --- 按键三行消抖
    }

    System.Task_Marks_Handler();  // 任务标记

    HAL_IncTick(); // 系统自动生成的
}

/*
* @function: HAL_TIM_PeriodElapsedCallback
* @param: None
* @retval: None
* @brief: 定时器中断回调函数
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim == &htim1) // 2ms
    {
        static uint8_t Encoder_cnt = 0;
        static uint8_t Motor_cnt = 0;
        static uint8_t Key_cnt = 0;

        Encoder_cnt++;
        Motor_cnt++;
        Key_cnt++;

        /********************** 红外 ************************/
        if(FALSE == bsp_UART3.Mode_Change_Flag)  // 改变模式标志位为0为红外寻迹模式
        {
          Infrared.PID_Control_HW_Tracking();
        }

        /********************** 编码器 ************************/
        if(5 == Encoder_cnt)  // 10ms计算编码器速度
        {
            Encoder_cnt = 0;
            Encoder.Encoder_Get_Speed();
        }

        /********************** 按键 ************************/
        if(7 == Key_cnt)  // 14ms按键检测
        {
          Key_cnt = 0;
          KEY.Key_Scan();
        }

        /********************** 电机 ************************/
        if(10 == Motor_cnt)
        {
          Motor_cnt = 0;
          Encoder.Encoder_Get_Mileage(); // 计算里程数

          // 计算PID输出作用到电机  参数1 -> 左边电机的PID结构体  参数2 -> 左边编码器的速度
          PID_Motor_Left.PWM_out = PID.PID_Control(&PID_Motor_Left, Encoder.Encoder_Left_Speed);
          Motor.Motor_Set_PWM(Motor_Left, PID_Motor_Left.PWM_out); // 设置电机PWM值

          // 计算PID输出作用到电机  参数1 -> 右边电机的PID结构体  参数2 -> 右边编码器的速度
          PID_Motor_Right.PWM_out = PID.PID_Control(&PID_Motor_Right, Encoder.Encoder_Right_Speed);
          Motor.Motor_Set_PWM(Motor_Right, PID_Motor_Right.PWM_out); // 设置电机PWM值
        }

        /********************** 继电器 ************************/
        if(Relay.Relay_Flip_Flag)
        {
          Relay.Relay_Flip_Count++;
          if(Relay.Relay_Flip_Count >= 200)
          {
            Relay.Relay_Flip_Count = 0;    // 继电器翻转计数清0
            Relay.Relay_Flip(Relay_Left);  // 继电器翻转
            Relay.Relay_Flip(Relay_Right); 
            Relay.Relay_Flip(Relay_Body_White);
            Relay.Relay_Flip(Relay_Body_Yellow);
          }
        }

        if (Relay.Relay_Left_Flip_Flag) // 如果左耳朵继电器翻转标志位置1
        {
          Relay.Relay_Left_Count++;          // 左耳朵继电器计数++
          if (Relay.Relay_Left_Count >= 200) // 200ms翻转一次
          {
            Relay.Relay_Left_Count = 0;   // 左耳朵继电器翻转计数清0
            Relay.Relay_Flip(Relay_Left); // 继电器翻转
          }
        }

        if (Relay.Relay_Right_Flip_Flag) // 如果右耳朵继电器翻转标志位置1
        {
          Relay.Relay_Right_Count++;          // 右耳朵继电器翻转计数++
          if (Relay.Relay_Right_Count >= 200) // 200ms翻转一次
          {
            Relay.Relay_Right_Count = 0;   // 右耳朵继电器翻转计数清0
            Relay.Relay_Flip(Relay_Right); // 右耳朵继电器翻转
          }
        }
    }
}

/*
* @function: USART1_IRQHandler
* @param: None
* @retval: None
* @brief: 串口1中断服务函数 （CubeMX自动生成的）
*/
void USART1_IRQHandler(void)
{
  if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) == SET) // 判断是否发生空闲中断
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);  // 清除空闲中断标志位
    HAL_UART_DMAStop(&huart1);           // 停止DMA接收
    bsp_UART1.UART1_Rec_Len = UART1_REC_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx); // 接收的数据个数 = 最大个数 - 未传输的数据个数
    bsp_UART1.UART1_Rec_Over_Flag = TRUE;  // 接收标志位置1
  }
  HAL_UART_IRQHandler(&huart1); // CubeMX自动生成
}

/*
* @function: USART2_IRQHandler
* @param: None
* @retval: None
* @brief: 串口2中断服务函数 （CubeMX自动生成的）
*/
void USART2_IRQHandler(void)
{
  if(__HAL_UART_GET_FLAG(&huart2, UART_IT_IDLE) == SET)
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart2);

    HAL_UART_Receive_DMA(&huart2, bsp_UART2.UART2_Rec_Buf, UART2_REC_MAX_LEN); // 使能串口2DMA接收
  }
  HAL_UART_IRQHandler(&huart2);
  
}

/*
* @function: USART3_IRQHandler
* @param: None
* @retval: None
* @brief: 串口3中断服务函数 （CubeMX自动生成的）
*/
void USART3_IRQHandler(void)
{
  if(__HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) == SET) // 判断是否发生空闲中断
  {
    __HAL_UART_CLEAR_IDLEFLAG(&huart3); // 清除空闲中断标志位
    HAL_UART_DMAStop(&huart3);          // 停止DMA接收
    bsp_UART3.UART3_Rec_Len = UART3_REC_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx); // 接收的数据个数 = 最大个数 - 未传输的数据个数
    bsp_UART3.UART3_Rec_Over_Flag = TRUE; // 接收标志位置1
  }
  HAL_UART_IRQHandler(&huart3);
  
}

