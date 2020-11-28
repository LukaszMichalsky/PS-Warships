#include "client.h"
#include "common.h"

void Client::drawHostInput() {
	xyio::xyprintf(0, 0, "------------------------------------------");
	xyio::xyprintf(0, 1, "  >> Initalize Client - Select Host       ");
	xyio::xyprintf(0, 2, "------------------------------------------");
	xyio::xyprintf(0, 3, "  >> Enter host name/address              ");
	xyio::xyprintf(0, 4, "  >> Enter 'quit' to leave to main menu   ");
	xyio::xyprintf(0, 5, "------------------------------------------");
	xyio::xyprintf(0, 6, "  >> ");

	char input[64] = {};
	int readBytes = scanf_s("%s", input, 63);

	strcpy_s(NetworkConfiguration::host, 64, input);
	xyio::clear();

	if (strcmp(input, "quit") != 0) {
		drawPortInput();
	} else {
		NetworkConfiguration::myRole = Role::ROLE_DEFAULT;
		Common::drawMainMenu();
	}
}

void Client::drawPortInput() {
	xyio::xyprintf(0, 0, "------------------------------------------");
	xyio::xyprintf(0, 1, "  >> Initalize Client - Select Port       ");
	xyio::xyprintf(0, 2, "------------------------------------------");
	xyio::xyprintf(0, 3, "  >> Enter a port (between 1024 and 65535)");
	xyio::xyprintf(0, 4, "------------------------------------------");
	xyio::xyprintf(0, 5, "  >> ");

	char input[8] = {};
	int selectedPort = 0;
	int readBytes = scanf_s("%s", input, 7);

	selectedPort = atoi(input);

	if (selectedPort >= 1024 && selectedPort <= 65535) {
		strcpy_s(NetworkConfiguration::port, 8, input);
		xyio::clear();
		initializeWinsock();
	}
	else {
		xyio::xyprintf(5, 5, "Invalid port, try again...");
		Sleep(3000);

		xyio::clear();
		drawPortInput();
	}
}

void Client::initializeClient() {
	drawHostInput();
}

void Client::initializeWinsock() {
	xyio::xyprintf(0, 0, "-----------------------------------------------");
	xyio::xyprintf(0, 1, "  >> Client initialization                     ");
	xyio::xyprintf(0, 2, "-----------------------------------------------");

	int initCode = WSAStartup(MAKEWORD(2, 2), NetworkConfiguration::wsaData);

	if (initCode != 0) {
		xyio::xyprintf(0, 3, "  >> WSA initialization failed, try again (error ID %d)", initCode);
		Sleep(3000);

		xyio::clear();
		drawHostInput();
	}
	else {
		xyio::xyprintf(0, 3, "  >> WSA initialized successfully");
	}

	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int resultCode = getaddrinfo(NetworkConfiguration::host, NetworkConfiguration::port, &hints, &result);

	if (resultCode != 0) {
		xyio::xyprintf(0, 4, "  >> WSA address resolving failed (error ID %d)", resultCode);
		WSACleanup();

		Sleep(3000);
		xyio::clear();
		drawHostInput();
	}
	else {
		xyio::xyprintf(0, 4, "  >> WSA address resolving succeeded");
	}

	xyio::xyprintf(0, 5, "  >> Trying to connect to the server (%s:%s)...", NetworkConfiguration::host, NetworkConfiguration::port);
	Sleep(2000);

	for (ptr = result; ptr != NULL; ptr = ptr -> ai_next) {
		NetworkConfiguration::clientSocket = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);

		if (NetworkConfiguration::clientSocket == INVALID_SOCKET) {
			xyio::xyprintf(0, 6, "    >> WSA failed (error ID %d)", WSAGetLastError());
			WSACleanup();

			Sleep(3000);
			xyio::clear();
			drawHostInput();
		}

		int connectionCode = connect(NetworkConfiguration::clientSocket, ptr -> ai_addr, (int) ptr -> ai_addrlen);

		if (connectionCode == SOCKET_ERROR) {
			closesocket(NetworkConfiguration::clientSocket);
			NetworkConfiguration::clientSocket = INVALID_SOCKET;
			continue;
		}
	}

	if (NetworkConfiguration::clientSocket == INVALID_SOCKET) {
		xyio::xyprintf(0, 6, "    >> Unable to connect to the server");
		Sleep(3000);

		xyio::clear();
		freeaddrinfo(result);
		drawHostInput();
	} else {
		xyio::xyprintf(0, 6, "    >> Connected!");
		freeaddrinfo(result);
	}

	Sleep(3000);
	xyio::clear();
	Common::drawModeSelector();
}