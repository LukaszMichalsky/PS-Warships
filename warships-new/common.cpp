#include "common.h"

void Common::drawMainMenu() {
	xyio::xyprintf(0, 0, "---------------------------------------");
	xyio::xyprintf(0, 1, "-- Programowanie Systemowe - Projekt --");
	xyio::xyprintf(0, 2, "---------------------------------------");
	xyio::xyprintf(0, 3, "  >> Network Warships - Main Menu      ");
	xyio::xyprintf(0, 4, "---------------------------------------");
	xyio::xyprintf(0, 5, "  >> 1 - Create new game (server)      ");
	xyio::xyprintf(0, 6, "  >> 2 - Join to game (client)         ");
	xyio::xyprintf(0, 7, "  >> quit - Exit program               ");
	xyio::xyprintf(0, 8, "---------------------------------------");
	xyio::xyprintf(0, 9, "  >> ");

	char input[8] = {};
	int selectedOption = 0;
	int readBytes = scanf_s("%s", input, 7);

	if (strcmp(input, "quit") != 0) {
		selectedOption = atoi(input);
		selectMenuOption(selectedOption);
	} else {
		ExitProcess(0);
	}
}

void Common::drawModeSelector() {
	xyio::xyprintf(0, 0, "------------------------------");
	xyio::xyprintf(0, 1, "  >> Game mode selector       ");
	xyio::xyprintf(0, 2, "------------------------------");
	xyio::xyprintf(0, 3, "  >> 1 - Generate random ships");
	xyio::xyprintf(0, 4, "  >> 2 - Set ships manually   ");
	xyio::xyprintf(0, 5, "------------------------------");
	xyio::xyprintf(0, 6, "  >> ");

	char input[8] = {};
	int selectedMode = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedMode = atoi(input);
	selectGameMode(selectedMode);
}

void Common::selectGameMode(int mode) {
	switch (mode) {
		case 1: {
			xyio::clear();
			drawModeSelector();

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