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

bool Board::checkPoint(Point point) {
	short x = point.getX();
	short y = point.getY();

	return (x >= 0 && x < boardSize) && (y >= 0 && y < boardSize);
}

Ship Board::getShip(Point point) {
	if (checkPoint(point) == true) { // Check is coordinate exists
		short x = point.getX();
		short y = point.getY();

		return boardTable[x][y];
	} else {
		return Ship(Point(), ShipState::STATE_INVALID); // Ship does not exist, error
	}
}

short Board::getSize() {
	return boardSize;
}

bool Board::setShip(Point point, Ship origin) {
	if (checkPoint(point) == true) {
		short x = point.getX();
		short y = point.getY();

		boardTable[x][y] = origin;
		return true;
	} else {
		return false;
	}
}

void Board::fillShips(Ship origin) {
	for (short x = 0; x < boardSize; x++) {
		for (short y = 0; y < boardSize; y++) {
			setShip(Point(x, y), origin);
		}
	}
}