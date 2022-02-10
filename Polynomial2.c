#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TERMS 101

typedef struct polynomial {
	float coef;
	int expon;
}Poly;
Poly terms[MAX_TERMS] = { {0,}, };

char Compare(int a, int b)
{
	if (a > b)
		return '>';
	else if (a == b)
		return '=';
	else
		return '<';
}

int Attach(float coef, int expon, int avail)
{
	if (avail > MAX_TERMS)
	{
		fprintf(stderr, "항의 개수가 너무 많음 \n");
		exit(1);
	}

	terms[avail].coef = coef;
	terms[avail].expon = expon;
	avail++;
	return avail;
}

void Add(int As, int Ae, int Bs, int Be, int *Cs, int *Ce, int avail)
{
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (Compare(terms[As].expon, terms[Bs].expon))
		{
		case '>':
			avail=Attach(terms[As].coef, terms[As].expon, avail);
			As++;
			break;

		case '=':
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef)
				avail=Attach(tempcoef, terms[As].expon, avail);
			As++;
			Bs++;
			break;

		case '<':
			avail=Attach(terms[Bs].coef, terms[Bs].expon, avail);
			Bs++;
			break;
		}

	for (;As <= Ae;As++)
		avail=Attach(terms[As].coef, terms[As].expon, avail);
	for (;Bs <= Be;Bs++)
		avail=Attach(terms[Bs].coef, terms[Bs].expon, avail);
	*Ce = avail - 1;
}

void PrintPoly(int s, int e)
{
	for (int i = s;i < e;i++)
		printf("%.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%.1fx^%d \n", terms[e].coef, terms[e].expon);
}


void ScanPoly(int Ae, int Be)
{
	printf("A의 계수와 차수 입력: ");
	for (int i = 0;i <= Ae;i++)
		scanf("%f, %d", &terms[i].coef, &terms[i].expon);
	printf("B의 계수와 차수 입력: ");
	for (int i = Ae+1;i <= Be;i++)
		scanf("%f, %d", &terms[i].coef, &terms[i].expon);
}

void Calx(int Cs, int Ce)
{
	
	int x = 0;
	float result = 0;
	printf("\n");
	printf("x값을 입력하세요: ");
	scanf("%d", &x);
	for (int i = Cs;i <= Ce;i++)
		result += terms[i].coef*pow(x, terms[i].expon);
	printf("결과값 : %.1f", result);
	printf("\n");	
}

int main(void)
{
	int As = 0, Ae,Be,Cs,Ce;
	printf("A를 몇까지 입력받으시겠습니까?(인덱스 값으로 입력): ");
	scanf("%d", &Ae);
	
	printf("B를 몇까지 입력받으시겠습니까?(인덱스 값으로 입력): ");
	scanf("%d", &Be);
	
	ScanPoly(Ae, Be);
	int Bs = Ae + 1;
	int avail = Be + 1;
	Add(As, Ae, Bs, Be, &Cs, &Ce, avail);

	PrintPoly(As, Ae);
	PrintPoly(Bs, Be);
	printf("------------------------------------------------\n");
	PrintPoly(Cs, Ce);

	Calx(Cs, Ce);

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
			As = 0, Ae=0, Be=0, Cs, Ce;
			printf("A를 몇까지 입력받으시겠습니까?(인덱스 값으로 입력): ");
			scanf("%d", &Ae);
			printf("B를 몇까지 입력받으시겠습니까?(인덱스 값으로 입력): ");
			scanf("%d", &Be);
			ScanPoly(Ae, Be);
			Bs = Ae + 1;
			avail = Be + 1;
			Add(As, Ae, Bs, Be, &Cs, &Ce, avail);

			PrintPoly(As, Ae);
			PrintPoly(Bs, Be);
			printf("------------------------------------------------\n");
			PrintPoly(Cs, Ce);

			Calx(Cs, Ce);
			break;

		case 2:
			Calx(Cs, Ce);
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