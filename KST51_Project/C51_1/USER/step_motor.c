#include "AllHead.h"


/*******************************************************************************
* 函 数 名 : step_motor_28BYJ48_send_pulse
* 函数功能 : 输出一个数据给 ULN2003 从而实现向步进电机发送一个脉冲
* 输 入 : step：指定步进序号，可选值 0~7
dir：方向选择,1：逆时针, 0：顺时针
* 输 出 : 无
*******************************************************************************/
/*void step_motor_28BYJ48_send_pluse(u8 step, u8 dir)
{
	u8 temp = step;
	if(dir == 0)            //如果为顺时针旋转
		temp = 7 - step;      //调换节拍信号
  switch(temp)            //8 个节拍控制：D->DC->C->CB->B->BA->A->DA(高电平驱动)
	{      //步进电机为低电平驱动，但是ULN2003芯片控制步进电机管脚,相当于非门，所以高电平才能驱动步进电机
		                      
		case 0: IN4_A = 0;IN3_B = 0;IN2_C = 0;IN1_D = 1; break; //D
		case 1: IN4_A = 0;IN3_B = 0;IN2_C = 1;IN1_D = 1; break; //DC
		case 2: IN4_A = 0;IN3_B = 0;IN2_C = 1;IN1_D = 0; break; //C
		case 3: IN4_A = 0;IN3_B = 1;IN2_C = 1;IN1_D = 0; break; //CB
		case 4: IN4_A = 0;IN3_B = 1;IN2_C = 0;IN1_D = 0; break; //B
		case 5: IN4_A = 1;IN3_B = 1;IN2_C = 0;IN1_D = 0; break; //BA
		case 6: IN4_A = 1;IN3_B = 0;IN2_C = 0;IN1_D = 0; break; //A
		case 7: IN4_A = 1;IN3_B = 0;IN2_C = 0;IN1_D = 1; break; //DA
	}
}*/

