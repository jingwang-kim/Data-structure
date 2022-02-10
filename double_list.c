#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIZE 100
typedef struct element {
	char subject[MAX_SIZE];
	char genre;
	int year;
	int p;      //재생 시간
}element;

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
void print_list(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		if (p == current)
			printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		else
			printf("| 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
	printf("\n");
}

//역방향 출력
void print_reverse(DListNode* phead)
{
	DListNode* p;
	for (p = phead->llink; p != phead; p = p->llink)
	{
		if (p == current)
			printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		else
			printf("| 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
	printf("\n");
}

//삽입
void insert_node(DListNode *phead)
{
	DListNode* newnode = (DListNode *)malloc(sizeof(DListNode));
	DListNode* cur;
	cur = phead->rlink;
	getchar();
	printf("제목 입력: ");
	gets(newnode->data.subject);

	while (1)
	{
		printf("장르 입력 ('A' 'C' 'F' 'R' 중 하나): ");
		scanf("%c", &newnode->data.genre);
		if (newnode->data.genre == 'A' || newnode->data.genre == 'C' || newnode->data.genre == 'F' || newnode->data.genre == 'R')
			break;
		else {
			printf("다시 입력하세요.\n");
			getchar();
		}
		char a;
		scanf("%c", &a);
	}

	printf("개봉년도 입력: ");
	scanf("%d", &newnode->data.year);

	printf("재생시간 입력: ");
	scanf("%d", &newnode->data.p);

	if (strcmp(phead->rlink->data.subject, newnode->data.subject) == 1)  //앞에 붙일 떄
	{
		newnode->llink = phead;              //newnode의 왼쪽에 phead
		newnode->rlink = phead->rlink;       //newnode의 오른쪽에 phead의 다음 값
		phead->rlink->llink = newnode;       //phead의 다음 값의 왼쪽에 newnode
		phead->rlink = newnode;              //phead의 오른쪽에 newnode
	}                                        //phead newnode newnode->rlink

	else if (strcmp(phead->llink->data.subject, newnode->data.subject) == -1)  //뒤에 붙일 떄
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
				newnode->llink = cur;                 //new의 왼쪽에 cur
				newnode->rlink = cur->rlink;          //new의 오른쪽에 cur의 다음 값
				cur->rlink = newnode;                 //cur의 오른쪽에 new
				cur->rlink->llink = newnode;          //cur 다음값의 왼쪽에 new         cur new new->rlink
				break;
			}
		}
		cur = cur->rlink;
	}
}

// 노드 개수 계산 함수
int list_length(DListNode *phead)
{
	DListNode *p = phead->rlink;

	int cnt = 0;
	for (p = phead->rlink;p != phead; p = p->rlink)
		cnt++;
	return cnt;
}

//삭제
void delete_node(DListNode* head)
{
	DListNode *removed;
	removed = head->rlink;
	printf("삭제할 영화 제목 입력: ");
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
			printf("삭제되었습니다. \n");
			return;
		}

		else
			removed = removed->rlink;
	}

}

//최근 영화 검색 함수
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
	printf("최근 영화 \n");
	for (p=phead->rlink;p != phead; p = p->rlink)
	{
		if (rec == p->data.year)
			printf("| 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
	}
}

//영화 제목 검색 함수
void search_subject(DListNode *phead)
{
	DListNode *p = phead->rlink;
	element tmp;
	printf("검색할 제목을 입력하세요.");
	scanf("%s", tmp.subject);
	for (p = phead->rlink;p != phead; p = p->rlink)
	{
		if (strcmp(tmp.subject, p->data.subject) == 0) {
			printf("| 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
			return 0;
		}
	}
	printf("NULL \n");
}

// 영화 장르 검색 함수
void search_genre(DListNode *phead)
{
	DListNode *p = phead->rlink;
	char gen;
	printf("장르 검색: ");
	getchar();
	scanf("%c", &gen);

	while (p != phead)
	{
		if (p->data.genre == gen)
		{
			printf("| 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d | \n", p->data.subject, p->data.genre, p->data.year, p->data.p);
		}
		p = p->rlink;
	}
}

//영화 재생 함수
void play_movie(DListNode *phead)
{
	printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
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
	printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
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
	printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
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
	printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
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
	printf("|# 제목: %s, 장르: %c, 개봉년도: %d ,재생 시간 :%d #| \n", current->data.subject, current->data.genre, current->data.year, current->data.p);
	for (int i = 1;i <= current->data.p;i++)
	{
		Sleep(1000);
		printf("%d ", i);
	}
}

void menu()
{
	printf("=================================\n");
	printf("1.삽입 \n");
	printf("2.출력 \n");
	printf("3.특정 영화 삭제 \n");
	printf("4.최근 영화 검색 \n");
	printf("5.영화 장르 검색 \n");
	printf("6.영화 제목 검색 \n");
	printf("6.역방향 출력 \n");
	printf("p.영화 재생 \n");
	printf("<.영화 왼쪽 이동 \n");
	printf(">.영화 오른쪽 이동 \n");
	printf("F/f.처음 영화 이동 \n");
	printf("L/l.마지막 영화 이동 \n");
	printf("0.종료 \n");
	printf("=================================\n");
}

int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	int cnt1 = 0;     //노드 계산
	char m;           //메뉴 선택
	menu();

	while (1)
	{
		printf("\n");
		printf("메뉴 선택: ");
		m = getchar();
		switch (m)
		{
		case '1':
			insert_node(head);
			current = head->rlink;
			break;

		case '2':
			printf("=========================================================================\n");
			printf("출력 \n");
			print_list(head);
			printf("\n");

			cnt1 = list_length(head);
			printf("노드 개수: %d \n", cnt1);
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
			printf("노드 개수: %d \n", cnt1);
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