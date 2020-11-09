#include "board.h"
#include "xyio.h"

int main() {
	Board testBoard(10);
	testBoard.fillShips(ShipState::STATE_EMPTY); // Fills the board with empty ships (ShipState::EMPTY)

	testBoard.setShip(Ship(Point(2, 2), ShipState::STATE_NOT_HIT)); // New ship set at point (2, 2)
	xyio::xyprintf(0, 0, "New ship set at point (2, 2)");

	bool isValid = testBoard.isFieldValidForShip(Point(0, 0)); // Test whether new ship could be set at point (0, 0) --> should be true (1)
	xyio::xyprintf(0, 1, "(0, 0) --> %d", isValid);

	isValid = testBoard.isFieldValidForShip(Point(1, 1)); // Test whether new ship could be set at point (1, 1) --> should be false (0)
	xyio::xyprintf(0, 2, "(1, 1) --> %d", isValid);

	return 0;
}