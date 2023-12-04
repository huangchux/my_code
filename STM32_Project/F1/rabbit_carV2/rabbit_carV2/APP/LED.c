/***************************************************************************
 * File: LED.c
 * Author: Emily
 * Date: 2023/11/11
 * description: LED
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void LED_Contral(LED_Status_et state);
static void LED_Flip(void);

/* Public variables==========================================================*/
LED_st LED =	
{
	.LED_Contral = &LED_Contral,
	.LED_Flip = &LED_Flip,
};

/*
 * @function: LED_Contral
 * @param: state -> LED�ܽ�
 * @retval: None
 * @brief: ����LED�����Ƶ���
 */
static void LED_Contral(LED_Status_et state)
{
	if (LED_ON == state)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET); // LEDĳ����������Ϊ�͵�ƽ������
	}
	else
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET); // LEDĳ����������Ϊ�ߵ�ƽ����
	}
}

/*
 * @function: LED_Flip
 * @param: None
 * @retval: None
 * @brief: ��ת
 */
static void LED_Flip(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // ��תĳ��LED����
}





