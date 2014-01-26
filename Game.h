#pragma once

#include "Scene.h"

class Game : public Scene {
private:
	typedef Scene base;
public:

	/**
	 * 描画用
	 */
	void draw();

protected:
	/**
	 * 初期化
	 */
	void init();

	/**
	 * 更新用
	 */
	void update();

	/**
	 * 後処理用
	 */
	void uninit();

};
