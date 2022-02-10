#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 30

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
	/*if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else*/ return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

int check_matching(const char *in)
{
	StackType s;
	char ch;
	int n = strlen(in); 
	int temp = 1;
	int result = 0;
	init_stack(&s);

	for (int i = 0; i < n; i++) {
		ch = in[i];		// ch = 다음 문자
		switch (ch) {
		case '(':       //'('나오면 *2
			temp *= 2;
			push(&s, ch);
			break;

		case '[':       //'['나오면 *3
			temp *= 3;
			push(&s, ch);
			break;

		case ')':
			if (in[i - 1] == '(')     //'()' 일 때 result 에 값 저장
				result += temp;

			else if (ch == ')' && (is_empty(&s) || peek(&s) != '(')) //괄호 검사
			{
				printf("0");
				return 0;
			}

			if (peek(&s) == '(')  //현재 top스택이 '('일 때 temp 값 줄어듦
			{
				pop(&s);
				temp /= 2;
			}
			break;

		case ']':
			if (in[i - 1] == '[')     //'[]'일 때 result에 값 저장
				result += temp;

			else if (ch == ']' && (is_empty(&s) || peek(&s) != '['))  //괄호 검사
			{
				printf("0");
				return 0;
			}

			if (peek(&s) == '[')  //현재 top스택이 '['일 때 temp 값 줄어듦
			{
				pop(&s);
				temp /= 3;
			}
			break;
		}
	}

	if (!is_empty(&s)) {
		printf("0");
		return 0; // 스택에 남아있으면 오류
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