#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_


#include "AllHead.h"

//���� ULN2003 ���Ʋ�������ܽ�
sbit IN1_D = P1^0;
sbit IN2_C = P1^1;
sbit IN3_B = P1^2;
sbit IN4_A = P1^3;

// ���岽������ٶȣ��ٶȷ�ΧΪ1��5����ֵԽС���ٶ�Խ��(��Ϊʱ��Խ�̣��ٶ�Խ��)
// ��С����С��1
#define STEPMOTOR_MAXSPEED	1  //����ٶ�����ʱ��
#define STEPMOTOR_MINSPEED	5  //��С�ٶ�����ʱ��

void step_motor_28BYJ48_send_pluse(u8 step, u8 dir);

#endif
