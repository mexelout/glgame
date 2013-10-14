#include <gl/freeglut/freeglut.h>
#include "Common.h"
#include "Vector.h"
#include "Frame.h"
#include "Input.h"
#include "Config.h"
#include "Graphics.h"

Frame::Frame() : Object2D("frame") {
	size.set(400, 400);
}

Frame::~Frame() {
}

Frame* Frame::init() {
	return this;
}

void Frame::update() {

	if(Input::getKeyState(GLUT_KEY_LEFT, Input::STATE_PRESS)) {
		position.x--;
	}
	if(Input::getKeyState(GLUT_KEY_RIGHT, Input::STATE_PRESS)) {
		position.x++;
	}
	if(Input::getKeyState(GLUT_KEY_UP, Input::STATE_PRESS)) {
		position.y++;
	}
	if(Input::getKeyState(GLUT_KEY_DOWN, Input::STATE_PRESS)) {
		position.y--;
	}

}

void Frame::draw() {
	static VECTOR2 state(512, 1);
	static boolean isOpen = true;

	if(Input::getKeyState(VK_ESCAPE, Input::STATE_TRIGGER)) {
		isOpen = !isOpen;
	}

	if(isOpen) {
		if(state.x > 0) {
			state.x *= 0.8f;
		}
		if(state.x < 1) {
			state.x = 0;
			float add = (size.height - state.y) * 0.2f;
			state.y += add;
		}
		if(state.y > size.height) {
			state.y = size.height;
		}
	} else {
		if(state.y > 0) {
			state.y *= 0.8f;
		}
		const POINT* ws = Config::GetWindowSize();
		if(state.y < 1) {
			state.y = 0;
			float add = ((ws->x + size.width) - state.x) * 0.1f;
			state.x += add;
		}
		if(state.x > (ws->x + size.width)) {
			state.x = (ws->x + size.width);
		}
	}

	glColor3f(1, 1, 1);
	VECTOR2 dp(position.x+state.x, position.y);
	SIZE2D ds(size.width, state.y);
	Graphics::getInst()->drawRect(dp, ds);
	glColor3f(0, 0, 0);
	Graphics::getInst()->drawRect(dp, ds+SIZE2D(2, 2), true);

}

void Frame::release() {

	Object2D::release();
}
