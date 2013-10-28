#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <gl/freeglut/freeglut.h>
#include <math.h>
#include <crtdbg.h>
#include <alut.h>
#include "Common.h"
#include "Config.h"
#include "Input.h"
#include "Central.h"

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Central::getInst()->draw();

	glutSwapBuffers();

	// 入力の更新は最後にする
	Input::update();
}

void timer(int value) {
	Central::getInst()->update();

	glutPostRedisplay();
	glutTimerFunc(16 , timer , value);
}

void init() {
	glClearColor(0.3f, 0.6f, 0.9f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_ALPHA_TEST);//アルファテスト開始
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
	Input::init();
}

void close() {
	Input::release();
	Central::getInst()->release();
}

void resize(int width, int height) {
	const POINT* s = Config::GetWindowSize();
	if(width != s->x || height != s->y)
		glutReshapeWindow(s->x, s->y);
	//glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]) {
	// メモリーリーク検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(1960);
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	const POINT* s = Config::GetWindowSize();
	glutInitWindowSize(s->x, s->y);
	glutCreateWindow("3d game");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCloseFunc(close);
	glutTimerFunc(100 , timer , 0);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	init();
	glutMainLoop();
	return 0;
}