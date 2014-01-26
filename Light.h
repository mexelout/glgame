#include <windows.h>
#include <gl/freeglut/freeglut.h>
#include <vector>
#include "Object3D.h"
#include "Color.h"

class Light : public Object3D {
	typedef Object3D base;
public:
	typedef enum {
		DIRECTIONAL = 0,
		POINT,
		SPOT
	}TYPE;
	Light();
	Light* init();
	void setType(TYPE t);
	void setColor(GLenum pname, COLOR_FULL& col);
	void update();
	void draw();
	void release();
private:
	unsigned int light_num;
	TYPE type;
	COLOR_FULL color;
	static bool enables[8];
	/**
	 * �󂫂̔ԍ��𒲂ׂ�
	 * @return int �󂫂̌��̔ԍ��B�������-1
	 */
	static int getVacancy();
};
