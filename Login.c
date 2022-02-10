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
	printf("비밀번호를 입력하세요: ");
	scanf("%s", &inputpw);
	
		if (strcmp(L[check].pw, inputpw) == 0)
		{
			printf("로그인에 성공하였습니다. \n");
			return 0;
		}

		else 
		{
			printf("비밀번호를 틀렸습니다. 다시 입력하세요 \n");
			if (num == 3)
			{
				printf("비밀번호를 3회이상 틀렸으므로 프로그램을 종료합니다. \n");
				return num;
			}
			CheckPw(L, check, num+1);
			
		}
}

login ChangePw(login *L, int check)
{
	int n = 0;
	char changepw[7];
	printf("비밀번호를 바꾸시겠습니까? (1.yes 2.no): ");
	scanf("%d", &n);

		switch (n)
		{
		case 1:
			printf("바꿀 비밀번호를 입력하세요: ");
			scanf("%s", &changepw);
			printf("비밀번호 확인: ");
			scanf("%s", &L[check].pw);
			if (strcmp(changepw, L[check].pw) == 0)
			{
				strcpy(L[check].pw, changepw);
				printf("비밀번호가 변경되었습니다. 다시 로그인하세요 \n");
				printf("바뀐 id와 pw: [%s %s] \n", L[check].id, L[check].pw);
			}

			else
			{
				printf("비밀번호 확인이 다릅니다. 비밀번호 변경 초기 페이지로 이동합니다. \n");
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
	
	//id오름차순 정렬
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
	
	//오름차순 되었는지 확인
	for (int i = 0;i < 9;i++)
	{
		printf("[id: %s, pw: %s] \n", L1[i].id, L1[i].pw);
	}
	printf("-------------------------------------------\n");

	int first = 0;
	int last = 8;
	char inputid[11];
	char inputpw[7];
	printf("아이디를 입력하세요: : ");
	scanf("%s", &inputid);
	int check=IdSearch(L1, inputid, first, last);
	int num = 1;
	if (check == -1)
	{
		printf("아이디가 존재하지 않습니다. \n");
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
		printf("다시 로그인 하려면 1, 프로그램을 종료하려면 2를 누르십시오:");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("아이디를 입력하세요: : ");
			scanf("%s", &inputid);
			int check = IdSearch(L1, inputid, first, last);
			if (check == -1)
			{
				printf("아이디가 존재하지 않습니다. \n");
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