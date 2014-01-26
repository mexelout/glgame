#pragma once

#include <string>
#include "Transform.h"

class Object {
public:
	Object(const std::string tag);
	virtual ~Object(){}
	virtual Object* init()=0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual void release();
	bool tagEqual(const std::string tag);
	unsigned int getDimension();
	static void close();
	const Transform* getTransform();
	void setTransform(const Transform* transform);
protected:
	unsigned int dimension;
	static bool end; // èIóπóp trueÇ…Ç∑ÇÈÇ∆èIóπÇ∑ÇÈ
	Transform transform;
private:
	std::string tag;
};

