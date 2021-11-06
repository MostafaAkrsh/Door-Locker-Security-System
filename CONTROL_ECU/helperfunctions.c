#include "helperfunctions.h"

/* function to calculate the power */
uint32 power(uint8 base , uint8 power)
{
	uint32 sum = 1;

	int i = 1;
	for(i = 1 ; i <= power ; i++)
	{
		sum *= base;
	}

	return sum;
}

