/*
 * helpers.c
 *
 *  Created on: Nov 4, 2021
 *      Author: LENOVO
 */

#include "helpers.h"

uint8 check_identical(uint8* pass1, uint8* pass2)
{
	int pass_index;
	for(pass_index = 0 ; pass_index < PASS_SIZE ; pass_index++)
	{
		if(pass1[pass_index]!=pass2[pass_index])
		{
			return 0;
		}
	}

	return 1;
}
