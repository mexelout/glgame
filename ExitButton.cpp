
#include <gl/freeglut/freeglut.h>
#include "ExitButton.h"

ExitButton::ExitButton() {
}
ExitButton::~ExitButton() {
}
ExitButton* ExitButton::init() {
	base::init();
	mouseUp = new ExitButtonUp();
	title = "exit";
	pos.set(-200+size.width/2+15, 150-size.height/2-15);
	return this;
}
void ExitButton::update() {
	if(fade_flag) {
		alpha += 0.1f;
		if(alpha > 1) {
			alpha = 1;
		}
	} else {
		alpha -= 0.1f;
		if(alpha < 0) {
			alpha = 0;
		}
	}
	base::update();
}
void ExitButton::draw() {
	base::draw();
}
void ExitButton::release() {
	base::release();
}
void ExitButton::fadeIn() {
	fade_flag = true;
}
void ExitButton::fadeOut() {
	fade_flag = false;
}
