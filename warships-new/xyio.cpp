#include "xyio.h"

void xyio::setcursor(int x, int y) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(screen, point);
}

void xyio::getcursor(int* x, int* y) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	GetConsoleScreenBufferInfo(screen, &buffer);

	*x = buffer.dwCursorPosition.X;
	*y = buffer.dwCursorPosition.Y;
}

void xyio::getrange(int* maxx, int* maxy) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	GetConsoleScreenBufferInfo(screen, &buffer);

	*maxx = buffer.dwMaximumWindowSize.X;
	*maxy = buffer.dwMaximumWindowSize.Y;
}

void xyio::getscreen(int* xorg, int* yorg, int* xend, int* yend) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	GetConsoleScreenBufferInfo(screen, &buffer);

	*xorg = buffer.srWindow.Left;
	*yorg = buffer.srWindow.Top;
	*xend = buffer.srWindow.Right;
	*yend = buffer.srWindow.Bottom;
}

int xyio::xyscanf(int x, int y, const char* format, ...) {
	HANDLE keyboard = GetStdHandle(STD_INPUT_HANDLE);
	char text[150];
	DWORD count;
	BOOL success;
	va_list args;
	int res;

	va_start(args, format);
	setcursor(x, y);
	success = ReadConsole(keyboard, text, 150, &count, NULL);

	if (!success) res = EOF;
	else {
		while (count > 0 && (text[count - 1] == '\n' || text[count - 1] == '\r')) count--;
		text[count] = '\0';
		res = vsscanf(text, format, args);
	}

	va_end(args);
	return res;
}

int xyio::xyprintf(int x, int y, const char* format, ...) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	char text[150];
	DWORD count;
	BOOL success;
	va_list args;
	int res;

	va_start(args, format);
	res = vsprintf(text, format, args);

	if (res >= 0) {
		count = (DWORD)res;
		setcursor(x, y);
		success = WriteConsole(screen, text, count, NULL, NULL);
		if (!success) res = EOF;
	}

	va_end(args);
	return res;
}

void xyio::clear(void) {
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffer;
	COORD start = { 0,0 };
	DWORD count;
	GetConsoleScreenBufferInfo(screen, &buffer);
	FillConsoleOutputCharacter(screen, ' ', buffer.dwSize.X * buffer.dwSize.Y, start, &count);
	SetConsoleCursorPosition(screen, start);
}