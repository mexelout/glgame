#include "Object.h"

// object.cpp‚ª–³‚¢ˆ×‚±‚±‚Å’è‹`
bool Object::end = false;

Object::Object(const std::string tag){
	dimension=0; this->tag = tag;
}

void Object::release(){
	delete this;
}

bool Object::tagEqual(const std::string tag){
	return (this->tag == tag);
}
unsigned int Object::getDimension() {
	return dimension;
}
void Object::close(){
	end = true;
}
const Transform* Object::getTransform() {
	return &transform;
}
void Object::setTransform(const Transform* transform) {
	this->transform.position = transform->position;
	this->transform.rotate = transform->rotate;
	this->transform.scale = transform->scale;
}