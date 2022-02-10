#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType *s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// �����Լ�
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� =====

int Checkpipe(char *str)
{
	StackType s;
	init_stack(&s);
	int sum = 0;
	int num = 0;
	for (int i = 0;i < strlen(str);i++)
	{
		if (str[i] == '(')
		{
			push(&s, str[i]);
			if (str[i + 1] == '(')
				num++;
		}

		else
		{
			pop(&s);
			if (str[i - 1] == '(')
			{
				sum += num;
			}

			else
			{
				num--;
				sum += 1;
			}
		}
	}
	return sum;
}

int main(void)
{
	printf("��ȣ �Է�: ");
	char *str = malloc(sizeof(char)*MAX_STACK_SIZE);
	scanf("%s", str);
	int sum = Checkpipe(str);
	printf("�������� ����: %d", sum);
}