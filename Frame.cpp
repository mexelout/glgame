#include <gl/freeglut/freeglut.h>
#include "Common.h"
#include "Vector.h"
#include "Frame.h"
#include "Input.h"
#include "Config.h"
#include "Graphics.h"
#include "ExitButton.h"

Frame::Frame() : Object2D("frame") {
	size.set(400, 300);
}

Frame::~Frame() {
}

Frame* Frame::init() {
	position.set(-300, 125);
	childs.push_back((new ExitButton())->init());
	return this;
}

void Frame::update() {
	ExitButton* exit_button = (ExitButton*)(childs[0]);
	exit_button->setOffset(&position);
	for each(Button* child in childs) {
		child->update();
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
		if(state.y > size.height-1) {
			ExitButton* exit_button = (ExitButton*)(childs[0]);
			exit_button->fadeIn();
		}
	} else {
		ExitButton* exit_button = (ExitButton*)(childs[0]);
		exit_button->fadeOut();
		if(exit_button->getAlpha() == 0) {
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
	}

	glColor3f(1, 1, 1);
	VECTOR2 dp(position.x+state.x, position.y);
	SIZE2D ds(size.width, state.y);
	Graphics::getInst()->drawRect(dp, ds);
	glColor3f(0, 0, 0);
	Graphics::getInst()->drawRect(dp, ds+SIZE2D(2, 2), true);

	for each(Button* child in childs) {
		child->draw();
	}
	glLoadIdentity();
}

void Frame::release() {
	for each(Object2D* child in childs) {
		child->release();
	}
	childs.clear();
	Object2D::release();
}
