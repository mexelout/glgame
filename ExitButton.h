#pragma once

#include "Button.h"

class ExitButtonUp : public Command {
public:
	void execute() {
		Object::close();
	}
};

class ExitButton : public Button {
typedef Button base;
public:
	ExitButton();
	~ExitButton();
	ExitButton* init();
	void update();
	void draw();
	void release();
	void fadeIn();
	void fadeOut();
private:
	bool fade_flag; // true : in false : out
};

