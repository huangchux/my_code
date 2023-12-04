/*******************************************************************************
 * @file    MyInit
 * @author  6+1
 * @date    2023-10-11 15:49:19
 * @brief   我的初始化文件
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

static void Peripheral_Set(void);

/* Public variables-----------------------------------------------------------*/
MyInit_t MyInit =
	{
		Peripheral_Set};

/* Private function prototypes------------------------------------------------*/

/*
 * @name   Peripheral_Set
 * @brief  外设设置
 * @param  None
 * @retval None
 */
static void Peripheral_Set()
{
	HAL_UART_Receive_IT(&huart3, &Usart3_ReceiveData, 1); // 串口3接收数据
	__HAL_UART_ENABLE_IT(&huart_debug, UART_IT_RXNE);	  // 启用串口中断
	PID.PID_Init();										  // PID初始化
	Timer.Time_Init();									  // 定时器初始化
	OLED_Init();										  // OLED初始化


	
}

/********************************************************
  End Of File
********************************************************/
