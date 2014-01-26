#pragma once

#include "Scene.h"

class Model;
class Light;

class ModelEdit : public Scene {
	typedef Scene base;

protected:
	/**
	 * ������
	 */
	void init();

	/**
	 * �X�V�p
	 */
	void update();

	/**
	 * �`��p
	 */
	void draw();

	/**
	 * �㏈���p
	 */
	void uninit();

private:
	Model* model;
	Light* light;
};
