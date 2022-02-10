#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입함수
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// 피크함수
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

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
	printf("수식 입력:");
	scanf("%s", exp);
	int result = eval(exp);
	printf("결과값: %d", result);
	free(exp);
	return 0;
}