#include <stdio.h>
#include <math.h>
#define MAX_TERMS 101

typedef struct polynomial {
	int degree;
	float coef[MAX_TERMS];
}Poly;

Poly ScanPoly(Poly p)
{
	printf("degree�� �Է��ϼ���: ");
	scanf("%d", &p.degree);
	printf("coef�� �Է��ϼ���: ");
	for (int i = 0;i < p.degree+1;i++)
	{
		scanf("%f", &p.coef[i]);
	}
	return p;
}

Poly Add(Poly A, Poly B)
{
	Poly C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	
	if (A.degree > B.degree)
		C.degree = A.degree;
	else
		C.degree = B.degree;
	
	while (Apos <= A.degree&&Bpos <= B.degree)
	{
		if (degree_a > degree_b)
		{
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		
		else if (degree_a == degree_b)
		{
			C.coef[Cpos++] = B.coef[Bpos++] + A.coef[Apos++];
			degree_a--;
			degree_b--;
		}
		
		else
		{
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void PrintPoly(Poly p)
{
	printf("Degree : %d \n", p.degree);
	for (int i = p.degree;i > 0;i--)
		printf("%.1fX^%d + ", p.coef[p.degree-i], i);
	printf("%.1f \n", p.coef[p.degree]);
}

void PrintCPoly(Poly C)
{
	int num = 0;
	for (int i = 0;i < C.degree;i++)
	{
		if (C.coef[i] == 0)
			num++;
		else
			break;
	}
	printf("Degree : %d \n", C.degree-num);
	for (int i = C.degree;i > 0;i--)
		printf("%.1fX^%d + ", C.coef[C.degree - i], i);
	printf("%.1f \n", C.coef[C.degree]);
}

void CalX(Poly p)
{
	int x;
	float result = 0;
	int degree_p = p.degree;
	printf("X���� �����ϼ���: ");
	scanf("%d", &x);
	for (int i = 0;i <= p.degree;i++)
		result += p.coef[i] * pow(x, degree_p--);
	printf("�����: %.1f", result);
	printf("\n");
}

int main(void)
{
	Poly a = { 0,{0,} };
	Poly b = { 0,{0,} };
	Poly c;
	printf("A���� �Է� \n");
	a = ScanPoly(a);
	printf("B���� �Է� \n");
	b = ScanPoly(b);
	c = Add(a, b);
	
	printf("[ A ] \n");
	PrintPoly(a);
	printf("\n");
	
	printf("[ B ] \n");
	PrintPoly(b);
	printf("\n");
	
	printf("[ C ] \n");
	PrintCPoly(c);
	printf("\n");
	
	printf("----------------------------------------\n");
	CalX(c);

	while (1)
	{
		int n = 0;
		printf("\n");
		printf("���׽� ���� �ٽ� �Է��Ϸ��� 1��, x���� �ٽ� �Է��Ϸ��� 2��, �Լ��� �����Ϸ��� 3���� �����ʽÿ�.");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:
			Poly a = { 0,{0,} };
			Poly b = { 0,{0,} };
			c;
			printf("A���� �Է� \n");
			a = ScanPoly(a);
			printf("B���� �Է� \n");
			b = ScanPoly(b);
			c = Add(a, b);

			printf("[ A ] \n");
			PrintPoly(a);
			printf("\n");

			printf("[ B ] \n");
			PrintPoly(b);
			printf("\n");

			printf("[ C ] \n");
			PrintCPoly(c);
			printf("\n");

			printf("----------------------------------------\n");
			CalX(c);
			break;

		case 2:
			CalX(c);
			break;

		case 3:
			return 0;

		default:
			printf("1~3������ ���ڸ� �Է��ϼ��� \n");
			break;
		}
	}
	return 0;
}