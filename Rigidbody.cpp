#include "Common.h"
#include "Rigidbody.h"
#include "Ground.h"
#include "Central.h"

Rigidbody::Rigidbody() : base("rigidbody") {
	parent = null;
}
Rigidbody::Rigidbody(Object *parent) : base("rigidbody") {
	this->parent = parent;
	Rigidbody();
}
Rigidbody::~Rigidbody() {
}
Rigidbody* Rigidbody::init() {
	limit.position.set(10, 10, 10);
	return this;
}
void Rigidbody::update() {

	force.position.x *= 0.8f;
	force.position.z *= 0.8f;
	force.position.y -= 0.01568f;

	Transform trans(*(parent->getTransform()));
	trans.position += force.position;

	Ground* ground = (Ground*)(Central::getInst()->findObject("ground"));
	float ground_height = (ground->getHeight(&trans.position));
	if(ground_height > trans.position.y) {
		trans.position.y = ground_height;
		force.position.y = 0;
		is_grounded = true;
	} else {
		is_grounded = false;
	}
	trans.rotate += force.rotate;
	if(force.rotate.w) {
		force.rotate.w *= 0.9f;
	}
	parent->setTransform(&trans);
}

void Rigidbody::draw() {
}

void Rigidbody::release() {
	parent = null;
	base::release();
}

void Rigidbody::addForce(const VECTOR3& v) {
	force.position += v;
}
void Rigidbody::addTorque(const VECTOR4& v) {
	force.rotate += v;
}
void Rigidbody::setLimit(const VECTOR3& v) {
	limit.position = v;
}
bool Rigidbody::isGrounded() {
	return is_grounded;
}