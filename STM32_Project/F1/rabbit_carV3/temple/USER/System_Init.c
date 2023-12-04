/***************************************************************************
 * File: System_Init.c
 * Author: Emily
 * Date: 2023/11/20
 * description: 系统初始化
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Hardware_Init(void);

/* Public variables==========================================================*/
System_Init_st System_Init = 
{
    .Hardware_Init = &Hardware_Init
};

/*
* @function: Hardware_Init
* @param: None
* @retval: None
* @brief: 硬件初始化
*/
static void Hardware_Init(void)
{
    OLED.OLED_Init();           // OLED初始化
    Menu.Menu_Init();           // 页面初始化
    Encoder.Encoder_Init();     // 编码器初始化
    Motor.Motor_Init();         // 电机初始化
    bsp_UART1.Bsp_UART1_Init(); // 串口1初始化
    bsp_UART3.Bsp_UART3_Init(); // 蓝牙初始化
    bsp_UART2.Bsp_UART2_Init(); // 语音模块初始化
    bsp_ADC.Bsp_ADC_Init();     // ADC初始化
    PID.PID_Init();             // PID初始化
    Relay.Relay_Init();         // 继电器初始化
}