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

//리스트 헤더 생성
ListType* create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

//오류 체크
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//앞 삽입 함수
void insert_first_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
	if (temp == NULL)
		error("메모리 할당 에러");

	printf("제목 입력: ");
	gets(temp->data.subject);

	while (1)
	{
		printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
		scanf("%c", &temp->data.genre);
		if (temp->data.genre == 'A' || temp->data.genre == 'C' || temp->data.genre == 'F' || temp->data.genre == 'R')
			break;
		else
			printf("다시 입력하세요.\n");
		char a;
		scanf("%c", &a);
	}

	printf("개봉년도 입력: ");
	scanf("%d", &temp->data.year);
	temp->link = NULL;

	if (plist->tail == NULL)                            //첫번째 노드가 만들어지는 과정
		plist->head = plist->tail = temp;               //head와 tail에 새로운 값 추가

	else {
		temp->link = plist->head;                       //temp가 현재 head를 가리키게 함
		plist->head = temp;                             //head 가 temp값이 됨
	}
}

//오름차순 삽입 함수
void insert_ascending_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
	Listnode *cur;              //현재 가리키는 값
	cur = plist->head;
	if (temp == NULL)
		error("메모리 할당 에러");

	printf("제목 입력: ");
	gets(temp->data.subject);

	while (1)
	{
		printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
		scanf("%c", &temp->data.genre);
		if (temp->data.genre == 'A' || temp->data.genre == 'C' || temp->data.genre == 'F' || temp->data.genre == 'R')
			break;
		else
			printf("다시 입력하세요.\n");
		char a;
		scanf("%c", &a);
	}

	printf("개봉년도 입력: ");
	scanf("%d", &temp->data.year);
	temp->link = NULL;

	if (plist->tail == NULL)                                  //처음 값 넣을 때
		plist->head = plist->tail = temp;

	else if (strcmp(plist->head->data.subject, temp->data.subject)==1)  //head가 temp보다 클 때 앞에 연결
	{
		temp->link = plist->head;
		plist->head = temp;
	}

	else if(strcmp(plist->tail->data.subject, temp->data.subject)==-1)  //tail이 temp보다 작을때 뒤에 연결
	{
		plist->tail->link = temp;             
		plist->tail = temp;
	}

	else            //중간에 연결
	{
		while (cur->link != NULL)
		{
			if (strcmp(cur->link->data.subject, temp->data.subject)==1)  //현재의 다음 번쨰 값이 temp보다 크면 temp를 그 값 뒤에 넣어야 함(cur temp 다음값)
			{
				temp->link = cur->link;  //temp에 cur 다음 값 연결
				cur->link = temp;        //cur에 temp연결
				break;
			}
			cur = cur->link;             //현재 값 증가시키면서 하나씩 검사
		}
	}
}

// 뒤 삽입 함수
void insert_last_node(ListType *plist)
{
	Listnode *temp = (Listnode *)malloc(sizeof(Listnode));
	if (temp == NULL)
		error("메모리 할당 에러");

	printf("제목 입력: ");
	gets(temp->data.subject);

	while (1)
	{
		printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
		scanf("%c", &temp->data.genre);
		if (temp->data.genre == 'A' || temp->data.genre == 'C' || temp->data.genre == 'F' || temp->data.genre == 'R')
			break;
		else
			printf("다시 입력하세요.\n");
		char a;
		scanf("%c", &a);
	}

	printf("개봉년도 입력: ");
	scanf("%d", &temp->data.year);
	temp->link = NULL;

	if (plist->tail == NULL)
		plist->head = plist->tail = temp;

	else                                      //2번째 노드 이상부터 실행
	{
		plist->tail->link = temp;             //tail을 temp에 연결
		plist->tail = temp;                   //지금의 새 노드가 tail이 됨
	}
}

// 출력 함수
void print_list(ListType *plist)
{
	Listnode *p = plist->head;
	printf("\n");
	for (;p != NULL; p = p->link)
	{
		printf("[제목: %s, 장르: %c, 개봉년도: %d] \n--> ", p->data.subject, p->data.genre, p->data.year);
	}
	printf("NULL \n");
}

// 노드 개수 계산 함수
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
	printf("앞에 연결하려면 1, 뒤에 연결하려면 2, 오름차순으로 연결하려면 3을 입력하세요.");
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
			printf("노드 개수: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("더 입력하시겠습니까? (yes=1, no=0) : ");
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
			printf("노드 개수: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("더 입력하시겠습니까? (yes=1, no=0) : ");
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
			printf("노드 개수: %d \n", cnt);
			printf("\n");
			printf("=========================================================================\n");
			printf("더 입력하시겠습니까? (yes=1, no=0) : ");
			scanf("%d", &go);
			char c;
			scanf("%c", &c);
			if (go == 0)
				return 0;
		}
	}
	free(list);
}
