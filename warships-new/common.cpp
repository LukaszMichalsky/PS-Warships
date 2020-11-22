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

void Common::modeSelectorManual() {

	
		xyio::clear();
		xyio::xyprintf(0, 0, "|------------------------------|");
		xyio::xyprintf(0, 1, "|  >> Manually adding ships... |");
		xyio::xyprintf(0, 2, "|------------------------------|");

		
		Board manualBoard;
		std::vector<short> shipsSizes = SHIPS;

		manualBoard.fillShips();
		manualBoard.drawBoard(2, 5);

		

		for (short manualShip = 0; manualShip < shipsSizes.size(); manualShip++) {

			char input[8] = {};
			char emptyLine[60];
			memset(emptyLine, ' ', 59 * (sizeof input[0]));
			emptyLine[59] = '\0';
			int x, y;
			short currentSize = shipsSizes[manualShip];
			char side;
			xyio::xyprintf(50, 6, "|  x,y - First coordinates of %d-length ship ... |",currentSize);
			xyio::xyprintf(50, 7, " %s", emptyLine);
			xyio::xyprintf(50, 8, " %s", emptyLine);
			xyio::xyprintf(50, 9, " %s", emptyLine);
			xyio::xyprintf(50, 10, " %s", emptyLine);
			xyio::xyprintf(50, 11, " %s", emptyLine);
			xyio::xyprintf(50, 7 , "  >> ");
			xyio::setcursor(56, 7);
			int readBytes = scanf_s("%s", input, 7);

			if (strcmp(input, "q") != 0) {
				if (sscanf(input, "%d %*1s %d", &x, &y) > 0) {
					do {
						xyio::xyprintf(50, 8, "Adding new ship started at coordinates %d and %d...", x, y);
						xyio::xyprintf(50, 9, "Which way the ship is situated - down,up,left,right? d/u/l/p");
						xyio::xyprintf(50, 10, "  >> %s", emptyLine);
						xyio::xyprintf(50, 11, " %s", emptyLine);
						xyio::setcursor(56, 10);
						memset(input, 0, 7 * (sizeof input[0]));
						int readBytes = scanf_s("%s", input, 7);
						char selectedSide = input[0];
						switch (selectedSide)
						{
						case 'd':
							xyio::xyprintf(50, 11, "1char: %s", input);
							break;
						case 'u':
							xyio::xyprintf(50, 11, "2char: %s", input);
							break;
						case 'l':
							xyio::xyprintf(50, 11, "3char: %s", input);
							break;
						case 'p':
							xyio::xyprintf(50, 11, "4char: %s", input);
							break;
						default:
							xyio::xyprintf(50, 11, "Invalid option, try again...");
							Sleep(3000);
							continue;
						}
						break;
					} while (true);
					
				}
				else {
					xyio::xyprintf(50, 11, "Invalid option, try again...");
					manualShip--;
					continue;
					Sleep(3000);
				}
			}
		}
		
}


void Common::selectGameMode(int mode) {
	switch (mode) {
		case 1: {
			xyio::clear();
			modeSelectorRandom();

			break;
		} case 2: {
			xyio::clear();
			modeSelectorManual();

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