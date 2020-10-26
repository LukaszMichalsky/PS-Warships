#pragma once
#include "Ships.h"

Ships::Ships(int s)
	:size(s)
{
	vertical = randDirection();
	X = randPosition();
	Y = randPosition();

	if (vertical)
	{
		if(Y>10-s)
		Y-=s-1;
	}
	else
	{
		if (X > 10 - s)
			X -= s - 1;
	}

}