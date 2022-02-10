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
	printf("���̸� ����� ���ڿ� �Է�: ");
	scanf("%s", str);
	printf("�ε����� �̿��� ���� ���: %d \n", IndexLen(str));
	printf("�����͸� �̿��� ���� ���: %d \n", PointerLen(str));
	printf("��ȯȣ���� �̿��� ���̰��: %d \n", RecursiveLen(str));
	return 0;
}