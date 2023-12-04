/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

static void Motor_set(int, int);
static void Motor_SpeedUp(void);
static void Motor_SpeedCut(void);

/* Public variables-----------------------------------------------------------*/

Motor_t Motor =
    {
        .Motor_set = Motor_set,
        .Motor_SpeedUp = Motor_SpeedUp,
        .Motor_SpeedCut = Motor_SpeedCut,
};

float MotorSetSpeed = 1;

/* function prototypes--------------------------------------------------------*/

/*
 * @name   Motor_set
 * @param  None
 * @retval None
 * @brief  设置电机的转速和方向
 */
static void Motor_set(int motor1, int motor2)
{
    // 判断 motor1 的正负来确定电机1的方向
    if (motor1 < 0)
    {
        BIN1_SET; // 设置引脚为高电平，电机1反转
    }
    else
    {
        BIN1_RESET; // 设置引脚为低电平，电机1正转
    }

    // 判断 motor2 的正负来确定电机2的方向
    if (motor2 < 0)
    {
        AIN1_SET; // 设置引脚为高电平，电机2反转
    }
    else
    {
        AIN1_RESET; // 设置引脚为低电平，电机2正转
    }

    // 对 motor1 进行范围限制
    if (motor1 < 0)
    {
        if (motor1 < -99)
        {
            motor1 = -99; // 将 motor1 限制在 -99 到 0 之间
        }

        // 设置定时器 htim1 的通道1比较寄存器的值来控制电机1的转速
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (100 + motor1));
    }
    else
    {
        if (motor1 > 99)
        {
            motor1 = 99; // 将 motor1 限制在 0 到 99 之间
        }
        // 设置定时器 htim1 的通道1比较寄存器的值来控制电机1的转速
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor1);
    }

    // 对 motor2 进行范围限制
    if (motor2 < 0)
    {
        if (motor2 < -99)
        {
            motor2 = -99; // 将 motor2 限制在 -99 到 0 之间
        }
        // 设置定时器 htim1 的通道4比较寄存器的值来控制电机2的转速
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (100 + motor2));
    }
    else
    {
        if (motor2 > 99)
        {
            motor2 = 99; // 将 motor2 限制在 0 到 99 之间
        }
        // 设置定时器 htim1 的通道4比较寄存器的值来控制电机2的转速
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, motor2);
    }
}

/**
 * @name   Motor_SpeedUp
 * @param  None
 * @retval None
 * @brief  电机加速
 */
static void Motor_SpeedUp(void)
{

    if (MotorSetSpeed <= 4)
    {
        MotorSetSpeed += 0.5;
        if (Swerve == 1)
        {
            PID.Motor_Set_Speed(MotorSetSpeed, MotorSetSpeed);
        }
        else
        {
            PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed));
        }
    }
}

/**
 * @name   Motor_SpeedCut
 * @param  None
 * @retval None
 * @brief  电机减速
 */
static void Motor_SpeedCut(void)
{

    if (MotorSetSpeed >= 0.5)
    {
        MotorSetSpeed -= 0.5;
        if (Swerve == 1)
        {
            PID.Motor_Set_Speed(MotorSetSpeed, MotorSetSpeed);
        }
        else
        {
            PID.Motor_Set_Speed(-(MotorSetSpeed), -(MotorSetSpeed));
        }
    }
}

/********************************************************
  End Of File
********************************************************/
