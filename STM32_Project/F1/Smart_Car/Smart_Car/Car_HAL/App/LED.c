/*******************************************************************************
 * @file    LED
 * @author  6+1
 * @date    2023-10-11 15:52:41
 * @brief   LED灯文件
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

static void LED_ON(uint8_t);
static void LED_OFF(uint8_t);
static void LED_Flip(uint8_t);

/* Public variables-----------------------------------------------------------*/

LED_t LED =
	{
		LED_ON,	 // 打开LED
		LED_OFF, // 关闭LED
		LED_Flip // 翻转LED
};

/* function prototypes--------------------------------------------------------*/

/*
 * @name   LED_ON
 * @brief  打开LED
 * @param  Num -> 编号
 * @retval None
 */
static void LED_ON(uint8_t LED_Num)
{
	// 条件选择语句
	switch (LED_Num)
	{
	case LED1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		break;
	default:
		System.Assert_Failed();
	}
}

/*
 * @name   LED_OFF
 * @brief  关闭LED
 * @param  Num -> 编号
 * @retval None
 */
static void LED_OFF(uint8_t LED_Num)
{
	// 条件选择语句
	switch (LED_Num)
	{
	case LED1:
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		break;
	default:
		System.Assert_Failed();
	}
}

/*
 * @name   LED_Flip
 * @brief  取反LED
 * @param  Num -> 编号
 * @retval None
 */
static void LED_Flip(uint8_t LED_Num)
{
	// 条件选择语句
	switch (LED_Num)
	{
	case LED1:
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		break;
	default:
		System.Assert_Failed();
	}
}

/********************************************************
  End Of File
********************************************************/
