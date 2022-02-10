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
		printf("%d번째 배열의 x좌표: ", i + 1); scanf("%d", &pos[i].xpos);
		printf("%d번째 배열의 y좌표: ", i + 1); scanf("%d", &pos[i].ypos);
	}
	printf("-----------------------------\n");

	for (int i = 0;i < 5;i++)
	{
		printf("입력한 좌표값: [%d,%d] \n", pos[i].xpos, pos[i].ypos);
	}

	Distance(pos, &dis);
	printf("-----------------------------\n");
	for (int i = 0;i < 5;i++)
	{
		printf("각각 좌표의 거리: %f \n", dis[i]);
	}
	
	printf("-----------------------------\n");
	num=Compare(&dis, num);
	printf("가장 먼 거리의 좌표는 [%d,%d]입니다.", pos[num].xpos, pos[num].ypos);

	return 0;
}