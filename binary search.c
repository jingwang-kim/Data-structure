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
				printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid], mid);
				printf("찾으려는 타겟 %d은(는) %d번째 인덱스에 있습니다. \n", target, mid);
				num++;
				break;
			}

			else if (target < arr[mid])
			{
				last = mid - 1;
				printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid],mid);
				num++;
			}

			else
			{
				first = mid + 1;
				printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid], mid);
				num++;
			}
		}

		else {
			printf("반복문으로 돌렸을 때 값이 존재하지 않습니다. \n");
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
		printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid], mid);
		return mid;
	}
	else if (target < arr[mid])
	{
		printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid], mid);
		RecurSearch(arr, target, first, mid - 1);
	}
	else
	{
		printf("현재 중간값과 인덱스: [%d,%d] \n", arr[mid], mid);
		RecurSearch(arr, target, mid + 1, last);
	}
}

int main(void)
{
	int len;
	int target;
	int first = 0;
	printf("몇 개의 정수를 업력하시겠습니까?: ");
	scanf("%d", &len);
	int *arr = malloc(sizeof(int)*len);
	int last = len - 1;
	printf("배열에 저장할 정수를 입력하시오 (%d개): ", len);
	for (int i = 0;i < len;i++)
		scanf("%d", &arr[i]);

	//정렬
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

	//정렬 되었는지 확인
	for (int i = 0;i < len;i++)
		printf("[%d]", arr[i]);
	printf("\n");

	printf("타겟 입력: ");
	scanf("%d", &target);

	printf("[반복문을 이용하여 이진탐색]\n");
	int num=ForSearch(arr, target, first, last);
	
	printf("[재귀함수를 이용하여 이진탐색]\n");
	int result=RecurSearch(arr, target, first, last);
	
	if (result == -1)
	{
		printf("재귀함수로 돌렸을 때 값이 존재하지 않습니다. \n");
		return 0;
	}
	else
		printf("찾으려는 타겟 %d은(는) %d번째 인덱스에 있습니다. \n", target, result);
	printf("----------------------------------\n");
	printf("%d 번만에 값을 찾았습니다. \n", num);
	free(arr);
	return 0;
}