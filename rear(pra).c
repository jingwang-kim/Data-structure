#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
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

int eval(char *exp)
{
	int value, op1, op2;
	char ch;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);
	for (int i = 0;i < len;i++)
	{
		ch = exp[i];
		if (ch != '+'&&ch != '-'&&ch != '*'&&ch != '/')
		{
			value = ch - '0';
			push(&s, value);
		}

		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch)
			{
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}

	}
	return pop(&s);
}


int main(void)
{
	char *exp = malloc(sizeof(char)*MAX_STACK_SIZE);
	printf("���� �Է�:");
	scanf("%s", exp);
	int result = eval(exp);
	printf("�����: %d", result);
	free(exp);
	return 0;
}