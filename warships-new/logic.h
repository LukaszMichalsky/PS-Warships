#pragma once

#include "point.h"
#include "ship-state.h"

#include <vector>

enum class BoardCharacters : char {
	BOARD_HORIZONTAL_LINE = '-',
	BOARD_VERTICAL_LINE = '|',

	SHIP_EMPTY = ' ',
	SHIP_HIT = 'X',
	SHIP_MISSED_HIT = 'O',
	SHIP_NOT_HIT = '#'
};

enum class ShipDirection { // Types required for positioning ships on board
	DIRECTION_HORIZONTAL,
	DIRECTION_VERTICAL
};

enum class ShipSizes : short { // Predefined ship sizes, other sizes may be used too
	TYPE_CARRIER = 5,
	TYPE_BATTLESHIP = 4,
	TYPE_DESTROYER = 3,
	TYPE_SUBMARINE = 2,
	TYPE_PATROL_BOAT = 1
};

class Board;
class Ship;
class ShipGroup;

class Board {
	private:
		Ship** boardTable = nullptr;
		unsigned short boardSize = 0;

		bool checkPointInBoard(Point point = Point());

	public:
		Board(unsigned short newBoardSize = 10);
		~Board();

		Board(const Board&) = delete; // Removing copy constructor and operator
		Board& operator= (const Board&) = delete;

		Ship getShip(Point point = Point());
		unsigned short getBoardSize();

		void drawBoard(int x, int y);
		bool setShip(Ship origin);
		void fillShips(ShipState newState = ShipState::STATE_EMPTY); // Fills entire board with given ship (may be used to create empty board)

		bool isFieldValidForShip(Point point = Point());
		std::vector<Ship> getNeighbors(Point point = Point()); // Returns ships in a 3x3 square with center of given point
		std::vector<Ship> getStraightNeighbors(Point point = Point()); // Returns ships in closest neighbor fields (up, down, left, right)
};

class Ship {
	private:
		Point shipPoint = Point();
		ShipGroup* myGroup = nullptr; // Ship group, which this ship object belongs to
		ShipState shipState = ShipState::STATE_EMPTY; // By default, field is empty

	public:
		Ship(Point newPoint = Point(0, 0), ShipState newState = ShipState::STATE_EMPTY);
		~Ship();

		Point getPoint();
		ShipState getShipState();

		void setPoint(Point newPoint = Point());
		void setShipState(ShipState newState = ShipState::STATE_EMPTY);
};

class ShipGroup {
	private:
		bool validObject = false;
		std::vector<Ship*> shipObjects = std::vector<Ship*>(); // Pointers to ship objects on board
		short groupSize = 0;
		ShipDirection shipDirection = ShipDirection::DIRECTION_HORIZONTAL; // Ships are positioned horizontally by default

	public:
		// ShipGroup(Board* targetBoard = nullptr, Point topLeftPoint = Point(0, 0));
		ShipGroup(const ShipGroup&) = delete; // Removing copy and move constructors, they are unnecessary
		ShipGroup(ShipGroup&&) = delete;

		ShipGroup& operator=(const ShipGroup&) = delete;
		ShipGroup& operator=(ShipGroup&&) = delete;

		static bool checkPosition(Board* targetBoard = nullptr, Point topLeftPoint = Point(0, 0), short shipSize = 1, ShipDirection shipDirection = ShipDirection::DIRECTION_HORIZONTAL);
		bool isValid();

		ShipDirection getDirection();
		std::vector<Ship*> getShipObjects();
		short getSize();
};