#include <stdio.h>

int Interative(int m, int n)
{
	int sum = 0;
	for (int i = m;i <= n;i++)
	{
		sum += i;
	}
	return sum;
}

int Recursive(int m, int n)
{
	if (n < m)
		return 0;
	return n + Recursive(m, n - 1);
}

int main(void)
{
	int firstnum = 0, lastnum = 0;
	
	printf("처음 숫자를 입력하세요: ");
	scanf("%d", &firstnum);
	
	printf("마지막 숫자를 입력하세요: ");
	scanf("%d", &lastnum);
	
	printf("반복문을 이용한 합: %d \n", Interative(firstnum, lastnum));
	printf("순환호출을 이용한 합: %d \n", Recursive(firstnum, lastnum));
	return 0;
}