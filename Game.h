#pragma once

#include "Scene.h"

class Game : public Scene {
private:
	typedef Scene base;
public:

	/**
	 * �`��p
	 */
	void draw();

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
	 * �㏈���p
	 */
	void uninit();

};
