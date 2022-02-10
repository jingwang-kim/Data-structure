#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
		//fprintf(stderr, "���� ���� ����\n");
		return 0;
		//exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType *s)
{
	/*if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else */return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

int prec(char op)  //�켱���� �� �Լ�
{
	switch (op)
	{
	case '(': case ')': return 2; 
	case '^': return 5;
	case '*': case '/': case '%': return 4;
	case '+': case '-': return 3;
	case '>': case '<': return 1;
	case '&': case '|': return 0;
	}
	return -1;
}

void postfix(char *arr)      //�������� ������ �ٲٴ� �Լ�
{
	char ch, top_op;
	char exp[MAX_STACK_SIZE] = { 0, };
	int len = strlen(arr);
	StackType s;
	init_stack(&s);
	int a = 0;

	for (int i = 0;i < len;i++)
	{
		ch = arr[i];
		switch (ch)
		{
		case '+': case '-': case '*': case '/': case '%': case '>': case '<': case '|': case '&':      //�켱���� üũ
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
				exp[a] = pop(&s);
				printf("pop %c \n", exp[a]);
				a++;
			}
			printf("push %c \n", ch);
			push(&s, ch);
			break;

		case '^':
			printf("push %c \n", ch);
			push(&s, ch);
			break;

		case '(':
			printf("push %c \n", ch);
			push(&s, ch);
			break;

		case ')':
			top_op = pop(&s);
			printf("pop %c \n", top_op);
			while (top_op != '(') {
				exp[a] = top_op;
				top_op = pop(&s);
				printf("pop %c \n", top_op);
				a++;
			}
			break;

		default:
			exp[a] = ch;
			a++;
			break;
		}
	}

	while (!is_empty(&s)) {
		exp[a] = pop(&s);
		printf("pop %c \n", exp[a]); 
		a++;
	}

	exp[a] = NULL;

	strcpy(arr, exp);
}

int eval(char *exp)         //���� ���
{
	int value, op1, op2;
	int and = 0;
	int or = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init_stack(&s);

	for (int i = 0;i < len;i++)
	{
		ch = exp[i];
		if (ch != '+'&&ch != '-'&&ch != '*'&&ch != '/'&&ch != '%'&&ch!='^'&&ch!='('&&ch!=')'&&ch!='<'&&ch!='>'&&ch!='&'&&ch!='|')
		{
			value = ch - '0';
			printf("push %d \n", value);
			push(&s, value);
		}

		else
		{
			op2 = pop(&s);

			if (is_empty(&s)) {
				fprintf(stderr, "------------------�ǿ����ڰ� �����մϴ�.------------------\n");
				return 0;
				//exit(1);
			}
			printf("pop %d \n", op2);
			op1 = pop(&s);

			printf("pop %d \n", op1);
			switch (ch)
			{
			case'+': 
				printf("%d + %d ��� ���: %d \n", op1, op2, op1 + op2);
				push(&s, op1 + op2); 
				break;
			
			case'-': 
				printf("%d - %d ��� ���: %d \n", op1, op2, op1 - op2);
				push(&s, op1 - op2);
				break;
			
			case'*': 
				printf("%d * %d ��� ���: %d \n", op1, op2, op1 * op2);
				push(&s, op1 * op2); 
				break;
			
			case'/': 
				printf("%d / %d ��� ���: %d \n", op1, op2, op1 / op2);
				push(&s, op1 / op2); 
				break;
			
			case'%':
				printf("%d %% %d ��� ���: %d \n",op1, op2, op1 % op2);
				push(&s, op1 % op2); 
				break;
			
			case'^': 
				printf("%d ^ %d ��� ���: %.0lf \n", op1, op2, pow(op1, op2));
				push(&s, pow(op1, op2)); 
				break;

			case '<':
				printf("%d < %d ��� ���: %d \n", op1, op2, op1<op2);
				push(&s, op1 < op2);
				break;

			case '>':
				printf("%d > %d ��� ���: %d \n", op1, op2, op1>op2);
				push(&s, op1 > op2);
				break;

			case '|':
				if (op1!=0 || op2!=0)
				{
					or = 1;
				}
				else
					or = 0;
				printf("%d | %d ��� ���: %d \n", op1, op2, or);
				push(&s, or);
				break;

			case '&':
				if (op1==1 && op2==1)
				{
					and = 1;
				}
				else
					and = 0;
				printf("%d & %d ��� ���: %d \n", op1, op2, and);
				push(&s, and);
				break;
			}
		}
	}

	if (s.top!=0)
	{
		printf("-----------------�����ڰ� �����մϴ�.----------------- \n");
		return 0;
	}

	else
		return pop(&s);
}

int main(void)
{
	do {
		char *arr = malloc(sizeof(char)*MAX_STACK_SIZE);
		printf("���� ǥ��� ���� �Է�:");
		scanf("%s", arr);
		postfix(arr);

		//��ȯ �Ǿ����� Ȯ��
		printf("���� ǥ�� ��ȯ �˻�: ");
		for (int i = 0;i < strlen(arr);i++)
			printf("%c", arr[i]);
		printf("\n");

		double result = eval(arr);
		printf("���� ��� ���: %.0lf \n", result);

		printf("��� �Ͻðڽ��ϱ�?(1.yes, 2.no) \n");
		int n = 0;
		scanf("%d", &n);
		if (n == 2)
			return 0;
		free(arr);
	} while (1);
}