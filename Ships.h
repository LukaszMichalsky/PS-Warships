#pragma once
#include <iostream>
#include <string.h>
#include "Some_functions.h"
using namespace std;

class Ships : public Some_functions
{
protected:
	int size = 4;
	bool vertical = true; //0 - horizontal / 1 - vertical
	int X = 0;
	int Y = 0;

public:
	Ships();
	Ships(int s);

	Ships(bool vert,int x,int y, int size)
		:vertical(vert), size(size),X(x),Y(y)
	{
		
	}
	void set_Y(int y) {if(y<10 && y>=0) Y = y; }
	void set_X(int x) {if(x<10 && x>=0) X = x; }
	void set_negativevertical() { if (vertical) vertical = false; else vertical = true; }
	int get_X() { return X; }
	int get_Y() { return Y; }
	int get_size() { return size; }
	bool get_vertical() { return vertical; }
};
