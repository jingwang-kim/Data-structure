#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 큐 초기화 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 공백 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 원형큐 출력
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

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 피크 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

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
	printf("문자열을 입력하시오:");
	gets(str);
	for (int i = 0; i < strlen(str);i++)
	{
		str[i] = tolower(str[i]);
	}

	int result = palindrome(str);

	if (result == -1)
		printf("회문이 아닙니다. \n");
	else
		printf("회문입니다. \n");

	free(str);
	return 0;
}