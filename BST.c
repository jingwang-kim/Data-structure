#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_SIZE 100
typedef struct element {
	char name[MAX_SIZE];
	int appear;
}element;

typedef struct TreeNode {
	element data;
	struct TreeNode *left, *right;
}TreeNode;

int compare(element e1, element e2)
{
	return strcmp(e1.name, e2.name);
}

TreeNode *search(TreeNode *root, element key)
{
	TreeNode *cur = root;
	while (cur != NULL)
	{
		if (compare(key, cur->data) == 0) {
			cur->data.appear += 1;
			return cur;        //탐색 성공 시 cur값 반환
		}
		else if (compare(key, cur->data) < 0)
			cur = cur->left;
		else if (compare(key, cur->data) > 0)
			cur = cur->right;
	}
	return cur;                //탐색 실패 시 NULL 반환
}

TreeNode *new_node(element item)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	item.appear = 1;
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode *insert_node(TreeNode *root, element key)
{
	if (root == NULL) return new_node(key);            //트리가 공백일 때 새 노드 반환

	if (compare(key, root->data) < 0)                  //트리가 공백이 아닐 때 트리 탐색하여 넣을 자리 찾음
		root->left = insert_node(root->left, key);
	else if (compare(key, root->data) > 0)
		root->right = insert_node(root->right, key);

	return root;                                      //루트 포인터 반환
}

//중위순회 출력
void inorder(TreeNode *root, FILE *fp2)
{
	if (root!=NULL)
	{
		inorder(root->left, fp2);
		fprintf(fp2, "[이름 : %s, 출현 빈도 : %d]\n", root->data.name, root->data.appear);
		inorder(root->right, fp2);
	}
}

//최대값 반환
element max = { NULL, };
 void max_appear(TreeNode *root)
{
	TreeNode *cur;
	if (root != NULL)
	{
		max_appear(root->left);
		max_appear(root->right);

		cur = root;
		if (max.appear < cur->data.appear)
		{
			max = cur->data;
		}
	}
}

/*
break, 4
case, 3
else, 4
for, 5
if, 4
int , 14
printf, 33
return, 4
scanf, 4
switch, 1
while, 2
do, 0
float, 2
*/

int main(void)
{
	TreeNode *root = NULL;
	element key;

	FILE *fp1;
	if ((fp1 = fopen("bst_in.txt", "r")) == NULL)
	{
		printf("파일이 열리지 않습니다. \n");
		exit(1);
	}

	FILE *fp2;
	if ((fp2 = fopen("bst_out.txt", "w")) == NULL)
	{
		printf("파일이 열리지 않습니다. \n");
		exit(1);
	}

	char *arr = malloc(sizeof(char)*MAX_SIZE);
	char *str[14] = { "break", "case", "do", "else", "for", "if", "int ", "float", "printf","scanf", "return", "sizeof","switch", "while" };

	while (fgets(arr, MAX_SIZE, fp1))
	{
		for (int i = 0;i < 14; i++)
		{
			if (strstr(arr, str[i]))
			{
				strcpy(key.name, str[i]);
				if (search(root, key) == NULL)
					root = insert_node(root, key);

				else
					continue;
			}
		}
	}
	inorder(root, fp2);
	max_appear(root);
	fprintf(fp2, "\n[빈도 최대값: %s(이)가 %d개]",max.name, max.appear);

	free(arr);
	fclose(fp1);
	fclose(fp2);
}