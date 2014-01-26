#pragma once

#include <vector>
#include <string>
#include "Common.h"
#include "Object.h"

class Scene;

class Central : public Object {
private:
	Central(void);
	~Central(void);
	Central* operator = (Central*){}
	std::vector<Object*> objects[2];
	static Central* inst;
	Scene* scene;
public:
	static Central* getInst();
	Central* init();
	void update();
	void draw();
	void release();
	void allSubObject();
	void addObject(Object* object);
	Object* findObject(std::string tag);
	void subObject(Object* object);
};

