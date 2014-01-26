#pragma once

#include "Fade.h"

class Central;

/// シーン切り替え用
class Scene {
public:
	Scene(void);
	virtual ~Scene(void);

	/**
	 * 更新中はこれだけ呼び出す
	 */
	void method();

	/**
	 * 描画用
	 */
	virtual void draw();

protected:
	/**
	 * 初期化
	 */
	virtual void init();

	/**
	 * 更新用
	 */
	virtual void update();

	/**
	 * 後処理用
	 */
	virtual void uninit();

	/**
	 * フェード開始
	 * @param next_scene 次のシーン
	 */
	void fadeIn(Scene* next_scene);

	/// centralクラスを保存しておく(いちいちゲットするコストは無駄と判断)
	Central* central;

private:
	/// state情報
	unsigned int phase;

	/// fade
	Fade* fade;

};
