#include "Transform.h"

Transform::Transform() {
	rotate.y = 1;
	scale.set(1, 1, 1);
}

Transform::Transform(const Transform& t) {
	position = t.position;
	rotate = t.rotate;
	scale = t.scale;
}

Transform::Transform(const VECTOR3& p, const VECTOR4& r, const VECTOR3& s) {
	this->position.set(p);
	this->rotate.set(r);
	this->scale.set(s);
}

