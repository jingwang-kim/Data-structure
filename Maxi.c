#include <stdio.h>

int Maxi_num(int *arr,int n)
{
	if (n == 0)
		return arr[0];
	int maxnum = Maxi_num(arr, n - 1);
	
	if (maxnum < arr[n])
	{
		return arr[n];
	}
	else
		arr[n] = maxnum;
	return arr[n];
}

int main(void)
{
	int arr[10] = { 0, };
	printf("10���� ���� �Է�: ");
	for (int i = 0;i < 10;i++)
	{
		scanf("%d", &arr[i]);
	}
	int n = 9;
	int max=Maxi_num(arr,n);
	printf("�ִ밪�� %d �Դϴ�.", max);
	return 0;
}