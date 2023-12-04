/*******************************************************************************
 * @file    System
 * @author  6+1
 * @date    2023-10-11 15:48:36
 * @brief   �����������ļ�
 ******************************************************************************/

//=============================================================================

/******************************************************************************
 ��������������������������������������������������������������������������������������������������������������������������������������������������������������
 ������ĿΪ����STM32F103C8T6����������С��
 ��������������������������������������������������������������������������������������������������������������������������������������������������������������
 *******************************************************************************/

//==============================================================================

/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"



/* Private define-------------------------------------------------------------*/

float Pitch,Roll,Course; // ������ ����� �����
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
 * @brief  ϵͳ����
 * @param  None
 * @retval None
 */
static void Run()
{	
	

///************����ѭ������ PID/��PID******************/
	// PID.PID_Ir_Tracking();
	// IR.Ir_Tracking();
////**************���Ϲ���********************//	
	
	//HC_SR04.HC_SR04_Elude();
	
////**********PID���湦��***********//
	 	//HC_SR04_Follow();
	
//***************OLED���****************************//
//	sprintf((char *)OledString, "HC:%.2fcm", HC_SR04.HC_SR04_Read_Distance());							 // ��ʾ����������
//	OLED_ShowString(0, 3, OledString, 12);	
//	sprintf((char *)OledString, "V1:%.2f V2:%.2f", Motor1Speed, Motor2Speed); // ��ʾ����������ٶ�
//	OLED_ShowString(0, 0, OledString, 12);									  // �����oled��������ģ�����ʾλ�õ�һ������
//	Check_Clear_OLED();

//	sprintf((char *)OledString, "ODO:%dcm", (uint16_t)Mileage); // ��ʾ�����
//	OLED_ShowString(0, 1, OledString, 12);						// �����oled��������ģ�����ʾλ�õ�һ������

//	sprintf((char *)OledString, "U:%.1fv", My_ADC2.ADC_Get_Battery_Voltage()); 
//	OLED_ShowString(0, 2, OledString, 12);									   // �����oled��������ģ�����ʾλ�õ�һ������
//	Check_And_Clear_OLED();
	
//ͨ��������(����)�����Ϣ
//***************���������****************************//

//		sprintf((char *)Usart3String,"V1:%.2fV2:%.2f\r\n",Motor1Speed,Motor2Speed);//��ʾ�������ת�� ��λ��ת/��
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//����ʽ����ͨ������������ַ� strlen:�����ַ�����С
//		
//	
//		sprintf((char *)Usart3String,"Mileage%.2f\r\n",Mileage);//����С����� ��λcm
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//����ʽ����ͨ������������ַ� strlen:�����ַ�����С
//	
//		sprintf((char *)Usart3String,"U:%.2fV\r\n",My_ADC2.ADC_Get_Battery_Voltage());//��ʾ��ص�ѹ
//		HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),50);//����ʽ����ͨ������������ַ� strlen:�����ַ�����С
//		
//		
//	sprintf((char *)Usart3String, "HC_SR04:%.2fcm\r\n", HC_SR04.HC_SR04_Read_Distance());							 // ��ʾ����������
//	HAL_UART_Transmit(&huart3, (uint8_t *)Usart3String, strlen((const char *)Usart3String), 0xFFFF); // ͨ������������ַ� strlen:�����ַ�����С
//	
//	
		sprintf((char *)Usart3String,"Pitch:%.2f Roll:%.2f Course:%.2f\r\n",Pitch,Roll,Course);//��ʾ6050����
	HAL_UART_Transmit(&huart3,( uint8_t *)Usart3String,strlen(( const  char  *)Usart3String),0xFFFF);//ͨ������������ַ� strlen:�����ַ�����С	
   
   //mpu_dmp_get_data(&Pitch,&Roll,&Course);//����ֵ:0,DMP�ɹ����ŷ����
//   while(mpu_dmp_get_data(&Pitch,&Roll,&Course)!=0){}  //������Խ���������������ݵ�����
	
	HAL_Delay(1000);
	
	
	
//***************������λ��****************************//	
	//	ANO_DT_Send_F2(Motor1Speed * 100, 3.0 * 100, Motor2Speed * 100, 3.0 * 100);
	//	UART_JSON_Parser();
	
	
}

/*
 * @name   Error_Handler
 * @brief  ϵͳ������
 * @param  None
 * @retval None
 */
static void Error_Handler()
{
	/* User can add his own implementation to report the HAL error return state */
}

/*
 * @name   Assert_Failed
 * @brief  ��������������
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
