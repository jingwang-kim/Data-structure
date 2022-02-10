#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 7000

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


int check_matching(char *arr ,FILE *fp2)
{
	StackType s;
	char ch, open_ch;
	int i = 0;
	init_stack(&s);			// 스택의 초기화

	for(int i=0;i<strlen(arr);i++)
	{
		ch = arr[i];
		switch (ch) {

		case '\'':    //작은 따옴표 예외 처리
			i++;
			while (arr[i] != '\'')
				i++;
			break;

		case '\"':    //큰 따옴표 예외 처리
			i++;
			while (arr[i] != '\"')
				i++;
			break;

		case '/':     // 주석 예외 처리
			if (arr[i + 1] == '*')   // '/*'
			{
				i++;
				while (1)
				{
					i++;
					while (arr[i]!='*' && arr[i+1]!='/')
						i++;
					break;
				}
			}
			
			else if (arr[i + 1] == '/')  // '//'
			{
				i++;
				while (arr[i] != '\n')
					i++;
			}
			break;

		case '(':   case '[':    case '{':
			push(&s, ch);
			printf("push %c \n", ch);
			fprintf(fp2, "push %c \n", ch);
			break;

		case ')':   case ']':    case '}':
			if (is_empty(&s))  return 0;
			else {
				open_ch = pop(&s);
				printf("pop %c \n", open_ch);
				fprintf(fp2, "pop %c \n", open_ch);
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}')) {
					printf("괄호 검사 실패");
					fputs("괄호 검사 실패 \n", fp2);
					return 0;
				}
				break;
			}
		}
	}

	if (!is_empty(&s))
	{
		printf("스택에 괄호가 남아있습니다. \n");
		fputs("스택에 괄호가 남아있습니다. \n", fp2);
		return 0;
	}

	return 1;
}

int main(void)
{
	FILE *fp1;
	char ch;
	int i;
	if ((fp1 = fopen("stack_in.txt", "r")) == NULL)
	{
		printf("파일이 열리지 않습니다. \n");
		exit(1);
	}

	FILE *fp2;
	if ((fp2 = fopen("stack_out.txt", "w")) == NULL)
	{
		printf("파일이 열리지 않습니다. \n");
		exit(1);
	}

	char *arr=malloc(sizeof(char)*MAX_STACK_SIZE);
	for(i=0;!feof(fp1);i++)
	{
		arr[i] = fgetc(fp1);
	}
	arr[i] = NULL;


	int check=check_matching(arr, fp2);
	if (check == 1)
	{
		printf("괄호 매칭 성공");
		fputs("괄호 매칭 성공 \n", fp2);
	}
	else {
		printf("괄호 매칭 실패 \n");
		fputs("괄호 매칭 실패 \n", fp2);
	}
	free(arr);
	fclose(fp1);
	fclose(fp2);
	return 0;
}