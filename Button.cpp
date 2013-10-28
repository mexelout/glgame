#include <gl/freeglut/freeglut.h>
#include "Button.h"
#include "Graphics.h"
#include "Common.h"
#include "Font.h"

Button::Button() : base("button") {
	title = "button";
	alpha = 1.0f;
}
Button::~Button() {
}
Button* Button::init() {
	base::init();
	return this;
}
void Button::update() {
	if(alpha > 0) {
		pos += offset;
		base::update();
		pos -= offset;
	}
}
void Button::draw() {
	if(alpha > 0) {
		if(selected) {
			glColor4f(0.6f, 0.6f, 0.6f, alpha);
		} else {
			glColor4f(1, 1, 1, alpha);
		}
		pos += offset;
		Graphics::getInst()->drawRect(pos, size);
		glColor4f(0, 0, 0, alpha);
		Graphics::getInst()->drawRect(pos, size+SIZE2D(2, 2), true);
		Font::drawString((int)pos.x-title.length()*8, (int)pos.y-8, title.c_str());
		pos -= offset;
	}
}
void Button::release() {
	base::release();
}
void Button::setAlpha(float alpha) {
	this->alpha = alpha;
}
float Button::getAlpha() {
	return alpha;
}
void Button::setTitle(std::string title) {
	this->title = title;
}
std::string Button::getTitle() {
	return title;
}
void Button::setOffset(const VECTOR2* offset) {
	this->offset = *offset;
}
const VECTOR2* Button::getOffset() {
	return &offset;
}
