#pragma once

#include "ship.h"

#include <vector>

class Board {
	private:
		Ship** boardTable = nullptr;
		short boardSize = 0;

		bool checkPointInBoard(Point point = Point());

	public:
		Board(short newBoardSize = 10);
		~Board();

		Board(const Board&) = delete; // Removing copy constructor and operator
		Board& operator= (const Board&) = delete;

		Ship getShip(Point point = Point());
		short getBoardSize();

		bool setShip(Ship origin = Ship());
		void fillShips(ShipState newState = ShipState::STATE_EMPTY); // Fills entire board with given ship (may be used to create empty board)

		bool isFieldValidForShip(Point point = Point());
		std::vector<Ship> getNeighbors(Point point = Point()); // Returns ships in a 3x3 square with center of given point
		std::vector<Ship> getStraightNeighbors(Point point = Point()); // Returns ships in closest neighbor fields (up, down, left, right)
};