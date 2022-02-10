#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

DListNode *current;

//초기화
void init(DListNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

//출력
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		if (p == current)
			printf("<-|#%s#|->", p->data);
		else
			printf("<-| %s |->", p->data);
	}
	printf("\n");
}

//삽입
void dinsert(DListNode *before, element data)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

//삭제
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

int main(void)
{
	char ch;
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);

	dinsert(head, "Mamamia");
	dinsert(head, "Karatino");
	dinsert(head, "Danceing Queen");

	current = head->rlink;
	print_dlist(head);

	do {
		printf("\n명령어 입력(<,>,q): ");
		ch = getchar();
		if (ch == '<')
		{
			current = current->llink;
			if (current == head)
				current = current->llink;
		}

		else if (ch == '>')
		{
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}
		print_dlist(head);
		getchar();
	} while (ch != 'q');
	free(head);
}