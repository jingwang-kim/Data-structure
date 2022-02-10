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
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

//���� üũ
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�� ���� �Լ�
void insert_first_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
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

	if (plist->tail == NULL)                            //ù��° ��尡 ��������� ����
		plist->head = plist->tail = temp;               //head�� tail�� ���ο� �� �߰�

	else {
		temp->link = plist->head;                       //temp�� ���� head�� ����Ű�� ��
		plist->head = temp;                             //head �� temp���� ��
	}
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

	else if (strcmp(plist->head->data.subject, temp->data.subject)==1)  //head�� temp���� Ŭ �� �տ� ����
	{
		temp->link = plist->head;
		plist->head = temp;
	}

	else if(strcmp(plist->tail->data.subject, temp->data.subject)==-1)  //tail�� temp���� ������ �ڿ� ����
	{
		plist->tail->link = temp;             
		plist->tail = temp;
	}

	else            //�߰��� ����
	{
		while (cur->link != NULL)
		{
			if (strcmp(cur->link->data.subject, temp->data.subject)==1)  //������ ���� ���� ���� temp���� ũ�� temp�� �� �� �ڿ� �־�� ��(cur temp ������)
			{
				temp->link = cur->link;  //temp�� cur ���� �� ����
				cur->link = temp;        //cur�� temp����
				break;
			}
			cur = cur->link;             //���� �� ������Ű�鼭 �ϳ��� �˻�
		}
	}
}

// �� ���� �Լ�
void insert_last_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
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

	if (plist->tail == NULL)
		plist->head = plist->tail = temp;

	else                                      //2��° ��� �̻���� ����
	{
		plist->tail->link = temp;             //tail�� temp�� ����
		plist->tail = temp;                   //������ �� ��尡 tail�� ��
	}
}

// ��� �Լ�
void print_list(ListType *plist)
{
	Listnode *p = plist->head;
	printf("\n");
	for (;p != NULL; p = p->link)
	{
		printf("[����: %s, �帣: %c, �����⵵: %d] \n--> ", p->data.subject, p->data.genre, p->data.year);
	}
	printf("NULL \n");
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

int main(void)
{
	ListType *list;
	list = create();
	int cnt = 0;
	int choice;
	int go;
	printf("�տ� �����Ϸ��� 1, �ڿ� �����Ϸ��� 2, ������������ �����Ϸ��� 3�� �Է��ϼ���.");
	scanf("%d", &choice);
	char f;
	scanf("%c", &f);

	switch (choice)
	{

	case 1:
		while (1)
		{
			insert_first_node(list);
			cnt = list_length(list);
			printf("=========================================================================\n");
			print_list(list);
			printf("\n");
			printf("��� ����: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("�� �Է��Ͻðڽ��ϱ�? (yes=1, no=0) : ");
			scanf("%d", &go);
			char a;
			scanf("%c", &a);
			if (go == 0)
				return 0;
		}

	case 2:
		while (1)
		{
			insert_last_node(list);
			cnt = list_length(list);
			printf("=========================================================================\n");
			print_list(list);
			printf("\n");
			printf("��� ����: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("�� �Է��Ͻðڽ��ϱ�? (yes=1, no=0) : ");
			scanf("%d", &go);
			char b;
			scanf("%c", &b);
			if (go == 0)
				return 0;

		}

	case 3:
		while (1)
		{
			insert_ascending_node(list);
			cnt = list_length(list);
			printf("=========================================================================\n");
			print_list(list);
			printf("\n");
			printf("��� ����: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("�� �Է��Ͻðڽ��ϱ�? (yes=1, no=0) : ");
			scanf("%d", &go);
			char c;
			scanf("%c", &c);
			if (go == 0)
				return 0;
		}
	}
	free(list);
}
