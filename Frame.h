#pragma once

#include <vector>
#include "Object2D.h"
#include "Vector.h"
#include "Size.h"

class Frame : public Object2D {
public:
	Frame();
	~Frame();
	Frame* init();
	void update();
	void draw();
	void release();
private:
	VECTOR2 position;
	SIZE2D size;
	std::vector<Object2D*> childs;
};
