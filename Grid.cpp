#include <gl/freeglut/freeglut.h>
#include "Vector.h"
#include "Grid.h"
#include "Graphics.h"

Grid::Grid() : Object3D("grid") {
	size.set(10, 10, 10);
}

Grid::~Grid(void) {
}

Grid* Grid::init() {
	return this;
}

void Grid::update() {
}

void Grid::draw() {
	glPushMatrix();

	glDisable(GL_LIGHTING);

	// x
	glColor3f(1, 1, 1);
	for(float z = -size.depth; z <= size.depth; z++) {
		if(z != 0) {
			Graphics::getInst()->drawLine(VECTOR3(size.width, 0, z), VECTOR3(-size.width, 0, z));
		} else {
			// x origin
			glColor3f(1, 0, 0);
			Graphics::getInst()->drawLine(VECTOR3(size.width, 0, z), VECTOR3(-size.width, 0, z));
			glColor3f(1, 1, 1);
		}
	}
	for(float w = -size.width; w <= size.width; w++) {
		if(w != 0) {
			Graphics::getInst()->drawLine(VECTOR3(w, 0, size.depth), VECTOR3(w, 0, -size.depth));
		} else {
			// z origin
			glColor3f(0, 0, 1);
			Graphics::getInst()->drawLine(VECTOR3(w, 0, size.depth), VECTOR3(w, 0, -size.depth));
			glColor3f(1, 1, 1);
		}
	}
	// y origin
	glColor3f(0, 1, 0);
	Graphics::getInst()->drawLine(VECTOR3(0, size.height, 0), VECTOR3(0, -size.height, 0));

	glColor3f(1, 1, 1);

	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Grid::release() {
	Object3D::release();
}

void Grid::setGrid(const SIZE3D &size) {
	this->size = size;
}