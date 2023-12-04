#ifndef __Motor_H
#define __Motor_H

// **********小车运动************

// 前进(两边速度一致)
#define __Motor_Go(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(L_Speed + Motor.base_speed, R_Speed + Motor.base_speed)
// 后退(两边速度一致)
#define __Motor_Back(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(-L_Speed - Motor.base_speed, -R_Speed - Motor.base_speed)
// 向左转弯(左边速度小右边速度大)
#define __Motor_Left(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(L_Speed + Motor.base_speed, R_Speed + Motor.base_speed)
// 向右转弯(左边速度大右边速度小)
#define __Motor_Right(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(L_Speed + Motor.base_speed, R_Speed + Motor.base_speed)
// 原地左转(左边速度为负数右边速度为正数)
#define __Motor_Inplace_Left(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(-L_Speed - Motor.base_speed, R_Speed + Motor.base_speed)
// 原地右转(左边速度为正数右边速度为负数)
#define __Motor_Inplace_Right(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(L_Speed + Motor.base_speed, -R_Speed - Motor.base_speed)
// 停止
#define __Motor_Stop(L_Speed, R_Speed)    Motor.Motor_PID_Set_Speed(L_Speed, R_Speed)

// 选择电机枚举
typedef enum
{
    Motor_Left = 0x00,  // 左电机
    Motor_Right = 0x01  // 右电机
} Motor_Switch_et;

// 电机方向枚举
typedef enum
{
    Motor_Forward = 0x00, // 正向
    Motor_Reverse = 0x01  // 反向
} Motor_Direction_et;

typedef struct
{
    uint8_t base_speed;                                               // 电机基础速度
    void (*Motor_Init)(void);                                         // 电机初始化
    void (*Motor_Set_Direction)(Motor_Switch_et, Motor_Direction_et); // 设置哪个电机的方向
    void (*Motor_Set_PWM)(Motor_Switch_et, int16_t);                  // 设置电机PWM值
    void (*Motor_PID_Set_Speed)(float, float);                        // 设置电机PID目标速度
} Motor_st;

extern Motor_st Motor;

#endif
