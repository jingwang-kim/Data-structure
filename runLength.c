#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
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

StackType CountStr(char *str)
{
	int count = 0;
	int i = 0;
	StackType s1, s2;
	init_stack(&s1);
	init_stack(&s2);
	while (str[i] != NULL)
	{
		count = 0;
		char check = str[i++];
		count++;
		while (check == str[i])
		{
			count++;
			i++;
		}
		push(&s1, count+'0');
		if ('a' <= check && 'z' >= check)
			push(&s1, check);

	}

	while (!is_empty(&s1))
		push(&s2, pop(&s1));
	
	return s2;
}


int main(void)
{
	char *str=malloc(sizeof(char)*MAX_STACK_SIZE);
	printf("���ڿ��� �Է��Ͻÿ�:");
	scanf("%s", str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}
	
	StackType s = CountStr(str);

	printf("���ప:");
	while (!is_empty(&s))
	{
		printf("%c", pop(&s));
	}
	printf("\n");
	free(str);

	while (1)
	{
		int n = 0;
		printf("��� �Ͻðڽ��ϱ�? (1.yes 2.no)");
		scanf("%d", &n);
		
		if (n == 1)
		{
			char *str = malloc(sizeof(char)*MAX_STACK_SIZE);
			printf("���ڿ��� �Է��Ͻÿ�:");
			scanf("%s", str);
			for (int i = 0; i < strlen(str);i++)
			{
				str[i] = tolower(str[i]);
			}

			s = CountStr(str);

			printf("���ప:");
			while (!is_empty(&s))
			{
				printf("%c", pop(&s));
			}
			printf("\n");
			free(str);
		}

		else
			return 0;
	}
}