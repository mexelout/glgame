#pragma once
#include "object.h"
class Object3D : public Object {
public:
	Object3D(std::string tag);
	virtual ~Object3D(void);
	virtual Object3D* init();
	virtual void update();
	virtual void draw();
	virtual void release();
private:
};

