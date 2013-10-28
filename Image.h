#pragma once

#include <gl/freeglut/freeglut.h>
#include <vector>
#include "Object.h"
#include "Size.h"

class Image : public Object {
typedef Object base;
public:
	Image();
	~Image();
	Image* init();
	void update();
	void draw();
	void release();
	void setTexNum();
	// png file
	void load(const char* file_name);
private:
	GLuint tex_num;
	SIZE2D size;
	unsigned char* buffer;
};