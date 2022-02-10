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
	
	printf("ó�� ���ڸ� �Է��ϼ���: ");
	scanf("%d", &firstnum);
	
	printf("������ ���ڸ� �Է��ϼ���: ");
	scanf("%d", &lastnum);
	
	printf("�ݺ����� �̿��� ��: %d \n", Interative(firstnum, lastnum));
	printf("��ȯȣ���� �̿��� ��: %d \n", Recursive(firstnum, lastnum));
	return 0;
}