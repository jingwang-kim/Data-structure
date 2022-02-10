/*연결리스트 실습(준비)

(2)  새 노드를 현재 리스트의 특정 위치에 삽입하는 함수 insert_node() 작성하시오
(교재의 예제처럼 insert_first()와 특정 위치를 지정해서 삽입하는 insert()를 따로 작성할 수 있음)

(3)  현재 리스트에 연결된 노드의 개수를 계산해서 반환하는 함수 list_length() 를 작성하시오

(4)  현재 리스트에 연결된 각 노드에서 {
		영화제목, 장르, 개봉년도
	}를 차례로 출력하는 함수
		print_list() 를 작성하시오

			main() 함수에서는 : 빈 리스트에서 시작하여 아래와 같은 메뉴로 테스트하시오.

			- insert_node()를 호출하여 좋아하는 영화의 데이터를 저장한 새 노드를 만들고,
			현재 리스트에 삽입하여 연결.
			(이 때, ‘제목’의 오름차순을 유지하도록 연결하거나, 항상 맨 앞, 또는 맨 뒤에 연결하는
				방법 중 선택할 수 있음)

			- list_length()를 호출하여, 현재 리스트에 연결된 노드의 개수를 계산
			- print_list()를 호출하여 현재 리스트에 연결된 각 노드의 데이터를 출력*/


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

//리스트 헤더 생성
ListType* create() 
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// 삽입 함수
Listnode* insert_node(Listnode *head, Listnode *pre)
{
	Listnode *p = (Listnode *)malloc(sizeof(Listnode));
	printf("제목 입력: ");
	gets(p->data.subject);
	printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
	gets(p->data.genre);
	printf("개봉년도 입력: ");
	scanf("%d", &p->data.year);

	p->link = pre->link;      //pre가 가리키는 노드를 p가 가리키게 함
	pre->link = p;            //pre가 p의 위치를 가리키게 함
	return head;
}

// 첫 번째 삽입 함수
Listnode* insert_first_node(Listnode *head)
{
	Listnode *p = (Listnode *)malloc(sizeof(Listnode));
	printf("제목 입력: ");
	gets(p->data.subject);
	printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
	scanf("%c", &p->data.genre);
	printf("개봉년도 입력: ");
	scanf("%d", &p->data.year);
	printf("--------------------------------------------------------------------------------------\n");

	p->link = head;         //p가 현재 head를 가리키게 함
	head = p;               //head 가 p값이 됨
	return head;
}

// 출력 함수
void print_list(Listnode *head)
{
	
	for (Listnode *p = head;p != NULL; p = p->link)
	{
		printf("[제목: %s, 장르: %c, 개봉년도: %d] \n--> ", p->data.subject, p->data.genre, p->data.year);
	}
	printf("NULL \n");
}

// 노드 개수 계산 함수
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
		printf("노드 개수: %d \n", cnt);
		printf("\n");
		printf("더 입력하시겠습니까? (yes=1, no=0) : ");
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