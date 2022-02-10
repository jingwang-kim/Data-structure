#include <stdio.h>
#include <math.h>
#define MAX_TERMS 101

typedef struct polynomial {
	int degree;
	float coef[MAX_TERMS];
}Poly;

Poly ScanPoly(Poly p)
{
	printf("degree를 입력하세요: ");
	scanf("%d", &p.degree);
	printf("coef를 입력하세요: ");
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
	printf("X값을 설정하세요: ");
	scanf("%d", &x);
	for (int i = 0;i <= p.degree;i++)
		result += p.coef[i] * pow(x, degree_p--);
	printf("결과값: %.1f", result);
	printf("\n");
}

int main(void)
{
	Poly a = { 0,{0,} };
	Poly b = { 0,{0,} };
	Poly c;
	printf("A정보 입력 \n");
	a = ScanPoly(a);
	printf("B정보 입력 \n");
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
		printf("다항식 부터 다시 입력하려면 1번, x값을 다시 입력하려면 2번, 함수를 종료하려면 3번을 누르십시오.");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:
			Poly a = { 0,{0,} };
			Poly b = { 0,{0,} };
			c;
			printf("A정보 입력 \n");
			a = ScanPoly(a);
			printf("B정보 입력 \n");
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
			printf("1~3까지의 숫자만 입력하세요 \n");
			break;
		}
	}
	return 0;
}