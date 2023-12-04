/***************************************************************************
 * File: LED.c
 * Author: Emily
 * Date: 2023/11/20
 * description: LED
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void LED_Contral(LED_State_et state);
static void LED_Flip(void);

/* Public variables==========================================================*/
LED_st LED = 
{
    .LED_Contral = &LED_Contral,
    .LED_Flip = &LED_Flip
};

/*
* @function: LED_Contral
* @param: None
* @retval: None
* @brief: 控制LED单个灯点亮
*/
static void LED_Contral(LED_State_et state)
{
    if(LED_ON == state)
    {
        HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);  // LED某个引脚设置为低电平（亮）
    }
    else
    {
       HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);     // LED某个引脚设置为高电平（灭）
    }
}

/*
* @function: LED_Flip
* @param: None
* @retval: None
* @brief: LED翻转
*/
static void LED_Flip(void)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);  // 翻转某个LED引脚
}