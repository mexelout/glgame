#include <gl/freeglut/freeglut.h>
#include <gl/glu.h>
#include "Scene.h"
#include "Input.h"
#include "Font.h"
#include "Central.h"

Scene::Scene(void) {
	fade = 0;
	phase = 0;
	fade = new Fade();
	fade->init();
}

Scene::~Scene(void) {
	SAFE_RELEASE(fade);
	uninit();
}

void Scene::method() {
	switch(phase) {
		case 0:
			init();
			break;
		case 1:
			update();
			break;
		case 2:
			uninit();
			break;
	}
}

void Scene::init() {
	central = Central::getInst();
	fade->fadeIn();
	phase = 1;
}

void Scene::update() {

	if(fade) fade->update();

	if(fade->getState() == Fade::FADESTATE_OUT_END) {
		phase = 2;
	}

	if(Input::getKeyState(GLUT_KEY_ALT_L, Input::STATE_PRESS) && Input::getKeyState(GLUT_KEY_F4, Input::STATE_PRESS)) {
		Object::close();
	}
}

void Scene::draw() {
	if(fade) fade->draw();
}

void Scene::uninit() {
	phase = 0;
}
