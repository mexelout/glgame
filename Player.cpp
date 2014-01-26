#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include "Central.h"
#include "Common.h"
#include "Model.h"
#include "Camera.h"
#include "Ground.h"
#include "Image.h"
#include "Player.h"
#include "Frame.h"
#include "Input.h"
#include "Camera.h"

static float rad_1 = (PI / 180.0f);

Player::Player() : Object("player") {
	dimension = 0;
	model = null;
	rigidbody = null;
}

Player::~Player(void) {
}

Player* Player::init() {
	model = (new Model("model"))->init();
	model->load("model/heisi.x");
	rigidbody = (new Rigidbody(this))->init();

	return this;
}

void Player::update() {
	Central* cent = Central::getInst();
	Camera* camera = (Camera*)(cent->findObject("camera"));

	if(Input::getKeyState(VK_SPACE, Input::STATE_TRIGGER) && rigidbody->isGrounded()) {
		rigidbody->addForce(VECTOR3::Up() * 0.3f);
	}
	Camera::LockAtUp lau(*(camera->getLockAtUp()));
	VECTOR3 dir(lau.at - lau.eye);
	dir.y = 0;
	dir *= 10;
	Vector3Normalize(&dir, &dir);

	if(Input::getKeyState('a', Input::STATE_PRESS)) {
		if(Input::getKeyState('w', Input::STATE_PRESS)) {
			float s = sinf(PI * 0.75f), c = cosf(PI * 0.75f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		} else if(Input::getKeyState('s', Input::STATE_PRESS)) {
			float s = sinf(PI * 0.25f), c = cosf(PI * 0.25f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		} else {
			float s = sinf(PI * 0.5f), c = cosf(PI * 0.5f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		}
	} else if(Input::getKeyState('d', Input::STATE_PRESS)) {
		if(Input::getKeyState('w', Input::STATE_PRESS)) {
			float s = sinf(PI * 1.25f), c = cosf(PI * 1.25f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		} else if(Input::getKeyState('s', Input::STATE_PRESS)) {
			float s = sinf(PI * 1.75f), c = cosf(PI * 1.75f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		} else {
			float s = sinf(PI * 1.5f), c = cosf(PI * 1.5f);
			dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
			rigidbody->addForce(dir*-0.05f);
			updateRotationFromDirection(dir * -1);
		}
	} else if(Input::getKeyState('w', Input::STATE_PRESS)) {
		float s = sinf(PI * 0.0f), c = cosf(PI * 0.0f);
		dir.set(dir.x * c - dir.z * s, 0, dir.x * s + dir.z * c);
		rigidbody->addForce(dir*0.05f);
		updateRotationFromDirection(dir);
	} else if(Input::getKeyState('s', Input::STATE_PRESS)) {
		rigidbody->addForce(dir*-0.05f);
		updateRotationFromDirection(dir * -1);
	}

	lau.at.set(transform.position + VECTOR3::Up() * 1.5f);
	lau.eye.set(transform.position + VECTOR3::Up() * 1.5f + (*camera->getDirection())*camera->getLength()*-1);
	camera->setKind(CAMERAKIND_APPLYNOW);
	camera->setLockAtUp(&lau);

	rigidbody->update();
}

void Player::draw() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(-transform.rotate.w + 90, transform.rotate.x, transform.rotate.y, transform.rotate.z);
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
	SAFE_METHOD(model, draw);
	rigidbody->draw();
	glPopMatrix();
}

void Player::release() {
	SAFE_RELEASE(model);
	SAFE_RELEASE(rigidbody);
	Object::release();
}

void Player::updateRotationFromDirection(VECTOR3& dir) {
	VECTOR3 now_rot_vec(cosf(transform.rotate.w * rad_1), 0, sinf(transform.rotate.w * rad_1));
	float cross = Vector3CrossXZ(&now_rot_vec, &dir);
	float dot = Vector3DotXZ(&now_rot_vec, &dir);
	float angle = 0;
	if (1 >= dot && dot >= -1) angle = acosf(dot);
	if(cross < 0) angle *= -1;
	angle = angle / (PI / 180.0f);
	transform.rotate.w += (angle * 0.1f);
//	rigidbody->addTorque(VECTOR4(0, 0, 0, angle * 0.1f));
}
