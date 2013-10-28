#include <gl/freeglut/freeglut.h>
#include "Central.h"
#include "Config.h"
#include "Camera.h"
#include "Input.h"
#include "Scene.h"
#include "Font.h"

#define _DEBUG_AT_DISP_ 0

Central* Central::inst = null;

// object.cpp‚ª–³‚¢ˆ×‚±‚±‚Å’è‹`
bool Object::end = false;

Central::Central(void) : Object("central") {
	scene = null;
}

Central::~Central(void) {
}

Central* Central::getInst() {
	if(inst == null) inst = (new Central)->init();
	return inst;
}

Central* Central::init() {
	Font::init();
	scene = new Scene;

	return this;
}

void Central::update() {

	if(scene) scene->method();

	for each (std::vector<Object*> vec_obj in objects) {
		for each (Object* obj in vec_obj) {
			obj->update();
		}
	}
	cleanString();
}

void Central::draw() {

	Camera::Perspective pers;
	Camera* camera = findObject<Camera>("camera");
	if(camera) {
		const Camera::LockAtUp* lock_at_up = camera->getLockAtUp();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(pers.fovy, pers.aspect, pers.near, pers.far);
		gluLookAt(lock_at_up->eye.x, lock_at_up->eye.y, lock_at_up->eye.z, // lock
				  lock_at_up->at.x, lock_at_up->at.y, lock_at_up->at.z, // at
				  lock_at_up->up.x, lock_at_up->up.y, lock_at_up->up.z); // up
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if(_DEBUG_AT_DISP_) {
			glDisable(GL_LIGHTING);
			glTranslatef(lock_at_up->at.x, lock_at_up->at.y, lock_at_up->at.z);
			glBegin(GL_LINES);

			glColor3f(1, 0, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(-1, 0, 0);
			glColor3f(0, 1, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, -1, 0);
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 1);
			glVertex3f(0, 0, -1);

			glEnd();
			glLoadIdentity();
			glEnable(GL_LIGHTING);
		}
	}

	glEnable(GL_LIGHTING);
	for each (Object* obj in objects[0]) {
		obj->draw();
	}

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const POINT* ws = Config::GetWindowSize();
	gluOrtho2D(-ws->x/2, ws->x/2, -ws->y/2, ws->y/2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);

	for each (Object* obj in objects[1]) {
		obj->draw();
	}

	if(scene) scene->draw();

	glEnable(GL_DEPTH_TEST);

	if(end) {
		glutExit();
	}
}

void Central::release() {
	allSubObject();
	if(scene) {delete scene; scene = null;}

	Object::release();
	Font::release();

	inst = null;
}

void Central::addObject(Object* object) {
	objects[object->getDimension()].push_back(object);
}

void Central::allSubObject() {
	for each (std::vector<Object*> vec_obj in objects) {
		for each (Object* obj in vec_obj) {
			obj->release();
		}
		vec_obj.clear();
	}
}

template <class u>
u* Central::findObject(std::string tag) {
	for each (std::vector<Object*> vec_obj in objects) {
		for each (Object* obj in vec_obj) {
			if(obj->tagEqual(tag)) {
				return (u*)obj;
			}
		}
	}
	// ŠY“–ƒ^ƒO‚ÍŒ©‚Â‚©‚ç‚È‚©‚Á‚½
	return null;
}

void Central::subObject(Object* object) {
	for each (std::vector<Object*> vec_obj in objects) {
		for(std::vector<Object*>::iterator obj = vec_obj.begin(); obj != vec_obj.end(); obj++) {
			if((*obj) == object) {
				(*obj)->release();
				vec_obj.erase(obj);
				break;
			}
		}
	}
}
