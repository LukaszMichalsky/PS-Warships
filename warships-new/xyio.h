#pragma once
#pragma warning(disable:4244)
#pragma warning(disable:4996 4005)
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#ifdef UNICODE
# undef UNICODE
# define _MBCS
#endif

#ifndef __cplusplus
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#else
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
using namespace std;
#endif
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

class xyio {
	public:
		static void setcursor(int x, int y); // Ustaw kursor w zadanym miejscu
		static void getcursor(int* x, int* y); // Pobierz współrzędne kursora

		static void getrange(int* maxx, int* maxy); // Pobierz zakres współrzędnych (wielkość dostępnego bufora konsoli)
		static void getscreen(int* xorg, int* yorg, int* xend, int* yend);

		static int xyscanf(int x, int y, const char* format, ...); // Wczytaj tekst z zadanej pozycji
		static int xyprintf(int x, int y, const char* format, ...); // Wyświetl tekst w zadanej pozycji

		static void clear(void); // Wyczyść ekran (bufor konsoli)
};

#ifdef __cplusplus
}
#endif