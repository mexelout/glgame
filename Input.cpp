#include <gl/freeglut/freeglut.h>
#include "Input.h"
#include "Common.h"
#include "Config.h"

Input::MOUSESTATE Input::mouse_press;
Input::MOUSESTATE Input::mouse_trigger;
Input::MOUSESTATE Input::mouse_release;
VECTOR2 Input::mouse_point;
VECTOR2 Input::drag_point;
int Input::wheel;
std::vector<unsigned int> Input::key_element;
std::vector<boolean> Input::key_press;
std::vector<boolean> Input::key_trigger;
std::vector<boolean> Input::key_release;

Input::Input(void) {
}

Input::~Input(void) {
}

void Input::init() {
	key_element.push_back(VK_SPACE);
	key_element.push_back(VK_ESCAPE);
	key_element.push_back(GLUT_KEY_LEFT);
	key_element.push_back(GLUT_KEY_RIGHT);
	key_element.push_back(GLUT_KEY_UP);
	key_element.push_back(GLUT_KEY_DOWN);
	key_element.push_back(GLUT_KEY_ALT_L);
	key_element.push_back(GLUT_KEY_F4);

	key_press.resize(key_element.size());
	key_trigger.resize(key_element.size());
	key_release.resize(key_element.size());

	mouse_press.flgs = 0;
	mouse_trigger.flgs = 0;
	mouse_release.flgs = 0;

	mouse_point.Zero();
	drag_point.Zero();

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(Input::mouse);
	glutMotionFunc(Input::drag);
	glutPassiveMotionFunc(Input::passive);
	glutMouseWheelFunc(Input::mouseWheel);//ホイールコールバック
}

void Input::update() {
	mouse_trigger.flgs = 0;
	mouse_release.flgs = 0;
	for(unsigned int i = 0; i < key_element.size(); i++) {
		key_trigger[i] = false;
		key_release[i] = false;
	}
	drag_point.x = drag_point.y = 0;
	wheel = 0;
}

void Input::release() {
}

const boolean Input::getKeyState(const unsigned int key, const Input::STATE state) {
	unsigned int i;
	boolean r = false;
	for(i = 0; i < key_element.size(); i++) {
		if(key == key_element[i]) {
			switch(state) {
				case STATE_PRESS:
					r = key_press[i];
					break;
				case STATE_TRIGGER:
					r = key_trigger[i];
					break;
				case STATE_RELEASE:
					r = key_release[i];
					break;
			}
		}
	}
	return r;
}

const Input::MOUSESTATE Input::getMouseState(const Input::STATE state) {
	switch(state) {
		case STATE_PRESS:
			return mouse_press;
		case STATE_TRIGGER:
			return mouse_trigger;
		case STATE_RELEASE:
			return mouse_release;
		default:
			return mouse_press;
	}
}

void Input::keyboard(unsigned char key, int x, int y) {
	for(unsigned int i = 0; i < key_element.size(); i++) {
		if(key == key_element[i]) {
			if(key_press[i] == false) key_trigger[i] = true;
			key_press[i] = true;
		}
	}
}

void Input::keyboardUp(unsigned char key, int x, int y) {
	for(unsigned int i = 0; i < key_element.size(); i++) {
		if(key == key_element[i]) {
			key_press[i] = false;
			key_release[i] = true;
		}
	}
//	if(key == 27) glutExit();//ESCキーで終了
}

void Input::special(int key, int x, int y) {
	for(unsigned int i = 0; i < key_element.size(); i++) {
		if(key == key_element[i]) {
			if(key_press[i] == false) key_trigger[i] = true;
			key_press[i] = true;
		}
	}
}

void Input::specialUp(int key, int x, int y) {
	for(unsigned int i = 0; i < key_element.size(); i++) {
		if(key == key_element[i]) {
			key_press[i] = false;
			key_release[i] = true;
		}
	}
//	if(key == 27) glutExit();//ESCキーで終了
}

//マウス(クリック)
void Input::mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:
			mouse_press._left = !state;
			mouse_trigger._left = !state;
			mouse_release._left = state;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_press._right = !state;
			mouse_trigger._right = !state;
			mouse_release._right = state;
			break;
		case GLUT_MIDDLE_BUTTON:
			mouse_press._middle = !state;
			mouse_trigger._middle = !state;
			mouse_release._middle = state;
			break;
	}
}

//ドラッグ
void Input::drag(int x, int y) {
	const POINT* ws = Config::GetWindowSize();
	x -= ws->x / 2;
	y *= -1;
	y += ws->y / 2;
	drag_point.x = mouse_point.x - x;
	drag_point.y = mouse_point.y - y;
	mouse_point.x = (float)x;
	mouse_point.y = (float)y;
}

//パッシブ
void Input::passive(int x, int y) {
	const POINT* ws = Config::GetWindowSize();
	x -= ws->x / 2;
	y *= -1;
	y += ws->y / 2;
	mouse_point.x = (float)x;
	mouse_point.y = (float)y;
}

//ホイール
void Input::mouseWheel(int wheel_number, int direction, int x, int y) {
	if(direction == 1) {
		wheel++;
	} else {
		wheel--;
	}
}

int const __cdecl Input::getWheel(void) {
	return wheel;
}

const VECTOR2* Input::getMousePoint(void) {
	return &mouse_point;
}

VECTOR2 const * __cdecl Input::getDragPoint(void) {
	return &drag_point;
}