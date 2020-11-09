#pragma once

#include "ship.h"

class Board {
	private:
		Ship** boardTable = nullptr;
		short boardSize = 0;

		bool checkPoint(Point point = Point());

	public:
		Board(short newBoardSize = 10);
		~Board();

		Board(const Board&) = delete; // Removing copy constructor and operator
		Board& operator= (const Board&) = delete;

		Ship getShip(Point point = Point());
		short getSize();

		bool setShip(Point point = Point(), Ship origin = Ship());
		void fillShips(Ship origin = Ship()); // Fills entire board with given ship (may be used to create empty board)
};