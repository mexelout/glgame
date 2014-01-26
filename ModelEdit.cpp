#include "ModelEdit.h"
#include "Common.h"
#include "Central.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "Grid.h"
#include "Input.h"

void ModelEdit::init() {
	base::init();
	model = new Model("model");
	model->load("model/heisi.x");
	central->addObject(model);
	Camera* camera = (new Camera)->init();
	Camera::LockAtUp lock_at_up;
	lock_at_up.eye.set(4, 3, 4);
	lock_at_up.at.set(0, 1, 0);
	lock_at_up.up.set(0, 1, 0);
	camera->setLockAtUp(&lock_at_up);
	camera->setKind(CAMERAKIND_INTERPOLATION);
	central->addObject(camera);
	light = (new Light)->init();
	light->setType(Light::DIRECTIONAL);
	light->setColor(GL_AMBIENT, COLOR_FULL(0.2f, 0.2f, 0.4f, 1.0f));
	light->setTransform(&Transform(VECTOR3(0, 0, 0), VECTOR4(0.0f, 0, 0, 0), VECTOR3(1, 1, 1)));
	central->addObject(light);
	central->addObject((new Grid)->init());
}

void ModelEdit::update() {
	base::update();
	Camera* camera = (Camera*)(central->findObject("camera"));
	const Input::MOUSESTATE mouse_state = Input::getMouseState(Input::STATE_PRESS);
	const VECTOR2* drag_point = Input::getDragPoint();
	if(camera) {
		const int wheel = Input::getWheel();
		if(mouse_state._right) {
			camera->rotateXAtPivot(drag_point->x / 90.f);
			camera->rotateYAtPivot(drag_point->y / 90.f);
		}
		camera->changeRelativeLength((float)wheel);
	}
	if(mouse_state._left) {
		Transform t(*light->getTransform());
		t.rotate.y += drag_point->x / 90.f;
		t.rotate.x += drag_point->y / -90.f;
		light->setTransform(&t);
	}
}

void ModelEdit::draw() {
	base::draw();
}

void ModelEdit::uninit() {
	base::uninit();
}
