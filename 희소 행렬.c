#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100

typedef struct Element {
	int row; //��
	int col; //��
	int value; //����� ��
}element;

typedef struct sparseMatrix {
	element data[MAX_TERMS];
	int rows; //���� ����
	int cols; //���� ����
	int terms; //���� ����
}sparse;

sparse Input(sparse a)
{
	printf("���� ������ ���� ����, �׸��� ���� ������ �Է��ϼ���.");
	scanf("%d %d %d", &a.rows, &a.cols, &a.terms);

	printf("�����͸� �Է��ϼ���.(��, ��, ��) \n");
	for (int i = 0;i < a.terms;i++)
	{
		scanf("%d %d %d", &a.data[i].row, &a.data[i].col, &a.data[i].value);
	}
	return a;
}

sparse Transpose(sparse a)  //a���� b�� �̵�
{
	sparse b;

	int bindex;
	b.rows = a.rows;
	b.cols = a.cols;
	b.terms = a.terms;

	if (a.terms > 0)
	{
		bindex = 0;
		for (int c = 0;c < a.cols;c++) 
		{
			for (int i = 0;i < a.terms;i++)
			{
				if (a.data[i].col == c)
				{
					b.data[bindex].row = a.data[i].col;
					b.data[bindex].col = a.data[i].row;
					b.data[bindex].value = a.data[i].value;
					bindex++;
				}
			}
		}
	}
	return b;
}

sparse Add(sparse a, sparse b)
{
	sparse c;
	if (a.rows != b.rows || a.cols == b.cols)
	{
		printf("a�� b�� ��� ũ�Ⱑ ���� �ʽ��ϴ�.");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;
	c.terms = 0;
	int counta = 0, countb = 0, countc = 0;

	while (counta<a.terms&&countb<b.terms)
	{
		int compaA = a.data[counta].row*a.rows + a.data[counta].col;
		int compaB = b.data[countb].row*b.rows + b.data[countb].col;
		
		if (compaA < compaB)
		{
			c.data[countc++] = a.data[counta++];
		}

		else if (compaA == compaB)
		{
			if (a.data[counta].value + b.data[countb].value)
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
	
	c.terms = countc;
	return c;
}

void Print(sparse a)
{
	printf("------------------------------------\n");
	for (int i = 0;i < a.terms;i++)
	{
		printf("[%d, %d, %d] \n", a.data[i].row, a.data[i].col, a.data[i].value);
	}
	printf("------------------------------------\n");
}


int main(void)
{
	sparse m = { 0 };
	m = Input(m);
	sparse result;
	result = Transpose(m);
	printf("[���� ��] \n");
	Print(m);
	printf("[���� ��] \n");
	Print(result);
	sparse sum;
	sum = Add(m, result);
	printf("[���� ���]");
	Print(sum);
	return 0;
}