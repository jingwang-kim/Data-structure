#include <stdio.h>
#include <math.h>

typedef struct coordinate{
	int xpos;
	int ypos;
}Codi;

int Distance(Codi *pos, double *dis)
{
	for (int i = 0;i < 5;i++)
	{
		 dis[i] = sqrt((pos[i].xpos*pos[i].xpos) + (pos[i].ypos*pos[i].ypos));
	}
	return dis;
}

int Compare(double *dis, int num)
{
	for (int i = 0;i < 4;i++)
	{
		if (dis[num] < dis[i])
		{
			num = i;
		}
	}
	return num;
}

int main(void)
{
	Codi pos[5];
	double dis[5];
	int num=0;
	for (int i = 0;i < 5;i++)
	{
		printf("%d��° �迭�� x��ǥ: ", i + 1); scanf("%d", &pos[i].xpos);
		printf("%d��° �迭�� y��ǥ: ", i + 1); scanf("%d", &pos[i].ypos);
	}
	printf("-----------------------------\n");

	for (int i = 0;i < 5;i++)
	{
		printf("�Է��� ��ǥ��: [%d,%d] \n", pos[i].xpos, pos[i].ypos);
	}

	Distance(pos, &dis);
	printf("-----------------------------\n");
	for (int i = 0;i < 5;i++)
	{
		printf("���� ��ǥ�� �Ÿ�: %f \n", dis[i]);
	}
	
	printf("-----------------------------\n");
	num=Compare(&dis, num);
	printf("���� �� �Ÿ��� ��ǥ�� [%d,%d]�Դϴ�.", pos[num].xpos, pos[num].ypos);

	return 0;
}