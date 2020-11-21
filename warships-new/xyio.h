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
	private:
		static WORD currentColor;

	public:
		static WORD defaultColor;

		static void setcursor(int x, int y);
		static void getcursor(int* x, int* y);

		static void getrange(int* maxx, int* maxy);
		static void getscreen(int* xorg, int* yorg, int* xend, int* yend);

		static int xyscanf(int x, int y, const char* format, ...);
		static int xyprintf(int x, int y, const char* format, ...);

		static void setColor(WORD newColor);
		static void resetColor();

		static void clear(void);
};

#ifdef __cplusplus
}
#endif