#include "reg52.h"
sbit LED1 = P2^0;
sbit KEY1 = P3^1;
void Delay(xms)  //@12.000MHz
{
 unsigned char i, j;
 while(xms)
 {
  i = 2;
 j = 239;
 do
 {
  while (--j);
 } while (--i);
 xms--;
 }
}
void main()
{
	while(1)
	{
		if(KEY1 == 0)
		{
			Delay(20);
			while(KEY1 == 0)
				Delay(20);
			LED1 = !LED1;
		}
	}
}