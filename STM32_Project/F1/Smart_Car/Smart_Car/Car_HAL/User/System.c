/*******************************************************************************
 * @file    System
 * @author  6+1
 * @date    2023-10-11 15:48:36
 * @brief   主程序运行文件
 ******************************************************************************/

//=============================================================================

/******************************************************************************
 ┌─────────────────────────────────────────────────────────────────────────────┐
 │此项目为基于STM32F103C8T6制作的智能小车
 └─────────────────────────────────────────────────────────────────────────────┘
 *******************************************************************************/

//==============================================================================

/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"



/* Private define-------------------------------------------------------------*/

float Pitch,Roll,Course; // 俯仰角 横滚角 航向角
uint8_t res;
/* Private variables----------------------------------------------------------*/
static void Run(void);
static void Error_Handler(void);
static void Assert_Failed(void);

/* Public variables-----------------------------------------------------------*/
System_t System =
	{
		Run,
		Error_Handler,
		Assert_Failed};

/* Private function prototypes------------------------------------------------*/

/*
 * @name   Run
 * @brief  系统运行
 * @param  None
 * @retval None
 */
static void Run()
{	
	

///************红外循迹功能 PID/无PID******************/
	// PID.PID_Ir_Tracking();
	// IR.Ir_Tracking();
////**************避障功能********************//	
	
	//HC_SR04.HC_SR04_Elude();
	
////**********PID跟随功能***********//
	 	//HC_SR04_Follow();
	
//***************OLED输出****************************//
//	sprintf((char *)OledString, "HC:%.2fcm", HC_SR04.HC_SR04_Read_Distance());							 // 显示超声波数据
//	OLED_ShowString(0, 3, OledString, 12);	
//	sprintf((char *)OledString, "V1:%.2f V2:%.2f", Motor1Speed, Motor2Speed); // 显示两个电机的速度
//	OLED_ShowString(0, 0, OledString, 12);									  // 这个是oled驱动里面的，是显示位置的一个函数
//	Check_Clear_OLED();

//	sprintf((char *)OledString, "ODO:%dcm", (uint16_t)Mileage); // 显示里程数
//	OLED_ShowString(0, 1, OledString, 12);						// 这个是oled驱动里面的，是显示位置的一个函数

//	sprintf((char *)OledString, "U:%.1fv", My_ADC2.ADC_Get_Battery_Voltage()); 
//	OLED_ShowString(0, 2, OledString, 12);									   // 这个是oled驱动里面的，是显示位置的一个函数
//	Check_And_Clear_OLED();
	
//通过串口三(蓝牙)输出信息
//***************串口三输出****************************//

//		sprintf((char *)Usart3String,"V1:%.2fV2:%.2f\r\n",Motor1Speed,Motor2Speed);//显示两个电机转速 单位：转/秒
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//阻塞式发送通过串口三输出字符 strlen:计算字符串大小
//		
//	
//		sprintf((char *)Usart3String,"Mileage%.2f\r\n",Mileage);//计算小车里程 单位cm
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//阻塞式发送通过串口三输出字符 strlen:计算字符串大小
//	
//		sprintf((char *)Usart3String,"U:%.2fV\r\n",My_ADC2.ADC_Get_Battery_Voltage());//显示电池电压
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//阻塞式发送通过串口三输出字符 strlen:计算字符串大小
//		
//		
//	sprintf((char *)Usart3String, "HC_SR04:%.2fcm\r\n", HC_SR04.HC_SR04_Read_Distance());							 // 显示超声波数据
//	HAL_UART_Transmit(&huart3, (uint8_t *)Usart3String, strlen((const char *)Usart3String), 0xFFFF); // 通过串口三输出字符 strlen:计算字符串大小
//	
//	
		sprintf((char *)Usart3String,"Pitch:%.2f Roll:%.2f Course:%.2f\r\n",Pitch,Roll,Course);//显示6050数据
	HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),0xFFFF);//通过串口三输出字符 strlen:计算字符串大小	
   
   //mpu_dmp_get_data(&Pitch,&Roll,&Course);//返回值:0,DMP成功解出欧拉角
//   while(mpu_dmp_get_data(&Pitch,&Roll,&Course)!=0){}  //这个可以解决经常读不出数据的问题
	
	HAL_Delay(1000);
	
	
	
//***************匿名上位机****************************//	
	//	ANO_DT_Send_F2(Motor1Speed * 100, 3.0 * 100, Motor2Speed * 100, 3.0 * 100);
	//	UART_JSON_Parser();
	
	
}

/*
 * @name   Error_Handler
 * @brief  系统错误处理
 * @param  None
 * @retval None
 */
static void Error_Handler()
{
	/* User can add his own implementation to report the HAL error return state */
}

/*
 * @name   Assert_Failed
 * @brief  函数参数错误处理
 * @param  None
 * @retval None
 */
static void Assert_Failed()
{
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	while (1)
	{
	}
}
/********************************************************
  End Of File
********************************************************/
