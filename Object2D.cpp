#include "Object2D.h"

Object2D::Object2D(std::string tag) : Object(tag){
	dimension = 1;
}

Object2D::~Object2D(void) {
}

Object2D* Object2D::init() {
	return this;
}

void Object2D::update() {
}

void Object2D::draw() {
}

void Object2D::release() {
	Object::release();
}
