#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 100
typedef struct element {
	char subject[MAX_SIZE];
	char genre;
	int year;
	int p;      //��� �ð�
}element;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

DListNode *current;

//�ʱ�ȭ
void init(DListNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

//���
void print_list(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		if (p == current)
			printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		else
			printf("| ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
	printf("\n");
}

//������ ���
void print_reverse(DListNode* phead)
{
	DListNode* p;
	for (p = phead->llink; p != phead; p = p->llink)
	{
		if (p == current)
			printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		else
			printf("| ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
	printf("\n");
}

//����
void insert_node(DListNode *phead)
{
	DListNode* newnode = (DListNode *)malloc(sizeof(DListNode));
	DListNode* cur;
	cur = phead->rlink;
	getchar();
	printf("���� �Է�: ");
	gets(newnode->data.subject);

	while (1)
	{
		printf("�帣 �Է� ('A' 'C' 'F' 'R' �� �ϳ�): ");
		scanf("%c", &newnode->data.genre);
		if (newnode->data.genre == 'A' || newnode->data.genre == 'C' || newnode->data.genre == 'F' || newnode->data.genre == 'R')
			break;
		else {
			printf("�ٽ� �Է��ϼ���.\n");
			getchar();
		}
		char a;
		scanf("%c", &a);
	}

	printf("�����⵵ �Է�: ");
	scanf("%d", &newnode->data.year);

	printf("����ð� �Է�: ");
	scanf("%d", &newnode->data.p);

	if (strcmp(phead->rlink->data.subject, newnode->data.subject) == 1)  //�տ� ���� ��
	{
		newnode->llink = phead;              //newnode�� ���ʿ� phead
		newnode->rlink = phead->rlink;       //newnode�� �����ʿ� phead�� ���� ��
		phead->rlink->llink = newnode;       //phead�� ���� ���� ���ʿ� newnode
		phead->rlink = newnode;              //phead�� �����ʿ� newnode
	}                                        //phead newnode newnode->rlink

	else if (strcmp(phead->llink->data.subject, newnode->data.subject) == -1)  //�ڿ� ���� ��
	{
		newnode->rlink = phead;              
		newnode->llink = phead->llink;
		phead->llink->rlink = newnode;
		phead->llink = newnode;
	}

	else
	{
		while (cur != phead)          
		{
			if (strcmp(cur->rlink->data.subject, newnode->data.subject) == 1)
			{
				newnode->llink = cur;                 //new�� ���ʿ� cur
				newnode->rlink = cur->rlink;          //new�� �����ʿ� cur�� ���� ��
				cur->rlink = newnode;                 //cur�� �����ʿ� new
				cur->rlink->llink = newnode;          //cur �������� ���ʿ� new         cur new new->rlink
				break;
			}
		}
		cur = cur->rlink;
	}
}

// ��� ���� ��� �Լ�
int list_length(DListNode *phead)
{
	DListNode *p = phead->rlink;

	int cnt = 0;
	for (p = phead->rlink;p != phead; p = p->rlink)
		cnt++;
	return cnt;
}

//����
void delete_node(DListNode* head)
{
	DListNode *removed;
	removed = head->rlink;
	printf("������ ��ȭ ���� �Է�: ");
	char del[MAX_SIZE];
	scanf("%s", del);

	while (removed != head)
	{
		if (strcmp(removed->data.subject, del) == 0)
		{
			if (strcmp(removed->data.subject, current->data.subject) == 0)
			{
				current = current->rlink;
			}
			removed->llink->rlink = removed->rlink;          //a b c
			removed->rlink->llink = removed->llink;          //a   c
			free(removed);
			printf("�����Ǿ����ϴ�. \n");
			return;
		}

		else
			removed = removed->rlink;
	}

}

//�ֱ� ��ȭ �˻� �Լ�
void recent_year(DListNode *phead)
{
	DListNode *p = phead->rlink;
	int rec = p->data.year;
	for (p = phead->rlink;p != phead; p = p->rlink)
	{
		if (rec < p->data.year)
			rec = p->data.year;
	}

	p = phead->rlink;
	printf("�ֱ� ��ȭ \n");
	for (p=phead->rlink;p != phead; p = p->rlink)
	{
		if (rec == p->data.year)
			printf("| ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
}

//��ȭ ���� �˻� �Լ�
void search_subject(DListNode *phead)
{
	DListNode *p = phead->rlink;
	element tmp;
	printf("�˻��� ������ �Է��ϼ���.");
	scanf("%s", tmp.subject);
	for (p = phead->rlink;p != phead; p = p->rlink)
	{
		if (strcmp(tmp.subject, p->data.subject) == 0) {
			printf("| ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
			return 0;
		}
	}
	printf("NULL \n");
}

// ��ȭ �帣 �˻� �Լ�
void search_genre(DListNode *phead)
{
	DListNode *p = phead->rlink;
	char gen;
	printf("�帣 �˻�: ");
	getchar();
	scanf("%c", &gen);

	while (p != phead)
	{
		if (p->data.genre == gen)
		{
			printf("| ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		}
		p = p->rlink;
	}
}

//��ȭ ��� �Լ�
void play_movie(DListNode *phead)
{
	printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
	current = current->rlink;
	if (current == phead)
		current = current->rlink;
}

//>
void move_right(DListNode *phead)
{
	current = current->rlink;
	if (current == phead)
		current = current->rlink;
	printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
}

//<
void move_left(DListNode *phead)
{
	current = current->llink;
	if (current == phead)
		current = current->llink;
	printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
}

//F/f
void move_first(DListNode *phead)
{
	current = phead->rlink;
	printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
}

//L/l
void move_last(DListNode *phead)
{
	current = phead->llink;
	printf("|# ����: %s, �帣: %c, �����⵵: %d ,��� �ð� :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
}

void menu()
{
	printf("=================================\n");
	printf("1.���� \n");
	printf("2.��� \n");
	printf("3.Ư�� ��ȭ ���� \n");
	printf("4.�ֱ� ��ȭ �˻� \n");
	printf("5.��ȭ �帣 �˻� \n");
	printf("6.��ȭ ���� �˻� \n");
	printf("6.������ ��� \n");
	printf("p.��ȭ ��� \n");
	printf("<.��ȭ ���� �̵� \n");
	printf(">.��ȭ ������ �̵� \n");
	printf("F/f.ó�� ��ȭ �̵� \n");
	printf("L/l.������ ��ȭ �̵� \n");
	printf("0.���� \n");
	printf("=================================\n");
}

int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	int cnt1 = 0;     //��� ���
	char m;           //�޴� ����
	menu();

	while (1)
	{
		printf("\n");
		printf("�޴� ����: ");
		m = getchar();
		switch (m)
		{
		case '1':
			insert_node(head);
			current = head->rlink;
			break;

		case '2':
			printf("=========================================================================\n");
			printf("��� \n");
			print_list(head);
			printf("\n");

			cnt1 = list_length(head);
			printf("��� ����: %d \n", cnt1);
			printf("\n");
			break;

		case '3':
			delete_node(head);
			cnt1 = list_length(head);
			break;

		case '4':
			recent_year(head);
			break;

		case '5':
			search_genre(head);
			break;

		case '6':
			search_subject(head);
			break;

		case '7':
			print_reverse(head);
			cnt1 = list_length(head);
			printf("��� ����: %d \n", cnt1);
			break;

		case 'p':
			play_movie(head);
			break;

		case '<':
			move_left(head);
			break;

		case '>':
			move_right(head);
			break;

		case 'F': case 'f':
			move_first(head);
			break;

		case 'L': case 'l':
			move_last(head);
			break;

		case '0':
			return 0;
		}
		getchar();
	}
	free(head);
}