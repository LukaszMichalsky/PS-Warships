#include "board.h"
#include "xyio.h"

int main() {
	xyio::xyprintf(0, 0, "Hello World %d", 123);

	Board testBoard(10);
	testBoard.fillShips(); // Fills the board with empty ships (ShipState::EMPTY)

	return 0;
}