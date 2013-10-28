#pragma once
#include <gl/freeglut/freeglut.h>

class Font {
	Font();
	~Font();
	HFONT Hfont;
	HDC Hdc;
public:
	static void init();
	static void drawString(int x,int y, const char* format, ...);
	static void release();
};

