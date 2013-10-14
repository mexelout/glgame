#pragma once

#include "Object.h"
#include "Vector.h"

enum CAMERAKIND {
	CAMERAKIND_APPLYNOW = 0, // 設定後すぐ適用
	CAMERAKIND_INTERPOLATION, // 補間
	CAMERAKIND_DEFAULT = CAMERAKIND_APPLYNOW,
};

#undef far
#undef near

class Camera : public Object {
public:
	typedef struct LockAtUp {
		VECTOR3 eye, at, up;
		LockAtUp();
		LockAtUp(const LockAtUp* origin);
	}LOCKATUP;
	typedef struct Perspective {
		float fovy, aspect, near, far;
		Perspective();
	}PERSPECTIVE;

	Camera(void);
	~Camera(void);

	/** 初期化
	*/
	Camera* init();

	/** 更新
	*/
	void update();

	/**
	* 描画・・・するのか？
	*/
	void draw(){}

	/**
	* LockAtUp要素の設定
	*/

	void setLockAtUp(const LockAtUp* lock_at_up);

	/**
	* LockAtUp要素の取得
	*/
	const LockAtUp* getLockAtUp(void);

	/** 長さ設定
	*/
	void setLength(float length);

	/** 長さ取得
	*/
	float getLength();

	/**
	 * 長さを相対値で変更
	 */
	void changeRelativeLength(float length);

	/** 挙動設定
	*/
	void setKind(CAMERAKIND kind);

	/** 挙動取得
	*/
	CAMERAKIND getKind();

	/** 向き取得
	*/
	const VECTOR3* getDirection();

	/** 視点を中心に横回転
	*/
	void rotateXEyePivot(float angle);

	/** 視点を中心に縦回転
	*/
	void rotateYEyePivot(float angle);

	/** 注視点を中心に横回転
	*/
	void rotateXAtPivot(float angle);

	/** 注視点を中心に縦回転
	*/
	void rotateYAtPivot(float angle);

	/** カメラの回転量取得
	* @return 回転量ポインタ
	*/
	const VECTOR2* getRotate();

private:
	/**
	* 長さの再計算
	*/
	void calcLength();
	/**
	* 向きの再計算
	*/
	void calcDirection();

	LockAtUp now_lock_at_up;
	LockAtUp target_lock_at_up;
	VECTOR3 m_Direction;
	VECTOR2 m_Rotate;
	float m_Length;
	CAMERAKIND m_Kind;
};
