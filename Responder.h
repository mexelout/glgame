#pragma once

#include "Object2d.h"
#include "Vector.h"
#include "Size.h"
#include "Command.h"

class Responder : public Object2D {
	typedef Object2D base;
public:
	Responder(std::string tag = "responder");
	~Responder();
	virtual Responder* init();
	virtual void update();
	virtual void draw();
	virtual void release();
	Command* mouseDown;
	Command* mouseUp;
	Command* mouseIn;
	Command* mouseOut;
protected:
	VECTOR2 pos;
	SIZE2D size;
	bool selected;
private:
	bool is_in;
};
