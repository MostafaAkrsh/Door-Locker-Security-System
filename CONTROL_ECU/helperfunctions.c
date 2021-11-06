/*
 * helperfunctions.cpp
 *
 *  Created on: Nov 1, 2021
 *      Author: LENOVO
 */

#include "helperfunctions.h"

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

