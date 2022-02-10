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
	plist->head = plist->tail = NULL;
	return plist;
}

//오류 체크
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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

	else if (strcmp(plist->head->data.subject, temp->data.subject) == 1)  //head가 temp보다 클 때 앞에 연결
	{
		temp->link = plist->head;                              //temp가 현재 head를 가리키게 함
		plist->head = temp;                                    //head 가 temp값이 됨
	}

	else if (strcmp(plist->tail->data.subject, temp->data.subject) == -1)  //tail이 temp보다 작을때 뒤에 연결
	{
		plist->tail->link = temp;                  //tail을 temp에 연결
		plist->tail = temp;                        //지금의 새 노드가 tail이 됨
	}

	else            //중간에 연결
	{
		while (cur->link != NULL)
		{
			if (strcmp(cur->link->data.subject, temp->data.subject) == 1)  //현재의 다음 번쨰 값이 temp보다 크면 temp를 그 값 뒤에 넣어야 함(cur temp 다음값)
			{
				temp->link = cur->link;  //temp에 cur 다음 값 연결
				cur->link = temp;        //cur에 temp연결
				break;
			}
			cur = cur->link;             //현재 값 증가시키면서 하나씩 검사
		}
	}
}

// 출력 함수
void print_list(ListType *plist)
{
	Listnode *p = plist->head;

	for (;p != NULL; p = p->link)
	{
		printf("[제목: %s, 장르: %c, 개봉년도: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
}

//순환 출력 함수
void print_list2(Listnode *p)
{
	if (p == NULL) {
		return 0;
	}

	else
	{
		printf("[제목: %s, 장르: %c, 개봉년도: %d]\n", p->data.subject, p->data.genre, p->data.year);
		print_list2(p->link);
	}
}

//순환 역순 출력 함수
void print_list3(Listnode *p)
{
	if (p == NULL)
		return 0;
	else
	{
		print_list3(p->link);
		printf("[제목: %s, 장르: %c, 개봉년도: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
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

// 노드 개수 계산(순환호출)
int list_length2(Listnode *p, int cnt)
{

	if (p == NULL)
		return cnt;

	else
	{
		list_length2(p->link, cnt+=1);
	}
}

//삭제 함수
void delete_node(ListType *plist)
{
	Listnode *cur;
	Listnode *removed;
	cur = plist->head;
	if (plist->head == NULL)
		error("메모리 할당 에러");
	printf("삭제할 영화 제목 입력: ");
	char del[MAX_SIZE];
	scanf("%s", del);

	if (strcmp(cur->data.subject, del)==0)  //처음 값
	{
		plist->head = cur->link;            //head에 cur의 다음 값 연결
		free(cur);                          //cur 삭제
		printf("삭제되었습니다. \n");
		return;
	}

	while (cur->link != NULL)
	{
		if (strcmp(cur->link->data.subject, del) == 0)
		{
			removed = cur->link;
			if (removed->link != NULL) {
				cur->link = removed->link;    //중간 값
			}
			else {
				cur->link = NULL;  //마지막 값
			}

			free(removed);
			printf("삭제되었습니다. \n");
			return;
		}
		cur = cur->link;
	}
}

//최근 영화 검색 함수
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
	printf("최근 영화 \n");
	for (;p != NULL; p = p->link)
	{
		if(rec==p->data.year)
			printf("[제목: %s, 장르: %c, 개봉년도: %d]\n", p->data.subject, p->data.genre, p->data.year);
	}
}

 //영화 제목 검색 함수
void search_subject(ListType *plist)
{
	Listnode *p = plist->head;
	element tmp;
	printf("검색할 제목을 입력하세요.");
	scanf("%s", tmp.subject);
	for (;p != NULL; p = p->link)
	{
		if (strcmp(tmp.subject, p->data.subject)==0 ) {
			printf("[제목: %s, 장르: %c, 개봉년도: %d]\n ", p->data.subject, p->data.genre, p->data.year);
			return 0;
		}
	}
	printf("NULL \n");
}

// 영화 장르 검색 함수
void search_genre(ListType *plist)
{
	Listnode *p = plist->head;
	char gen;
	printf("장르 검색: ");
	getchar();
	scanf("%c", &gen);

	while (p != NULL)
	{
		if (p->data.genre == gen)
		{
			printf("[제목: %s, 장르: %c, 개봉년도: %d]\n", p->data.subject, p->data.genre, p->data.year);
		}
		p = p->link;
	}
}

void menu()
{
	printf("=================================\n");
	printf("1.삽입 \n");
	printf("2.출력 \n");
	printf("3.역순 출력 \n");
	printf("4.특정 영화 삭제 \n");
	printf("5.최근 영화 검색 \n");
	printf("6.영화 장르 검색 \n");
	printf("7.영화 제목 검색 \n");
	printf("0.종료 \n");
	printf("=================================\n");
}

int main(void)
{
	ListType *list;
	list = create();
	int cnt1 = 0;     //기본 노드 계산
	int cnt2;         //순환을 이용한 노드 계산
	int m = 0;        //메뉴 선택
	int choice;       //입력 횟수 결정

	menu();
	while (1)
	{
		printf("\n");
		printf("메뉴 선택: ");
		scanf("%d", &m);
		switch (m)
		{
		case 1:
			printf("몇 번 입력하시겠습니까?");
			scanf("%d", &choice);
			for (int i = 0;i < choice;i++) {
				char a;
				scanf("%c", &a);
				insert_ascending_node(list);
			}
			break;

		case 2:
			printf("=========================================================================\n");
			printf("기본적인 출력 \n");
			print_list(list);
			printf("\n");

			Listnode *p = list->head;
			printf("순환 출력 \n");
			print_list2(p);
			printf("\n");

			cnt1 = list_length(list);
			Listnode *e = list->head;
			cnt2 = 0;
			cnt2 = list_length2(e, cnt2);

			printf("노드 개수(기본): %d \n", cnt1);
			printf("노드 개수(순환): %d \n", cnt2);
			printf("\n");
			break;

		case 3:
			printf("역순 출력 \n");
			Listnode *r = list->head;
			print_list3(r);
			printf("\n");

			cnt1 = list_length(list);
			Listnode *q = list->head;
			cnt2 = 0;
			cnt2 = list_length2(q, cnt2);

			printf("노드 개수(기본): %d \n", cnt1);
			printf("노드 개수(순환): %d \n", cnt2);
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