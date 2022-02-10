#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
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
	printf("문자열을 입력하시오:");
	scanf("%s", str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}
	
	StackType s = CountStr(str);

	printf("압축값:");
	while (!is_empty(&s))
	{
		printf("%c", pop(&s));
	}
	printf("\n");
	free(str);

	while (1)
	{
		int n = 0;
		printf("계속 하시겠습니까? (1.yes 2.no)");
		scanf("%d", &n);
		
		if (n == 1)
		{
			char *str = malloc(sizeof(char)*MAX_STACK_SIZE);
			printf("문자열을 입력하시오:");
			scanf("%s", str);
			for (int i = 0; i < strlen(str);i++)
			{
				str[i] = tolower(str[i]);
			}

			s = CountStr(str);

			printf("압축값:");
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