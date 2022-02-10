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
			return cur;        //Ž�� ���� �� cur�� ��ȯ
		}
		else if (compare(key, cur->data) < 0)      //Ű ���� ���� ��庸�� ���� �� �������� ��
			cur = cur->left;
		else if (compare(key, cur->data) > 0)      //Ű ���� ���� ��庸�� Ŭ �� ���������� ��
			cur = cur->right;
	}
	return cur;                //Ž�� ���� �� NULL ��ȯ
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
	if (root == NULL) return new_node(key);            //Ʈ���� ������ �� �� ��� ��ȯ

	if (compare(key, root->data) < 0)                  //Ʈ���� ������ �ƴ� �� Ʈ�� Ž���Ͽ� ���� �ڸ� ã��
		root->left = insert_node(root->left, key);
	else if (compare(key, root->data) > 0)
		root->right = insert_node(root->right, key);

	return root;                                      //��Ʈ ������ ��ȯ
}

//������ȸ ���
void inorder(TreeNode *root, FILE *fp2)
{
	if (root != NULL)
	{
		inorder(root->left, fp2);
		fprintf(fp2, "[�̸� : %s, ���� �� : %d]\n", root->data.name, root->data.appear);
		inorder(root->right, fp2);
	}
}

//�ִ밪 ��ȯ
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
break, 15
case, 34
do, 1
double, 1
else, 7
for, 3
fprintf, 4
if, 9
int, 17
printf, 27
return, 17
sizeof, 1
switch, 3
while, 4
*/

int main(void)
{
	TreeNode *root = NULL;
	element key;

	FILE *fp1;
	if ((fp1 = fopen("bst_in.txt", "r")) == NULL)
	{
		printf("������ ������ �ʽ��ϴ�. \n");
		exit(1);
	}

	FILE *fp2;
	if ((fp2 = fopen("bst_out.txt", "w")) == NULL)
	{
		printf("������ ������ �ʽ��ϴ�. \n");
		exit(1);
	}

	char *arr = malloc(sizeof(char)*MAX_SIZE);
	char *str[16] = {"fprintf", "printf", "double", "break", "case", "do", "else", "for", "if", "int", "float",  "return", "sizeof", "switch", "while" };

	while (!feof(fp1))
	{
		fscanf(fp1, "%s", arr);
		for (int i = 0;i < 15; i++)
		{
			if (strstr(arr, str[i]))
			{
				strcpy(key.name, str[i]);
				if (search(root, key) == NULL) {
					root = insert_node(root, key);
					break;
				}

				else 
					break;
			}
		}
	}

	inorder(root, fp2);
	max_appear(root);
	fprintf(fp2, "\n[�� �ִ밪: %s(��)�� %d��]", max.name, max.appear);

	free(arr);
	fclose(fp1);
	fclose(fp2);
}