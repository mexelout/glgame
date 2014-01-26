#pragma once

#include <gl/freeglut/freeglut.h>
#include <vector>
#include <string>
#include "Object.h"
#include "Size.h"
#include "Color.h"
#include "Vector.h"

class Image : public Object {
typedef Object base;
public:
	Image();
	~Image();
	Image* init();
	static Image* initWithName(std::string file_name);
	void update();
	void draw();
	void release();
	// png file
	void load(std::string file_name);
	/**
	* �t�@�C�����擾
	* @return std::string �ǂݍ��݂����t�@�C����
	*/
	std::string getName();
	/**
	* �摜�����W�w��œ\��
	* @param pPos ���W
	*/
	void drawAtPoint(const VECTOR3* pPos);
	/**
	* �摜�����W�E�傫���w��œ\��
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl);
	/**
	* �摜�����W�E��]�ʎw��œ\��
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pRotVec, const float angle);
	/**
	* �摜�����W�E�傫���E��]�ʎw��œ\��
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl, const VECTOR3* pRotVec, const float angle);
	/**
	* �摜�̓K�p
	*/
	void apply();
	/**
	* GL_CLAMP or GL_REPEAT
	*/
	void setWrap(GLint wrap);
	/**
	* GL_NEAREST or GL_LINEAR
	*/
	void setFilter(GLint filter);
	/**
	* �u�����h�F
	* @param color �ݒ�F
	*/
	static void blendColor(COLOR_FULL& color);
private:
	GLuint tex_num;
	std::string file_name;
	SIZE2D size;
	unsigned char* buffer;
	static COLOR_FULL color;
};