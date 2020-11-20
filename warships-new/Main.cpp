#include "common.h"
#include "logic.h"
#include "xyio.h"

int main() {
	// Common::drawMainMenu(); // Application entry point

	// Board b; // Creating default board (10x10)
	// Board b(20); // Creating board with custom size (20x20)

	// b.fillShips(ShipState::STATE_EMPTY); // Filling board with empty ships (fields)
	// b.drawBoard(0, 0); // Draw board from point (0, 0) - top left pixel

	// Checking whether ship with size 5 can be placed on board 'b' in point (0, 0) <-- top/left point, horizontally
	// bool canBePlaced = ShipGroup::checkPosition(&b, Point(0, 0), 5, ShipDirection::DIRECTION_HORIZONTAL);

	// bool wasShipPlaced = ShipGroup::add(&b, Point(0, 0), (short) ShipSizes::TYPE_CARRIER, ShipDirection::DIRECTION_VERTICAL); // Add new ship to board
	// b.drawBoard(0, 0);

	// Shooting on board
	// b.shoot(Point(0, 0));
	// b.shoot(Point(3, 5));
	// b.shoot(Point(9, 9));

	return 0;
}