#pragma once

#include "netconf.h"
#include "xyio.h"

class Server {
	public:
		static void initializeServer();

	private:
		static void drawPortInput();
		static void initializeWinsock();
};