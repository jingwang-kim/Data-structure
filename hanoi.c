#include <stdio.h>

void Hanoi(int n, char from, char tmp, char to)
{
	if (n == 1)
		printf("���� 1�� %c���� %c���� �ű��. \n", from, to);
	else {
		Hanoi(n - 1, from, to, tmp);
		printf("���� %d�� %c���� %c���� �ű�� \n", n, from, to);
		Hanoi(n - 1, tmp, from, to);
	}
}


int main(void)
{
	Hanoi(3, 'A', 'B', 'C');
	return 0;
}