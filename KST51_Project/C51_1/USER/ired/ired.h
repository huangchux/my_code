#ifndef _IRED_H_
#define _IRED_H_

#include "AllHead.h"

//�ܽŶ���
sbit IRED = P3^2; //�ܽŶ���

//��������
void ired_init(void);

//��������
extern u8 gired_data[4];

#endif
