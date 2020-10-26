#pragma once
#include "AI.h"

AI::AI(Board*board)
	:newX(0),newY(0)
{
	int f=1;
	cout << "Seting ships :";
	for(int i=4;i>1;i--)//size
	{ 
		for(int j=0;j<f;j++)//how
		{ 
			
			Ships warship = Ships(i);
			while (board->isColision(&warship))
			{
				warship.set_negativevertical();

				if (board->isColision(&warship))
					warship = Ships(i);
			}
			board->setShip(&warship);
			cout << i <<" ";
		}
		f++;
	}//set 1 4-length, 2 3-length ships

	int h = 0;
	while (h < 4)
	{
		for (int x = 11; x > 1; x-=1)
		{
			for (int y = 1; y < 11; y+=2)
			{
				Ships warship = Ships(0, x, y, 1);
				if (!board->isColision(&warship))
				{
					board->setShip(&warship);
					h++;
					cout << "1 ";
					break;
				}
			}
		}
	}
	system("cls");
}

void AI::shotingsystem(Board*board,int &score)
{

	int tk = 0;
	do
	{
		newX = randPosition() + 1;//generate random cords
		newY = randPosition() + 1;

		++tk;
		if (tk > 500)
		{
			break;
		}

	} while (board->boardtab[newY][newX] == 'M' || board->boardtab[newY][newX] == 'X');
	if (tk > 500) {//mechanizm ma wskazac nastepne wolne pole, by skrocic czas oczekiwania na ruch bota
		bool br = false;
		for (int i = 1; i < 11; i++)
		{
			if (!br)
				break;
			for (int j = 1; j < 11; j++)
				if (board->boardtab[i][j] != 'X' && board->boardtab[i][j] != 'M')
				{
					newX = i;
					newY = j;
					br = true;
					break;
				}
		}
	}

	if (board->boardtab[newY][newX] == 'O')
	{
		board->boardtab[newY][newX] = 'X';
		score++;
	}
	else
		board->boardtab[newY][newX] = 'M';
	
	/*
	if (!was_hit)//if miss beafore or first shot
	{
		do
		{
			newX = randPosition()+1;//generate random cords
			newY = randPosition()+1;
		} while (board->boardtab[newY][newX]=='M'|| board->boardtab[newY][newX] == 'X');
		
		if (board->boardtab[newY][newX] == 'O')//and check is hit
		{
			was_hit = true;
			lastX = newX;
			lastY = newY;
			score++;
			board->boardtab[newY][newX] = 'X';
		}
		else
		{
			board->boardtab[newY][newX] = 'M';
		}
	}
	else//if before hit
	{
		if (cheat(lastX,lastY,board))//if dont sunk
		{
			int pos = randPosition() % 4;

			switch (pos)
			{
			case(0)://one up
				newY = lastY - 1;
				newX = lastX;
				break;
			case(1)://one right
				newX = lastX + 1;
				newY = lastY;
				break;
			case(2)://one down
				newX = lastX;
				newY = lastY + 1;
				break;
			case(3)://one left
				newX = lastX - 1;
				newY = lastY;
				break;
			}


			if (board->boardtab[newY][newX] == 'O')//and check is hit
			{
				was_hit = true;
				lastX = newX;
				lastY = newY;
				score++;
				board->boardtab[newY][newX] = 'X';
			}
			else
			{
				board->boardtab[newY][newX] = 'M';
				was_hit = false;
			}
		}
		else
		{
			do
			{
				newX = randPosition() + 1;//generate random cords
				newY = randPosition() + 1;
			} while (board->boardtab[newY][newX] == 'M' ||board->boardtab[newY][newX] == 'X');

			if (board->boardtab[newY][newX] == 'O')//and check is hit
			{
				was_hit = true;
				lastX = newX;
				lastY = newY;
				score++;
				board->boardtab[newY][newX] = 'X';
			}
			else
			{
				board->boardtab[newY][newX] = 'M';
				was_hit = false;
			}
		}
	}
*/
}


bool AI::cheat(int x, int y,Board*board)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (board->boardtab[y + i][x + j] == 'O')
				return true;

	return false;
}