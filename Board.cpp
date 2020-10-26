#pragma once
#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			boardtab[i][j] = ' '; //fill array space marks

	for (int i = 1; i < 11; i++)
	{	
		boardtab[0][i] = char(47 + i);
	}
	for (int j = 1; j < 11; j++)
	{
		boardtab[j][0] = char(47 + j);//(64 + j);
	}
	boardtab[0][0] = ' ';
	
}


void Board::Drawboard()
{
	for (int i = 0; i < 11; i++)
	{
		for (size_t j = 0; j < 11; j++)
		{
			cout << boardtab[i][j] << "|";
		}

		cout << endl;
	}
	cout << endl;
}

void Board::setShip(Ships* i_src)
{
	int x = i_src->get_X()+1;
	int y = i_src->get_Y()+1;
	int s = i_src->get_size();
		if (i_src->get_vertical())
		{//jezeli pion
			for (int i = 0; i < s; i++)
			{
				boardtab[y+i][x] = 'O';
			}

		}
		else
		{//jezeli poziom
			for (int i = 0; i < s; i++)
				boardtab[y][x+i] = 'O';
		}
}


bool Board::isColision(Ships* i_src)
{
	bool ver = i_src->get_vertical();
	int x = i_src->get_X() + 1;
	int y = i_src->get_Y() + 1;
	int s = i_src->get_size();
	
	if (ver)
	{//Y/pion
		if (y + s > 11)
			return true;
		
		for (int i = -1; i < s + 1; i++)
			for (int j = -1; j <= 1; j++)
				if (boardtab[y + i][x +j] == 'O')
					return true;
			
	}
	else
	{//X/poziom
		if (x + s > 11)//check if ship is out of board
			return true;

		for (int i = -1; i <= 1; i++)
			for (int j = -1; j < s + 1; j++)
				if (boardtab[y + i][x + j] == 'O')				
					return true;
	}
	return false;
}

