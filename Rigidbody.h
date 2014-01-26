#pragma once

#include "Object.h"
#include "Transform.h"

class Rigidbody : public Object {
	typedef Object base;
public:
	Rigidbody(Object* parent);
	~Rigidbody();
	Rigidbody* init();
	void update();
	void draw();
	void release();
	void addForce(const VECTOR3& v);
	void addTorque(const VECTOR4& v);
	void setLimit(const VECTOR3& v);
	bool isGrounded();
private:
	Rigidbody();
	Object* parent;
	Transform force;
	Transform limit;
	bool is_grounded;
};