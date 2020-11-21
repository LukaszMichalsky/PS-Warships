#include "common.h"
#include "logic.h"

#include <cstdlib>
#include <ctime>
#include <string>

void Common::drawMainMenu() {
	xyio::xyprintf(0, 0, "|---------------------------------------|");
	xyio::xyprintf(0, 1, "|-- Programowanie Systemowe - Projekt --|");
	xyio::xyprintf(0, 2, "|---------------------------------------|");
	xyio::xyprintf(0, 3, "|  >> Network Warships - Main Menu      |");
	xyio::xyprintf(0, 4, "|---------------------------------------|");
	xyio::xyprintf(0, 5, "|  >> 1 - Create new game (server)      |");
	xyio::xyprintf(0, 6, "|  >> 2 - Join to game (client)         |");
	xyio::xyprintf(0, 7, "|  >> q - Exit program                  |");
	xyio::xyprintf(0, 8, "|---------------------------------------|");
	xyio::xyprintf(0, 9, "|  >> ");

	char input[8] = {};
	int selectedOption = 0;
	int readBytes = scanf_s("%s", input, 7);

	if (strcmp(input, "q") != 0) {
		selectedOption = atoi(input);
		selectMenuOption(selectedOption);
	} else {
		ExitProcess(0);
	}
}

void Common::drawModeSelector() {
	xyio::xyprintf(0, 0, "|------------------------------|");
	xyio::xyprintf(0, 1, "|  >> Game mode selector       |");
	xyio::xyprintf(0, 2, "|------------------------------|");
	xyio::xyprintf(0, 3, "|  >> 1 - Generate random ships|");
	xyio::xyprintf(0, 4, "|  >> 2 - Set ships manually   |");
	xyio::xyprintf(0, 5, "|------------------------------|");
	xyio::xyprintf(0, 6, "| >> ");

	char input[8] = {};
	int selectedMode = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedMode = atoi(input);
	selectGameMode(selectedMode);
}

void Common::modeSelectorRandom() {
	xyio::xyprintf(0, 0, "----------------------");
	xyio::xyprintf(0, 1, "  >> Ships randomizer ");
	xyio::xyprintf(0, 2, "----------------------");

	Board randomizerBoard;
	std::vector<short> shipsSizes = SHIPS;

	randomizerBoard.fillShips();
	randomizerBoard.drawBoard(2, 4);

	xyio::xyprintf(50, 4, "Generating random ships...");
	xyio::xyprintf(50, 5, "--------------------------");

	for (short randomShip = 0; randomShip < shipsSizes.size(); randomShip++) {
		std::srand(std::time(nullptr));

		short currentSize = shipsSizes[randomShip];
		xyio::xyprintf(50, 6 + randomShip, "  >> Generating ship with size %d...", currentSize);

		while (true) {
			short randomX = rand() % randomizerBoard.getBoardSize();
			short randomY = rand() % randomizerBoard.getBoardSize();

			Point randomPoint(randomX, randomY);
			ShipDirection randomDirection = (rand() % 2 == 1) ? ShipDirection::DIRECTION_HORIZONTAL : ShipDirection::DIRECTION_VERTICAL;
			bool ready = ShipGroup::checkPosition(&randomizerBoard, randomPoint, currentSize, randomDirection);
			
			if (ready == true) {
				ShipGroup::add(&randomizerBoard, randomPoint, currentSize, randomDirection);
				xyio::xyprintf(50, 6 + randomShip, "  >> Generating ship with size %d... Generated!", currentSize);

				randomizerBoard.drawBoard(2, 4);
				break;
			}

			Sleep(50);
		}
	}

	int shift = shipsSizes.size();
	xyio::xyprintf(50,  6 + shift, "---------------------------------");
	xyio::xyprintf(50,  7 + shift, "  >> Generated all ships");
	xyio::xyprintf(50,  8 + shift, "  >> Is this OK?");
	xyio::xyprintf(50,  9 + shift, "    >> 1. Yes, I confirm");
	xyio::xyprintf(50, 10 + shift, "    >> 2. No, randomize it again");
	xyio::xyprintf(50, 11 + shift, "---------------------------------");
	xyio::xyprintf(50, 12 + shift, "  >> ");

	char input[8] = {};
	int selectedOption = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedOption = atoi(input);
	selectRandomizeAgain(shift, selectedOption, &randomizerBoard);
}

void Common::selectGameMode(int mode) {
	switch (mode) {
		case 1: {
			xyio::clear();
			modeSelectorRandom();

			break;
		} case 2: {
			xyio::clear();
			drawModeSelector();

			break;
		} default: {
			xyio::xyprintf(5, 6, "Invalid game mode, try again...");
			Sleep(3000);

			xyio::clear();
			drawModeSelector();
		}
	}
}

void Common::selectMenuOption(int option) {
	switch (option) {
		case 1: {
			xyio::clear();
			Server::initializeServer();

			break;
		} case 2: {
			xyio::clear();
			Client::initializeClient();

			break;
		} default: {
			xyio::xyprintf(5, 9, "Invalid option, try again...");
			Sleep(3000);

			xyio::clear();
			drawMainMenu();

			break;
		}
	}
}

void Common::selectRandomizeAgain(int ships, int option, Board* myBoard) {
	switch (option) {
		case 1: {
			xyio::clear();
			waitForSecondPlayer(myBoard);

			break;
		} case 2: {
			xyio::clear();
			modeSelectorRandom();

			break;
		} default: {
			xyio::xyprintf(55, 12 + ships, "Invalid option, try again...");
			Sleep(3000);

			xyio::xyprintf(50, 12 + ships, (std::string("  >> ") + std::string(50, ' ')).c_str());
			xyio::xyprintf(50, 12 + ships, "  >> ");

			char input[8] = {};
			int selectedOption = 0;
			int readBytes = scanf_s("%s", input, 7);

			selectedOption = atoi(input);
			selectRandomizeAgain(ships, selectedOption, myBoard);

			break;
		}
	}
}

void Common::restartGame() {
	printf("  >> Would you like to start game again?\r\n");
	printf("    >> 1. Yes\r\n");
	printf("    >> Any other value will stop and exit\r\n");
	printf("-----------------------------------------\r\n");
	printf("    >> ");

	char input[8] = {};
	int selectedOption = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedOption = atoi(input);

	if (selectedOption == 1) {
		drawMainMenu();
	} else {
		ExitProcess(0);
	}
}

void Common::waitForSecondPlayer(Board* playerBoard) {
	xyio::xyprintf(0, 0, "----------------------------------------------");
	xyio::xyprintf(0, 1, "  >> Waiting for second player to be ready... ");
	xyio::xyprintf(0, 2, "----------------------------------------------");

	int sendCode = send(NetworkConfiguration::clientSocket, "OK", NetworkConfiguration::bufferLength, NULL);
	int readData = recv(NetworkConfiguration::clientSocket, NetworkConfiguration::receiveBuffer, NetworkConfiguration::bufferLength, NULL);

	if (readData == -1 || readData == 0) {
		xyio::xyprintf(0, 3, "  >> Player has disconnected");
		xyio::xyprintf(0, 4, "");

		restartGame();
		closesocket(NetworkConfiguration::clientSocket);
		WSACleanup();
	} else {
		xyio::xyprintf(0, 3, "  >> OK! Starting game...");
	}
}