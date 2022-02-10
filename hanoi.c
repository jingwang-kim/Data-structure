#include <stdio.h>

void Hanoi(int n, char from, char tmp, char to)
{
	if (n == 1)
		printf("원판 1을 %c에서 %c으로 옮긴다. \n", from, to);
	else {
		Hanoi(n - 1, from, to, tmp);
		printf("원판 %d을 %c에서 %c으로 옮긴다 \n", n, from, to);
		Hanoi(n - 1, tmp, from, to);
	}
}


int main(void)
{
	Hanoi(3, 'A', 'B', 'C');
	return 0;
}