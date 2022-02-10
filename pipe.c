#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
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
	printf("괄호 입력: ");
	char *str = malloc(sizeof(char)*MAX_STACK_SIZE);
	scanf("%s", str);
	int sum = Checkpipe(str);
	printf("파이프의 개수: %d", sum);
}