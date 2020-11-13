#include "netconf.h"

WSADATA* NetworkConfiguration::wsaData = new WSADATA;
CHAR NetworkConfiguration::host[64] = {};
CHAR NetworkConfiguration::port[8] = {};

SOCKET NetworkConfiguration::listeningSocket = INVALID_SOCKET;
SOCKET NetworkConfiguration::clientSocket = INVALID_SOCKET;
SOCKET NetworkConfiguration::connectionSocket = INVALID_SOCKET;

int NetworkConfiguration::bufferLength = BUFFER_LENGTH;
char NetworkConfiguration::receiveBuffer[BUFFER_LENGTH] = {};
char NetworkConfiguration::sendBuffer[BUFFER_LENGTH] = {};