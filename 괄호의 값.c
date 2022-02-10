#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 30

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
	/*if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else*/ return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

int check_matching(const char *in)
{
	StackType s;
	char ch;
	int n = strlen(in); 
	int temp = 1;
	int result = 0;
	init_stack(&s);

	for (int i = 0; i < n; i++) {
		ch = in[i];		// ch = ���� ����
		switch (ch) {
		case '(':       //'('������ *2
			temp *= 2;
			push(&s, ch);
			break;

		case '[':       //'['������ *3
			temp *= 3;
			push(&s, ch);
			break;

		case ')':
			if (in[i - 1] == '(')     //'()' �� �� result �� �� ����
				result += temp;

			else if (ch == ')' && (is_empty(&s) || peek(&s) != '(')) //��ȣ �˻�
			{
				printf("0");
				return 0;
			}

			if (peek(&s) == '(')  //���� top������ '('�� �� temp �� �پ��
			{
				pop(&s);
				temp /= 2;
			}
			break;

		case ']':
			if (in[i - 1] == '[')     //'[]'�� �� result�� �� ����
				result += temp;

			else if (ch == ']' && (is_empty(&s) || peek(&s) != '['))  //��ȣ �˻�
			{
				printf("0");
				return 0;
			}

			if (peek(&s) == '[')  //���� top������ '['�� �� temp �� �پ��
			{
				pop(&s);
				temp /= 3;
			}
			break;
		}
	}

	if (!is_empty(&s)) {
		printf("0");
		return 0; // ���ÿ� ���������� ����
	}

	return result;
}

int main(void)
{
	char *p = malloc(sizeof(char)*MAX_STACK_SIZE);
	scanf("%s", p);
	int result = check_matching(p);
	if (result == 0)
		return 0;
	else
		printf("%d", result);
	free(p);
	return 0;
}