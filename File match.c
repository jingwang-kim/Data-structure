#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 7000

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
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 


int check_matching(char *arr ,FILE *fp2)
{
	StackType s;
	char ch, open_ch;
	int i = 0;
	init_stack(&s);			// ������ �ʱ�ȭ

	for(int i=0;i<strlen(arr);i++)
	{
		ch = arr[i];
		switch (ch) {

		case '\'':    //���� ����ǥ ���� ó��
			i++;
			while (arr[i] != '\'')
				i++;
			break;

		case '\"':    //ū ����ǥ ���� ó��
			i++;
			while (arr[i] != '\"')
				i++;
			break;

		case '/':     // �ּ� ���� ó��
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
					printf("��ȣ �˻� ����");
					fputs("��ȣ �˻� ���� \n", fp2);
					return 0;
				}
				break;
			}
		}
	}

	if (!is_empty(&s))
	{
		printf("���ÿ� ��ȣ�� �����ֽ��ϴ�. \n");
		fputs("���ÿ� ��ȣ�� �����ֽ��ϴ�. \n", fp2);
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
		printf("������ ������ �ʽ��ϴ�. \n");
		exit(1);
	}

	FILE *fp2;
	if ((fp2 = fopen("stack_out.txt", "w")) == NULL)
	{
		printf("������ ������ �ʽ��ϴ�. \n");
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
		printf("��ȣ ��Ī ����");
		fputs("��ȣ ��Ī ���� \n", fp2);
	}
	else {
		printf("��ȣ ��Ī ���� \n");
		fputs("��ȣ ��Ī ���� \n", fp2);
	}
	free(arr);
	fclose(fp1);
	fclose(fp2);
	return 0;
}