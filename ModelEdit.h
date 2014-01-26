#pragma once

#include "Scene.h"

class Model;
class Light;

class ModelEdit : public Scene {
	typedef Scene base;

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
	 * 描画用
	 */
	void draw();

	/**
	 * 後処理用
	 */
	void uninit();

private:
	Model* model;
	Light* light;
};
