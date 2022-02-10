#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100

typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;   // ���� ����
	int cols;   // ���� ����
	int terms;    // ���� ����
} SparseMatrix;

SparseMatrix Convert(SparseMatrix a, int* arr, int row, int col)
{
	a.rows = row;
	a.cols = col;
	a.terms = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (*arr != 0)
			{
				a.data[a.terms].row = i;
				a.data[a.terms].col = j;
				a.data[a.terms].value = *arr;
				a.terms++;
			}
			arr++;
		}
	}

	return a;
}

void Print_Sparse(SparseMatrix a)
{
	int aindex = 0;
	for (int i = 0; i < a.rows; i++)
	{
		for (int j = 0; j < a.cols; j++)
		{

			if (a.data[aindex].col == j && a.data[aindex].row == i)
			{
				printf("  | %d |  ", a.data[aindex].value);
				aindex++;
			}
			else
				printf("  | 0 |  ");

		}
		printf("\n");
	}
	printf("=======================================================\n");
}

void Calculate(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;
	if (a.rows != b.rows || a.cols != b.cols)
	{
		printf("a�� b�� ��� ũ�Ⱑ ���� �ʽ��ϴ�. \n");
		exit(1);
	}

	int counta = 0, countb = 0, countc = 0;

	printf("[����] \n");
	while (counta < a.terms && countb < b.terms)
	{
		int compaA = a.data[counta].row * 10 + a.data[counta].col; //��*������ ��+��
		int compaB = b.data[countb].row * 10 + b.data[countb].col;

		if (compaA < compaB)
			c.data[countc++] = a.data[counta++];

		else if (compaA == compaB)
		{
			if (a.data[counta].value + b.data[countb].value != 0)
			{
				c.data[countc].row = a.data[counta].row;
				c.data[countc].col = a.data[counta].col;
				c.data[countc++].value = a.data[counta++].value + b.data[countb++].value;

			}

			else
			{
				counta++;
				countb++;
			}
		}
		else
			c.data[countc++] = b.data[countb++];
	}
	while (counta < a.terms)
	{
		c.data[countc++] = a.data[counta++];
		counta++;
	}
	while (countb < b.terms)
	{
		c.data[countc++] = b.data[countb++];
		countb++;
	}

	c.terms = countc;
	Print_Sparse(c);

	getchar();
	printf("[����] \n");
	SparseMatrix d;
	d.rows = a.rows;
	d.cols = a.cols;
	counta = 0, countb = 0;
	int countd = 0;
	while (counta < a.terms && countb < b.terms)
	{
		int compaA = a.data[counta].row * 10 + a.data[counta].col;
		int compaB = b.data[countb].row * 10 + b.data[countb].col;

		if (compaA < compaB)
			d.data[countd++] = a.data[counta++];

		else if (compaA == compaB)
		{
			if (a.data[counta].value - b.data[countb].value != 0)    //���� 0�̸� ���� x
			{
				d.data[countd].row = a.data[counta].row;
				d.data[countd].col = a.data[counta].col;
				d.data[countd++].value = a.data[counta++].value - b.data[countb++].value;
			}
			else
			{
				counta++;
				countb++;
			}
		}

		else
		{
			d.data[countd].row = b.data[countb].row;
			d.data[countd].col = b.data[countb].col;
			d.data[countd++].value = b.data[countb++].value*(-1);
		}
			
	}

	while (counta < a.terms)
	{
		d.data[countd++] = a.data[counta++];
		counta++;
	}

	while (countb < b.terms)
	{
		d.data[countd++] = b.data[countb++];
		countb++;
	}

	d.terms = countd;
	Print_Sparse(d);
}

int main(void)
{
	int Ar = 7; int Ac = 5;
	int A[7][5] = { { 0, 0, 0, 0, 2 },
				   { 0, 0,-1, 0, 0 },
				   { 0, 0, 0, 0, 0 },
				   { 5, 0, 0, 0, 0 },
				   { 0, 0, 0, 0, 0 },
				   { 0, 0, 0, 0, 3 },
				   { 0, 0, 1, 0, 0 } };

	int Br = 7; int Bc = 5;
	int B[7][5] = { { 0, 0, 0, 0, 0 },
				   { 0, 0, 1, 0, 0 },
				   { 0,-2, 0, 0, 0 },
				   { 0, 0, 0, 0, 0 },
				   { 0, 0, 0, 0, 0 },
				   { 0, 0, 0, 0, 0 },
				   { 0, 0, 5, 0, 0 } };

	int Cr = 5; int Cc = 6;
	int C[5][6] = { { 0, 0, 0, 0, 0, 2 },
				   { 0, 0, 0,-1, 0, 0 },
				   { 0, 0, 0, 0, 0, 0 },
				   { 0, 5, 0, 0, 0, 0 },
				   { 0, 0, 0, 0, 3, 0 } };

	int Dr = 5; int Dc = 6;
	int D[5][6] = { { 0, 2, 0, 0, 0, 0 },
				   { 0, 0, 0, 1, 0, 0 },
				   { 0, 3, 0, 0, 0, 0 },
				   { 0, 5, 0, 0, 0, 0 },
				   { 0, 0, 0, 0,-1, 0 } };

	SparseMatrix SA = { 0, }, SB = { 0, }, SC = { 0, }, SD = { 0, };
	
	SA = Convert(SA, A[0], Ar, Ac);
	printf("[A��] \n");
	Print_Sparse(SA);

	SB = Convert(SB, B[0], Br, Bc);
	printf("[B��] \n");
	Print_Sparse(SB);

	getchar();
	Calculate(SA, SB);

	SC = Convert(SC, C[0], Cr, Cc);
	getchar();
	printf("[C��] \n");
	Print_Sparse(SC);

	SD = Convert(SD, D[0], Dr, Dc);
	printf("[D��] \n");
	Print_Sparse(SD);

	getchar();
	Calculate(SC, SD);
	return 0;
}