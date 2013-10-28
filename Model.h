#pragma once

#include <vector>
#include "Vector.h"
#include "Object3D.h"
#include "Image.h"

class Model : public Object3D {
typedef Object3D base;
public:
	Model(std::string tag);
	virtual ~Model();
	virtual Model* init();
	virtual void update();
	virtual void draw();
	virtual void release();
	/** 
	 * xÉtÉ@ÉCÉãì«Ç›çûÇ›
	 */
	bool load(const char* file_name);
private:
	VECTOR3 pos;
	std::vector<VECTOR3> vertexies;
	std::vector<VECTOR3> normals;
	std::vector<VECTOR2> texcoords;
	std::vector<Image*> images;
	std::vector<int> vertex_index;
	std::vector<int> face_index;
	std::vector<int> normal_index;
	std::vector<int> material_index;
};