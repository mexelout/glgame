#pragma once

#include <string>

class Object {
public:
	Object(const std::string tag){dimension=0; this->tag = tag;}
	virtual ~Object(){}
	virtual Object* init()=0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual void release(){delete this;}
	bool tagEqual(const std::string tag){return (this->tag == tag);}
	unsigned int getDimension() {return dimension;}
protected:
	unsigned int dimension;
private:
	std::string tag;
};
