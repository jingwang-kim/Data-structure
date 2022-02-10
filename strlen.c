#include <stdio.h>

int IndexLen(char *str)
{
	int count = 0;
	for (int i = 0 ; str[i] != NULL ; i++)
	{
		count++;
	}
	return count;
}

int PointerLen(char *str)
{
	int count = 0;
	for (int i = 0 ; *(str+i) != NULL ; i++)
	{
		count++;
	}
	return count;
}

int RecursiveLen(char *str)
{
	if (*str == NULL)
		return 0;
	return 1 + RecursiveLen(str + 1);
}

int main(void)
{
	char str[20];
	printf("길이를 계산할 문자열 입력: ");
	scanf("%s", str);
	printf("인덱스를 이용한 길이 계산: %d \n", IndexLen(str));
	printf("포인터를 이용한 길이 계산: %d \n", PointerLen(str));
	printf("순환호출을 이용한 길이계산: %d \n", RecursiveLen(str));
	return 0;
}