#pragma once
#include "object3d.h"
#include "Size.h"

class Grid : public Object3D {
public:
	Grid();
	~Grid();
	Grid* init();
	void update();
	void draw();
	void release();
	void setGrid(const SIZE3D& size);
private:
	SIZE3D size;
};
