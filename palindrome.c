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

int Palindrome(char *str)
{
	StackType s;
	init_stack(&s);
	int len = strlen(str);
	char ch, open;
	
	for (int i = 0;i < len;i++)
	{
		ch = str[i];
		if (ch == ' ' || ch == '.' || ch == '\"' || ch == '\'' || ch == ',')
			continue;
		push(&s, ch);
	}

	for (int i = 0;i < len;i++)
	{
		ch = str[i];
		if (ch == ' ' || ch == '.' || ch == '\"' || ch == '\'' || ch == ',')
			continue;
		open = pop(&s);
		if (ch != open)
			return -1;
	}

}

int main(void)
{
	char *str = malloc(sizeof(char)*MAX_STACK_SIZE);
	printf("���ڿ��� �Է��Ͻÿ�:");
	gets(str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}
	
	int result = Palindrome(str);

	if (result == -1)
		printf("ȸ���� �ƴմϴ�. \n");
	else
		printf("ȸ���Դϴ�. \n");

	free(str);
	return 0;
}