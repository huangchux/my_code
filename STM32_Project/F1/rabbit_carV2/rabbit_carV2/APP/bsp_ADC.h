#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "AllHead.h"

typedef struct
{
    float Battery_Voltage;      // 电池电压
    uint16_t ADC1_Read_Arr[50]; // ADC读取数组

    void (*bsp_ADC_Init)(void);                // ADC初始化
    void (*Bsp_ADC_Get_Battery_Voltage)(void); // 测量小车电池电压
} bsp_ADC_st;

extern bsp_ADC_st bsp_ADC;

#endif
