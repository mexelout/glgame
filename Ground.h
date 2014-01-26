#pragma once

#include "Object.h"
#include "Vector.h"

class Image;

class Ground : public Object {
public:
	Ground(void);
	~Ground(void);

	Ground* init();
	void update();
	void draw();
	void release();

	/** 座標の高さ取得
	 * @param pPos 調べる座標
	 * @return float 調べた際の高さ(範囲外は-100(上空へリスボーン位置))
	 */
	float getHeight(const VECTOR3* pPos);

private:
	/**
	 * 法線求める
	 */
	void initNormalVector(int width, int height);

	Image* texture;

	VECTOR3* vtx;
	int* idx;
	VECTOR2* tex;
	VECTOR3* nor;
	VECTOR3* faceNor;

	int vtxNum;
	int idxNum;
	int texNum;
	int norNum;
	int faceNum;
	int prmNum;
};
