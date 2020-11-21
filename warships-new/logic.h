#pragma once

#include "point.h"

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
	TYPE_BATTLESHIP = 4,
	TYPE_DESTROYER = 3,
	TYPE_SUBMARINE = 2,
	TYPE_PATROL_BOAT = 1
};

enum class ShipState {
	STATE_EMPTY = 0x10, // Field is empty (no ship in it)
	STATE_MISSED_HIT = 0x20, // Field which was tried to hit, but there was no ship.
	STATE_NOT_HIT = 0x30, // Field contains ship which is not hit yet
	STATE_HIT = 0x40 // Field contains ship after being hit
};

class Board;
class Ship;
class ShipGroup;

class Board {
	private:
		Ship** boardTable = nullptr;
		unsigned short boardSize = 0;

		bool checkPointInBoard(Point point = Point());
		bool setShip(Ship origin);

		friend class ShipGroup;

	public:
		Board(unsigned short newBoardSize = 10);
		~Board();

		Board(const Board&) = delete; // Removing copy constructor and operator
		Board& operator= (const Board&) = delete;

		Ship* getShip(Point point = Point());
		unsigned short getBoardSize();

		void drawBoard(int x, int y);
		void fillShips(ShipState newState = ShipState::STATE_EMPTY); // Fills entire board with given ship (may be used to create empty board)

		bool isFieldValidForShip(Point point = Point());
		bool shoot(Point point = Point()); // Shooting function, returns if the shoot has been done (if point was valid - not whether ship has been hit)
		std::vector<Ship*> getNeighbors(Point point = Point()); // Returns ships in a 3x3 square with center of given point
};

class Ship {
	private:
		Point shipPoint = Point();
		ShipGroup* myGroup = nullptr; // Ship group, which this ship object belongs to
		ShipState shipState = ShipState::STATE_EMPTY; // By default, field is empty

		void setShipGroup(ShipGroup* newGroup = nullptr);

		friend class ShipGroup;

	public:
		Ship(Point newPoint = Point(0, 0), ShipState newState = ShipState::STATE_EMPTY);
		~Ship();

		Point getPoint();
		ShipGroup* getShipGroup();
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

		ShipGroup(); // Default constructor is not available to public interface

	public:
		ShipGroup(const ShipGroup&) = delete; // Removing copy and move constructors, they are unnecessary
		ShipGroup(ShipGroup&&) = delete;

		ShipGroup& operator=(const ShipGroup&) = delete; // Removing default copy and move operators
		ShipGroup& operator=(ShipGroup&&) = delete;

		static ShipGroup* add(Board* targetBoard = nullptr, Point topLeftPoint = Point(0, 0), short shipSize = 1, ShipDirection shipDirection = ShipDirection::DIRECTION_HORIZONTAL);
		static bool checkPosition(Board* targetBoard = nullptr, Point topLeftPoint = Point(0, 0), short shipSize = 1, ShipDirection shipDirection = ShipDirection::DIRECTION_HORIZONTAL);
		bool isValid();

		ShipDirection getDirection();
		std::vector<Ship*> getShipObjects();

		short getShipsLeft(); // Returns number of undamaged ship modules (only those with ShipState::STATE_NOT_HIT state value)
		short getSize();
};