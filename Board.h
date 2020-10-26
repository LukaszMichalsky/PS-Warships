#pragma once

#include "AI.h"
#include "Ships.h"
using namespace std;

class Board
{
public:
	char boardtab[11][11];

	//constructors
	Board();

	void setShip(Ships* i_src);
	bool isColision(Ships* i_src);//if is colision return true, if else return false
	//functions
	void Drawboard();

};