#include <gl/freeglut/freeglut.h>
#include "Responder.h"
#include "Graphics.h"
#include "Input.h"
#include "Common.h"

Responder::Responder(std::string tag) : base(tag) {
	isIn = false;
}
Responder::~Responder() {
}
Responder* Responder::init() {
	size.set(100, 50);
	return this;
}
void Responder::update() {
	const VECTOR2& mp = *Input::getMousePoint();
	const Input::MOUSESTATE ms_t = Input::getMouseState(Input::STATE_TRIGGER);
	const Input::MOUSESTATE ms_r = Input::getMouseState(Input::STATE_RELEASE);
	const SIZE2D hs = size / 2;
	// mouse in
	if(boundBox(VECTOR2(pos.x - hs.width, pos.y + hs.height), VECTOR2(pos.x + hs.width, pos.y - hs.height), mp)) {
		if(!isIn) {
			isIn = true;
			mouseIn();
		}
		if(ms_t._left) mouseDown();
		if(ms_r._left) mouseUp();
	} else {
		if(isIn) {
			isIn = false;
			mouseOut();
		}
	}
}
void Responder::draw() {
	glColor3f(1, 1, 1);
	Graphics::getInst()->drawRect(pos, size);
	glColor3f(0, 0, 0);
	Graphics::getInst()->drawRect(pos, size+SIZE2D(2, 2), true);
}
void Responder::release() {
	base::release();
}
void Responder::mouseDown() {
}
void Responder::mouseUp() {
}
void Responder::mouseIn() {
}
void Responder::mouseOut() {
}
