#ifndef __MOTOR_H
#define __MOTOR_H

//宏定义
#define AIN1_RESET HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET) // 设置AIN1 PB13为低电平
#define AIN1_SET HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET)     // 设置AIN1 PB13为高电平

#define BIN1_RESET HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET) // 设置BIN1 PB3为低电平
#define BIN1_SET HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET)     // 设置AIN1 PB3为高电平

//结构体类型
typedef struct 
{
    void(*Motor_set)(int,int);
    void (*Motor_SpeedUp)(void);
    void (*Motor_SpeedCut)(void);
} Motor_t;


/* extern variables-----------------------------------------------------------*/

extern Motor_t Motor;
extern float MotorSetSpeed;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
