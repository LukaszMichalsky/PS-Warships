#pragma once

#define BUFFER_LENGTH 64
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")

#include "windows.h"
#include "winsock2.h"

#include <ws2tcpip.h>

class NetworkConfiguration {
	public:
		static CHAR host[64];
		static CHAR port[8];
		static WSADATA* wsaData;

		static SOCKET listeningSocket;
		static SOCKET clientSocket;
		static SOCKET connectionSocket;

		static int bufferLength;
		static char receiveBuffer[];
		static char sendBuffer[];
};