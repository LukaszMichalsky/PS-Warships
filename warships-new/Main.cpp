#include "board.h"
#include "common.h"
#include "xyio.h"

int main() {
	Common::drawMainMenu(); // Application entry point

	// Board b; // Creating default board (10x10)
	// Board b(20); // Creating board with custom size (20x20)
	// b.fillShips(ShipState::STATE_EMPTY); // Filling board with empty ships (fields)
	// b.drawBoard(0, 0); // Draw board from point (0, 0) - top left pixel

	return 0;
}