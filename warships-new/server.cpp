#include "common.h"
#include "server.h"

void Server::drawPortInput() {
	xyio::xyprintf(0, 0, "|------------------------------------------|");
	xyio::xyprintf(0, 1, "|  >> Initalize Server - Select Port       |");
	xyio::xyprintf(0, 2, "|------------------------------------------|");
	xyio::xyprintf(0, 3, "|  >> Enter a port (between 1024 and 65535)|");
	xyio::xyprintf(0, 4, "|  >> Enter 'quit' to leave to main menu   |");
	xyio::xyprintf(0, 5, "|------------------------------------------|");
	xyio::xyprintf(0, 6, "|  >> ");

	char input[8] = {};
	int selectedPort = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedPort = atoi(input);

	if (strcmp(input, "quit") != 0) {
		if (selectedPort >= 1024 && selectedPort <= 65535) {
			strcpy_s(NetworkConfiguration::port, 8, input);
			xyio::clear();
			initializeWinsock();
		} else {
			xyio::xyprintf(5, 6, "Invalid port, try again...");
			Sleep(3000);

			xyio::clear();
			drawPortInput();
		}
	} else {
		xyio::clear();
		Common::drawMainMenu();
	}
}

void Server::initializeServer() {
	drawPortInput();
}

void Server::initializeWinsock() {
	xyio::xyprintf(0, 0, "|-----------------------------------------------|");
	xyio::xyprintf(0, 1, "|  >> Server initialization                     |");
	xyio::xyprintf(0, 2, "|-----------------------------------------------|");

	int initCode = WSAStartup(MAKEWORD(2, 2), NetworkConfiguration::wsaData);

	if (initCode != 0) {
		xyio::xyprintf(0, 3, "  >> WSA initialization failed, try again (error ID %d)", initCode);
		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 3, "  >> WSA initialized successfully");
	}

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	int resultCode = getaddrinfo(NULL, NetworkConfiguration::port, &hints, &result);

	if (resultCode != 0) {
		xyio::xyprintf(0, 4, "  >> WSA address resolving failed (error ID %d)", resultCode);
		WSACleanup();

		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 4, "  >> WSA address resolving succeeded");
	}

	xyio::xyprintf(0, 5, "  >> Creating listener socket...");
	NetworkConfiguration::listeningSocket = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol);

	if (NetworkConfiguration::listeningSocket == INVALID_SOCKET) {
		xyio::xyprintf(0, 6, "    >> Failed (error ID &d)", WSAGetLastError());
		WSACleanup();

		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 6, "    >> Success");
	}

	xyio::xyprintf(0, 7, "  >> Binding listener socket...");
	int bindingCode = bind(NetworkConfiguration::listeningSocket, result -> ai_addr, (int) result -> ai_addrlen);

	if (bindingCode == SOCKET_ERROR) {
		xyio::xyprintf(0, 8, "    >> Failed (error ID &d)", WSAGetLastError());
		WSACleanup();

		freeaddrinfo(result);
		closesocket(NetworkConfiguration::listeningSocket);

		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 8, "    >> Success");
	}

	xyio::xyprintf(0, 9, "  >> Preparing TCP socket to listen");
	int listeningCode = listen(NetworkConfiguration::listeningSocket, SOMAXCONN);

	if (listeningCode == SOCKET_ERROR) { // Setting up the socket for listening
		xyio::xyprintf(0, 10, "    >> Failed (error ID %d)", WSAGetLastError());
		WSACleanup();

		freeaddrinfo(result);
		closesocket(NetworkConfiguration::listeningSocket);

		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 10, "    >> Success! Waiting for a player to join...");
	}

	// Waiting for a player to join this server
	NetworkConfiguration::clientSocket = accept(NetworkConfiguration::listeningSocket, NULL, NULL);

	if (NetworkConfiguration::clientSocket == INVALID_SOCKET) {
		xyio::xyprintf(0, 11, "      >> Connection failed (error ID %d)", WSAGetLastError());
		WSACleanup();

		freeaddrinfo(result);
		closesocket(NetworkConfiguration::listeningSocket);

		Sleep(3000);
		drawPortInput();
	} else {
		xyio::xyprintf(0, 11, "      >> A player has joined! Hello!");
	}

	freeaddrinfo(result);
	closesocket(NetworkConfiguration::listeningSocket);
	Sleep(3000);

	xyio::clear();
	Common::drawModeSelector();
}