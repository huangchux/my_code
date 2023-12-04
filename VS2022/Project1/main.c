#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int score;
	char grade;
	printf("Your score:");
	scanf("%d", &score);
	if (score >= 90 && score <= 100)
	{
		grade = 'A';
	}
	else if (score >= 80 && score <= 89)
	{
		grade = 'B';
	}
	else if (score >= 70 && score <= 79)
	{
		grade = 'C';
	}
	else if (score >= 60 && score <= 69)
	{
		grade = 'D';
	}
	else if (score < 60)
	{
		grade = 'E';
	}
	printf("你的成绩等级为：%c\n", grade);
	return 0;
}