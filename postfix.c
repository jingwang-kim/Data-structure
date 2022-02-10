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
		//fprintf(stderr, "스택 공백 에러\n");
		return 0;
		//exit(1);
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
	else */return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

int prec(char op)  //우선순위 비교 함수
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

void postfix(char *arr)      //중위에서 후위로 바꾸는 함수
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
		case '+': case '-': case '*': case '/': case '%': case '>': case '<': case '|': case '&':      //우선순위 체크
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

int eval(char *exp)         //수식 계산
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
				fprintf(stderr, "------------------피연산자가 부족합니다.------------------\n");
				return 0;
				//exit(1);
			}
			printf("pop %d \n", op2);
			op1 = pop(&s);

			printf("pop %d \n", op1);
			switch (ch)
			{
			case'+': 
				printf("%d + %d 계산 결과: %d \n", op1, op2, op1 + op2);
				push(&s, op1 + op2); 
				break;
			
			case'-': 
				printf("%d - %d 계산 결과: %d \n", op1, op2, op1 - op2);
				push(&s, op1 - op2);
				break;
			
			case'*': 
				printf("%d * %d 계산 결과: %d \n", op1, op2, op1 * op2);
				push(&s, op1 * op2); 
				break;
			
			case'/': 
				printf("%d / %d 계산 결과: %d \n", op1, op2, op1 / op2);
				push(&s, op1 / op2); 
				break;
			
			case'%':
				printf("%d %% %d 계산 결과: %d \n",op1, op2, op1 % op2);
				push(&s, op1 % op2); 
				break;
			
			case'^': 
				printf("%d ^ %d 계산 결과: %.0lf \n", op1, op2, pow(op1, op2));
				push(&s, pow(op1, op2)); 
				break;

			case '<':
				printf("%d < %d 계산 결과: %d \n", op1, op2, op1<op2);
				push(&s, op1 < op2);
				break;

			case '>':
				printf("%d > %d 계산 결과: %d \n", op1, op2, op1>op2);
				push(&s, op1 > op2);
				break;

			case '|':
				if (op1!=0 || op2!=0)
				{
					or = 1;
				}
				else
					or = 0;
				printf("%d | %d 계산 결과: %d \n", op1, op2, or);
				push(&s, or);
				break;

			case '&':
				if (op1==1 && op2==1)
				{
					and = 1;
				}
				else
					and = 0;
				printf("%d & %d 계산 결과: %d \n", op1, op2, and);
				push(&s, and);
				break;
			}
		}
	}

	if (s.top!=0)
	{
		printf("-----------------연산자가 부족합니다.----------------- \n");
		return 0;
	}

	else
		return pop(&s);
}

int main(void)
{
	do {
		char *arr = malloc(sizeof(char)*MAX_STACK_SIZE);
		printf("중위 표기로 수식 입력:");
		scanf("%s", arr);
		postfix(arr);

		//변환 되었는지 확인
		printf("후위 표기 변환 검사: ");
		for (int i = 0;i < strlen(arr);i++)
			printf("%c", arr[i]);
		printf("\n");

		double result = eval(arr);
		printf("최종 계산 결과: %.0lf \n", result);

		printf("계속 하시겠습니까?(1.yes, 2.no) \n");
		int n = 0;
		scanf("%d", &n);
		if (n == 2)
			return 0;
		free(arr);
	} while (1);
}