#ifndef _HC595_H_
#define _HC595_H_

#include "AllHead.h"

//����74HC595���ƹܽ�
sbit SER = P3^4;            //������������
sbit rCLK = P3^5;           //�洢�Ĵ���ʱ������
sbit SRCLK = P3^6;          //��λ�Ĵ���ʱ������
 
#define LEDDZ_COL_PORT  P0  //�����п��ƶ˿�

void hc595_write_data(u8 dat);
void MatrixLED_ShowCol(u8 col,u8 dat);

#endif
