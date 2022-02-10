#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef struct element {
	char subject[MAX_SIZE];
	char genre;
	int year;
}element;

typedef struct Listnode {
	element data;
	struct Listnode *link;
}Listnode;

typedef struct ListType {
	Listnode *head;
	Listnode *tail;
}ListType;

//����Ʈ ��� ����
ListType* create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));
	plist->head = plist->tail = NULL;
	return plist;
}

//���� üũ
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�������� ���� �Լ�
void insert_ascending_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
	Listnode *cur;              //���� ����Ű�� ��
	cur = plist->head;
	if (temp == NULL)
		error("�޸� �Ҵ� ����");

	printf("���� �Է�: ");
	gets(temp->data.subject);

	while (1)
	{
		printf("�帣 �Է� ('A' 'C' 'F' 'R' �� �ϳ�): ");
		scanf("%c", &temp->data.genre);
		if (temp->data.genre == 'A' || temp->data.genre == 'C' || temp->data.genre == 'F' || temp->data.genre == 'R')
			break;
		else
			printf("�ٽ� �Է��ϼ���.\n");
		char a;
		scanf("%c", &a);
	}

	printf("�����⵵ �Է�: ");
	scanf("%d", &temp->data.year);
	temp->link = NULL;
	if (plist->tail == NULL)                                  //ó�� �� ���� ��
		plist->head = plist->tail = temp;

	else if (strcmp(plist->head->data.subject, temp->data.subject) == 1)  //head�� temp���� Ŭ �� �տ� ����
	{
		temp->link = plist->head;                              //temp�� ���� head�� ����Ű�� ��
		plist->head = temp;                                    //head �� temp���� ��
	}

	else if (strcmp(plist->tail->data.subject, temp->data.subject) == -1)  //tail�� temp���� ������ �ڿ� ����
	{
		plist->tail->link = temp;                  //tail�� temp�� ����
		plist->tail = temp;                        //������ �� ��尡 tail�� ��
	}

	else            //�߰��� ����
	{
		while (cur->link != NULL)
		{
			if (strcmp(cur->link->data.subject, temp->data.subject) == 1)  //������ ���� ���� ���� temp���� ũ�� temp�� �� �� �ڿ� �־�� ��(cur temp ������)
			{
				temp->link = cur->link;  //temp�� cur ���� �� ����
				cur->link = temp;        //cur�� temp����
				break;
			}
			cur = cur->link;             //���� �� ������Ű�鼭 �ϳ��� �˻�
		}
	}
}

// ��� �Լ�
void print_list(ListType *plist)
{
	Listnode *p = plist->head;

	for (;p != NULL; p = p->link)
	{
		printf("[����: %s, �帣: %c, �����⵵: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
}

//��ȯ ��� �Լ�
void print_list2(Listnode *p)
{
	if (p == NULL) {
		return 0;
	}

	else
	{
		printf("[����: %s, �帣: %c, �����⵵: %d]\n", p->data.subject, p->data.genre, p->data.year);
		print_list2(p->link);
	}
}

//��ȯ ���� ��� �Լ�
void print_list3(Listnode *p)
{
	if (p == NULL)
		return 0;
	else
	{
		print_list3(p->link);
		printf("[����: %s, �帣: %c, �����⵵: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
}

// ��� ���� ��� �Լ�
int list_length(ListType *plist)
{
	Listnode *p = plist->head;

	int cnt = 0;
	for (; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

// ��� ���� ���(��ȯȣ��)
int list_length2(Listnode *p, int cnt)
{

	if (p == NULL)
		return cnt;

	else
	{
		list_length2(p->link, cnt+=1);
	}
}

//���� �Լ�
void delete_node(ListType *plist)
{
	Listnode *cur;
	Listnode *removed;
	cur = plist->head;
	if (plist->head == NULL)
		error("�޸� �Ҵ� ����");
	printf("������ ��ȭ ���� �Է�: ");
	char del[MAX_SIZE];
	scanf("%s", del);

	if (strcmp(cur->data.subject, del)==0)  //ó�� ��
	{
		plist->head = cur->link;            //head�� cur�� ���� �� ����
		free(cur);                          //cur ����
		printf("�����Ǿ����ϴ�. \n");
		return;
	}

	while (cur->link != NULL)
	{
		if (strcmp(cur->link->data.subject, del) == 0)
		{
			removed = cur->link;
			if (removed->link != NULL) {
				cur->link = removed->link;    //�߰� ��
			}
			else {
				cur->link = NULL;  //������ ��
			}

			free(removed);
			printf("�����Ǿ����ϴ�. \n");
			return;
		}
		cur = cur->link;
	}
}

//�ֱ� ��ȭ �˻� �Լ�
void recent_year(ListType *plist)
{
	Listnode *p = plist->head;
	int rec=p->data.year;
	for (;p != NULL; p = p->link)
	{
		if (rec < p->data.year)
			rec = p->data.year;
	}

	p = plist->head;
	printf("�ֱ� ��ȭ \n");
	for (;p != NULL; p = p->link)
	{
		if(rec==p->data.year)
			printf("[����: %s, �帣: %c, �����⵵: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
}

 //��ȭ ���� �˻� �Լ�
void search_subject(ListType *plist)
{
	Listnode *p = plist->head;
	element tmp;
	printf("�˻��� ������ �Է��ϼ���.");
	scanf("%s", tmp.subject);
	for (;p != NULL; p = p->link)
	{
		if (strcmp(tmp.subject, p->data.subject)==0 ) {
			printf("[����: %s, �帣: %c, �����⵵: %d]\n ", p->data.subject, p->data.genre, p->data.year);
			return 0;
		}
	}
	printf("NULL \n");
}

// ��ȭ �帣 �˻� �Լ�
void search_genre(ListType *plist)
{
	Listnode *p = plist->head;
	char gen;
	printf("�帣 �˻�: ");
	getchar();
	scanf("%c", &gen);

	while (p != NULL)
	{
		if (p->data.genre == gen)
		{
			printf("[����: %s, �帣: %c, �����⵵: %d]\n", p->data.subject, p->data.genre, p->data.year);
		}
		p = p->link;
	}
}

void menu()
{
	printf("=================================\n");
	printf("1.���� \n");
	printf("2.��� \n");
	printf("3.���� ��� \n");
	printf("4.Ư�� ��ȭ ���� \n");
	printf("5.�ֱ� ��ȭ �˻� \n");
	printf("6.��ȭ �帣 �˻� \n");
	printf("7.��ȭ ���� �˻� \n");
	printf("0.���� \n");
	printf("=================================\n");
}

int main(void)
{
	ListType *list;
	list = create();
	int cnt1 = 0;     //�⺻ ��� ���
	int cnt2;         //��ȯ�� �̿��� ��� ���
	int m = 0;        //�޴� ����
	int choice;       //�Է� Ƚ�� ����

	menu();
	while (1)
	{
		printf("\n");
		printf("�޴� ����: ");
		scanf("%d", &m);
		switch (m)
		{
		case 1:
			printf("�� �� �Է��Ͻðڽ��ϱ�?");
			scanf("%d", &choice);
			for (int i = 0;i < choice;i++) {
				char a;
				scanf("%c", &a);
				insert_ascending_node(list);
			}
			break;

		case 2:
			printf("=========================================================================\n");
			printf("�⺻���� ��� \n");
			print_list(list);
			printf("\n");

			Listnode *p = list->head;
			printf("��ȯ ��� \n");
			print_list2(p);
			printf("\n");

			cnt1 = list_length(list);
			Listnode *e = list->head;
			cnt2 = 0;
			cnt2 = list_length2(e, cnt2);

			printf("��� ����(�⺻): %d \n", cnt1);
			printf("��� ����(��ȯ): %d \n", cnt2);
			printf("\n");
			break;

		case 3:
			printf("���� ��� \n");
			Listnode *r = list->head;
			print_list3(r);
			printf("\n");

			cnt1 = list_length(list);
			Listnode *q = list->head;
			cnt2 = 0;
			cnt2 = list_length2(q, cnt2);

			printf("��� ����(�⺻): %d \n", cnt1);
			printf("��� ����(��ȯ): %d \n", cnt2);
			printf("\n");
			break;

		case 4:
			delete_node(list);
			cnt1 = list_length(list);
			Listnode *t = list->head;
			cnt2 = 0;
			cnt2 = list_length2(t, cnt2);
			break;

		case 5:
			recent_year(list);
			break;

		case 6:
			search_genre(list);
			break;

		case 7:
			search_subject(list);
			break;

		case 0:
			return 0;
		}
	}
	free(list);
}