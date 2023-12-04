#ifndef __PID_H
#define __PID_H

typedef struct
{
    float target_val; // 目标值
    float actual_val; // 实际值
    float err;        // 当前偏差
    float err_last;   // 上次偏差
    float err_sum;    // 误差累计值
    float Kp;         // 比例系数
    float Ki;         // 积分系数
    float Kd;         // 微分系数
    float PWM_out;    // PID总输出
} PID_Parameters_st;

typedef struct
{
    void (*PID_Init)(void);                           // PID初始化
    float (*PID_Control)(PID_Parameters_st *, float); // PID控制函数
    void (*PID_Parameters_Clear)(void);               // PID清除参数
} PID_st;

extern PID_st PID;

extern PID_Parameters_st PID_Motor_Left;
extern PID_Parameters_st PID_Motor_Right;
extern PID_Parameters_st PID_HW_Tracking;

#endif