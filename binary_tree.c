#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode n1 = {19, NULL, NULL };
TreeNode n2 = {23, NULL, NULL };
TreeNode n3 = { 5, &n1, &n2 };
TreeNode n4 = { 27, NULL, NULL };
TreeNode n5 = { 29, NULL, NULL };
TreeNode n6 = { 7, &n4, &n5 };
TreeNode n7 = { 3, &n3, &n6 };
TreeNode n8 = { 13, NULL, NULL };
TreeNode n9 = { 17, NULL, NULL };
TreeNode n10 = { 11, &n8, &n9 };
TreeNode n11 = { 2, &n7, &n10 };
TreeNode *root = &n11;

//               2
//            /     \
//           3       11
//         /   \    /   \
//        5    7   13   17
//      /  \  /  \
//     19  23 27 29

//������ȸ
void inorder(TreeNode *root)
{
	if (root != NULL)
	{
		inorder(root->left);            //���� ���� Ʈ�� ���
		printf("[%d] ", root->data);    //�θ������
		inorder(root->right);           //������ ���� Ʈ�� ���
	}
}

//���� ��ȸ
void preorder(TreeNode *root)
{
	if (root != NULL)
	{
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//������ȸ
void postorder(TreeNode *root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}

//�� 1 ����
void plus_preorder(TreeNode *root)
{
	if (root != NULL)
	{
		printf("[%d] ", ++root->data);
		plus_preorder(root->left);
		plus_preorder(root->right);
	}
}

//���� ���
int sum = 0;
int sum_postorder(TreeNode *root)
{
	if (root != NULL)
	{
		sum_postorder(root->left);
		sum_postorder(root->right);
		sum += root->data;
	}

	return sum;
}

//�ִ밪 ��ȯ
int max_postorder(TreeNode *root)
{
	int max=0, cur, left, right;
	if (root != NULL)
	{
		left = max_postorder(root->left);
		right = max_postorder(root->right);
		if (left > right)
			max = left;
		else
			max = right;
		cur = root->data;
		if (max < cur)
		{
			max = cur;
		}
	}
	return max;
}

//x���� ���� �� ���
void min_x(TreeNode *root, int x)
{
	if (root != NULL)
	{
		min_x(root->left, x);
		if (root->data < x)
			printf("[%d] ", root->data);
		min_x(root->right, x);
	}
}

void menu()
{
	printf("==========================================\n");
	printf("1. �� 1 ���� \n");
	printf("2. ���� ��� \n");
	printf("3. �ִ밪 ��ȯ \n");
	printf("4. x���� ���� ���� ��� \n");
	printf("0. ���� \n");
	printf("==========================================\n");
}

int main(void)
{
	int choice;
	int result = 0;
	int max;
	int x = 0;

	printf("���� ��ȸ = ");
	inorder(root);
	printf("\n");

	printf("���� ��ȸ = ");
	preorder(root);
	printf("\n");

	printf("���� ��ȸ = ");
	postorder(root);
	printf("\n");

	menu();
	while (1)
	{
		printf("�޴� ����: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("�� 1 ���� = ");
			plus_preorder(root);
			printf("\n");
			break;

		case 2:
			result = sum_postorder(root);
			printf("���� ��� = %d", result);
			sum = 0;
			printf("\n");
			break;
		
		case 3:
			max = max_postorder(root);
			printf("�ִ밪 ��ȯ = %d", max);
			printf("\n");
			break;

		case 4:
			printf("x�� �Է�: ");
			scanf("%d", &x);
			min_x(root, x);
			printf("\n");
			break;

		case 0:
			return 0;
		}
	}
	
	return 0;
}