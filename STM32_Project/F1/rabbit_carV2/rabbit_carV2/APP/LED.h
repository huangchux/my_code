#ifndef _LED_H_
#define _LED_H_
#include "AllHead.h"

typedef enum
{
	LED_ON = 1,   // LED��
	LED_OFF = 0   // LED��
} LED_Status_et; // �Ƶ�״̬

typedef struct
{
	void (*LED_Contral)(LED_Status_et); // ����LED����
	void (*LED_Flip)(void);                  // ��תLED
} LED_st; // ������

extern LED_st LED; // �ⲿ�ɵ���

#endif