#pragma once

#include "Object.h"
#include "Transform.h"
#include "Rigidbody.h"

class Model;

class Player : public Object {
public:
	Player();
	~Player();
	Player* init();
	void update();
	void draw();
	void release();
private:
	Model* model;
	Rigidbody* rigidbody;
	void updateRotationFromDirection(VECTOR3& dir);
};
