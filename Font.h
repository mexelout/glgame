#pragma once
#include <gl/freeglut/freeglut.h>

class GLFONT {
	GLFONT();
	~GLFONT();
	HFONT Hfont;
	HDC Hdc;
public:
	static void init();
	static void drawString(int x,int y,wchar_t *format, ...);
	static void release();
};

