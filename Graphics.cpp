#include <gl/freeglut/freeglut.h>
#include "Common.h"
#include "Graphics.h"

Graphics::Graphics() {
}

Graphics::~Graphics() {
}

Graphics* Graphics::getInst() {
	static Graphics inst;
	return &inst;
}

void Graphics::drawLine(const VECTOR3& start, const VECTOR3& end, float width) {
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);

	glVertex3fv((float*)&(start.x));
	glVertex3fv((float*)&(end.x));

	glEnd();
}

void Graphics::drawRect(const VECTOR2& pos, const SIZE2D& size, const bool wire) {

	SIZE2D h = size/2;
	VECTOR2 lt(pos.x - h.width, pos.y + h.height);
	VECTOR2 rb(pos.x + h.width, pos.y - h.height);

	if(wire) {
		glBegin(GL_LINE_LOOP);
	} else {
		glBegin(GL_QUADS);
	}
	glVertex2f(lt.x, lt.y);
	glVertex2f(lt.x, rb.y);
	glVertex2f(rb.x, rb.y);
	glVertex2f(rb.x, lt.y);
	glEnd();

	glPolygonMode(GL_BACK, GL_FILL);
}

void Graphics::drawCube(const VECTOR3& pos, const SIZE3D& size, const bool wire) {
	SIZE3D b = size/2;
	VECTOR3 ltn(pos.x - b.width, pos.y + b.height, pos.z + b.depth);
	VECTOR3 rbf(pos.x + b.width, pos.y - b.height, pos.z - b.depth);

	if(wire) {
		glBegin(GL_LINE_LOOP);
	} else {
		glBegin(GL_QUADS);
	}
	glVertex2f(ltn.x, ltn.y);
	glVertex2f(ltn.x, rbf.y);
	glVertex2f(rbf.x, rbf.y);
	glVertex2f(rbf.x, ltn.y);
	glEnd();

	glPolygonMode(GL_BACK, GL_FILL);
}
