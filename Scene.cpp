#include <gl/freeglut/freeglut.h>
#include <gl/glu.h>
#include "Scene.h"
#include "Input.h"
#include "Camera.h"
#include "Central.h"
#include "Grid.h"
#include "Font.h"
#include "Frame.h"
#include "Responder.h"

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
	Camera* camera = (new Camera)->init();
	camera->setKind(CAMERAKIND_INTERPOLATION);

	central->addObject(camera);
	central->addObject((new Grid())->init());

	central->addObject((new Frame())->init());
	central->addObject((new Responder())->init());

	phase = 1;
}

void Scene::update() {
	Camera* camera = central->findObject<Camera>("camera");
	if(camera) {
		const Input::MOUSESTATE mouse_state = Input::getMouseState(Input::STATE_PRESS);
		const VECTOR2* drag_point = Input::getDragPoint();
		const int wheel = Input::getWheel();
		if(mouse_state._left) {
			camera->rotateXEyePivot(drag_point->x / 90.f);
			camera->rotateYEyePivot(drag_point->y / -90.f);
		} else if(mouse_state._right) {
			camera->rotateXAtPivot(drag_point->x / 90.f);
			camera->rotateYAtPivot(drag_point->y / -90.f);
		}
		camera->changeRelativeLength((float)wheel);
	}

	if(fade) fade->update();
	const Input::MOUSESTATE ms = Input::getMouseState(Input::STATE_RELEASE);
	if(ms._left) {
//		if(fade) fade->fadeOut();
	}
	if(fade->getState() == Fade::FADESTATE_OUT_END) {
		phase = 2;
	}

	if(Input::getKeyState(GLUT_KEY_ALT_L, Input::STATE_PRESS) && Input::getKeyState(GLUT_KEY_F4, Input::STATE_PRESS)) {
		glutExit();
	}
}

void Scene::draw() {
	if(fade) fade->draw();
}

void Scene::uninit() {
	phase = 0;
}
