#include "stdio.h"

long long power(char base , char power)
{
	long long sum = 1;

	int i = 1;
	for(i = 1 ; i <= power ; i++)
	{
		sum *= base;
	}

	return sum;
}

int main()
{
	printf("%d",power(4,5));
}
