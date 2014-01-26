
#include "Light.h"
#include "Common.h"
#include <Math.h>

bool Light::enables[8] = {0};

Light::Light() : base("light") {
	glEnable(GL_LIGHTING);
}

Light* Light::init() {
	int idx = getVacancy();
	if(idx != -1) {
		light_num = GL_LIGHT0 + idx;
		glEnable(light_num);
	}
	return this;
}

void Light::update() {
	base::update();
	GLfloat light_position[4];
	if(type == DIRECTIONAL) {
		float len = cosf(transform.rotate.x);
		VECTOR3 v(cosf(transform.rotate.y) * len, sinf(transform.rotate.x), sinf(transform.rotate.y) * len);
		light_position[0] = v.x;
		light_position[1] = v.y;
		light_position[2] = v.z;
		light_position[3] = 0.0f;
	} else {
		light_position[0] = transform.position.x;
		light_position[1] = transform.position.y;
		light_position[2] = transform.position.z;
		light_position[3] = 1.0f;
	}
	glLightfv(light_num, GL_POSITION, light_position);
	
}

void Light::draw() {
	base::draw();
#ifdef _DEBUG
	glPushMatrix();
	glDisable(GL_LIGHTING);
	if(type == DIRECTIONAL) {
		float rad_1 = PI / 180.0f;
		glTranslatef(transform.position.x, transform.position.y, transform.position.z);
		glRotatef(transform.rotate.x / rad_1, 1, 0, 0);
		glRotatef(transform.rotate.y / rad_1, 0, 1, 0);
		glBegin(GL_LINE_LOOP);
		dm(glColor3f, VECTOR3(1, 1, 0));
		for(int i = 0; i < 8; i++) dm(glVertex3f, VECTOR3(0, sinf(i * rad_1 * 360.0f / 8.0f), cosf(i * rad_1 * 360.0f / 8.0f))*0.5f);
		glEnd();
		glBegin(GL_LINES);
		for(int i = 0; i < 8; i++) {
			dm(glVertex3f, VECTOR3(0, sinf(i * rad_1 * 360.0f / 8.0f), cosf(i * rad_1 * 360.0f / 8.0f))*0.5f);
			dm(glVertex3f, VECTOR3(3, sinf(i * rad_1 * 360.0f / 8.0f), cosf(i * rad_1 * 360.0f / 8.0f))*0.5f);
		}
		glEnd();
	} else {
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
#endif
}

void Light::release() {
	glDisable(light_num);
	enables[light_num] = false;
	base::release();
}

void Light::setType(TYPE t) {
	type = t;
}

void Light::setColor(GLenum pname, COLOR_FULL& col) {
	GLfloat params[4] = {col.r, col.g, col.b, col.a};
	glLightfv(light_num, pname, params);
}

/**
 * ‹ó‚«‚Ì”Ô†‚ð’²‚×‚é
 * @return int ‹ó‚«‚ÌŒõ‚Ì”Ô†B–³‚¯‚ê‚Î-1
 */
int Light::getVacancy() {
	int idx = -1;
	for(int i = 0, len = sizeof(enables) / sizeof(bool); i < len; i++) {
		if(!enables[i]) {
			idx = i;
			break;
		}
	}
	return idx;
}