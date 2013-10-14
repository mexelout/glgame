#pragma once

#include <gl/freeglut/freeglut.h>

class Fade {
public:
	enum FADESTATE{
		FADESTATE_IN = 0,
		FADESTATE_IN_END,
		FADESTATE_NONE,
		FADESTATE_OUT,
		FADESTATE_OUT_END,
	};
	Fade(void);
	~Fade(void);
	void init(void);
	void update(void);
	void draw(void);
	void release(void);
	void fadeIn(void);
	void fadeOut(void);
	FADESTATE getState(void);
private:
	GLuint tex_num;
	float alpha;
	float rev_alpha;
	FADESTATE state;
};

