#include <gl/freeglut/freeglut.h>
#include <math.h>
#include "Vector.h"
#include "Object3D.h"

Object3D::Object3D(std::string tag) : Object(tag){
	dimension = 0;
}

Object3D::~Object3D(void) {
}

Object3D* Object3D::init() {
	return this;
}

void Object3D::update() {
}

void Object3D::draw() {
}

void Object3D::release() {
	Object::release();
}
