#pragma once

#include "Font.h"
#include "Vector.h"
#include "Size.h"

class Graphics {
private:
	Graphics();
	~Graphics();
public:
	static Graphics* getInst();
	void drawLine(const VECTOR3& start, const VECTOR3& end, float width = 1);
	void drawRect(const VECTOR2& pos, const SIZE2D& size, const bool wire = false);
	void drawCube(const VECTOR3& pos, const SIZE3D& size, const bool wire = false);
};
