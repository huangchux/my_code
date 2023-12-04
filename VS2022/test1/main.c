#define _CRT_SECURE_NO_WARNINGS 1

#include "stdio.h"


typedef struct
{
	int a;
	int b;
} Test_st;

void func(Test_st *p)
{
	p->a = 99;
	p->b = 11;
}


int main(void)
{
	Test_st Test = { 10,20 };

	func(&Test);

	printf("%d----%d\r\n", Test.a, Test.b);


	return 0;
}