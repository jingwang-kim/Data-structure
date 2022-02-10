#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ListNode {
	int coef;             //���
	int expon;            //����
	struct ListNode *link;
}ListNode;

typedef struct ListType {
	ListNode *head;
	ListNode *tail;
}ListType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListType *create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));
	plist->head = plist->tail = NULL;
	return plist;
}

void insert_last(ListType* plist)
{
	ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
	if (temp == NULL) error("�޸� �Ҵ� ����");
	printf("��� �Է�: ");
	scanf("%d", &temp->coef);
	printf("���� �Է�: ");
	scanf("%d", &temp->expon);
	temp->link = NULL;

	if (plist->tail == NULL)
		plist->head = plist->tail = temp;

	else                                      //2��° ��� �̻���� ����
	{
		plist->tail->link = temp;             //tail�� temp�� ����
		plist->tail = temp;                   //������ �� ��尡 tail�� ��
	}
}

int cal(ListType* plist)
{
	int x = 0;
	printf("x�� �Է�: ");
	scanf("%d", &x);
	double sum = 0;
	ListNode *p = plist->head;
	for (;p;p = p->link)
	{
		sum += pow(p->coef*x, p->expon);
	}
	return sum;
}

void print_poly(ListType *plist)
{
	ListNode *p = plist->head;

	for (;p;p = p->link)
	{
		printf("%dx ^ %d + ", p->coef, p->expon);
	}
	printf("\n");
}

int main(void)
{
	int choice;
	ListType *list;
	list = create();
	while (1)
	{
		insert_last(list);
		print_poly(list);
		printf("===================================\n");
		printf("�� �Է��Ͻðڽ��ϱ�? (yes=1, no=0) ");
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}

	int a = 0;
	do
	{
		double result = cal(list);
		printf("���� �� : %.0lf \n", result);
		printf("===================================\n");
		printf("�ٸ� ���� �������� 1, �����Ϸ��� 0�� �Է��ϼ���. ");
		scanf("%d", &a);
		if (a == 0)
			return 0;
	} while (1);
	
	return 0;

}