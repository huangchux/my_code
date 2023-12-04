/***************************************************************************
 * File: CallBack.c
 * Author: Emily
 * Date: 2023/11/11
 * description: 中断服务函数
****************************************************************************/
#include "AllHead.h"

/*
* @function:  HAL_TIM_PeriodElapsedCallback
* @param: None
* @retval: None
* @brief: 定时器回调函数
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1) // 2ms
    {
        static uint8_t Encoder_Cnt = 0;
        static uint8_t Motor_Cnt = 0;
        static uint8_t Key_Cnt = 0;

        Encoder_Cnt++;
        Motor_Cnt++;
        Key_Cnt++;

        /********************** 红外 ************************/
        if (FALSE == bsp_UART3.Mode_change_flag) // 改变模式标志位为0为红外寻迹模式
        {
            Infrared.PID_Control_HW_Tracking();
        }

        /********************** 编码器 ************************/
        if (5 == Encoder_Cnt) // 10ms计算编码器速度
        {
            Encoder.Encoder_Get_Speed();
            Encoder_Cnt = 0;
        }

        /********************** 按键 ************************/
        if (7 == Key_Cnt) // 14ms按键检测
        {
            Key_Cnt = 0;
            KEY.KEY_Scan();
        }

        /********************** 电机 ************************/
        if (10 == Motor_Cnt)
        {
            Encoder.Encoder_Get_Mileage(); // 计算里程数

            // 计算PID输出作用到电机  参数1 -> 左边电机的PID结构体  参数2 -> 左边编码器的速度
            PID_Motor_Left.PWM_out = PID.PID_Control(&PID_Motor_Left, Encoder.Encoder_Left_Speed);
            Motor.Motor_Set_PWM(Motor_Left, PID_Motor_Left.PWM_out);
            // 计算PID输出作用到电机  参数1 -> 右边电机的PID结构体  参数2 -> 右边编码器的速度
            PID_Motor_Right.PWM_out = PID.PID_Control(&PID_Motor_Right, Encoder.Encoder_Right_Speed);
            Motor.Motor_Set_PWM(Motor_Right, PID_Motor_Right.PWM_out);
            Motor_Cnt = 0;
        }

        /********************** 继电器 ************************/
        if (Relay.Relay_Flip_Flag) // 如果继电器翻转标志位置1
        {
            Relay.Relay_Flip_Count++;          // 继电器翻转计数++
            if (Relay.Relay_Flip_Count >= 200) // 200ms翻转一次
            {
                Relay.Relay_Flip_Count = 0;          // 继电器翻转计数清0
                Relay.Relay_Flip(Relay_Left);        // 继电器翻转
                Relay.Relay_Flip(Relay_Right);       // 继电器翻转
                Relay.Relay_Flip(Relay_Body_White);  // 继电器翻转
                Relay.Relay_Flip(Relay_Body_Yellow); // 继电器翻转
            }
        }
        if(Relay.Relay_Left_Flip_Flag)  // 如果左耳朵继电器翻转标志位置1
        {
            Relay.Relay_Left_Count++;          // 左耳朵继电器计数++
            if (Relay.Relay_Left_Count >= 200) // 200ms翻转一次
            {
                Relay.Relay_Left_Count = 0;   // 左耳朵继电器翻转计数清0
                Relay.Relay_Flip(Relay_Left); // 左耳朵继电器翻转
            }
        }

        if(Relay.Relay_Right_Flip_Flag) // 如果右耳朵继电器翻转标志位置1
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
* @function: SysTick_Handler
* @param: None
* @retval: None
* @brief: 滴答定时器
*/
void SysTick_Handler(void)
{
    static uint8_t Key_Cnt = 0;

    Key_Cnt++;
    
    if (Key_Cnt >= 100) // 100ms++ *10=1s
    {
        Key_Cnt = 0;
        KEY.Key_Long_Count++;  // 按键长按计数
    }

    System.Task_Marks_Handler();    // 任务标记

    HAL_IncTick(); // 系统自动生成的
}
 /*
 * @function: USART1_IRQHandler
 * @param: None
 * @retval: None
 * @brief: 串口1中断服务函数 （CubeMX自动生成的）
 */
void USART1_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE) != 0x00u)   // 判断是否发生空闲中断
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1); // 清除空闲中断标志位
        HAL_UART_DMAStop(&huart1);          // 停止DMA接收
        bsp_UART1.UART1_Rec_Len = UART1_REC_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);   // 接收的数据个数 = 最大个数 - 未传输的数据个数
        bsp_UART1.UART1_Rec_Over_Flag = TRUE;    // 接收标志位置1
    }
    HAL_UART_IRQHandler(&huart1);
}

/*
* @function: USART3_IRQHandler
* @param: None
* @retval: None
* @brief: 串口3中断服务函数 （CubeMX自动生成的）
*/
void USART3_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart3,UART_FLAG_IDLE) != 0x00u)   // 判断是否发生空闲中断
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart3); // 清除空闲中断标志位
        HAL_UART_DMAStop(&huart3);          // 停止DMA接收
        bsp_UART3.UART3_Rec_Len = UART3_REC_MAX_LEN - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);   // 接收的数据个数 = 最大个数 - 未传输的数据个数
        bsp_UART3.UART3_Rec_Over_Flag = TRUE;    // 接收标志位置1
    }    
    HAL_UART_IRQHandler(&huart3);
}

/*
* @function: USART2_IRQHandler
* @param: None
* @retval: None
* @brief: 串口2中断服务函数 （CubeMX自动生成的）
*/
void USART2_IRQHandler(void)
{
    if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE) == SET)  // 发生空闲中断
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart2);  // 清除空闲中断标志位
        Voice.Voice_Protocol_Analyze();      // 语音模块协议解析
        HAL_UART_Receive_DMA(&huart2, bsp_UART2.UART2_Rec_Buf, UART2_REC_MAX_LEN); // 使能串口2DMA接收
    }
    HAL_UART_IRQHandler(&huart2);
}
