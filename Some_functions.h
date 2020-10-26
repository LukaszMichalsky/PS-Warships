#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>


class Some_functions
{
	protected:
	int randDirection()
	{
		srand(time(NULL));
		return rand() % 2;
	}



	int randPosition()
	{
		srand(time(NULL));
		return rand() % 10;
	}
};