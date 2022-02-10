#include <stdio.h>
#include <stdlib.h>

int ForSearch(int *arr, int target, int first, int last)
{
	int num = 0;
	while (1)
	{
		if (first <= last)
		{
			int mid = (first + last) / 2;

			if (target == arr[mid])
			{
				printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid], mid);
				printf("ã������ Ÿ�� %d��(��) %d��° �ε����� �ֽ��ϴ�. \n", target, mid);
				num++;
				break;
			}

			else if (target < arr[mid])
			{
				last = mid - 1;
				printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid],mid);
				num++;
			}

			else
			{
				first = mid + 1;
				printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid], mid);
				num++;
			}
		}

		else {
			printf("�ݺ������� ������ �� ���� �������� �ʽ��ϴ�. \n");
			break;
		}
	}
	printf("----------------------------------\n");
	return num;
	
}

int RecurSearch(int *arr, int target, int first, int last)
{
	int mid = (first + last) / 2;
	if (first > last)
		return -1;
	
	if (target == arr[mid])
	{
		printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid], mid);
		return mid;
	}
	else if (target < arr[mid])
	{
		printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid], mid);
		RecurSearch(arr, target, first, mid - 1);
	}
	else
	{
		printf("���� �߰����� �ε���: [%d,%d] \n", arr[mid], mid);
		RecurSearch(arr, target, mid + 1, last);
	}
}

int main(void)
{
	int len;
	int target;
	int first = 0;
	printf("�� ���� ������ �����Ͻðڽ��ϱ�?: ");
	scanf("%d", &len);
	int *arr = malloc(sizeof(int)*len);
	int last = len - 1;
	printf("�迭�� ������ ������ �Է��Ͻÿ� (%d��): ", len);
	for (int i = 0;i < len;i++)
		scanf("%d", &arr[i]);

	//����
	int temp = 0;
	for (int i = 0;i < last - 1;i++)
	{
		for (int j = 0;j < last - i;j++)
		{
			if (arr[j + 1] < arr[j])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	//���� �Ǿ����� Ȯ��
	for (int i = 0;i < len;i++)
		printf("[%d]", arr[i]);
	printf("\n");

	printf("Ÿ�� �Է�: ");
	scanf("%d", &target);

	printf("[�ݺ����� �̿��Ͽ� ����Ž��]\n");
	int num=ForSearch(arr, target, first, last);
	
	printf("[����Լ��� �̿��Ͽ� ����Ž��]\n");
	int result=RecurSearch(arr, target, first, last);
	
	if (result == -1)
	{
		printf("����Լ��� ������ �� ���� �������� �ʽ��ϴ�. \n");
		return 0;
	}
	else
		printf("ã������ Ÿ�� %d��(��) %d��° �ε����� �ֽ��ϴ�. \n", target, result);
	printf("----------------------------------\n");
	printf("%d ������ ���� ã�ҽ��ϴ�. \n", num);
	free(arr);
	return 0;
}