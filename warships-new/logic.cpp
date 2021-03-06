#include "logic.h"
#include "xyio.h"

#include <string>

Board::Board(unsigned short newBoardSize) {
	boardSize = newBoardSize;
	boardTable = new Ship* [newBoardSize];

	for (unsigned short s = 0; s < boardSize; s++) {
		boardTable[s] = new Ship[boardSize];
	}
}

Board::~Board() {
	if (boardTable != nullptr) {
		for (unsigned short s = 0; s < boardSize; s++) {
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

Ship* Board::getShip(Point point) {
	if (checkPointInBoard(point) == true) { // Check is coordinate exists
		short x = point.getX();
		short y = point.getY();

		return &boardTable[x][y];
	} else {
		return nullptr; // Ship does not exist, error
	}
}

unsigned short Board::getBoardSize() {
	return boardSize;
}

void Board::drawBoard(int x, int y) {
	for (unsigned short s = 0; s < boardSize + 1; s++) {
		xyio::xyprintf(x, y + 1 + 2 * s, std::string(4 + 4 * ((size_t) boardSize), (char) BoardCharacters::BOARD_HORIZONTAL_LINE).c_str());

		for (unsigned short t = 0; t < boardSize + 1; t++) {
			char shipCharacter = (char) BoardCharacters::SHIP_EMPTY;
			ShipState shipState = ShipState::STATE_EMPTY;
			Ship* shipObject = getShip(Point(t - 1, s - 1));
			WORD color = xyio::defaultColor;

			if (shipObject != nullptr) {
				shipState = shipObject -> getShipState();

				if (shipState == ShipState::STATE_HIT) {
					color = FOREGROUND_RED;
					shipCharacter = (char) BoardCharacters::SHIP_HIT;
				} else if (shipState == ShipState::STATE_MISSED_HIT) {
					shipCharacter = (char) BoardCharacters::SHIP_MISSED_HIT;
				} else if (shipState == ShipState::STATE_NOT_HIT) {
					color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
					shipCharacter = (char) BoardCharacters::SHIP_NOT_HIT;
				} else if (shipState == ShipState::STATE_DROWNED) {
					color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
					shipCharacter = (char) BoardCharacters::SHIP_DROWNED;
				}
			}

			xyio::xyprintf(x + 4 * t, y + 2 * s, "   %c", (char) BoardCharacters::BOARD_VERTICAL_LINE);
			xyio::setColor(color);

			xyio::xyprintf(x + 4 * t, y + 2 * s, " %c ", shipCharacter);
			xyio::resetColor();

			if (s > 0 && t == 0) {
				xyio::xyprintf(x, y + 2 * s, "%2d", s);
			}

			if (s == 0 && t > 0) {
				xyio::xyprintf(x + 4 * t, y + 2 * s, " %c ", 96 + t);
			}
		}
	}
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
	for (unsigned short x = 0; x < boardSize; x++) {
		for (unsigned short y = 0; y < boardSize; y++) {
			setShip(Ship(Point(x, y), newState));
		}
	}
}

bool Board::isFieldValidForShip(Point point) {
	std::vector<Ship*> neighborShips = getNeighbors(point);

	for (short s = 0; s < neighborShips.size(); s++) {
		Ship* ship = neighborShips[s];
		ShipState state = ShipState::STATE_EMPTY;

		if (ship != nullptr) {
			state = ship -> getShipState();

			if (state == ShipState::STATE_HIT || state == ShipState::STATE_NOT_HIT) { // A ship is present in closest neighbor already
				return false;
			}
		}
	}

	if (getShip(point) != nullptr) {
		return getShip(point) -> getShipState() == ShipState::STATE_EMPTY; // Given field must be empty (cannot be invalid)
	} else {
		return false;
	}
}

bool Board::shoot(bool& targetHit, Point point) {
	bool wasHit = false;
	bool wasShoot = false;

	if (checkPointInBoard(point) == true) {
		Ship* shipObject = getShip(point);

		if (shipObject -> getShipState() == ShipState::STATE_NOT_HIT) {
			shipObject -> setShipState(ShipState::STATE_HIT);
			wasHit = true;

			if (shipObject -> getShipGroup() -> getShipsLeft() == 0) {
				for (Ship* ship : shipObject -> getShipGroup() -> getShipObjects()) {
					ship -> setShipState(ShipState::STATE_DROWNED);
				}
			}
		} else if (shipObject -> getShipState() == ShipState::STATE_EMPTY) {
			shipObject -> setShipState(ShipState::STATE_MISSED_HIT);
		}

		wasShoot = true;
	}

	targetHit = wasHit; // Flag was the shoot missed or not
	return wasShoot; // Flag was the shoot valid (in board point, or outside from it)
}

std::vector<Ship*> Board::getNeighbors(Point point) {
	short pointX = point.getX();
	short pointY = point.getY();
	std::vector<Ship*> neighbors;

	for (short x = -1; x < 2; x++) {
		for (short y = -1; y < 2; y++) {
			neighbors.push_back(getShip(Point(pointX + x, pointY + y)));
		}
	}

	return neighbors;
}

Ship::Ship(Point newPoint, ShipState newState) : shipPoint(newPoint), shipState(newState) {
	// Ship constructor, no additional code needed
}

Ship::~Ship() {
	// Ship destructor, no additional code needed
}

Point Ship::getPoint() {
	return shipPoint;
}

ShipGroup* Ship::getShipGroup() {
	return myGroup;
}

ShipState Ship::getShipState() {
	return shipState;
}

void Ship::setPoint(Point newPoint) {
	shipPoint = newPoint;
}

void Ship::setShipGroup(ShipGroup* newGroup) {
	myGroup = newGroup;
}

void Ship::setShipState(ShipState newState) {
	shipState = newState;
}

ShipGroup::ShipGroup() {
	// ShipGroup constructor, no additional code needed
}

ShipGroup* ShipGroup::add(Board* targetBoard, Point topLeftPoint, short shipSize, ShipDirection shipDirection) {
	short pointX = topLeftPoint.getX();
	short pointY = topLeftPoint.getY();
	ShipGroup* newObject = nullptr;

	if (targetBoard == nullptr || shipSize < 1) {
		return nullptr;
	}

	if (checkPosition(targetBoard, topLeftPoint, shipSize, shipDirection) == false) {
		return nullptr;
	} else {
		newObject = new ShipGroup();
		newObject -> groupSize = shipSize;
	}

	switch (shipDirection) {
		case ShipDirection::DIRECTION_HORIZONTAL: {
			for (short s = 0; s < shipSize; s++) {
				Point newPoint(pointX + s, pointY);
				targetBoard -> setShip(Ship(newPoint, ShipState::STATE_NOT_HIT));

				Ship* shipPointer = targetBoard -> getShip(newPoint);
				shipPointer -> setShipGroup(newObject);

				newObject -> shipObjects.push_back(shipPointer);
			}

			break;
		}

		case ShipDirection::DIRECTION_VERTICAL: {
			for (short s = 0; s < shipSize; s++) {
				Point newPoint(pointX, pointY + s);
				targetBoard -> setShip(Ship(newPoint, ShipState::STATE_NOT_HIT));

				Ship* shipPointer = targetBoard -> getShip(newPoint);
				shipPointer -> setShipGroup(newObject);
				newObject -> shipObjects.push_back(shipPointer);
			}

			break;
		}

		default: {
			delete newObject;
			return nullptr;
		}
	}

	return newObject;
}

bool ShipGroup::checkPosition(Board* targetBoard, Point topLeftPoint, short shipSize, ShipDirection shipDirection) {
	short pointX = topLeftPoint.getX();
	short pointY = topLeftPoint.getY();

	if (targetBoard == nullptr || shipSize < 1) {
		return false;
	}

	switch (shipDirection) {
		case ShipDirection::DIRECTION_HORIZONTAL: {
			for (short s = 0; s < shipSize; s++) {
				if (targetBoard -> isFieldValidForShip(Point(pointX + s, pointY)) == false) return false;
			}

			break;
		}

		case ShipDirection::DIRECTION_VERTICAL: {
			for (short s = 0; s < shipSize; s++) {
				if (targetBoard -> isFieldValidForShip(Point(pointX, pointY + s)) == false) return false;
			}

			break;
		}

		default: {
			return false;
		}
	}

	return true;
}

bool ShipGroup::isValid() {
	return validObject;
}

ShipDirection ShipGroup::getDirection() {
	return shipDirection;
}

std::vector<Ship*> ShipGroup::getShipObjects() {
	return shipObjects;
}

short ShipGroup::getShipsLeft() {
	short shipsLeft = 0;

	for (short s = 0; s < groupSize; s++) {
		if (shipObjects[s] -> getShipState() == ShipState::STATE_NOT_HIT) shipsLeft++;
	}

	return shipsLeft;
}

short ShipGroup::getSize() {
	return groupSize;
}