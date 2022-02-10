/*//2. run-length ���� -  ���� 143�� ���� 12
//������ ���� ���ڿ��� �����ϴ� ���α׷��� �ۼ��Ͻÿ�.  "4a3b"�� 'a'�� 4��, 'b'�� 3�� �ִٴ� �ǹ��̴�.
//�̷��� ���� ����� ������ �����̶�� �Ѵ�.�ҹ��ڿ� �빮�ڴ� �������� �ʴ´�.
//����� ���ڿ������� �ҹ��ڷ� ����Ѵ�.������ peek() ������ ����غ���.
//  ��: ���ڿ� �Է� aaaAbBb     ������ 4a3b

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 


int check_matching(const char* in)
{
	StackType s1, s2;
	char ch, open_ch;
	char ch2, pick;
	int i, n = strlen(in);     // n= ���ڿ��� ����
	init_stack(&s1);         // ������ �ʱ�ȭ
	init_stack(&s2);

	for (i = 0; i < n; i++) {
		ch = in[i];      // ch = ���� ����
		ch = tolower(ch);//�ҹ���
		push(&s1, ch);//�Է�
	}

	for (i = 0; i < n; i++) {
		ch2 = pop(&s1);
		push(&s2, ch2);//������ġ
	}

	printf("������: ");
	i = 0;
	int count = 0;
	while (i < n) {
		pick = in[i++];
		count++;
		if (pick == in[i]) {
			count++;
			i++;
		}
		else {
			printf("%d%c", count, pick);
			count = 0;
		}
	}
	printf("%d%c\n", count, pick);

	printf("-----------------------\n");
	printf("�Է��ߴ� ���ڿ�:");

	for (i = 0; i < n; i++) {
		open_ch = pop(&s2);
		printf("%c", open_ch);
	}

	printf("\n-----------------------\n");


	if (!is_empty(&s2)) return 0; // ���ÿ� ���������� ����
	return 1;
}

int main(void) {
	char* p = malloc(sizeof(char) * 20);
	int result;
	printf("���ڿ��Է�: ");
	scanf("%s", p);

	printf("-----------------------\n");

	result = check_matching(p);
	if (result == 1)
		printf("����");
	else
		printf("����");

	printf("\n");

	free(p);
	return 0;
}*/

//1�� ����
//1. ��ȣ ��Ī ��ȣ �ű�� ? ���� 143�� ���� 11
//���Ŀ� �ִ� ��ȣ�� ��ȣ�� ����ϴ� ���α׷��� �ۼ��϶�. 
//���� ��ȣ�� ���� ������ ��ȣ ��ȣ�� �ϳ��� �����Ѵ�.������ ��ȣ�� ������ ��Ī�Ǵ� ���� ��ȣ�� ��ȣ�� ����Ѵ�.
//((()) (()))
//12332 45541

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

int check_matching(const char* in)
{
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in);// n= ���ڿ��� ����
	init_stack(&s);// ������ �ʱ�ȭ
	StackType num;
	int number = 1;

	for (i = 0; i < n; i++) {
		ch = in[i];// ch = ���� ����
		switch (ch) {
		case '(':   case '[':    case '{':
			push(&s, ch);
			printf("%d", number);
			push(&num, number);
			number++;
			break;
		case ')':   case ']':    case '}':
			if (is_empty(&s))  return 0;
			else {
				open_ch = pop(&s);
				printf("%c", pop(&num));
				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}')) {
					return 0;
				}
				break;
			}
		}
	}
	if (!is_empty(&s)) return 0;// ���ÿ� ���������� ����
	return 1;
}

int main(void) {
	char* p = malloc(sizeof(char) * 10);
	printf("��ȣ �Է�: ");
	scanf("%s", p);
	if (check_matching(p) == 1)
		printf("��ȣ ��Ī ����");
	else
		printf("��ȣ ��Ī ����");
	free(p);
	return 0;
}