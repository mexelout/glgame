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
	template <class u>
	u* findObject(std::string tag);
	void subObject(Object* object);
};

