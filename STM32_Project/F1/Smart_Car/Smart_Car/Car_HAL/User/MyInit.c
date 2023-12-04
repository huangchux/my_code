/*******************************************************************************
 * @file    MyInit
 * @author  6+1
 * @date    2023-10-11 15:49:19
 * @brief   �ҵĳ�ʼ���ļ�
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
 * @brief  ��������
 * @param  None
 * @retval None
 */
static void Peripheral_Set()
{
	HAL_UART_Receive_IT(&huart3, &Usart3_ReceiveData, 1); // ����3��������
	__HAL_UART_ENABLE_IT(&huart_debug, UART_IT_RXNE);	  // ���ô����ж�
	PID.PID_Init();										  // PID��ʼ��
	Timer.Time_Init();									  // ��ʱ����ʼ��
	OLED_Init();										  // OLED��ʼ��


	
}

/********************************************************
  End Of File
********************************************************/
