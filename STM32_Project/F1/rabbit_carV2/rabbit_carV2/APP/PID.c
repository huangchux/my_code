/***************************************************************************
 * File: PID.c
 * Author: Emily
 * Date: 2023/11/13
 * description: PID
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void PID_Init(void);
static float PID_Control(PID_Parameters_st *p_pid, float new_actual_val);
static void PID_Parameters_Clear(void);

/* Public variables==========================================================*/
PID_Parameters_st PID_Motor_Left;   // 定义左电机结构体变量
PID_Parameters_st PID_Motor_Right;  // 定义右电机结构体变量
PID_Parameters_st PID_HW_Tracking;  // 定义红外寻迹结构体变量

PID_st PID = 
{
    .PID_Init = &PID_Init,
    .PID_Control = &PID_Control,
    .PID_Parameters_Clear = &PID_Parameters_Clear
};


/*
* @function: PID_Init
* @param: None
* @retval: None
* @brief: PID初始化
*/
static void PID_Init(void)
{
    // **************************  电机左PID **************************
    PID_Motor_Left.target_val = 0.00; // 目标值
    PID_Motor_Left.actual_val = 0.00; // 实际值

    PID_Motor_Left.err = 0.00;        // 当前偏差
    PID_Motor_Left.err_last = 0.00;   // 上次偏差
    PID_Motor_Left.err_sum = 0.00;    // 误差累计值

    PID_Motor_Left.Kp = 31.00; // 比例系数
    PID_Motor_Left.Ki = 5;     // 积分系数
    PID_Motor_Left.Kd = 0.00;  // 微分系数

    PID_Motor_Left.PWM_out = 0.00; // 总输出    

    // **************************  电机右PID **************************
    PID_Motor_Right.target_val = 0.00; // 目标值
    PID_Motor_Right.actual_val = 0.00; // 实际值

    PID_Motor_Right.err = 0.00;        // 当前偏差
    PID_Motor_Right.err_last = 0.00;   // 上次偏差
    PID_Motor_Right.err_sum = 0.00;    // 误差累计值

    PID_Motor_Right.Kp = 31.00; // 比例系数
    PID_Motor_Right.Ki = 5.00;  // 积分系数
    PID_Motor_Right.Kd = 0.00;  // 微分系数 

    PID_Motor_Right.PWM_out = 0.00; // 总输出

    // **************************  红外寻迹PID **************************
    PID_HW_Tracking.target_val = 0.00; // 目标值
    PID_HW_Tracking.actual_val = 0.00; // 实际值

    PID_HW_Tracking.err = 0.00;        // 当前偏差
    PID_HW_Tracking.err_last = 0.00;   // 上次偏差
    PID_HW_Tracking.err_sum = 0.00;    // 误差累计值

    PID_HW_Tracking.Kp = -1.80;   // 比例系数
    PID_HW_Tracking.Ki = 0.08; // 积分系数
    PID_HW_Tracking.Kd = 0.00; // 微分系数

    PID_HW_Tracking.PWM_out = 0.00; // 总输出
}

/*
 * @function: PID_Control
 * @param: p_pid -> 指向PID结构体的指针 new_actual_val -> 新的实际值
 * @retval: 返回真实值
 * @brief: PID控制函数
 */
static float PID_Control(PID_Parameters_st *p_pid, float new_actual_val)
{
    p_pid->actual_val = new_actual_val;                 // 传递真实值
    p_pid->err = p_pid->target_val - p_pid->actual_val; // 当前误差=目标值-真实值
    p_pid->err_sum += p_pid->err;                       // 误差累计值 = 当前误差累计和
    // 使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
    p_pid->actual_val = p_pid->Kp * p_pid->err + p_pid->Ki * p_pid->err_sum + p_pid->Kd * (p_pid->err - p_pid->err_last);
    // 保存上次误差: 这次误差赋值给上次误差
    p_pid->err_last = p_pid->err;

    return p_pid->actual_val;
}


/*
* @function: PID_Parameters_Clear
* @param: None
* @retval: None
* @brief: PID清除参数
*/
static void PID_Parameters_Clear(void)
{
    // **************************  电机左PID **************************
    PID_Motor_Left.target_val = 0.00; // 目标值
    PID_Motor_Left.actual_val = 0.00; // 实际值

    PID_Motor_Left.err = 0.00;      // 当前偏差
    PID_Motor_Left.err_last = 0.00; // 上次偏差
    PID_Motor_Left.err_sum = 0.00;  // 误差累计值

    PID_Motor_Left.PWM_out = 0.00; // 总输出

    // **************************  电机右PID **************************
    PID_Motor_Right.target_val = 0.00; // 目标值
    PID_Motor_Right.actual_val = 0.00; // 实际值

    PID_Motor_Right.err = 0.00;      // 当前偏差
    PID_Motor_Right.err_last = 0.00; // 上次偏差
    PID_Motor_Right.err_sum = 0.00;  // 误差累计值

    PID_Motor_Right.PWM_out = 0.00; // 总输出

    // **************************  红外寻迹PID **************************
    PID_HW_Tracking.target_val = 0.00; // 目标值
    PID_HW_Tracking.actual_val = 0.00; // 实际值

    PID_HW_Tracking.err = 0.00;      // 当前偏差
    PID_HW_Tracking.err_last = 0.00; // 上次偏差
    PID_HW_Tracking.err_sum = 0.00;  // 误差累计值

    PID_HW_Tracking.PWM_out = 0.00; // 总输出

    Motor.Motor_Set_PWM(Motor_Left, 0); // 停止
    Motor.Motor_Set_PWM(Motor_Right, 0);
}

