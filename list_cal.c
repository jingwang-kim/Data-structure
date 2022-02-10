#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ListNode {
	int coef;             //계수
	int expon;            //지수
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
	if (temp == NULL) error("메모리 할당 에러");
	printf("계수 입력: ");
	scanf("%d", &temp->coef);
	printf("지수 입력: ");
	scanf("%d", &temp->expon);
	temp->link = NULL;

	if (plist->tail == NULL)
		plist->head = plist->tail = temp;

	else                                      //2번째 노드 이상부터 실행
	{
		plist->tail->link = temp;             //tail을 temp에 연결
		plist->tail = temp;                   //지금의 새 노드가 tail이 됨
	}
}

int cal(ListType* plist)
{
	int x = 0;
	printf("x값 입력: ");
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
		printf("더 입력하시겠습니까? (yes=1, no=0) ");
		scanf("%d", &choice);
		if (choice == 0)
			break;
	}

	int a = 0;
	do
	{
		double result = cal(list);
		printf("계산된 값 : %.0lf \n", result);
		printf("===================================\n");
		printf("다른 값을 넣으려면 1, 종료하려면 0을 입력하세요. ");
		scanf("%d", &a);
		if (a == 0)
			return 0;
	} while (1);
	
	return 0;

}