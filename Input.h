#pragma once

#include <vector>
#include "Common.h"

class Input {
private:
	Input(void);
	~Input(void);
	static VECTOR2 mouse_point;
	static VECTOR2 drag_point;
	static int wheel;
	static std::vector<unsigned int> key_element;
	static std::vector<boolean> key_press;
	static std::vector<boolean> key_trigger;
	static std::vector<boolean> key_release;
	static void keyboard(unsigned char key, int x, int y);
	static void keyboardUp(unsigned char key, int x, int y);
	static void special(int key, int x, int y);
	static void specialUp(int key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void drag(int x, int y);
	static void passive(int x, int y);
	static void mouseWheel(int wheel_number, int direction, int x, int y);
public:
	union MOUSESTATE{
		boolean flgs;
		struct{
			boolean _left:1;
			boolean _middle:1;
			boolean _right:1;
		};
	};
	enum STATE{
		STATE_PRESS = 0,
		STATE_TRIGGER,
		STATE_RELEASE,
	};
	static void init();
	static void update();
	static void release();
	static const boolean getKeyState(const unsigned int key, const STATE state);
	static const MOUSESTATE getMouseState(const STATE state);
	static const VECTOR2* getMousePoint(void);
	static const VECTOR2* getDragPoint(void);
	static const int getWheel(void);
private:
	static MOUSESTATE mouse_press;
	static MOUSESTATE mouse_trigger;
	static MOUSESTATE mouse_release;
};

