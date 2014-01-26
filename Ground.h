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

	/** ���W�̍����擾
	 * @param pPos ���ׂ���W
	 * @return float ���ׂ��ۂ̍���(�͈͊O��-100(���փ��X�{�[���ʒu))
	 */
	float getHeight(const VECTOR3* pPos);

private:
	/**
	 * �@�����߂�
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
