#include "common.h"
#include "logic.h"
#include "xyio.h"

int main() {
	Common::drawMainMenu(); // Application entry point

	// Board b; // Creating default board (10x10)
	// Board b(20); // Creating board with custom size (20x20)

	// b.fillShips(ShipState::STATE_EMPTY); // Filling board with empty ships (fields)
	// b.setShip(Ship(Point(1, 1), ShipState::STATE_NOT_HIT)); // Setting new ship in point (1, 1)
	// b.drawBoard(0, 0); // Draw board from point (0, 0) - top left pixel

	// Checking whether ship with size 5 can be placed on board 'b' in point (0, 0) <-- top/left point, horizontally
	// bool canBePlaced = ShipGroup::checkPosition(&b, Point(0, 0), 5, ShipDirection::DIRECTION_HORIZONTAL);

	return 0;
}