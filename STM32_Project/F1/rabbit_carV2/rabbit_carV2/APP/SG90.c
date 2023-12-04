/***************************************************************************
 * File: xxx.c
 * Author: Emily
 * Date: 2023/11/16
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void SG90_Init(void);
static void SG90_Set_Angle(SG90_Angle_et angle);

/* Public variables==========================================================*/
SG90_st SG90 = 
{
    .SG90_Init = &SG90_Init,
    .SG90_Set_Angle = &SG90_Set_Angle
};

/*
* @function: SG90_Init
* @param: None
* @retval: None
* @brief: 舵机初始化
*/
static void SG90_Init(void)
{
    // HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);   // 打开定时器PWM模式
//    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);   // 打开定时器PWM模式
//    TIM3->CCR2 = 101;
    // SG90.SG90_Set_Angle(0);                     // 初始角度为0
}

/*
* @function: SG90_Set_Angle
* @param: angle 角度
* @retval: None
* @brief: 设置角度
*/
static void SG90_Set_Angle(SG90_Angle_et angle)
{
//    switch(angle)
//    {
//        case Angle_0:  // 0度
//        {
//            TIM3->CCR1 = 5;
//            TIM3->CCR2 = 5;
//            break;
//        }
//        case Angle_45: // 45度
//        {
//            TIM3->CCR1 = 10;
//            TIM3->CCR2 = 10;
//            break;
//        } 
//        case Angle_90: // 90度
//        {
//            TIM3->CCR1 = 15;
//            TIM3->CCR2 = 15;
//            break;
//        }
//        case Angle_135: // 135度
//        {
//            TIM3->CCR1 = 20;
//            TIM3->CCR2 = 20;
//            break;
//        }
//        case Angle_180: // 180度
//        {
//            TIM3->CCR1 = 25;
//            TIM3->CCR2 = 25;
//            break;
//        }
//        default:break;                                
//    }
}



