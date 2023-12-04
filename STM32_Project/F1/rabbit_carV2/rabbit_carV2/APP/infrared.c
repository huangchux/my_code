/***************************************************************************
 * File: infrared.c
 * Author: Emily
 * Date: 2023/11/14
 * description: 红外寻迹
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void PID_Control_HW_Tracking(void);

int8_t This_State = 0;        // 这次状态
int8_t Last_State = 0;        // 上次状态
float HW_PID_Out_Left_Speed;  // 左电机的最后循迹PID控制速度
float HW_PID_Out_Right_Speed; // 右电机的最后循迹PID控制速度

/* Public variables==========================================================*/
Infrared_st Infrared = 
{
    .HW_Read_OUT = {0},
    .PID_Control_HW_Tracking = &PID_Control_HW_Tracking,
};


/*
* @function: PID_Control_HW_Tracking
* @param: None
* @retval: None
* @brief: PID控制红外寻迹
*/
static void PID_Control_HW_Tracking(void)
{
    Infrared.HW_Read_OUT[0] = Read_HW_OUT_1;
    Infrared.HW_Read_OUT[1] = Read_HW_OUT_2;
    Infrared.HW_Read_OUT[2] = Read_HW_OUT_3;
    Infrared.HW_Read_OUT[3] = Read_HW_OUT_4;

    if((0 == Infrared.HW_Read_OUT[0]) && (0 == Infrared.HW_Read_OUT[1]) && (0 == Infrared.HW_Read_OUT[2]) && (0 == Infrared.HW_Read_OUT[3]))
    {
        This_State = 0;   // 前进
    }
    else if((0 == Infrared.HW_Read_OUT[0]) && (1 == Infrared.HW_Read_OUT[1]) && (0 == Infrared.HW_Read_OUT[2]) && (0 == Infrared.HW_Read_OUT[3]))
    {
        This_State = -1;  // 应该右转
    }
    else if((1 == Infrared.HW_Read_OUT[0]) && (0 == Infrared.HW_Read_OUT[1]) && (0 == Infrared.HW_Read_OUT[2]) && (0 == Infrared.HW_Read_OUT[3]))
    {
        This_State = -2;  // 快速右转
    }
    else if((1 == Infrared.HW_Read_OUT[0]) && (1 == Infrared.HW_Read_OUT[1]) && (0 == Infrared.HW_Read_OUT[2]) && (0 == Infrared.HW_Read_OUT[3]))
    {
        This_State = -3;  // 快速右转
    }
    else if((0 == Infrared.HW_Read_OUT[0]) && (0 == Infrared.HW_Read_OUT[1]) && (1 == Infrared.HW_Read_OUT[2]) && (0 == Infrared.HW_Read_OUT[3]))
    {
        This_State = 1;   // 应该左转	
    }
    else if((0 == Infrared.HW_Read_OUT[0]) && (0 == Infrared.HW_Read_OUT[1]) && (0 == Infrared.HW_Read_OUT[2]) && (1 == Infrared.HW_Read_OUT[3]))
    {
        This_State = 2;   // 快速左转
    }
    else if((0 == Infrared.HW_Read_OUT[0]) && (0 == Infrared.HW_Read_OUT[1]) && (1 == Infrared.HW_Read_OUT[2]) && (1 == Infrared.HW_Read_OUT[3]))
    {
        This_State = 3;   // 快速左转
    }

    PID_HW_Tracking.PWM_out = PID.PID_Control(&PID_HW_Tracking,This_State);  //PID计算输出目标速度 这个速度，会和基础速度加减

    HW_PID_Out_Left_Speed = 2 - PID_HW_Tracking.PWM_out;   // 左电机速度 = 基础速度 - 循迹PID输出速度
    HW_PID_Out_Right_Speed = 2 + PID_HW_Tracking.PWM_out;  // 右电机速度 = 基础速度 + 循迹PID输出速度

    if(HW_PID_Out_Left_Speed > 5)  //进行限幅 限幅速度在0-5之间
    {
        HW_PID_Out_Left_Speed = 5;
    }
    if(HW_PID_Out_Left_Speed < 0)
    {
        HW_PID_Out_Left_Speed = 0;
    }
    if(HW_PID_Out_Right_Speed > 5)
    {
        HW_PID_Out_Right_Speed = 5;
    }
    if(HW_PID_Out_Right_Speed < 0)
    {
        HW_PID_Out_Right_Speed = 0;
    }

    if(This_State != Last_State)  // 如果这次状态不等于上次状态、就进行改变目标速度和控制电机、在定时器中依旧定时控制电机
    {
        Motor.Motor_PID_Set_Speed(HW_PID_Out_Left_Speed,HW_PID_Out_Right_Speed); // 通过计算的速度控制电机
    }
    Last_State = This_State;  // 保存上次红外对管状态
}
