#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct COLOR_TRUE {
	COLOR_TRUE();
	COLOR_TRUE(float r, float g, float b);
	float r;
	float g;
	float b;
}COLOR_TRUE;

typedef struct COLOR_FULL : public COLOR_TRUE {
	COLOR_FULL();
	COLOR_FULL(float r, float g, float b, float a);
	COLOR_FULL(COLOR_TRUE color, float a = 1);
	float a;
}COLOR_FULL;

const COLOR_TRUE colorWhite = COLOR_TRUE(1, 1, 1);

float* ExtractTrueColor(float* pArray, COLOR_TRUE* color);
float* ExtractFullColor(float* pArray, COLOR_FULL* color);

#endif // _COLOR_H_