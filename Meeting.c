#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE  15
typedef int element;
typedef struct { // ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

/*// ����ť ��� �Լ�
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
}*/

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

// ���� �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

void Meeting()
{
	QueueType qboy, qgirl;
	init_queue(&qboy);
	init_queue(&qgirl);
	int random;
	int bcnt = 1;
	int gcnt = 1;
	int meet = 1;
	for (int i = 0;i < 100;i++)
	{
		random = rand() % 2;
		if (random == 0)  // ¦�� = ����
		{
			enqueue(&qgirl, random);
			printf("���� %d ���� - ", gcnt);
			gcnt++;
		}
		
		else  // Ȧ�� = ����
		{
			enqueue(&qboy, random);
			printf("���� %d ���� - ", bcnt);
			bcnt++;
		}

		if (!is_empty(&qboy) && !is_empty(&qgirl) && qboy.front == qgirl.front)
		{
			dequeue(&qgirl);
			dequeue(&qboy);
			printf("��%d/��%d ��Ī \n",meet ,meet );
			meet++;
		}

		else
			printf("��� \n");

		printf("���� front: %d, rear: %d \n", qboy.front, qboy.rear);
		printf("���� front: %d, rear: %d \n", qgirl.front, qgirl.rear);
		printf("\n");
		Sleep(300);
	}
	printf("�Ϸ� \n");
}

int main(void)
{
	Meeting();
	return 0;
}