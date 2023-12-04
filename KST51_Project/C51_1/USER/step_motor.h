#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_


#include "AllHead.h"

//定义 ULN2003 控制步进电机管脚
sbit IN1_D = P1^0;
sbit IN2_C = P1^1;
sbit IN3_B = P1^2;
sbit IN4_A = P1^3;

// 定义步进电机速度（速度范围为1到5），值越小，速度越快(因为时间越短，速度越快)
// 最小不能小于1
#define STEPMOTOR_MAXSPEED	1  //最大速度所用时间
#define STEPMOTOR_MINSPEED	5  //最小速度所用时间

void step_motor_28BYJ48_send_pluse(u8 step, u8 dir);

#endif
