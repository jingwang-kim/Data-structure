/*���Ḯ��Ʈ �ǽ�(�غ�)

(2)  �� ��带 ���� ����Ʈ�� Ư�� ��ġ�� �����ϴ� �Լ� insert_node() �ۼ��Ͻÿ�
(������ ����ó�� insert_first()�� Ư�� ��ġ�� �����ؼ� �����ϴ� insert()�� ���� �ۼ��� �� ����)

(3)  ���� ����Ʈ�� ����� ����� ������ ����ؼ� ��ȯ�ϴ� �Լ� list_length() �� �ۼ��Ͻÿ�

(4)  ���� ����Ʈ�� ����� �� ��忡�� {
		��ȭ����, �帣, �����⵵
	}�� ���ʷ� ����ϴ� �Լ�
		print_list() �� �ۼ��Ͻÿ�

			main() �Լ������� : �� ����Ʈ���� �����Ͽ� �Ʒ��� ���� �޴��� �׽�Ʈ�Ͻÿ�.

			- insert_node()�� ȣ���Ͽ� �����ϴ� ��ȭ�� �����͸� ������ �� ��带 �����,
			���� ����Ʈ�� �����Ͽ� ����.
			(�� ��, �������� ���������� �����ϵ��� �����ϰų�, �׻� �� ��, �Ǵ� �� �ڿ� �����ϴ�
				��� �� ������ �� ����)

			- list_length()�� ȣ���Ͽ�, ���� ����Ʈ�� ����� ����� ������ ���
			- print_list()�� ȣ���Ͽ� ���� ����Ʈ�� ����� �� ����� �����͸� ���*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef struct element{
	char subject[MAX_SIZE];
	char genre;
	int year;
}element;

typedef struct Listnode {
	element data;
	struct Listnode *link;
}Listnode;

typedef struct ListType {
	int size;
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

// ���� �Լ�
Listnode* insert_node(Listnode *head, Listnode *pre)
{
	Listnode *p = (Listnode *)malloc(sizeof(Listnode));
	printf("���� �Է�: ");
	gets(p->data.subject);
	printf("�帣 �Է� ('A' 'C' 'F' 'R' �� �ϳ�): ");
	gets(p->data.genre);
	printf("�����⵵ �Է�: ");
	scanf("%d", &p->data.year);

	p->link = pre->link;      //pre�� ����Ű�� ��带 p�� ����Ű�� ��
	pre->link = p;            //pre�� p�� ��ġ�� ����Ű�� ��
	return head;
}

// ù ��° ���� �Լ�
Listnode* insert_first_node(Listnode *head)
{
	Listnode *p = (Listnode *)malloc(sizeof(Listnode));
	printf("���� �Է�: ");
	gets(p->data.subject);
	printf("�帣 �Է� ('A' 'C' 'F' 'R' �� �ϳ�): ");
	scanf("%c", &p->data.genre);
	printf("�����⵵ �Է�: ");
	scanf("%d", &p->data.year);
	printf("--------------------------------------------------------------------------------------\n");

	p->link = head;         //p�� ���� head�� ����Ű�� ��
	head = p;               //head �� p���� ��
	return head;
}

// ��� �Լ�
void print_list(Listnode *head)
{
	
	for (Listnode *p = head;p != NULL; p = p->link)
	{
		printf("[����: %s, �帣: %c, �����⵵: %d] \n--> ", p->data.subject, p->data.genre, p->data.year);
	}
	printf("NULL \n");
}

// ��� ���� ��� �Լ�
int list_length(Listnode *head)
{
	int cnt = 0;
	for (Listnode *p = head; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

int main(void)
{
	Listnode *head = NULL;
	int cnt = 0;
	int go;
	do {
		head = insert_first_node(head);
		cnt = list_length(head);
		print_list(head);
		printf("\n");
		printf("��� ����: %d \n", cnt);
		printf("\n");
		printf("�� �Է��Ͻðڽ��ϱ�? (yes=1, no=0) : ");
		scanf("%d", &go);
		char a;
		scanf("%c", &a);
		if (go == 0)
			return 0;
		else
			printf("======================================================================================\n");
	} while (1);
	return 0;
}