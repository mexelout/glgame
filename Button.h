#pragma once

#include <string>
#include "Responder.h"

class Button : public Responder {
typedef Responder base;
public:
	Button();
	~Button();
	Button* init();
	void update();
	void draw();
	void release();
	void setButtonImage();
	void setButtonSelectImage();
	void setButtonString(const char* str);
	void setAlpha(float alpha);
	float getAlpha();
	void setTitle(std::string title);
	std::string getTitle();
	void setOffset(const VECTOR2* offset);
	const VECTOR2* getOffset();
protected:
	float alpha;
	std::string title;
private:
	VECTOR2 offset;
};