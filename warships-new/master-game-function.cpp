#include "common.h"

#include <set>
#include <string>

enum class Shoot : char {
	SHOOT_DROWNED,
	SHOOT_HIT,
	SHOOT_MISSED
};

int shootsTotal = 0;
int shootsHit = 0;
int shootsDrowned = 0;

void checkBoard(Board* playerBoard);
void checkShipsLeft(Board* playerBoard);
void closeConnection();

void drawOpponentBoard(Board* opponentBoard);
void getCoordinates(Board* playerBoard, int &outX, int &outY);

void waitForOpponent(Board* playerBoard);
void yourTurn(Board* playerBoard, Board* opponentBoard);

void Common::masterGameFunction(Board* playerBoard) {
	Board opponentBoard;

	checkBoard(playerBoard);
	checkShipsLeft(playerBoard);

	playerBoard -> drawBoard(1, 3);
	drawOpponentBoard(&opponentBoard);

	while (true) {
		try {
			if (NetworkConfiguration::myRole == Role::ROLE_SERVER) {
				yourTurn(playerBoard, &opponentBoard);
				waitForOpponent(playerBoard);
			} else if (NetworkConfiguration::myRole == Role::ROLE_CLIENT) {
				waitForOpponent(playerBoard);
				yourTurn(playerBoard, &opponentBoard);
			}
		} catch (...) {
			break;
		}
	}

	xyio::clear();
	restartGame();
}

void checkBoard(Board* playerBoard) {
	if (playerBoard == nullptr) {
		xyio::xyprintf(0, 0, "Error! Player board is null!");
		closeConnection();
		Sleep(1000);

		xyio::clear();
		Common::drawMainMenu();
	}
}

void checkShipsLeft(Board* playerBoard) {
	std::set<ShipGroup*> boardShipsTotal;
	std::set<ShipGroup*> boardShipsLeft;

	for (int x = 0; x < playerBoard -> getBoardSize(); x++) {
		for (int y = 0; y < playerBoard -> getBoardSize(); y++) {
			Ship* pointShip = playerBoard -> getShip(Point(x, y));

			if (pointShip != nullptr) {
				if (pointShip -> getShipState() == ShipState::STATE_NOT_HIT || pointShip -> getShipState() == ShipState::STATE_HIT) {
					boardShipsTotal.insert(pointShip -> getShipGroup());

					if (pointShip -> getShipState() == ShipState::STATE_NOT_HIT) {
						boardShipsLeft.insert(pointShip -> getShipGroup());
					}
				}
			}
		}
	}

	xyio::xyprintf(1, 1, "[Your ships] Total ships: %d | Ships left: %d ", boardShipsTotal.size(), boardShipsLeft.size());
}

void closeConnection() {
	shutdown(NetworkConfiguration::clientSocket, SD_BOTH);
	closesocket(NetworkConfiguration::clientSocket);
	WSACleanup();
}

void drawOpponentBoard(Board* opponentBoard) {
	opponentBoard -> drawBoard(50, 3);
	xyio::xyprintf(50, 1, "[Opponent ships] Shoots: %d | Hits: %d | Drowned ships: %d ", shootsTotal, shootsHit, shootsDrowned);
}

void getCoordinates(Board* playerBoard, int& outX, int& outY) { // Returns entered coordinates (as references) in range from 0 to 'board size' - 1 (e.g. from 0 to 9 in 10x10 board)
	char input[8] = {};
	int readBytes = scanf_s("%s", input, 7);
	int initX = -1, initY = -1;

	if (strlen(input) == 2) {
		int X = input[0] - 'a';
		int Y = input[1] - '0';

		if (X >= 0 && X <= playerBoard -> getBoardSize() - 1) {
			if (Y >= 0 && Y <= playerBoard -> getBoardSize() - 1) {
				initX = X;
				initY = Y;
			}
		}
	}

	outX = initX;
	outY = initY;
}

void waitForOpponent(Board* playerBoard) {
	xyio::xyprintf(1, playerBoard->getBoardSize() * 2 + 6, std::string(80, ' ').c_str());
	xyio::xyprintf(1, playerBoard->getBoardSize() * 2 + 6, "  >> Waiting for opponent's turn... ");

	int readCode = recv(NetworkConfiguration::clientSocket, NetworkConfiguration::receiveBuffer, NetworkConfiguration::bufferLength, NULL); // Wait for shoot coordinates

	if (readCode > 0) {
		bool wasHit = false;
		short shootX = (short) NetworkConfiguration::receiveBuffer[0];
		short shootY = (short) NetworkConfiguration::receiveBuffer[1];

		char bufferShoot[1];
		playerBoard -> shoot(wasHit, Point(shootX, shootY));

		if (wasHit == true) {
			if (playerBoard -> getShip(Point(shootX, shootY)) -> getShipGroup() -> getShipsLeft() == 0) {
				xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, std::string(80, ' ').c_str());
				xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> An opponent has DROWNED your ship! ");

				bufferShoot[0] = (char) Shoot::SHOOT_DROWNED;
			} else {
				xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, std::string(80, ' ').c_str());
				xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> An opponent has hit your ship! ");

				bufferShoot[0] = (char) Shoot::SHOOT_HIT;
			}
		} else {
			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, std::string(80, ' ').c_str());
			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Opponent missed... ");

			bufferShoot[0] = (char) Shoot::SHOOT_MISSED;
		}

		send(NetworkConfiguration::clientSocket, bufferShoot, NetworkConfiguration::bufferLength, NULL);
		checkShipsLeft(playerBoard);
		playerBoard -> drawBoard(1, 3);

		Sleep(1000);
	} else {
		closeConnection();
		ExitProcess(-1);
	}
}

void yourTurn(Board* playerBoard, Board* opponentBoard) {
	int shootX = 0, shootY = 0;
	bool wasHit = false;

	xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Your turn! Enter coordinate (e.g. a0, f9, h3, ...): ");
	getCoordinates(playerBoard, shootX, shootY);

	while (shootX == -1 || shootY == -1) {
		xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, std::string(80, ' ').c_str());
		xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Invalid coordinates, please try again... ");

		getCoordinates(playerBoard, shootX, shootY);
	}

	char bufferShoot[] = {shootX, shootY};
	send(NetworkConfiguration::clientSocket, bufferShoot, NetworkConfiguration::bufferLength, NULL); // Send shoot coordinate
	int readCode = recv(NetworkConfiguration::clientSocket, NetworkConfiguration::receiveBuffer, NetworkConfiguration::bufferLength, NULL); // Wait for shoot result

	if (readCode > 0) {
		char shootCode = NetworkConfiguration::receiveBuffer[0];
		xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, std::string(80, ' ').c_str());

		if (shootCode == (char) Shoot::SHOOT_DROWNED) {
			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Opponent's ship DROWNED!");
			shootsTotal++;
			shootsDrowned++;
			shootsHit++;

			ShipGroup::add(opponentBoard, Point(shootX, shootY));
			opponentBoard -> shoot(wasHit, Point(shootX, shootY));
		} else if (shootCode == (char) Shoot::SHOOT_HIT) {
			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Opponent's ship hit!");
			shootsTotal++;
			shootsHit++;

			ShipGroup::add(opponentBoard, Point(shootX, shootY));
			opponentBoard -> shoot(wasHit, Point(shootX, shootY));
		} else if (shootCode == (char) Shoot::SHOOT_MISSED) {
			shootsTotal++;

			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Missed...");
			opponentBoard -> shoot(wasHit, Point(shootX, shootY));
		} else {
			xyio::xyprintf(1, playerBoard -> getBoardSize() * 2 + 6, "  >> Unexpected error! Received shoot code: %d", (int) shootCode);
		}

		drawOpponentBoard(opponentBoard);
		Sleep(1000);
	} else {
		closeConnection();
		ExitProcess(-1);
	}
}