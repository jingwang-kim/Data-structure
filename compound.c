#include <stdio.h>

typedef struct Compound {
	double realnum;
	double imaginum;
}Com;

 Com Sum_num(Com *c1)
{
	double realsum = 0, imagisum = 0;
	Com sum;
	for (int i = 0;i < 10;i++)
	{
		realsum += c1[i].realnum;
		imagisum += c1[i].imaginum;
	}
	
	sum.realnum = realsum;
	sum.imaginum = imagisum;
	return sum;
}

int main(void)
{
	Com c1[10];
	Com sum;
	for (int i = 0;i < 10;i++)
	{
		printf("%d��° �Ǽ��ο� ����� �Է�: ", i + 1); scanf("%lf %lf", &c1[i].realnum, &c1[i].imaginum);
	}

	for (int i = 0;i < 10;i++)
	{
		printf("�Էµ� �Ǽ��� ���: [%.1lf + %.1lfi] \n", c1[i].realnum, c1[i].imaginum);
	}
	printf("------------------------------- \n");
	sum = Sum_num(c1);
	printf("�Ǽ��� ����� ��: [%.1lf + %.1lfi] \n", sum.realnum, sum.imaginum);
	return 0;
}