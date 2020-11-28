#pragma once

#define SHIPS { \
	4, \
	3, 3, \
	2, 2, 2, \
	1, 1, 1, 1 \
}

#include "client.h"
#include "logic.h"
#include "server.h"
#include "xyio.h"

class Common {
	public:
		static void drawMainMenu();
		static void drawModeSelector();
		static void masterGameFunction(Board* playerBoard);

	private:
		// static void masterGameFunction(Board* playerBoard);
		static void modeSelectorManual();
		static void modeSelectorRandom();

		static void selectGameMode(int mode);
		static void selectMenuOption(int option);
		static void selectRandomizeAgain(int ships, int option, Board* myBoard);

		static void showLoser();
		static void showWinner();

		static void restartGame();

		static void waitForSecondPlayer(Board* playerBoard);
};