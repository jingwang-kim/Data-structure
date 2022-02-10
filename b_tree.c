#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

/*//첫 번째 트리
TreeNode n1 = { 19, NULL, NULL };
TreeNode n2 = { 23, NULL, NULL };
TreeNode n3 = { 5, &n1, &n2 };
TreeNode n4 = { 27, NULL, NULL };
TreeNode n5 = { 29, NULL, NULL };
TreeNode n6 = { 7, &n4, &n5 };
TreeNode n7 = { 3, &n3, &n6 };
TreeNode n8 = { 13, NULL, NULL };
TreeNode n9 = { 11, &n8, NULL };
TreeNode n10 = { 2, &n7, &n9 };
TreeNode *root = &n10;*/


//               2
//            /     \
//           3       11
//         /   \    /  
//        5    7   13   
//      /  \  /  \
//     19  23 27 29


/*//두 번째 트리
TreeNode t1 = { 10, NULL, NULL };
TreeNode t2 = { 15, NULL, NULL };
TreeNode t3 = { 37, NULL, NULL };
TreeNode t4 = { 8, &t1, &t2 };
TreeNode t5 = { 9, NULL, &t3 };
TreeNode t6 = { 24, NULL, NULL };
TreeNode t7 = { 25, &t4, &t5 };
TreeNode t8 = { 22, &t6, &t7 };
TreeNode t9 = { 12, NULL, NULL };
TreeNode t10 = { 43, &t8, &t9 };
TreeNode *root = &t10;*/


//              43
//           /      \
//         22        12
//       /    \
//      24     25
//           /    \
//          8      9
//        /   \     \
//       10   15     37 


//세 번째 트리
TreeNode e1 = { 66, NULL, NULL };
TreeNode e2 = { 45, NULL, NULL };
TreeNode e3 = { 67, &e1, &e2 };
TreeNode e4 = { 28, NULL, NULL };
TreeNode e5 = { 16, &e3, NULL };
TreeNode e6 = { 53, NULL, NULL };
TreeNode e7 = { 55, NULL, &e6 };
TreeNode e8 = { 61, &e4, &e5 };
TreeNode e9 = { 41, NULL, &e7 };
TreeNode e10 = { 51, &e8, &e9 };
TreeNode *root = &e10;


//             51
//          /      \
//         61       41
//       /    \        \
//      28    16        55
//           /            \
//          67             53
//        /    \
//       66     45 


// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 100
typedef TreeNode *element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 큐 초기화 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// ===== 원형큐 코드 끝 ======

//레벨 순회 함수
void level_order(TreeNode *ptr)
{
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q))
	{
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

//최대 높이
int get_height(TreeNode *ptr)
{
	int height = 0;

	if (ptr != NULL)
		height = 1 + max(get_height(ptr->left), get_height(ptr->right));
	return height;
}

//노드 개수 계산
int result = 0;
int count_node(TreeNode *ptr, int lev, int cnt)
{
	if (ptr != NULL)
	{
		if (lev == cnt) {
			result += 1;
			return;
		}

		count_node(ptr->left, lev, cnt + 1);
		count_node(ptr->right, lev, cnt + 1);
	}

	return result;
}

//균형 트리인지 확인
int tree_balance(TreeNode *ptr)
{
	int lnum = 0;
	int rnum = 0;

	if (ptr != NULL)
	{
		lnum = get_height(ptr->left);
		rnum = get_height(ptr->right);

		if (abs(lnum - rnum) > 1)
			return -1;

		else {
			tree_balance(ptr->left);
			tree_balance(ptr->right);
			if (ptr == NULL)
				return;
		}
	}
}

//좌우 대칭
void tree_sym(TreeNode *ptr)
{
	if (ptr != NULL)
	{
		tree_sym(ptr->left);
		tree_sym(ptr->right);
		TreeNode *temp = ptr->left;
		ptr->left = ptr->right;
		ptr->right = temp;
	}
}

void menu()
{
	printf("================================\n");
	printf("1.레벨 순회 \n");
	printf("2.노드 계산 \n");
	printf("3.균형 트리 \n");
	printf("4.좌우 대칭 \n");
	printf("0.종료 \n");
	printf("================================\n");
}

int main(void)
{
	int n;
	int cnt=1;
	int choice;
	int num;
	int lev = 0;
	while (1) {
		menu();
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("레벨 순회: ");
			level_order(root);
			printf("\n");
			break;

		case 2:
			printf("노드를 계산할 레벨 선택: ");
			scanf("%d", &lev);
			if (lev > get_height(root))
			{
				printf(" < 높이 초과 > \n");
				break;
			}
			num=count_node(root, lev, cnt);
			printf(" < %d >", num);
			result = 0;
			printf("\n");
			break;

		case 3:
			printf("균형트리: ");
			n = tree_balance(root);
			if (n == -1)
				printf("NO");
			else
				printf("YES");
			printf("\n");
			break;

		case 4:
			printf("좌우 대칭: ");
			tree_sym(root);
			level_order(root);
			printf("\n");
			break;

		case 0:
			return 0;
		}
	}
	return 0;
}