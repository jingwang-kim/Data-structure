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
	printf("문자열을 입력하시오:");
	gets(str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}
	
	int result = Palindrome(str);

	if (result == -1)
		printf("회문이 아닙니다. \n");
	else
		printf("회문입니다. \n");

	free(str);
	return 0;
}