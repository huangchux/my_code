/*******************************************************************************
 * @file    Public
 * @author  6+1
 * @date    2023-10-11 15:50:31
 * @brief   公共函数文件
 ******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

static void Delay_us(uint16_t us);
static void Memory_Clr(uint8_t *, uint16_t); // 内存清除函数
uint8_t OledString[60];
/* Public variables-----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/
Public_t Public =
	{
		Delay_us,
		Memory_Clr};

/*
 * @function: Public_Delay_us
 * @param: us -> 需要延时的时间(us)
 * @retval: None
 * @brief: 系统us延时
 */
static void Delay_us(uint16_t us)
{
	//	// Set timer period for desired delay in microseconds
	//	__HAL_TIM_SET_AUTORELOAD(&htim13, us - 1);//定时器响应时间为period*定时器频率
	//	HAL_TIM_Base_Start(&htim13);//start the timer
	//	//通过轮询的方式等待定时器的更新事件
	//	//当定时器溢出并计数器更新时，TIM_FLAG_UPDATE标志会被置位。
	//	while(__HAL_TIM_GET_FLAG(&htim13,TIM_FLAG_UPDATE)==RESET);
	//	__HAL_TIM_CLEAR_FLAG(&htim13,TIM_FLAG_UPDATE);//清楚更新标志位
	//	HAL_TIM_Base_Stop(&htim13);//Stop the timer
	uint8_t i;
	// 通过示波器测量进行校准
	while (us--)
	{
		for (i = 0; i < 2; i++)
			;
	}
}

/*
	* @name   Memory_Set
	* @brief  内存清除函数
	* @param  pucBuffer -> 内存首地址
				LEN       -> 内存长度
	* @retval None
*/
static void Memory_Clr(uint8_t *pucBuffer, uint16_t LEN)
{
	uint16_t i;

	for (i = 0; i < LEN; i++)
	{
		*(pucBuffer + i) = (uint8_t)0;
	}
}

/*
 * @name   fputc
 * @brief  fputc映射物理串口
 * @param  ch -> 待发送字符
 * @retval ch -> 已发送字符
 */
int fputc(int ch, FILE *f)
{
	// 通过查询的方式循环发送
	HAL_UART_Transmit(&huart_debug, (uint8_t *)&ch, 1, 0x000A);

	return ch;
}

/*
 * @name   fgetc
 * @brief  fgetc映射物理串口
 * @param  none
 * @retval ch -> 已接收字符
 */
int fgetc(FILE *f)
{
	uint8_t ch = 0;

	// 通过查询的方式等待接收
	HAL_UART_Receive(&huart_debug, &ch, 1, 0xffff);

	return ch;
}

/**
 * 清除OLED屏幕上的内容
 * 
 * 这个函数用于判断电池电压是否变化超过阈值，并根据Swerve的值决定是否清除OLED屏幕上的内容。
 * 如果电压变化超过5，或者last_CleanBit和CleanBit的值不相等，就调用OLED_Clear()函数清除屏幕内容。
 * 同时记录上一次的CleanBit值和电池电压值以供下次比较。
 */
void Check_And_Clear_OLED(void)
{
    static float last_temp = 0; // 记录上一次电池电压的值
    float temp =My_ADC2.ADC_Get_Battery_Voltage(); // 获取当前电池电压的值
  
	

    // 判断电压变化是否超过5
   if (fabs(temp - last_temp) > 5) {
        OLED_Clear(); // 清除屏幕内容
    }

  


    last_temp = temp; // 更新上一次电池电压的值
}

void Check_Clear_OLED(void)
{
	  static uint8_t last_CleanBit = 2; // 记录上一次的CleanBit的值
    uint8_t CleanBit = Swerve; // 获取当前的Swerve值
		  // 检查last_CleanBit和CleanBit是否相等
    if (last_CleanBit != CleanBit) {
        OLED_Clear(); // 清除屏幕内容
    }
	    last_CleanBit = CleanBit; // 更新last_CleanBit的值为当前的CleanBit值
}


/********************************************************
  End Of File
********************************************************/
