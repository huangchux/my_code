/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

/* Public variables-----------------------------------------------------------*/

uint8_t Usart1_ReadBuf[256];
uint8_t Usart1_ReadCount = 0;
uint8_t Usart3_ReceiveData;
uint8_t Usart3String[60];
uint8_t Swerve = 1;


/* function prototypes--------------------------------------------------------*/

/**
 * @name   Usart_WaitRessFinish
 * @param  None
 * @retval None
 * @brief  等待串口接收完成
 */
uint8_t Usart_WaitRessFinish(void)
{
    static uint16_t Usart_LastReadCount = 0; // 记录上次的计数值
    if (Usart1_ReadCount == 0)               // 如果计数值为0，表示没有接收到数据
    {
        Usart_LastReadCount = 0;
        return 1; // 返回1，表示接收完成
    }
    if (Usart1_ReadCount == Usart_LastReadCount) // 如果计数值与上次的计数值相同，表示接收完成
    {
        Usart1_ReadCount = 0; // 将计数值重置为0
        Usart_LastReadCount = 0;
        return 0; // 返回0，表示未接收完成
    }
    Usart_LastReadCount = Usart1_ReadCount; // 更新上次的计数值
    return 2;                               // 返回2，表示正在接收中
}

/**
 * @name   UART_JSON_Parser
 * @param  None
 * @retval None
 * @brief  将UART接收到的JSON数据进行解析
 */
void UART_JSON_Parser(void)
{
    float p, i, d, a, b;           // 声明变量 p, i, d, a b用于存储解析后的参数值
    cJSON *cJsonData, *cJsonVlaue; // 声明 cJSON 对象指针 cJsonData 和 cJsonVlaue

    if (Usart_WaitRessFinish() == 0) // 检查串口接收是否完成
    {
        cJsonData = cJSON_Parse((const char *)Usart1_ReadBuf); // 解析接收到的 JSON 数据

        if (cJSON_GetObjectItem(cJsonData, "p") != NULL) // 检查是否存在键名为 "p" 的项
        {
            cJsonVlaue = cJSON_GetObjectItem(cJsonData, "p"); // 获取键名为 "p" 的值
            p = cJsonVlaue->valuedouble;                      // 将值转换为浮点型并赋给变量 p
            PID_Motor1_Speed.KP = p;                          // 将 p 设置为 PID 控制器的 Kp 参数
        }

        if (cJSON_GetObjectItem(cJsonData, "i") != NULL) // 类似地检查并处理键名为 "i" 的项
        {
            cJsonVlaue = cJSON_GetObjectItem(cJsonData, "i");
            i = cJsonVlaue->valuedouble;
            PID_Motor1_Speed.KI = i;
        }

        if (cJSON_GetObjectItem(cJsonData, "d") != NULL) // 类似地检查并处理键名为 "d" 的项
        {
            cJsonVlaue = cJSON_GetObjectItem(cJsonData, "d");
            d = cJsonVlaue->valuedouble;
            PID_Motor1_Speed.KD = d;
        }

        if (cJSON_GetObjectItem(cJsonData, "a") != NULL) // 类似地检查并处理键名为 "a" 的项
        {
            cJsonVlaue = cJSON_GetObjectItem(cJsonData, "a");
            a = cJsonVlaue->valuedouble;
            PID_Motor1_Speed.target_val = a;
        }

        if (cJSON_GetObjectItem(cJsonData, "b") != NULL)
        {

            cJsonVlaue = cJSON_GetObjectItem(cJsonData, "b");
            b = cJsonVlaue->valuedouble;
            PID_Motor2_Speed.target_val = b;
        }

        if (cJsonData != NULL)
        {
            cJSON_Delete(cJsonData); // 释放 cJSON 对象占用的内存空间，避免内存泄漏
        }
        memset(Usart1_ReadBuf, 0, 255); // 清空串口接收缓冲区
    }
    printf("P:%.3f  I:%.3f  D:%.3f A:%.3f B:%.3f\r\n", p, i, d, a, b); // 打印解析后的参数值
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void)
{
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE)) // 判断huart1 是否读到字节
    {
        if (Usart1_ReadCount >= 255) // 如果接收计数超过255，则将其重置为0
            Usart1_ReadCount = 0;
        HAL_UART_Receive(&huart1, &Usart1_ReadBuf[Usart1_ReadCount++], 1, 1000); // 接收一个字节并存入接收缓冲区
    }

    HAL_UART_IRQHandler(&huart1); // 调用HAL库提供的UART中断处理函数，处理其他中断相关操作
}

/********************************************************
  End Of File
********************************************************/
