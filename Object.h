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
	static void close(){end = true;}
protected:
	unsigned int dimension;
	static bool end; // I—¹—p true‚É‚·‚é‚ÆI—¹‚·‚é
private:
	std::string tag;
};

