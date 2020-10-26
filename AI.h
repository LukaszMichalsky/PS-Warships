#pragma once
#include "Board.h" 
#include "Ships.h"
#include "Some_functions.h"

class AI : public Some_functions
{
protected:
	//int lastX;//last shoting coords
	//int lastY;
	int newX;
	int newY;
	//bool was_hit;
public:
	//contructor setting ships on board
	AI(Board*board);

	//int get_lastX() { return lastX; }
	//int get_lastY() { return lastY; }
	int get_newX() { return newX; }
	int get_newY() { return newY; }

	//void set_lastX(int x) { if (x >= 0 && x < 10)lastX = x; }
	//void set_lastY(int y) { if (y >= 0 && y < 10)lastY = y; }


	void shotingsystem(Board*board,int &score);

	bool cheat(int x,int y,Board*board);//if any ship is near x and y
	
};