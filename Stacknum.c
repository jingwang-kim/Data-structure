#include <stdio.h>
#include <stdlib.h>
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

int check_matching(const char *in)
{
	StackType s1;
	StackType s2;
	char ch, open_ch;
	int i, n = strlen(in);  	// n= ���ڿ��� ����
	init_stack(&s1);
	init_stack(&s2);            // ������ �ʱ�ȭ
	int numpush = 1;

	for (i = 0; i < n; i++) {
		ch = in[i];		// ch = ���� ����
		switch (ch) {
		case '(':   case '[':    case '{':
			push(&s1, ch);
			printf("%d ", numpush);
			push(&s2, numpush);
			numpush++;
			break;
		case ')':   case ']':    case '}':
			if (is_empty(&s1))  return 0;
			else {
				printf("%d ", pop(&s2));
				open_ch = pop(&s1);
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}')) {
					return 0;
				}
				break;
			}
		}
	}
	if (!is_empty(&s1)) return 0; // ���ÿ� ���������� ����
	return 1;
}

int main(void)
{
	printf("��ȣ�� �Է��ϼ���: ");
	char *p = malloc(sizeof(char)*MAX_STACK_SIZE);
	scanf("%s", p);
	int result=check_matching(p);
	printf("\n");
	if (result == 1)
		printf("��ȣ �˻� ���� \n", p);
	else
		printf("��ȣ �˻� ���� \n", p);
	free(p);

	while (1)
	{
		int n = 0;
		printf("��� �Ͻðڽ��ϱ�? (1.yes 2.no)");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("��ȣ�� �Է��ϼ���: ");
			char *p = malloc(sizeof(char)*MAX_STACK_SIZE);
			scanf("%s", p);
			int result = check_matching(p);
			printf("\n");
			if (result == 1)
				printf("��ȣ �˻� ���� \n", p);
			else
				printf("��ȣ �˻� ���� \n", p);
			free(p);
		}

		else
			return 0;
	}
	return 0;
}