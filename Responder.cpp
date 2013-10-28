#include <gl/freeglut/freeglut.h>
#include "Responder.h"
#include "Graphics.h"
#include "Input.h"
#include "Common.h"

Responder::Responder(std::string tag) : base(tag) {
	is_in = false;
	selected = false;
	mouseIn = null;
	mouseDown = null;
	mouseUp = null;
	mouseOut = null;
}
Responder::~Responder() {
}
Responder* Responder::init() {
	base::init();
	size.set(100, 50);
	return this;
}
void Responder::update() {
	const VECTOR2& mp = *Input::getMousePoint();
	const SIZE2D hs = size / 2;
	// mouse in
	if(boundBox(VECTOR2(pos.x - hs.width, pos.y + hs.height), VECTOR2(pos.x + hs.width, pos.y - hs.height), mp)) {
		const Input::MOUSESTATE ms_p = Input::getMouseState(Input::STATE_PRESS);
		const Input::MOUSESTATE ms_t = Input::getMouseState(Input::STATE_TRIGGER);
		const Input::MOUSESTATE ms_r = Input::getMouseState(Input::STATE_RELEASE);
		if(!is_in) {
			is_in = true;
			if(mouseIn) mouseIn->execute();
		}
		if(ms_p._left) {
			selected = true;
		}
		if(ms_t._left) {
			if(mouseDown) mouseDown->execute();
		}
		if(ms_r._left) {
			if(mouseUp) mouseUp->execute();
		}
	} else {
		if(is_in) {
			is_in = false;
			selected = false;
			if(mouseOut) mouseOut->execute();
		}
	}
}
void Responder::draw() {
}
void Responder::release() {
	SAFE_RELEASE(mouseIn);
	SAFE_RELEASE(mouseDown);
	SAFE_RELEASE(mouseUp);
	SAFE_RELEASE(mouseOut);
	base::release();
}
