#include "AllHead.h"

////�������ʾ������
//u8 smg_Buf[9] = {0,10,10,10,10,10,10,10,10};
////����ܶ����
//u8 gsmg_code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x40}; 
//                                    //����������0-F����,gsmg��g����ȫ�ֱ���

u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				          0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//����������0-F����,gsmg��g����ȫ�ֱ���

/**
  * @brief  ������ʾ������
  * @param  Location Ҫ���õ�λ�ã���Χ��1~8
  * @param  Number Ҫ���õ����֣���Χ�������������Χ
  * @retval ��
  */
/*void smg_SetBuf(u8 location,u8 number)
{
	smg_Buf[location] = number; //��ĳ��λ�õ�����ܸĳ�ĳ������
}*/
							
/********************************************
* �� �� �� : smg_display
* �������� : ��̬�������ʾ
*********************************************/
/*void smg_display(u8 location,u8 number)
{
	  SMG_A_DP_PORT = 0x00;         //��Ӱ
		switch(location)
		{
			case 1: LSC = 1;LSB = 1;LSA = 1;break; //Y7 LED8 ���Ӵ��������һ�������
			case 2: LSC = 1;LSB = 1;LSA = 0;break; //Y6 LED7 ���Ӵ�������ڶ��������
			case 3: LSC = 1;LSB = 0;LSA = 1;break; //Y5 LED6 ���Ӵ�����������������
			case 4: LSC = 1;LSB = 0;LSA = 0;break; //Y4 LED5 ���Ӵ���������ĸ������
			case 5: LSC = 0;LSB = 1;LSA = 1;break; //Y3 LED4 ���Ӵ����������������
			case 6: LSC = 0;LSB = 1;LSA = 0;break; //Y2 LED3 ���Ӵ�����������������
			case 7: LSC = 0;LSB = 0;LSA = 1;break; //Y1 LED2 ���Ӵ���������߸������
			case 8: LSC = 0;LSB = 0;LSA = 0;break; //Y0 LED1 ���Ӵ�������ڰ˸������
		}
		SMG_A_DP_PORT = gsmg_code[number]; //�����ѡ����
}*/

/**
  * @brief  ������������������ж��е���
  * @param  ��
  * @retval ��
  */
/*void smg_loop(void)
{
	static u8 i = 1;
	smg_display(i,smg_Buf[i]);
	i++;
	if(i > 8)
		i = 1;
}*/

/*******************************************************************************
* �� �� ��       : smg_display
* ��������		     : ��̬�������ʾ
* ��    ��       : dat��Ҫ��ʾ������
				           location������ʼ�ڼ���λ�ÿ�ʼ��ʾ����Χ1-8
* ��    ��    	 : ��
*******************************************************************************/
void smg_display(u8 dat[], u8 location)
{
	u8 i = 0;
	u8 location_temp = location - 1;
	for(i = location_temp; i < 8;i++)
	{
		switch(i)
		{
			case 0: LSC = 1;LSB = 1;LSA = 1;break; //Y7 LED8 ���Ӵ��������һ�������
			case 1: LSC = 1;LSB = 1;LSA = 0;break; //Y6 LED7 ���Ӵ�������ڶ��������
			case 2: LSC = 1;LSB = 0;LSA = 1;break; //Y5 LED6 ���Ӵ�����������������
			case 3: LSC = 1;LSB = 0;LSA = 0;break; //Y4 LED5 ���Ӵ���������ĸ������
			case 4: LSC = 0;LSB = 1;LSA = 1;break; //Y3 LED4 ���Ӵ����������������
			case 5: LSC = 0;LSB = 1;LSA = 0;break; //Y2 LED3 ���Ӵ�����������������
			case 6: LSC = 0;LSB = 0;LSA = 1;break; //Y1 LED2 ���Ӵ���������߸������
			case 7: LSC = 0;LSB = 0;LSA = 0;break; //Y0 LED1 ���Ӵ�������ڰ˸������
		}
		SMG_A_DP_PORT = dat[i - location_temp]; //���Ͷ�ѡ����
		delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
		SMG_A_DP_PORT=0x00;//����
	}
}


