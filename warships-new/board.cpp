#include "board.h"

Board::Board(short newBoardSize) {
	boardSize = newBoardSize;
	boardTable = new Ship*[newBoardSize];

	for (short s = 0; s < boardSize; s++) {
		boardTable[s] = new Ship[boardSize];
	}
}

Board::~Board() {
	if (boardTable != nullptr) {
		for (short s = 0; s < boardSize; s++) {
			delete[] boardTable[s];
			boardTable[s] = nullptr;
		}

		delete[] boardTable;

		boardTable = nullptr;
		boardSize = 0;
	}
}

bool Board::checkPointInBoard(Point point) {
	short x = point.getX();
	short y = point.getY();

	return (x >= 0 && x < boardSize) && (y >= 0 && y < boardSize);
}

Ship Board::getShip(Point point) {
	if (checkPointInBoard(point) == true) { // Check is coordinate exists
		short x = point.getX();
		short y = point.getY();

		return boardTable[x][y];
	} else {
		return Ship(Point(), ShipState::STATE_INVALID); // Ship does not exist, error
	}
}

short Board::getBoardSize() {
	return boardSize;
}

bool Board::setShip(Ship origin) {
	Point shipPoint = origin.getPoint();
	short x = shipPoint.getX();
	short y = shipPoint.getY();

	if (checkPointInBoard(shipPoint) == true) {
		boardTable[x][y] = origin;
		return true;
	} else {
		return false;
	}
}

void Board::fillShips(ShipState newState) {
	for (short x = 0; x < boardSize; x++) {
		for (short y = 0; y < boardSize; y++) {
			setShip(Ship(Point(x, y), newState));
		}
	}
}

bool Board::isFieldValidForShip(Point point) {
	std::vector<Ship> neighborShips = getNeighbors(point);

	for (short s = 0; s < neighborShips.size(); s++) {
		Ship ship = neighborShips[s];
		ShipState state = ship.getShipState();

		if (state == ShipState::STATE_HIT || state == ShipState::STATE_NOT_HIT) { // A ship is present in closest neighbor already
			return false;
		}
	}

	return getShip(point).getShipState() == ShipState::STATE_EMPTY; // Given field must be empty (cannot be invalid)
}

std::vector<Ship> Board::getNeighbors(Point point) {
	short pointX = point.getX();
	short pointY = point.getY();
	std::vector<Ship> neighbors;

	for (short x = -1; x < 2; x++) {
		for (short y = -1; y < 2; y++) {
			neighbors.push_back(getShip(Point(pointX + x, pointY + y)));
		}
	}

	return neighbors;
}

std::vector<Ship> Board::getStraightNeighbors(Point point) {
	short pointX = point.getX();
	short pointY = point.getY();
	std::vector<Ship> neighbors;

	neighbors.push_back(getShip(Point(pointX, pointY - 1)));
	neighbors.push_back(getShip(Point(pointX, pointY + 1)));

	neighbors.push_back(getShip(Point(pointX - 1, pointY)));
	neighbors.push_back(getShip(Point(pointX + 1, pointY)));

	return neighbors;
}