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
	* ファイル名取得
	* @return std::string 読み込みしたファイル名
	*/
	std::string getName();
	/**
	* 画像を座標指定で貼る
	* @param pPos 座標
	*/
	void drawAtPoint(const VECTOR3* pPos);
	/**
	* 画像を座標・大きさ指定で貼る
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl);
	/**
	* 画像を座標・回転量指定で貼る
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pRotVec, const float angle);
	/**
	* 画像を座標・大きさ・回転量指定で貼る
	*/
	void drawAtPoint(const VECTOR3* pPos, const VECTOR3* pScl, const VECTOR3* pRotVec, const float angle);
	/**
	* 画像の適用
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
	* ブレンド色
	* @param color 設定色
	*/
	static void blendColor(COLOR_FULL& color);
private:
	GLuint tex_num;
	std::string file_name;
	SIZE2D size;
	unsigned char* buffer;
	static COLOR_FULL color;
};