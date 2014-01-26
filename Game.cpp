
#include "Game.h"
#include "Input.h"
#include "Camera.h"
#include "Grid.h"
#include "ExitButton.h"
#include "Ground.h"
#include "Player.h"
#include "Central.h"
#include "Frame.h"

/**
 * 初期化
 */
void Game::init() {
	base::init();
	Camera* camera = (new Camera)->init();
	Camera::LockAtUp lock_at_up;
	lock_at_up.eye.set(4, 3, 4);
	lock_at_up.at.set(0, 1, 0);
	lock_at_up.up.set(0, 1, 0);
	camera->setLockAtUp(&lock_at_up);
	camera->setKind(CAMERAKIND_INTERPOLATION);

	central->addObject(camera);

	central->addObject((new Frame())->init());
	central->addObject((new Player())->init());
	central->addObject((new Ground())->init());
}

/**
 * 更新用
 */
void Game::update() {
	base::update();

	Camera* camera = (Camera*)(central->findObject("camera"));
	if(camera) {
		const Input::MOUSESTATE mouse_state = Input::getMouseState(Input::STATE_PRESS);
		const VECTOR2* drag_point = Input::getDragPoint();
		const int wheel = Input::getWheel();
		if(mouse_state._right) {
			camera->rotateXAtPivot(drag_point->x / 90.f);
			camera->rotateYAtPivot(drag_point->y / 90.f);
		}
		camera->changeRelativeLength((float)wheel);
	}
}

/**
 * 描画用
 */
void Game::draw() {
	base::draw();
}

/**
 * 後処理用
 */
void Game::uninit() {
	base::uninit();
}
