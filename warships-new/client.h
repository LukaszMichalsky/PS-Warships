#pragma once

#include "netconf.h"
#include "xyio.h"

class Client {
	public:
		static void initializeClient();

	private:
		static void drawHostInput();
		static void drawPortInput();
		static void initializeWinsock();
};