#pragma once

#include "Object2d.h"
#include "Vector.h"
#include "Size.h"

class Responder : public Object2D {
	typedef Object2D base;
public:
	Responder(std::string tag = "responder");
	~Responder();
	Responder* init();
	void update();
	void draw();
	void release();
	virtual void mouseDown();
	virtual void mouseUp();
	virtual void mouseIn();
	virtual void mouseOut();
private:
	VECTOR2 pos;
	SIZE2D size;
	bool isIn;
};
