#include "AllHead.h"


/*******************************************************************************
* �� �� �� : step_motor_28BYJ48_send_pulse
* �������� : ���һ�����ݸ� ULN2003 �Ӷ�ʵ���򲽽��������һ������
* �� �� : step��ָ��������ţ���ѡֵ 0~7
dir������ѡ��,1����ʱ��, 0��˳ʱ��
* �� �� : ��
*******************************************************************************/
/*void step_motor_28BYJ48_send_pluse(u8 step, u8 dir)
{
	u8 temp = step;
	if(dir == 0)            //���Ϊ˳ʱ����ת
		temp = 7 - step;      //���������ź�
  switch(temp)            //8 �����Ŀ��ƣ�D->DC->C->CB->B->BA->A->DA(�ߵ�ƽ����)
	{      //�������Ϊ�͵�ƽ����������ULN2003оƬ���Ʋ�������ܽ�,�൱�ڷ��ţ����Ըߵ�ƽ���������������
		                      
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

