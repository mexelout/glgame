#include "Color.h"

COLOR_TRUE::COLOR_TRUE() {
	r = g = b = 1;
}

COLOR_TRUE::COLOR_TRUE(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

COLOR_FULL::COLOR_FULL() : COLOR_TRUE() {
	a = 1;
}

COLOR_FULL::COLOR_FULL(float r, float g, float b, float a) : COLOR_TRUE(r, g, b){
	this->a = a;
}

COLOR_FULL::COLOR_FULL(COLOR_TRUE color, float a) : COLOR_TRUE(color.r, color.g, color.b) {
	this->a = a;
}

float* ExtractTrueColor(float* pArray, COLOR_TRUE* color) {
	pArray[0] = color->r;
	pArray[1] = color->g;
	pArray[2] = color->b;
	return pArray;
}
float* ExtractFullColor(float* pArray, COLOR_FULL* color) {
	pArray[0] = color->r;
	pArray[1] = color->g;
	pArray[2] = color->b;
	pArray[3] = color->a;
	return pArray;
}
