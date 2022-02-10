#include <stdio.h>
#include <string.h>

typedef struct LogIn {
	char id[11];
	char pw[7];
}login;

int IdSearch(login *L, char *target, int first, int last)
{
	int mid = (first + last) / 2;
	if (first > last)
		return -1;
	if (strcmp(target, L[mid].id) == 0)
		return mid;
	else if (strcmp(target, L[mid].id) == 1)
		IdSearch(L, target, mid + 1, last);
	else
		IdSearch(L, target, first, mid-1);
}

int CheckPw(login *L ,int check,int num)
{
	char inputpw[7];
	printf("��й�ȣ�� �Է��ϼ���: ");
	scanf("%s", &inputpw);
	
		if (strcmp(L[check].pw, inputpw) == 0)
		{
			printf("�α��ο� �����Ͽ����ϴ�. \n");
			return 0;
		}

		else 
		{
			printf("��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ��� \n");
			if (num == 3)
			{
				printf("��й�ȣ�� 3ȸ�̻� Ʋ�����Ƿ� ���α׷��� �����մϴ�. \n");
				return num;
			}
			CheckPw(L, check, num+1);
			
		}
}

login ChangePw(login *L, int check)
{
	int n = 0;
	char changepw[7];
	printf("��й�ȣ�� �ٲٽðڽ��ϱ�? (1.yes 2.no): ");
	scanf("%d", &n);

		switch (n)
		{
		case 1:
			printf("�ٲ� ��й�ȣ�� �Է��ϼ���: ");
			scanf("%s", &changepw);
			printf("��й�ȣ Ȯ��: ");
			scanf("%s", &L[check].pw);
			if (strcmp(changepw, L[check].pw) == 0)
			{
				strcpy(L[check].pw, changepw);
				printf("��й�ȣ�� ����Ǿ����ϴ�. �ٽ� �α����ϼ��� \n");
				printf("�ٲ� id�� pw: [%s %s] \n", L[check].id, L[check].pw);
			}

			else
			{
				printf("��й�ȣ Ȯ���� �ٸ��ϴ�. ��й�ȣ ���� �ʱ� �������� �̵��մϴ�. \n");
				ChangePw(L, check);
			}
			break;

		case 2:
			break;
		}
}

int main(void)
{
	login L1[9] = { {"apple", "135468"},  {"kakao", "714876"}, {"banana", "234851"}, {"young", "465238"}, {"drama", "667542"}, 
	{"moderate", "871564"}, {"poem", "916574"}, {"zebra", "336721"}, {"cranberry", "854231"} };
	
	//id�������� ����
	char temp[11] = {'0',};
	for (int i = 0;i < 8;i++)
	{
		for (int j = 0;j < 8 - i;j++)
		{
			if (strcmp(L1[j].id , L1[j + 1].id)>0)
			{
				strcpy(temp, L1[j].id);
				strcpy(L1[j].id, L1[j + 1].id);
				strcpy(L1[j + 1].id, temp);
			}
		}
	}
	printf("-------------------------------------------\n");
	
	//�������� �Ǿ����� Ȯ��
	for (int i = 0;i < 9;i++)
	{
		printf("[id: %s, pw: %s] \n", L1[i].id, L1[i].pw);
	}
	printf("-------------------------------------------\n");

	int first = 0;
	int last = 8;
	char inputid[11];
	char inputpw[7];
	printf("���̵� �Է��ϼ���: : ");
	scanf("%s", &inputid);
	int check=IdSearch(L1, inputid, first, last);
	int num = 1;
	if (check == -1)
	{
		printf("���̵� �������� �ʽ��ϴ�. \n");
		return 0;
	}
	
	else
	{
		num=CheckPw(L1, check,num);
		if (num == 3)
			return 0;
		printf("\n");
		ChangePw(&L1, check);
		printf("\n");
	}
	
	while (1)
	{
		int n = 0;
		num = 1;
		printf("�ٽ� �α��� �Ϸ��� 1, ���α׷��� �����Ϸ��� 2�� �����ʽÿ�:");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("���̵� �Է��ϼ���: : ");
			scanf("%s", &inputid);
			int check = IdSearch(L1, inputid, first, last);
			if (check == -1)
			{
				printf("���̵� �������� �ʽ��ϴ�. \n");
				return 0;
			}

			else
			{
				num = CheckPw(L1, check, num);
				if (num == 3)
					return 0;
				printf("\n");
				ChangePw(&L1, check);
				printf("\n");
			}
			break;

		case 2:
			return 0;
		
		}

	}

	return 0;
}