#include "xyio.h"

void xyio::setcursor(int x, int y) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD punkt = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(ekran, punkt);
}

void xyio::getcursor(int* x, int* y) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);

	*x = bufor.dwCursorPosition.X;
	*y = bufor.dwCursorPosition.Y;
}

void xyio::getrange(int* maxx, int* maxy) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);

	*maxx = bufor.dwMaximumWindowSize.X;
	*maxy = bufor.dwMaximumWindowSize.Y;
}

void xyio::getscreen(int* xorg, int* yorg, int* xend, int* yend) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	GetConsoleScreenBufferInfo(ekran, &bufor);

	*xorg = bufor.srWindow.Left;
	*yorg = bufor.srWindow.Top;
	*xend = bufor.srWindow.Right;
	*yend = bufor.srWindow.Bottom;
}

int xyio::xyscanf(int x, int y, const char* format, ...) {
	HANDLE klawiatura = GetStdHandle(STD_INPUT_HANDLE);
	char tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list args;
	int res;

	va_start(args, format);
	setcursor(x, y);
	sukces = ReadConsole(klawiatura, tekst, 150, &znaki, NULL);

	if (!sukces) res = EOF;
	else {
		while (znaki > 0 && (tekst[znaki - 1] == '\n' || tekst[znaki - 1] == '\r')) znaki--;
		tekst[znaki] = '\0';
		res = vsscanf(tekst, format, args);
	}

	va_end(args);
	return res;
}

int xyio::xyprintf(int x, int y, const char* format, ...) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	char tekst[150];
	DWORD znaki;
	BOOL sukces;
	va_list args;
	int res;

	va_start(args, format);
	res = vsprintf(tekst, format, args);

	if (res >= 0) {
		znaki = (DWORD)res;
		setcursor(x, y);
		sukces = WriteConsole(ekran, tekst, znaki, NULL, NULL);
		if (!sukces) res = EOF;
	}

	va_end(args);
	return res;
}

void xyio::clear(void) {
	HANDLE ekran = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufor;
	COORD poczatek = { 0,0 };
	DWORD znaki;
	GetConsoleScreenBufferInfo(ekran, &bufor);
	FillConsoleOutputCharacter(ekran, ' ', bufor.dwSize.X * bufor.dwSize.Y, poczatek, &znaki);
	SetConsoleCursorPosition(ekran, poczatek);
}