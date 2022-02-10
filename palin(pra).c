#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ť �ʱ�ȭ �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ���� ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ����ť ���
void queue_print(QueueType *q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ��ũ �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

int palindrome(char *str)
{
	QueueType q;
	init_queue(&q);
	char ch, open;
	int len = strlen(str);

	for (int i = 0;i < len;i++)
	{
		ch = str[i];
		if (ch == ' ' || ch == '.' || ch == ',' || ch == '\"' || ch == '\'')
			continue;
		enqueue(&q, ch);
	}

	for (int i = 0;i < len;i++)
	{
		ch = str[i];
		if (ch == ' ' || ch == '.' || ch == ',' || ch == '\"' || ch == '\'')
			continue;
		open = dequeue(&q);
		if (ch != open)
			return -1;
	}
}

int main(void)
{
	char *str = malloc(sizeof(char)*MAX_QUEUE_SIZE);
	printf("���ڿ��� �Է��Ͻÿ�:");
	gets(str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}

	int result = palindrome(str);

	if (result == -1)
		printf("ȸ���� �ƴմϴ�. \n");
	else
		printf("ȸ���Դϴ�. \n");

	free(str);
	return 0;
}