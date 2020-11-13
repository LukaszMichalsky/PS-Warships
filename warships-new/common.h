#pragma once

#include "client.h"
#include "server.h"
#include "xyio.h"

class Common {
	public:
		static void drawMainMenu();
		static void drawModeSelector();

	private:
		static void selectGameMode(int mode);
		static void selectMenuOption(int option);
};