#pragma once
#include "object.h"
class Object2D : public Object {
public:
	Object2D(std::string tag);
	virtual ~Object2D(void);
	virtual Object2D* init();
	virtual void update();
	virtual void draw();
	virtual void release();
private:

};

