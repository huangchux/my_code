/***************************************************************************
 * File: bsp_ADC.c
 * Author: Emily
 * Date: 2023/12/3
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Bsp_ADC_Init(void);
static void Bsp_ADC_Get_Battery_Voltage(void);

/* Public variables==========================================================*/
bsp_ADC_st bsp_ADC = 
{
    .Battery_Voltage = 0.0,
    .ADC1_Read_Arr = {0},

    .Bsp_ADC_Init = &Bsp_ADC_Init,
    .Bsp_ADC_Get_Battery_Voltage = &Bsp_ADC_Get_Battery_Voltage
};

/*
* @function: Bsp_ADC_Init
* @param: None
* @retval: None
* @brief: ADC初始化
*/
static void Bsp_ADC_Init(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1);                              // ADC1校准
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)bsp_ADC.ADC1_Read_Arr, 50); // 启动ADC DMA
}

/*
* @function: Bsp_ADC_Get_Battery_Voltage
* @param: None
* @retval: None
* @brief: 测量小车电池电压
*/
static void Bsp_ADC_Get_Battery_Voltage(void)
{
    float ADC_Sum = 0;

    // 滤波
    for(uint8_t i = 0; i < 50; i++)
    {
        ADC_Sum += bsp_ADC.ADC1_Read_Arr[i];
    }
    ADC_Sum /= 50;

    bsp_ADC.Battery_Voltage = (float)ADC_Sum / 4096 * 3.3 * 5; // ADC点的电压是VBAT_IN的五分之一，所以要计算电池电压需要乘以5
}
