#include "common.h"
#include "logic.h"

#include <cstdlib>
#include <ctime>
#include <string>

void Common::drawMainMenu() {


	xyio::centerprintf(0, "|---------------------------------------|");
	xyio::centerprintf(1, "|-- Programowanie Systemowe - Projekt --|");
	xyio::centerprintf(2, "|---------------------------------------|");
	xyio::centerprintf(3, "|  >> Network Warships - Main Menu      |");
	xyio::centerprintf(4, "|---------------------------------------|");
	xyio::centerprintf(5, "|  >> 1 - Create new game (server)      |");
	xyio::centerprintf(6, "|  >> 2 - Join to game (client)         |");
	xyio::centerprintf(7, "|  >> q - Exit program                  |");
	xyio::centerprintf(8, "|---------------------------------------|");
	xyio::centerprintf(9, "| >>                                 << |");
	//xyio::setcursor(xyio::get_X()+5,9);
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

	xyio::centerprintf(0, "|------------------------------|");
	xyio::centerprintf(1, "|   >> Game mode selector <<   |");
	xyio::centerprintf(2, "|------------------------------|");
	xyio::centerprintf(3, "|  >> 1 - Generate random ships|");
	xyio::centerprintf(4, "|  >> 2 - Set ships manually   |");
	xyio::centerprintf(5, "|------------------------------|");
	xyio::centerprintf(6, "| >>                        << |");
	//xyio::setcursor(5,6);
	char input[8] = {};
	int selectedMode = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedMode = atoi(input);
	selectGameMode(selectedMode);
}

void Common::modeSelectorRandom() {
	xyio::centerprintf(0, "|------------------------|");
	xyio::centerprintf(1, "| >> Ships randomizer << |");
	xyio::centerprintf(2, "|------------------------|");

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
		bool isOk;
		char emptyLine[60];
		memset(emptyLine, ' ', 59 * (sizeof emptyLine[0]));
		emptyLine[59] = '\0';

		for (short manualShip = 0; manualShip < shipsSizes.size(); manualShip++) {

			char input[8] = {};
			int startX, startY;
			short currentSize = shipsSizes[manualShip];

			xyio::xyprintf(50, 6, "|  x,y - Set TopLeft coordinates of %d-length ship ... |",currentSize);
			xyio::xyprintf(50, 7, " %s", emptyLine);
			xyio::xyprintf(50, 8, " %s", emptyLine);
			xyio::xyprintf(50, 9, " %s", emptyLine);
			xyio::xyprintf(50, 10, " %s", emptyLine);
			xyio::xyprintf(50, 11, " %s", emptyLine);
			xyio::xyprintf(50, 12, " %s", emptyLine);

			xyio::xyprintf(50, 7 , "  >> ");
			xyio::setcursor(56, 7);
			int readBytes = scanf_s("%s", input, 7);

				if (sscanf(input, "%d %*1s %d", &startX, &startY) > 0 && manualBoard.isFieldValidForShip(Point(startX,startY))) {
					do {
						Point startPoint(startX, startY);

						xyio::xyprintf(50, 8, "Adding new ship started at coordinates %d and %d...", startX, startY);
						xyio::xyprintf(50, 9, "Which way the ship is situated - horizontal or vertical? h/v");
						xyio::xyprintf(50, 10, "Press q to cancel choice.");
						xyio::xyprintf(50, 11, "  >> %s", emptyLine);
						xyio::xyprintf(50, 12, " %s", emptyLine);

						xyio::setcursor(56, 11);
						memset(input, 0, 7 * (sizeof input[0]));
						int readBytes = scanf_s("%s", input, 7);
						char selectedSide = input[0];
						switch (selectedSide)
						{
						case 'h':
							isOk = ShipGroup::checkPosition(&manualBoard, startPoint, currentSize, ShipDirection::DIRECTION_HORIZONTAL);
							if (isOk) {
								ShipGroup::add(&manualBoard, startPoint, currentSize, ShipDirection::DIRECTION_HORIZONTAL);
								xyio::xyprintf(50, 12, "  >> Generating ship with size %d... Added!", currentSize);
								manualBoard.drawBoard(2, 5);
								Sleep(3000);
							}
							else {
								xyio::xyprintf(50, 11, "Shop won't fit...");
								Sleep(3000);
								continue;
							}
							break;
						case 'v':
							isOk = ShipGroup::checkPosition(&manualBoard, startPoint, currentSize, ShipDirection::DIRECTION_VERTICAL);
							if (isOk) {
								ShipGroup::add(&manualBoard, startPoint, currentSize, ShipDirection::DIRECTION_VERTICAL);
								xyio::xyprintf(50, 12, "  >> Generating ship with size %d... Added!", currentSize);
								manualBoard.drawBoard(2, 5);
								Sleep(3000);
							}
							else {
								xyio::xyprintf(50, 12, "Ship won't fit...");
								Sleep(3000);
								continue;
							}
							break;
						case 'q':
							xyio::xyprintf(50, 12, "Canceling...");
							manualShip--;
							Sleep(3000);
							break;
						default:
							xyio::xyprintf(50, 12, "Wrong direction, try again...");
							Sleep(3000);
							continue;
						}
						break;
					} while (true);

				}
				else {
					xyio::xyprintf(50, 12, "Invalid position, try again...");
					manualShip--;
					Sleep(3000);
					continue;

				}
		}

		Common::waitForSecondPlayer(&manualBoard);		

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
			NetworkConfiguration::myRole = Role::ROLE_SERVER;
			Server::initializeServer();

			break;
		} case 2: {
			xyio::clear();
			NetworkConfiguration::myRole = Role::ROLE_CLIENT;
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

void Common::showLoser() {
	xyio::xyprintf(0, 0, "------------------------------------------------");
	xyio::xyprintf(0, 1, "Game lost, all your ships have been destroyed...");
	xyio::xyprintf(0, 2, "------------------------------------------------");
	xyio::xyprintf(0, 3, "");

	restartGame();
};

void Common::showWinner() {
	xyio::xyprintf(0, 0, "-----------------------------------------------");
	xyio::xyprintf(0, 1, "Game over! You are the winner! CONGRATULATIONS!");
	xyio::xyprintf(0, 2, "-----------------------------------------------");
	xyio::xyprintf(0, 3, "");

	restartGame();
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
		xyio::clear();
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
		shutdown(NetworkConfiguration::clientSocket, SD_BOTH);
		closesocket(NetworkConfiguration::clientSocket);
		WSACleanup();
	} else {
		xyio::xyprintf(0, 3, "  >> OK! Starting game...");
		Sleep(1000);

		xyio::clear();
		masterGameFunction(playerBoard);
	}
}